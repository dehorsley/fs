import {Socket, Protocol} from 'nanomsg-browser';

const type = {
    DATA: Symbol("DATA"),
    HEARTBEAT: Symbol("HEARTBEAT"),
    END_OF_SESSION: Symbol("END_OF_SESSION"),
}

function type_unmarshal(t) {
    switch (t) {
        case 0:
            return type.DATA;
        case 1:
            return type.HEARTBEAT;
        case 2: 
            return type.HEARTBEAT;
    }
}

let utf8decoder = new TextDecoder();

function msg_unmarshal(buffer) {
    let view = new DataView(buffer);
    let msg = {};

    let bytes = 0;
    msg.type = type_unmarshal(view.getUint8(bytes));
    bytes += 1;
    msg.seq = view.getBigUint64(bytes, true);
    bytes += 8;

    if (msg.type != type.DATA) {
        return [msg, bytes];
    }

    let len = view.getUint16(bytes, true);
    bytes += 2;
    if (len == 0) return [msg, bytes];
    // TODO: probably don't want to decode here
    msg.data = utf8decoder.decode(buffer.slice(bytes, bytes+len));
    bytes += len
    return [msg, bytes];
}

function msgs_unmarshal(buffer) {
    let msgs = [];
    while (buffer.byteLength > 0) {
        let [msg, bytes] = msg_unmarshal(buffer);
        msgs.push(msg);
        buffer = buffer.slice(bytes);
    }
    return msgs;
}

export function Stream(addr) {
    this.perform_first_sync = true;
    let cbs = {
      data: [],
      end: [],
      restart: [],
      heartbeat: [],
      error: [],
    };

    this.on = function(type, cb) {
        if (cbs[type]) {
            cbs[type].push(cb);
        }
    }


    let seq = BigInt(0); // sequence id of the next msg we're expecting to receive
    let synced = false; // state of client

    let syncing = false
    let queue = []

    const subaddr = addr + "/pub";
    const repaddr = addr + "/rep";
    const sub = new Socket({
        protocol: Protocol.SUB,
        sendArrayBuffer: true,
        receiveArrayBuffer: true,
    });

    sub.connect(subaddr);
    sub.on('data', async (rawmsg) => {
        let [m, nbytes] = msg_unmarshal(rawmsg);

        if (syncing) {
            queue.push(m);
            return;
        }

        if (!this.perform_first_sync) {
            this.perform_first_sync = true;
            synced                  = true;
            seq                     = m.seq;
        }

        if (m.type == type.END_OF_SESSION) {
            for (let f of cbs.end) {
                f(m.data);
            }
        }


        if (m.seq < seq) {
            if (!synced) {
                // Ignore msgs we've already seen. This may happen during re-sync as
                // msgs received by OOB sync may also arrive at sub socket
                return;
            }
            // If we're not rsyncing and we see a message with lower seq than we expect,
            // the server may have restarted, and we need to resync right from the
            // start.
            seq = BigInt(0);
            for (let f of cbs.restart) {
                f(m.data);
            }
        }

        if (m.seq > seq) {
            // We've missed a message, perform out-of-band sync
            syncing = true;
            synced  = false;
            let s = await sync_msgs(seq, repaddr, -1);
            // We may have gotten fewer or more messages than we were expecting.
            // If we got more next, we ensure
            // TODO: we should check if we got less here and do another resync

            seq = s + BigInt(1);
            for (let m of queue) {
                if (m.seq != seq || m.type != type.DATA) {
                    continue
                }
                for (let f of cbs.data) {
                    f(m.data);
                }
                seq = m.seq + BigInt(1);
            }
            queue = [];
            syncing = false;

            return;
        }

        if (!synced && m.seq == seq) {
            synced = true;
        }

        if (m.type == type.HEARTBEAT) {
            for (let f of cbs.heartbeat) {
                f(m.data);
            }
            return;
        }

        for (let f of cbs.data) {
            f(m.data);
        }
        seq = m.seq + BigInt(1);
    });

    async function sync_msgs(seq, addr, timeout) {
        const req = new Socket({
            protocol: Protocol.REQ,
            sendArrayBuffer: true,
            receiveArrayBuffer: true,
        });
        try {
            await req.connect(addr);
        } catch {
            console.log("conn");
            return 0;
        }

        const buf = new ArrayBuffer(8);
        const view = new DataView(buf);

        view.setBigUint64(0, seq);
        const data = await req.send(buf);
        const msgs = msgs_unmarshal(data);
        for (const m of msgs) {
            for (let f of cbs.data) {
                f(m.data);
            }
        }
        return msgs[msgs.length - 1].seq;
    }
}

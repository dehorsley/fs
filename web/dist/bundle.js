/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/index.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./node_modules/nanomsg-browser/src/nanomsg.js":
/*!*****************************************************!*\
  !*** ./node_modules/nanomsg-browser/src/nanomsg.js ***!
  \*****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

const nanomsg = {
  debug: false,
  reconnectTime: 1000,
  receiveArrayBuffer: false,
  REQ: 'rep.sp.nanomsg.org',
  PAIR: 'pair.sp.nanomsg.org',
  SUB: 'pub.sp.nanomsg.org',
}

nanomsg.Socket = class {
  constructor(protocol) {
    this.protocol = protocol;
    this.wss = new Map();
    this.reqIdHeader = null;
    this.promise = null;
    this.cbs = {
      data: [],
      end: [],
      error: [],
    };

    if (this.protocol == nanomsg.REQ) {
      this.reqIdHeader = new Uint8Array(4);
      window.crypto.getRandomValues(this.reqIdHeader);
      // the first bit HAS TO BE one, in order to get a response
      this.reqIdHeader[0] |= 1 << 7;
    }
  }

  connect(url) {
    if (!this.wss.has(url)) {
      return new Promise((resolve, reject) => {
        if (nanomsg.debug) {
          console.log('nanomsg connect to: ' + url);
        }

        const tryConnect = () => {
          try {
            this.__setupSocketConnection(url, resolve);
          } catch (e) {
            console.log(e);
            this.wss.delete(url);

            setTimeout(tryConnect, nanomsg.reconnectTime);
          }
        };

        tryConnect();
      });
    }
  }

  __setupSocketConnection(url, resolve) {
    const ws = new WebSocket(url, [this.protocol]);
    ws.initialUrl = url; // evil hack of evilness, to access the original used url

    if (nanomsg.receiveArrayBuffer) {
      ws.binaryType = 'arraybuffer';
    }

    this.wss.set(url, ws);

    ws.onopen = () => {
      if (nanomsg.debug) {
        console.log('nanomsg connected: ' + url);
      }

      resolve();
    };

    ws.onmessage = (e) => {
      let data = null;

      if (this.protocol == nanomsg.REQ) {
        data = e.data.slice(4);
      } else {
        data = e.data;
      }

      if (nanomsg.receiveArrayBuffer) {
        this.__resolveNewData(data);
      } else {
        const reader = new FileReader();

        reader.onload = (event) => {
          this.__resolveNewData(event.target.result);
        };

        reader.readAsText(data);
      }
    };

    ws.onerror = (e) => {
      if (nanomsg.debug) {
        console.log('nanomsg error', e);
      }

      this.cbs.error.forEach(cb => cb(e));
    };

    ws.onclose = () => {
      if (nanomsg.debug) {
        console.log('nanomsg close: ' + ws.initialUrl);
      }

      if (this.wss.has(ws.initialUrl)) {
        if (nanomsg.debug) {
          console.log('nanomsg reconnect: ' + ws.initialUrl);
        }

        this.wss.delete(ws.initialUrl);
        this.connect(ws.initialUrl);
      }

      this.cbs.end.forEach(cb => cb(ws.initialUrl));
    };
  }

  __resolveNewData(data) {
    if (data) {
      if (this.promise) {
        this.promise.resolve(data);
        this.promise = null;
      }

      this.cbs.data.forEach(cb => cb(data));
    }
  }

  disconnect(url) {
    const ws = this.wss.get(url);

    if (ws) {
      this.wss.delete(url);
      ws.close();
    }
  }

  bind() {
    throw new Error('WHOAAAA!!! Nice try, but NO, we do not support these!');
  }

  on(type, cb) {
    const cbs = this.cbs[type];

    if (cbs) {
      cbs.push(cb);
    }
  }

  send(msg) {
    if (this.protocol === nanomsg.SUB) {
      throw new Exception('SUB socket can not send');
    }

    if (this.wss.size < 1) {
      throw new Exception('you are not connected to any socket');
    }

    // this is a good one: https://www.freelists.org/post/nanomsg/WebSocket-test-case-not-working,3
    if (this.protocol === nanomsg.REQ) {
      const length = msg.length || msg.byteLength;
      const data = new Uint8Array(length + 4);
      data.set(this.reqIdHeader, 0);

      if (typeof msg === 'string' || msg instanceof String) {
        for (let i = 4; i < msg.length + 4; ++i) {
          data[i] = msg.charCodeAt(i - 4);
        }

      } else {
        data.set(msg, 4);
      }

      msg = data;
    }

    if (nanomsg.debug) {
      console.log('nanomsg send =>', msg);
    }

    for (let ws of this.wss.values()) {
      if (ws.readyState === 1) {
        ws.send(msg);
      } else if (ws.readyState > 1) {
        if (this.wss.has(ws.url)) {
          this.wss.delete(ws.url);
        }

        if (nanomsg.debug) {
          console.log('nanomsg: could not send, because of closed connection (' + ws.url + ')');
        }
      }
    }

    if (this.protocol === nanomsg.REQ || this.protocol === nanomsg.PAIR) {
      return new Promise((resolve, reject) => {
        this.promise = { resolve, reject };
      });
    }
  }
};

if (true) {
  module.exports = nanomsg;
}


/***/ }),

/***/ "./src/index.js":
/*!**********************!*\
  !*** ./src/index.js ***!
  \**********************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _stream_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./stream.js */ "./src/stream.js");


let loc = window.location, new_uri;
if (loc.protocol === "https:") {
    new_uri = "wss:";
} else {
    new_uri = "ws:";
}
new_uri += "//" + loc.host;
new_uri += loc.pathname;

const subaddr = new_uri + "socks";

let content = document.querySelectorAll("#terminal .content")[0]

const max_nodes = 1000;
const s = new _stream_js__WEBPACK_IMPORTED_MODULE_0__["Stream"](subaddr);
s.perform_first_sync = false;
s.on('data', (data) => {
    content.appendChild(document.createTextNode(data));
    if (content.childNodes.length > max_nodes) {
        content.removeChild(content.firstChild);
    }
});
s.on('restart', (data) => {
    content.appendChild(document.createTextNode("RESTARTED\n"));

    if (content.childNodes.length > max_nodes) {
        content.removeChild(content.firstChild);
    }

})


/***/ }),

/***/ "./src/stream.js":
/*!***********************!*\
  !*** ./src/stream.js ***!
  \***********************/
/*! exports provided: Stream */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "Stream", function() { return Stream; });
/* harmony import */ var nanomsg_browser__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! nanomsg-browser */ "./node_modules/nanomsg-browser/src/nanomsg.js");
/* harmony import */ var nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(nanomsg_browser__WEBPACK_IMPORTED_MODULE_0__);

nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default.a.receiveArrayBuffer = true;

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

function Stream(addr) {
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
    const sub = new nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default.a.Socket(nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default.a.SUB);

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
        const req = new nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default.a.Socket(nanomsg_browser__WEBPACK_IMPORTED_MODULE_0___default.a.REQ);
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


/***/ })

/******/ });
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vd2VicGFjay9ib290c3RyYXAiLCJ3ZWJwYWNrOi8vLy4vbm9kZV9tb2R1bGVzL25hbm9tc2ctYnJvd3Nlci9zcmMvbmFub21zZy5qcyIsIndlYnBhY2s6Ly8vLi9zcmMvaW5kZXguanMiLCJ3ZWJwYWNrOi8vLy4vc3JjL3N0cmVhbS5qcyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiO1FBQUE7UUFDQTs7UUFFQTtRQUNBOztRQUVBO1FBQ0E7UUFDQTtRQUNBO1FBQ0E7UUFDQTtRQUNBO1FBQ0E7UUFDQTtRQUNBOztRQUVBO1FBQ0E7O1FBRUE7UUFDQTs7UUFFQTtRQUNBO1FBQ0E7OztRQUdBO1FBQ0E7O1FBRUE7UUFDQTs7UUFFQTtRQUNBO1FBQ0E7UUFDQSwwQ0FBMEMsZ0NBQWdDO1FBQzFFO1FBQ0E7O1FBRUE7UUFDQTtRQUNBO1FBQ0Esd0RBQXdELGtCQUFrQjtRQUMxRTtRQUNBLGlEQUFpRCxjQUFjO1FBQy9EOztRQUVBO1FBQ0E7UUFDQTtRQUNBO1FBQ0E7UUFDQTtRQUNBO1FBQ0E7UUFDQTtRQUNBO1FBQ0E7UUFDQSx5Q0FBeUMsaUNBQWlDO1FBQzFFLGdIQUFnSCxtQkFBbUIsRUFBRTtRQUNySTtRQUNBOztRQUVBO1FBQ0E7UUFDQTtRQUNBLDJCQUEyQiwwQkFBMEIsRUFBRTtRQUN2RCxpQ0FBaUMsZUFBZTtRQUNoRDtRQUNBO1FBQ0E7O1FBRUE7UUFDQSxzREFBc0QsK0RBQStEOztRQUVySDtRQUNBOzs7UUFHQTtRQUNBOzs7Ozs7Ozs7Ozs7QUNsRkE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxXQUFXO0FBQ1g7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7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QTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EiLCJmaWxlIjoiYnVuZGxlLmpzIiwic291cmNlc0NvbnRlbnQiOlsiIFx0Ly8gVGhlIG1vZHVsZSBjYWNoZVxuIFx0dmFyIGluc3RhbGxlZE1vZHVsZXMgPSB7fTtcblxuIFx0Ly8gVGhlIHJlcXVpcmUgZnVuY3Rpb25cbiBcdGZ1bmN0aW9uIF9fd2VicGFja19yZXF1aXJlX18obW9kdWxlSWQpIHtcblxuIFx0XHQvLyBDaGVjayBpZiBtb2R1bGUgaXMgaW4gY2FjaGVcbiBcdFx0aWYoaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0pIHtcbiBcdFx0XHRyZXR1cm4gaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0uZXhwb3J0cztcbiBcdFx0fVxuIFx0XHQvLyBDcmVhdGUgYSBuZXcgbW9kdWxlIChhbmQgcHV0IGl0IGludG8gdGhlIGNhY2hlKVxuIFx0XHR2YXIgbW9kdWxlID0gaW5zdGFsbGVkTW9kdWxlc1ttb2R1bGVJZF0gPSB7XG4gXHRcdFx0aTogbW9kdWxlSWQsXG4gXHRcdFx0bDogZmFsc2UsXG4gXHRcdFx0ZXhwb3J0czoge31cbiBcdFx0fTtcblxuIFx0XHQvLyBFeGVjdXRlIHRoZSBtb2R1bGUgZnVuY3Rpb25cbiBcdFx0bW9kdWxlc1ttb2R1bGVJZF0uY2FsbChtb2R1bGUuZXhwb3J0cywgbW9kdWxlLCBtb2R1bGUuZXhwb3J0cywgX193ZWJwYWNrX3JlcXVpcmVfXyk7XG5cbiBcdFx0Ly8gRmxhZyB0aGUgbW9kdWxlIGFzIGxvYWRlZFxuIFx0XHRtb2R1bGUubCA9IHRydWU7XG5cbiBcdFx0Ly8gUmV0dXJuIHRoZSBleHBvcnRzIG9mIHRoZSBtb2R1bGVcbiBcdFx0cmV0dXJuIG1vZHVsZS5leHBvcnRzO1xuIFx0fVxuXG5cbiBcdC8vIGV4cG9zZSB0aGUgbW9kdWxlcyBvYmplY3QgKF9fd2VicGFja19tb2R1bGVzX18pXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLm0gPSBtb2R1bGVzO1xuXG4gXHQvLyBleHBvc2UgdGhlIG1vZHVsZSBjYWNoZVxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5jID0gaW5zdGFsbGVkTW9kdWxlcztcblxuIFx0Ly8gZGVmaW5lIGdldHRlciBmdW5jdGlvbiBmb3IgaGFybW9ueSBleHBvcnRzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLmQgPSBmdW5jdGlvbihleHBvcnRzLCBuYW1lLCBnZXR0ZXIpIHtcbiBcdFx0aWYoIV9fd2VicGFja19yZXF1aXJlX18ubyhleHBvcnRzLCBuYW1lKSkge1xuIFx0XHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBuYW1lLCB7IGVudW1lcmFibGU6IHRydWUsIGdldDogZ2V0dGVyIH0pO1xuIFx0XHR9XG4gXHR9O1xuXG4gXHQvLyBkZWZpbmUgX19lc01vZHVsZSBvbiBleHBvcnRzXG4gXHRfX3dlYnBhY2tfcmVxdWlyZV9fLnIgPSBmdW5jdGlvbihleHBvcnRzKSB7XG4gXHRcdGlmKHR5cGVvZiBTeW1ib2wgIT09ICd1bmRlZmluZWQnICYmIFN5bWJvbC50b1N0cmluZ1RhZykge1xuIFx0XHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCBTeW1ib2wudG9TdHJpbmdUYWcsIHsgdmFsdWU6ICdNb2R1bGUnIH0pO1xuIFx0XHR9XG4gXHRcdE9iamVjdC5kZWZpbmVQcm9wZXJ0eShleHBvcnRzLCAnX19lc01vZHVsZScsIHsgdmFsdWU6IHRydWUgfSk7XG4gXHR9O1xuXG4gXHQvLyBjcmVhdGUgYSBmYWtlIG5hbWVzcGFjZSBvYmplY3RcbiBcdC8vIG1vZGUgJiAxOiB2YWx1ZSBpcyBhIG1vZHVsZSBpZCwgcmVxdWlyZSBpdFxuIFx0Ly8gbW9kZSAmIDI6IG1lcmdlIGFsbCBwcm9wZXJ0aWVzIG9mIHZhbHVlIGludG8gdGhlIG5zXG4gXHQvLyBtb2RlICYgNDogcmV0dXJuIHZhbHVlIHdoZW4gYWxyZWFkeSBucyBvYmplY3RcbiBcdC8vIG1vZGUgJiA4fDE6IGJlaGF2ZSBsaWtlIHJlcXVpcmVcbiBcdF9fd2VicGFja19yZXF1aXJlX18udCA9IGZ1bmN0aW9uKHZhbHVlLCBtb2RlKSB7XG4gXHRcdGlmKG1vZGUgJiAxKSB2YWx1ZSA9IF9fd2VicGFja19yZXF1aXJlX18odmFsdWUpO1xuIFx0XHRpZihtb2RlICYgOCkgcmV0dXJuIHZhbHVlO1xuIFx0XHRpZigobW9kZSAmIDQpICYmIHR5cGVvZiB2YWx1ZSA9PT0gJ29iamVjdCcgJiYgdmFsdWUgJiYgdmFsdWUuX19lc01vZHVsZSkgcmV0dXJuIHZhbHVlO1xuIFx0XHR2YXIgbnMgPSBPYmplY3QuY3JlYXRlKG51bGwpO1xuIFx0XHRfX3dlYnBhY2tfcmVxdWlyZV9fLnIobnMpO1xuIFx0XHRPYmplY3QuZGVmaW5lUHJvcGVydHkobnMsICdkZWZhdWx0JywgeyBlbnVtZXJhYmxlOiB0cnVlLCB2YWx1ZTogdmFsdWUgfSk7XG4gXHRcdGlmKG1vZGUgJiAyICYmIHR5cGVvZiB2YWx1ZSAhPSAnc3RyaW5nJykgZm9yKHZhciBrZXkgaW4gdmFsdWUpIF9fd2VicGFja19yZXF1aXJlX18uZChucywga2V5LCBmdW5jdGlvbihrZXkpIHsgcmV0dXJuIHZhbHVlW2tleV07IH0uYmluZChudWxsLCBrZXkpKTtcbiBcdFx0cmV0dXJuIG5zO1xuIFx0fTtcblxuIFx0Ly8gZ2V0RGVmYXVsdEV4cG9ydCBmdW5jdGlvbiBmb3IgY29tcGF0aWJpbGl0eSB3aXRoIG5vbi1oYXJtb255IG1vZHVsZXNcbiBcdF9fd2VicGFja19yZXF1aXJlX18ubiA9IGZ1bmN0aW9uKG1vZHVsZSkge1xuIFx0XHR2YXIgZ2V0dGVyID0gbW9kdWxlICYmIG1vZHVsZS5fX2VzTW9kdWxlID9cbiBcdFx0XHRmdW5jdGlvbiBnZXREZWZhdWx0KCkgeyByZXR1cm4gbW9kdWxlWydkZWZhdWx0J107IH0gOlxuIFx0XHRcdGZ1bmN0aW9uIGdldE1vZHVsZUV4cG9ydHMoKSB7IHJldHVybiBtb2R1bGU7IH07XG4gXHRcdF9fd2VicGFja19yZXF1aXJlX18uZChnZXR0ZXIsICdhJywgZ2V0dGVyKTtcbiBcdFx0cmV0dXJuIGdldHRlcjtcbiBcdH07XG5cbiBcdC8vIE9iamVjdC5wcm90b3R5cGUuaGFzT3duUHJvcGVydHkuY2FsbFxuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5vID0gZnVuY3Rpb24ob2JqZWN0LCBwcm9wZXJ0eSkgeyByZXR1cm4gT2JqZWN0LnByb3RvdHlwZS5oYXNPd25Qcm9wZXJ0eS5jYWxsKG9iamVjdCwgcHJvcGVydHkpOyB9O1xuXG4gXHQvLyBfX3dlYnBhY2tfcHVibGljX3BhdGhfX1xuIFx0X193ZWJwYWNrX3JlcXVpcmVfXy5wID0gXCJcIjtcblxuXG4gXHQvLyBMb2FkIGVudHJ5IG1vZHVsZSBhbmQgcmV0dXJuIGV4cG9ydHNcbiBcdHJldHVybiBfX3dlYnBhY2tfcmVxdWlyZV9fKF9fd2VicGFja19yZXF1aXJlX18ucyA9IFwiLi9zcmMvaW5kZXguanNcIik7XG4iLCJjb25zdCBuYW5vbXNnID0ge1xuICBkZWJ1ZzogZmFsc2UsXG4gIHJlY29ubmVjdFRpbWU6IDEwMDAsXG4gIHJlY2VpdmVBcnJheUJ1ZmZlcjogZmFsc2UsXG4gIFJFUTogJ3JlcC5zcC5uYW5vbXNnLm9yZycsXG4gIFBBSVI6ICdwYWlyLnNwLm5hbm9tc2cub3JnJyxcbiAgU1VCOiAncHViLnNwLm5hbm9tc2cub3JnJyxcbn1cblxubmFub21zZy5Tb2NrZXQgPSBjbGFzcyB7XG4gIGNvbnN0cnVjdG9yKHByb3RvY29sKSB7XG4gICAgdGhpcy5wcm90b2NvbCA9IHByb3RvY29sO1xuICAgIHRoaXMud3NzID0gbmV3IE1hcCgpO1xuICAgIHRoaXMucmVxSWRIZWFkZXIgPSBudWxsO1xuICAgIHRoaXMucHJvbWlzZSA9IG51bGw7XG4gICAgdGhpcy5jYnMgPSB7XG4gICAgICBkYXRhOiBbXSxcbiAgICAgIGVuZDogW10sXG4gICAgICBlcnJvcjogW10sXG4gICAgfTtcblxuICAgIGlmICh0aGlzLnByb3RvY29sID09IG5hbm9tc2cuUkVRKSB7XG4gICAgICB0aGlzLnJlcUlkSGVhZGVyID0gbmV3IFVpbnQ4QXJyYXkoNCk7XG4gICAgICB3aW5kb3cuY3J5cHRvLmdldFJhbmRvbVZhbHVlcyh0aGlzLnJlcUlkSGVhZGVyKTtcbiAgICAgIC8vIHRoZSBmaXJzdCBiaXQgSEFTIFRPIEJFIG9uZSwgaW4gb3JkZXIgdG8gZ2V0IGEgcmVzcG9uc2VcbiAgICAgIHRoaXMucmVxSWRIZWFkZXJbMF0gfD0gMSA8PCA3O1xuICAgIH1cbiAgfVxuXG4gIGNvbm5lY3QodXJsKSB7XG4gICAgaWYgKCF0aGlzLndzcy5oYXModXJsKSkge1xuICAgICAgcmV0dXJuIG5ldyBQcm9taXNlKChyZXNvbHZlLCByZWplY3QpID0+IHtcbiAgICAgICAgaWYgKG5hbm9tc2cuZGVidWcpIHtcbiAgICAgICAgICBjb25zb2xlLmxvZygnbmFub21zZyBjb25uZWN0IHRvOiAnICsgdXJsKTtcbiAgICAgICAgfVxuXG4gICAgICAgIGNvbnN0IHRyeUNvbm5lY3QgPSAoKSA9PiB7XG4gICAgICAgICAgdHJ5IHtcbiAgICAgICAgICAgIHRoaXMuX19zZXR1cFNvY2tldENvbm5lY3Rpb24odXJsLCByZXNvbHZlKTtcbiAgICAgICAgICB9IGNhdGNoIChlKSB7XG4gICAgICAgICAgICBjb25zb2xlLmxvZyhlKTtcbiAgICAgICAgICAgIHRoaXMud3NzLmRlbGV0ZSh1cmwpO1xuXG4gICAgICAgICAgICBzZXRUaW1lb3V0KHRyeUNvbm5lY3QsIG5hbm9tc2cucmVjb25uZWN0VGltZSk7XG4gICAgICAgICAgfVxuICAgICAgICB9O1xuXG4gICAgICAgIHRyeUNvbm5lY3QoKTtcbiAgICAgIH0pO1xuICAgIH1cbiAgfVxuXG4gIF9fc2V0dXBTb2NrZXRDb25uZWN0aW9uKHVybCwgcmVzb2x2ZSkge1xuICAgIGNvbnN0IHdzID0gbmV3IFdlYlNvY2tldCh1cmwsIFt0aGlzLnByb3RvY29sXSk7XG4gICAgd3MuaW5pdGlhbFVybCA9IHVybDsgLy8gZXZpbCBoYWNrIG9mIGV2aWxuZXNzLCB0byBhY2Nlc3MgdGhlIG9yaWdpbmFsIHVzZWQgdXJsXG5cbiAgICBpZiAobmFub21zZy5yZWNlaXZlQXJyYXlCdWZmZXIpIHtcbiAgICAgIHdzLmJpbmFyeVR5cGUgPSAnYXJyYXlidWZmZXInO1xuICAgIH1cblxuICAgIHRoaXMud3NzLnNldCh1cmwsIHdzKTtcblxuICAgIHdzLm9ub3BlbiA9ICgpID0+IHtcbiAgICAgIGlmIChuYW5vbXNnLmRlYnVnKSB7XG4gICAgICAgIGNvbnNvbGUubG9nKCduYW5vbXNnIGNvbm5lY3RlZDogJyArIHVybCk7XG4gICAgICB9XG5cbiAgICAgIHJlc29sdmUoKTtcbiAgICB9O1xuXG4gICAgd3Mub25tZXNzYWdlID0gKGUpID0+IHtcbiAgICAgIGxldCBkYXRhID0gbnVsbDtcblxuICAgICAgaWYgKHRoaXMucHJvdG9jb2wgPT0gbmFub21zZy5SRVEpIHtcbiAgICAgICAgZGF0YSA9IGUuZGF0YS5zbGljZSg0KTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIGRhdGEgPSBlLmRhdGE7XG4gICAgICB9XG5cbiAgICAgIGlmIChuYW5vbXNnLnJlY2VpdmVBcnJheUJ1ZmZlcikge1xuICAgICAgICB0aGlzLl9fcmVzb2x2ZU5ld0RhdGEoZGF0YSk7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBjb25zdCByZWFkZXIgPSBuZXcgRmlsZVJlYWRlcigpO1xuXG4gICAgICAgIHJlYWRlci5vbmxvYWQgPSAoZXZlbnQpID0+IHtcbiAgICAgICAgICB0aGlzLl9fcmVzb2x2ZU5ld0RhdGEoZXZlbnQudGFyZ2V0LnJlc3VsdCk7XG4gICAgICAgIH07XG5cbiAgICAgICAgcmVhZGVyLnJlYWRBc1RleHQoZGF0YSk7XG4gICAgICB9XG4gICAgfTtcblxuICAgIHdzLm9uZXJyb3IgPSAoZSkgPT4ge1xuICAgICAgaWYgKG5hbm9tc2cuZGVidWcpIHtcbiAgICAgICAgY29uc29sZS5sb2coJ25hbm9tc2cgZXJyb3InLCBlKTtcbiAgICAgIH1cblxuICAgICAgdGhpcy5jYnMuZXJyb3IuZm9yRWFjaChjYiA9PiBjYihlKSk7XG4gICAgfTtcblxuICAgIHdzLm9uY2xvc2UgPSAoKSA9PiB7XG4gICAgICBpZiAobmFub21zZy5kZWJ1Zykge1xuICAgICAgICBjb25zb2xlLmxvZygnbmFub21zZyBjbG9zZTogJyArIHdzLmluaXRpYWxVcmwpO1xuICAgICAgfVxuXG4gICAgICBpZiAodGhpcy53c3MuaGFzKHdzLmluaXRpYWxVcmwpKSB7XG4gICAgICAgIGlmIChuYW5vbXNnLmRlYnVnKSB7XG4gICAgICAgICAgY29uc29sZS5sb2coJ25hbm9tc2cgcmVjb25uZWN0OiAnICsgd3MuaW5pdGlhbFVybCk7XG4gICAgICAgIH1cblxuICAgICAgICB0aGlzLndzcy5kZWxldGUod3MuaW5pdGlhbFVybCk7XG4gICAgICAgIHRoaXMuY29ubmVjdCh3cy5pbml0aWFsVXJsKTtcbiAgICAgIH1cblxuICAgICAgdGhpcy5jYnMuZW5kLmZvckVhY2goY2IgPT4gY2Iod3MuaW5pdGlhbFVybCkpO1xuICAgIH07XG4gIH1cblxuICBfX3Jlc29sdmVOZXdEYXRhKGRhdGEpIHtcbiAgICBpZiAoZGF0YSkge1xuICAgICAgaWYgKHRoaXMucHJvbWlzZSkge1xuICAgICAgICB0aGlzLnByb21pc2UucmVzb2x2ZShkYXRhKTtcbiAgICAgICAgdGhpcy5wcm9taXNlID0gbnVsbDtcbiAgICAgIH1cblxuICAgICAgdGhpcy5jYnMuZGF0YS5mb3JFYWNoKGNiID0+IGNiKGRhdGEpKTtcbiAgICB9XG4gIH1cblxuICBkaXNjb25uZWN0KHVybCkge1xuICAgIGNvbnN0IHdzID0gdGhpcy53c3MuZ2V0KHVybCk7XG5cbiAgICBpZiAod3MpIHtcbiAgICAgIHRoaXMud3NzLmRlbGV0ZSh1cmwpO1xuICAgICAgd3MuY2xvc2UoKTtcbiAgICB9XG4gIH1cblxuICBiaW5kKCkge1xuICAgIHRocm93IG5ldyBFcnJvcignV0hPQUFBQSEhISBOaWNlIHRyeSwgYnV0IE5PLCB3ZSBkbyBub3Qgc3VwcG9ydCB0aGVzZSEnKTtcbiAgfVxuXG4gIG9uKHR5cGUsIGNiKSB7XG4gICAgY29uc3QgY2JzID0gdGhpcy5jYnNbdHlwZV07XG5cbiAgICBpZiAoY2JzKSB7XG4gICAgICBjYnMucHVzaChjYik7XG4gICAgfVxuICB9XG5cbiAgc2VuZChtc2cpIHtcbiAgICBpZiAodGhpcy5wcm90b2NvbCA9PT0gbmFub21zZy5TVUIpIHtcbiAgICAgIHRocm93IG5ldyBFeGNlcHRpb24oJ1NVQiBzb2NrZXQgY2FuIG5vdCBzZW5kJyk7XG4gICAgfVxuXG4gICAgaWYgKHRoaXMud3NzLnNpemUgPCAxKSB7XG4gICAgICB0aHJvdyBuZXcgRXhjZXB0aW9uKCd5b3UgYXJlIG5vdCBjb25uZWN0ZWQgdG8gYW55IHNvY2tldCcpO1xuICAgIH1cblxuICAgIC8vIHRoaXMgaXMgYSBnb29kIG9uZTogaHR0cHM6Ly93d3cuZnJlZWxpc3RzLm9yZy9wb3N0L25hbm9tc2cvV2ViU29ja2V0LXRlc3QtY2FzZS1ub3Qtd29ya2luZywzXG4gICAgaWYgKHRoaXMucHJvdG9jb2wgPT09IG5hbm9tc2cuUkVRKSB7XG4gICAgICBjb25zdCBsZW5ndGggPSBtc2cubGVuZ3RoIHx8IG1zZy5ieXRlTGVuZ3RoO1xuICAgICAgY29uc3QgZGF0YSA9IG5ldyBVaW50OEFycmF5KGxlbmd0aCArIDQpO1xuICAgICAgZGF0YS5zZXQodGhpcy5yZXFJZEhlYWRlciwgMCk7XG5cbiAgICAgIGlmICh0eXBlb2YgbXNnID09PSAnc3RyaW5nJyB8fCBtc2cgaW5zdGFuY2VvZiBTdHJpbmcpIHtcbiAgICAgICAgZm9yIChsZXQgaSA9IDQ7IGkgPCBtc2cubGVuZ3RoICsgNDsgKytpKSB7XG4gICAgICAgICAgZGF0YVtpXSA9IG1zZy5jaGFyQ29kZUF0KGkgLSA0KTtcbiAgICAgICAgfVxuXG4gICAgICB9IGVsc2Uge1xuICAgICAgICBkYXRhLnNldChtc2csIDQpO1xuICAgICAgfVxuXG4gICAgICBtc2cgPSBkYXRhO1xuICAgIH1cblxuICAgIGlmIChuYW5vbXNnLmRlYnVnKSB7XG4gICAgICBjb25zb2xlLmxvZygnbmFub21zZyBzZW5kID0+JywgbXNnKTtcbiAgICB9XG5cbiAgICBmb3IgKGxldCB3cyBvZiB0aGlzLndzcy52YWx1ZXMoKSkge1xuICAgICAgaWYgKHdzLnJlYWR5U3RhdGUgPT09IDEpIHtcbiAgICAgICAgd3Muc2VuZChtc2cpO1xuICAgICAgfSBlbHNlIGlmICh3cy5yZWFkeVN0YXRlID4gMSkge1xuICAgICAgICBpZiAodGhpcy53c3MuaGFzKHdzLnVybCkpIHtcbiAgICAgICAgICB0aGlzLndzcy5kZWxldGUod3MudXJsKTtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChuYW5vbXNnLmRlYnVnKSB7XG4gICAgICAgICAgY29uc29sZS5sb2coJ25hbm9tc2c6IGNvdWxkIG5vdCBzZW5kLCBiZWNhdXNlIG9mIGNsb3NlZCBjb25uZWN0aW9uICgnICsgd3MudXJsICsgJyknKTtcbiAgICAgICAgfVxuICAgICAgfVxuICAgIH1cblxuICAgIGlmICh0aGlzLnByb3RvY29sID09PSBuYW5vbXNnLlJFUSB8fCB0aGlzLnByb3RvY29sID09PSBuYW5vbXNnLlBBSVIpIHtcbiAgICAgIHJldHVybiBuZXcgUHJvbWlzZSgocmVzb2x2ZSwgcmVqZWN0KSA9PiB7XG4gICAgICAgIHRoaXMucHJvbWlzZSA9IHsgcmVzb2x2ZSwgcmVqZWN0IH07XG4gICAgICB9KTtcbiAgICB9XG4gIH1cbn07XG5cbmlmICh0eXBlb2YgbW9kdWxlICE9PSAndW5kZWZpbmVkJykge1xuICBtb2R1bGUuZXhwb3J0cyA9IG5hbm9tc2c7XG59XG4iLCJpbXBvcnQge1N0cmVhbX0gZnJvbSAnLi9zdHJlYW0uanMnXG5cbmxldCBsb2MgPSB3aW5kb3cubG9jYXRpb24sIG5ld191cmk7XG5pZiAobG9jLnByb3RvY29sID09PSBcImh0dHBzOlwiKSB7XG4gICAgbmV3X3VyaSA9IFwid3NzOlwiO1xufSBlbHNlIHtcbiAgICBuZXdfdXJpID0gXCJ3czpcIjtcbn1cbm5ld191cmkgKz0gXCIvL1wiICsgbG9jLmhvc3Q7XG5uZXdfdXJpICs9IGxvYy5wYXRobmFtZTtcblxuY29uc3Qgc3ViYWRkciA9IG5ld191cmkgKyBcInNvY2tzXCI7XG5cbmxldCBjb250ZW50ID0gZG9jdW1lbnQucXVlcnlTZWxlY3RvckFsbChcIiN0ZXJtaW5hbCAuY29udGVudFwiKVswXVxuXG5jb25zdCBtYXhfbm9kZXMgPSAxMDAwO1xuY29uc3QgcyA9IG5ldyBTdHJlYW0oc3ViYWRkcik7XG5zLnBlcmZvcm1fZmlyc3Rfc3luYyA9IGZhbHNlO1xucy5vbignZGF0YScsIChkYXRhKSA9PiB7XG4gICAgY29udGVudC5hcHBlbmRDaGlsZChkb2N1bWVudC5jcmVhdGVUZXh0Tm9kZShkYXRhKSk7XG4gICAgaWYgKGNvbnRlbnQuY2hpbGROb2Rlcy5sZW5ndGggPiBtYXhfbm9kZXMpIHtcbiAgICAgICAgY29udGVudC5yZW1vdmVDaGlsZChjb250ZW50LmZpcnN0Q2hpbGQpO1xuICAgIH1cbn0pO1xucy5vbigncmVzdGFydCcsIChkYXRhKSA9PiB7XG4gICAgY29udGVudC5hcHBlbmRDaGlsZChkb2N1bWVudC5jcmVhdGVUZXh0Tm9kZShcIlJFU1RBUlRFRFxcblwiKSk7XG5cbiAgICBpZiAoY29udGVudC5jaGlsZE5vZGVzLmxlbmd0aCA+IG1heF9ub2Rlcykge1xuICAgICAgICBjb250ZW50LnJlbW92ZUNoaWxkKGNvbnRlbnQuZmlyc3RDaGlsZCk7XG4gICAgfVxuXG59KVxuIiwiaW1wb3J0IG5hbm9tc2cgZnJvbSAnbmFub21zZy1icm93c2VyJztcbm5hbm9tc2cucmVjZWl2ZUFycmF5QnVmZmVyID0gdHJ1ZTtcblxuY29uc3QgdHlwZSA9IHtcbiAgICBEQVRBOiBTeW1ib2woXCJEQVRBXCIpLFxuICAgIEhFQVJUQkVBVDogU3ltYm9sKFwiSEVBUlRCRUFUXCIpLFxuICAgIEVORF9PRl9TRVNTSU9OOiBTeW1ib2woXCJFTkRfT0ZfU0VTU0lPTlwiKSxcbn1cblxuZnVuY3Rpb24gdHlwZV91bm1hcnNoYWwodCkge1xuICAgIHN3aXRjaCAodCkge1xuICAgICAgICBjYXNlIDA6XG4gICAgICAgICAgICByZXR1cm4gdHlwZS5EQVRBO1xuICAgICAgICBjYXNlIDE6XG4gICAgICAgICAgICByZXR1cm4gdHlwZS5IRUFSVEJFQVQ7XG4gICAgICAgIGNhc2UgMjogXG4gICAgICAgICAgICByZXR1cm4gdHlwZS5IRUFSVEJFQVQ7XG4gICAgfVxufVxuXG5sZXQgdXRmOGRlY29kZXIgPSBuZXcgVGV4dERlY29kZXIoKTtcblxuZnVuY3Rpb24gbXNnX3VubWFyc2hhbChidWZmZXIpIHtcbiAgICBsZXQgdmlldyA9IG5ldyBEYXRhVmlldyhidWZmZXIpO1xuICAgIGxldCBtc2cgPSB7fTtcblxuICAgIGxldCBieXRlcyA9IDA7XG4gICAgbXNnLnR5cGUgPSB0eXBlX3VubWFyc2hhbCh2aWV3LmdldFVpbnQ4KGJ5dGVzKSk7XG4gICAgYnl0ZXMgKz0gMTtcbiAgICBtc2cuc2VxID0gdmlldy5nZXRCaWdVaW50NjQoYnl0ZXMsIHRydWUpO1xuICAgIGJ5dGVzICs9IDg7XG5cbiAgICBpZiAobXNnLnR5cGUgIT0gdHlwZS5EQVRBKSB7XG4gICAgICAgIHJldHVybiBbbXNnLCBieXRlc107XG4gICAgfVxuXG4gICAgbGV0IGxlbiA9IHZpZXcuZ2V0VWludDE2KGJ5dGVzLCB0cnVlKTtcbiAgICBieXRlcyArPSAyO1xuICAgIGlmIChsZW4gPT0gMCkgcmV0dXJuIFttc2csIGJ5dGVzXTtcbiAgICAvLyBUT0RPOiBwcm9iYWJseSBkb24ndCB3YW50IHRvIGRlY29kZSBoZXJlXG4gICAgbXNnLmRhdGEgPSB1dGY4ZGVjb2Rlci5kZWNvZGUoYnVmZmVyLnNsaWNlKGJ5dGVzLCBieXRlcytsZW4pKTtcbiAgICBieXRlcyArPSBsZW5cbiAgICByZXR1cm4gW21zZywgYnl0ZXNdO1xufVxuXG5mdW5jdGlvbiBtc2dzX3VubWFyc2hhbChidWZmZXIpIHtcbiAgICBsZXQgbXNncyA9IFtdO1xuICAgIHdoaWxlIChidWZmZXIuYnl0ZUxlbmd0aCA+IDApIHtcbiAgICAgICAgbGV0IFttc2csIGJ5dGVzXSA9IG1zZ191bm1hcnNoYWwoYnVmZmVyKTtcbiAgICAgICAgbXNncy5wdXNoKG1zZyk7XG4gICAgICAgIGJ1ZmZlciA9IGJ1ZmZlci5zbGljZShieXRlcyk7XG4gICAgfVxuICAgIHJldHVybiBtc2dzO1xufVxuXG5leHBvcnQgZnVuY3Rpb24gU3RyZWFtKGFkZHIpIHtcbiAgICB0aGlzLnBlcmZvcm1fZmlyc3Rfc3luYyA9IHRydWU7XG4gICAgbGV0IGNicyA9IHtcbiAgICAgIGRhdGE6IFtdLFxuICAgICAgZW5kOiBbXSxcbiAgICAgIHJlc3RhcnQ6IFtdLFxuICAgICAgaGVhcnRiZWF0OiBbXSxcbiAgICAgIGVycm9yOiBbXSxcbiAgICB9O1xuXG4gICAgdGhpcy5vbiA9IGZ1bmN0aW9uKHR5cGUsIGNiKSB7XG4gICAgICAgIGlmIChjYnNbdHlwZV0pIHtcbiAgICAgICAgICAgIGNic1t0eXBlXS5wdXNoKGNiKTtcbiAgICAgICAgfVxuICAgIH1cblxuXG4gICAgbGV0IHNlcSA9IEJpZ0ludCgwKTsgLy8gc2VxdWVuY2UgaWQgb2YgdGhlIG5leHQgbXNnIHdlJ3JlIGV4cGVjdGluZyB0byByZWNlaXZlXG4gICAgbGV0IHN5bmNlZCA9IGZhbHNlOyAvLyBzdGF0ZSBvZiBjbGllbnRcblxuICAgIGxldCBzeW5jaW5nID0gZmFsc2VcbiAgICBsZXQgcXVldWUgPSBbXVxuXG4gICAgY29uc3Qgc3ViYWRkciA9IGFkZHIgKyBcIi9wdWJcIjtcbiAgICBjb25zdCByZXBhZGRyID0gYWRkciArIFwiL3JlcFwiO1xuICAgIGNvbnN0IHN1YiA9IG5ldyBuYW5vbXNnLlNvY2tldChuYW5vbXNnLlNVQik7XG5cbiAgICBzdWIuY29ubmVjdChzdWJhZGRyKTtcbiAgICBzdWIub24oJ2RhdGEnLCBhc3luYyAocmF3bXNnKSA9PiB7XG4gICAgICAgIGxldCBbbSwgbmJ5dGVzXSA9IG1zZ191bm1hcnNoYWwocmF3bXNnKTtcblxuICAgICAgICBpZiAoc3luY2luZykge1xuICAgICAgICAgICAgcXVldWUucHVzaChtKTtcbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmICghdGhpcy5wZXJmb3JtX2ZpcnN0X3N5bmMpIHtcbiAgICAgICAgICAgIHRoaXMucGVyZm9ybV9maXJzdF9zeW5jID0gdHJ1ZTtcbiAgICAgICAgICAgIHN5bmNlZCAgICAgICAgICAgICAgICAgID0gdHJ1ZTtcbiAgICAgICAgICAgIHNlcSAgICAgICAgICAgICAgICAgICAgID0gbS5zZXE7XG4gICAgICAgIH1cblxuICAgICAgICBpZiAobS50eXBlID09IHR5cGUuRU5EX09GX1NFU1NJT04pIHtcbiAgICAgICAgICAgIGZvciAobGV0IGYgb2YgY2JzLmVuZCkge1xuICAgICAgICAgICAgICAgIGYobS5kYXRhKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuXG5cbiAgICAgICAgaWYgKG0uc2VxIDwgc2VxKSB7XG4gICAgICAgICAgICBpZiAoIXN5bmNlZCkge1xuICAgICAgICAgICAgICAgIC8vIElnbm9yZSBtc2dzIHdlJ3ZlIGFscmVhZHkgc2Vlbi4gVGhpcyBtYXkgaGFwcGVuIGR1cmluZyByZS1zeW5jIGFzXG4gICAgICAgICAgICAgICAgLy8gbXNncyByZWNlaXZlZCBieSBPT0Igc3luYyBtYXkgYWxzbyBhcnJpdmUgYXQgc3ViIHNvY2tldFxuICAgICAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIC8vIElmIHdlJ3JlIG5vdCByc3luY2luZyBhbmQgd2Ugc2VlIGEgbWVzc2FnZSB3aXRoIGxvd2VyIHNlcSB0aGFuIHdlIGV4cGVjdCxcbiAgICAgICAgICAgIC8vIHRoZSBzZXJ2ZXIgbWF5IGhhdmUgcmVzdGFydGVkLCBhbmQgd2UgbmVlZCB0byByZXN5bmMgcmlnaHQgZnJvbSB0aGVcbiAgICAgICAgICAgIC8vIHN0YXJ0LlxuICAgICAgICAgICAgc2VxID0gQmlnSW50KDApO1xuICAgICAgICAgICAgZm9yIChsZXQgZiBvZiBjYnMucmVzdGFydCkge1xuICAgICAgICAgICAgICAgIGYobS5kYXRhKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChtLnNlcSA+IHNlcSkge1xuICAgICAgICAgICAgLy8gV2UndmUgbWlzc2VkIGEgbWVzc2FnZSwgcGVyZm9ybSBvdXQtb2YtYmFuZCBzeW5jXG4gICAgICAgICAgICBzeW5jaW5nID0gdHJ1ZTtcbiAgICAgICAgICAgIHN5bmNlZCAgPSBmYWxzZTtcbiAgICAgICAgICAgIGxldCBzID0gYXdhaXQgc3luY19tc2dzKHNlcSwgcmVwYWRkciwgLTEpO1xuICAgICAgICAgICAgLy8gV2UgbWF5IGhhdmUgZ290dGVuIGZld2VyIG9yIG1vcmUgbWVzc2FnZXMgdGhhbiB3ZSB3ZXJlIGV4cGVjdGluZy5cbiAgICAgICAgICAgIC8vIElmIHdlIGdvdCBtb3JlIG5leHQsIHdlIGVuc3VyZVxuICAgICAgICAgICAgLy8gVE9ETzogd2Ugc2hvdWxkIGNoZWNrIGlmIHdlIGdvdCBsZXNzIGhlcmUgYW5kIGRvIGFub3RoZXIgcmVzeW5jXG5cbiAgICAgICAgICAgIHNlcSA9IHMgKyBCaWdJbnQoMSk7XG4gICAgICAgICAgICBmb3IgKGxldCBtIG9mIHF1ZXVlKSB7XG4gICAgICAgICAgICAgICAgaWYgKG0uc2VxICE9IHNlcSB8fCBtLnR5cGUgIT0gdHlwZS5EQVRBKSB7XG4gICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlXG4gICAgICAgICAgICAgICAgfVxuICAgICAgICAgICAgICAgIGZvciAobGV0IGYgb2YgY2JzLmRhdGEpIHtcbiAgICAgICAgICAgICAgICAgICAgZihtLmRhdGEpO1xuICAgICAgICAgICAgICAgIH1cbiAgICAgICAgICAgICAgICBzZXEgPSBtLnNlcSArIEJpZ0ludCgxKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHF1ZXVlID0gW107XG4gICAgICAgICAgICBzeW5jaW5nID0gZmFsc2U7XG5cbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmICghc3luY2VkICYmIG0uc2VxID09IHNlcSkge1xuICAgICAgICAgICAgc3luY2VkID0gdHJ1ZTtcbiAgICAgICAgfVxuXG4gICAgICAgIGlmIChtLnR5cGUgPT0gdHlwZS5IRUFSVEJFQVQpIHtcbiAgICAgICAgICAgIGZvciAobGV0IGYgb2YgY2JzLmhlYXJ0YmVhdCkge1xuICAgICAgICAgICAgICAgIGYobS5kYXRhKTtcbiAgICAgICAgICAgIH1cbiAgICAgICAgICAgIHJldHVybjtcbiAgICAgICAgfVxuXG4gICAgICAgIGZvciAobGV0IGYgb2YgY2JzLmRhdGEpIHtcbiAgICAgICAgICAgIGYobS5kYXRhKTtcbiAgICAgICAgfVxuICAgICAgICBzZXEgPSBtLnNlcSArIEJpZ0ludCgxKTtcbiAgICB9KTtcblxuICAgIGFzeW5jIGZ1bmN0aW9uIHN5bmNfbXNncyhzZXEsIGFkZHIsIHRpbWVvdXQpIHtcbiAgICAgICAgY29uc3QgcmVxID0gbmV3IG5hbm9tc2cuU29ja2V0KG5hbm9tc2cuUkVRKTtcbiAgICAgICAgdHJ5IHtcbiAgICAgICAgICAgIGF3YWl0IHJlcS5jb25uZWN0KGFkZHIpO1xuICAgICAgICB9IGNhdGNoIHtcbiAgICAgICAgICAgIGNvbnNvbGUubG9nKFwiY29ublwiKTtcbiAgICAgICAgICAgIHJldHVybiAwO1xuICAgICAgICB9XG5cbiAgICAgICAgY29uc3QgYnVmID0gbmV3IEFycmF5QnVmZmVyKDgpO1xuICAgICAgICBjb25zdCB2aWV3ID0gbmV3IERhdGFWaWV3KGJ1Zik7XG5cbiAgICAgICAgdmlldy5zZXRCaWdVaW50NjQoMCwgc2VxKTtcbiAgICAgICAgY29uc3QgZGF0YSA9IGF3YWl0IHJlcS5zZW5kKGJ1Zik7XG4gICAgICAgIGNvbnN0IG1zZ3MgPSBtc2dzX3VubWFyc2hhbChkYXRhKTtcbiAgICAgICAgZm9yIChjb25zdCBtIG9mIG1zZ3MpIHtcbiAgICAgICAgICAgIGZvciAobGV0IGYgb2YgY2JzLmRhdGEpIHtcbiAgICAgICAgICAgICAgICBmKG0uZGF0YSk7XG4gICAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgcmV0dXJuIG1zZ3NbbXNncy5sZW5ndGggLSAxXS5zZXE7XG4gICAgfVxufVxuIl0sInNvdXJjZVJvb3QiOiIifQ==
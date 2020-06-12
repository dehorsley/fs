<style >

.operator-input {
    font-family: Menlo,consolas,monospace;
    color: #aaaaaa;
    max-height: 30em;
    min-height: 10em;
    overflow-y: auto;
    border-top: 5px solid #222;
}

input {
    color: inherit;
    resize: none;
    outline: none;
    background: none;
    border: 0;
    flex: 1;
    padding: 0;
}

.line::before {
    content: "> ";
    width: 1em;
}

.error {
    color: red;
}

.line {
    display: block;
    font-size: inherit;
    line-height: inherit;
}

.input-line {
    color: #dedede;
    display: flex;
    align-items: baseline;
}
.input-line::before {
    content: "> ";
    width: 1em;
}

</style>

<script>
    import { beforeUpdate, afterUpdate } from 'svelte';
    import {Socket, Protocol} from 'nanomsg-browser';

    export let addr;

    let div;
    let autoscroll = true;

	beforeUpdate(() => {
		autoscroll = div && (div.offsetHeight + div.scrollTop) > (div.scrollHeight - 20);
	});

	afterUpdate(() => {
		if (autoscroll) div.scrollTo(0, div.scrollHeight);
	});


    let history = [
    ]

    const req = new Socket({
        protocol: Protocol.REQ,
        sendArrayBuffer: true,
        receiveArrayBuffer: false,
    });

    let history_position = 0;

    let saved_input = '';

    function moveToEnd(el) {
        el.selectionStart = el.selectionEnd = el.value.length;
    }

    function handleArrowUp(event) {
        event.preventDefault()
        if (history_position == 0) {
            return;
        }
        if (history_position == history.length) {
            saved_input = event.target.value;
        }
        history_position--;
        event.target.value = history[history_position].input;
        moveToEnd(event.target);
    }

    function handleArrowDown(event) {
        event.preventDefault()
        if (history_position == history.length) {
            return;
        }
        history_position++;
        if (history_position == history.length) {
            event.target.value = saved_input;
            moveToEnd(event.target);
            return;
        }

        event.target.value = history[history_position].input;
        moveToEnd(event.target);
        return;
    }

    function handleKeydown(event) {
        switch (event.key) {
            case "Down": // IE/Edge specific value
            case "ArrowDown":
                handleArrowDown(event);
                return;
            case "Up": // IE/Edge specific value
            case "ArrowUp":
                handleArrowUp(event);
                return;
            case "Enter":
                break;
            default:
                return;
        }

        event.preventDefault()
        const input = event.target.value;
        if (!input) return;
        event.target.value = '';
        saved_input = '';

        let msg = {
            error: null,
            result: null,
            input
        };
        history = history.concat(msg);
        history_position = history.length; 

        (async () => {
            try {
                await req.connect(addr);
            } catch {
                msg.error = {message: "connection error"}
                return 0;
            }
            const fields = input.split(" ");
            let request = {
                method: fields[0],
                params: fields.slice(1),
                id: 0,
            }
            const data = await req.send(JSON.stringify(request));
            const reply = JSON.parse(data);
            Object.assign(msg, reply);
            history = history;
        })();

    }

</script>

<div class="operator-input" bind:this={div} >
    <div class="history">
        {#each history as line}
            <div class="line" class:error="{line.error !== null}">
				<span>{line.input}</span>
                {#if line.error !== null}
                    <div> error {line.error.code}: {line.error.message} </div>
                {/if}
                {#if line.result !== null}
                <div>
                    {line.result}
                </div>
                {/if}
			</div>
		{/each}
    </div>
    <div class="input-line">
        <input on:keydown={handleKeydown}>
    </div>
</div>

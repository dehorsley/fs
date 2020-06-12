<style >

.operator-input {
    font-family: Menlo,consolas,monospace;
    color: #aaaaaa;
    max-height: 30em;
    min-height: 10em;
    overflow-y: auto;
}

input {
    color: inherit;
    resize: none;
    outline: none;
    background: none;
    border: 0;
    flex: 1;
}

.line::before {
    content: "> ";
    width: 1em;
}

.error {
    color: red;
}

.line {
    padding: .2rem;
    display: block;
    font-size: inherit;
    line-height: inherit;
}

.input-line {
    padding: .2rem;
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

    function handleKeydown(event) {
		if (event.key !== 'Enter') {
            return
        }
        const input = event.target.value;
        if (!input) return;
        event.target.value = '';

        let msg = {
            error: null,
            input
        };
        history = history.concat(msg);

        // TODO: call
        setTimeout(() => {
            msg.error = "bad!"
            history = history;
        }, 1000 + Math.random() * 200);

    }

</script>

<div class="operator-input" bind:this={div} >
    <div class="history">
        {#each history as line}
            <div class="line" class:error="{line.error !== null}">
				<span>{line.input}</span>
                {#if line.error !== null}
                    <div> {line.error} </div>
                {/if}
			</div>
		{/each}
    </div>
    <div class="input-line">
        <input on:keydown={handleKeydown}>
    </div>
</div>

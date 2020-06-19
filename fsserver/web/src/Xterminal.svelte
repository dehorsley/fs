<script>
	import { beforeUpdate, afterUpdate } from 'svelte';
    import {Stream} from './stream.js';
    import {Terminal} from "xterm";
    import { FitAddon } from 'xterm-addon-fit';

    export let addr = "";
    export let perform_first_sync = true;

    let div;

    let s = new Stream(addr);
    s.perform_first_sync = perform_first_sync;

    const term = new Terminal();
    const fitAddon = new FitAddon();
    term.loadAddon(fitAddon);


    $: if (div) {
        term.open(div);
        fitAddon.fit();
    }

    let resize = event => {
        console.log(event);

    }

    s.on('data', (data) => {
        term.write(data);
    });

    s.on('resync', () => {
    })
    
</script>

<style>

</style>

<div>
    <div bind:this={div} on:resize={resize}>
    </div>
</div>

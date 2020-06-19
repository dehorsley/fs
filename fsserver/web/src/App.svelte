<script>
    import {Stream} from './stream.js'
    import Terminal from './Terminal.svelte';
    import Xterminal from './Xterminal.svelte';
    import Monitor from './Monitor.svelte';
    import OperatorInput from './OperatorInput.svelte';
    let scrollback = 200;


    let loc = window.location, wsbase;
    if (loc.protocol === "https:") {
        wsbase = "wss:";
    } else {
        wsbase = "ws:";
    }
    wsbase += "//" + loc.host;
    wsbase += loc.pathname;

    const cmdaddr = wsbase + "cmd";

</script>
<style>
    .container {
        display: flex;
        flex-direction: column;
        height: 100%;
    }
</style>

<div class="container">
    <Xterminal addr={wsbase + "windows/fs"}/>
    <OperatorInput addr={cmdaddr}/>
</div>

<script>
    import {Stream} from './stream.js'
    import Terminal from './Terminal.svelte';
    import Monitor from './Monitor.svelte';
    import OperatorInput from './OperatorInput.svelte';
    let scrollback = 200;
    let data = {}

    let loc = window.location, new_uri;
    if (loc.protocol === "https:") {
        new_uri = "wss:";
    } else {
        new_uri = "ws:";
    }
    new_uri += "//" + loc.host;
    new_uri += loc.pathname;

    const subaddr = new_uri + "socks";

    const cmdaddr = new_uri + "cmd";

    const max_nodes = 1000;
    const s = new Stream(subaddr);
    s.perform_first_sync = true;
    s.on('data', (d) => {
        data = JSON.parse(d);
    });
    s.on('restart', (data) => {
    })

</script>
<style>
    .container {
        display: flex;
        flex-direction: column;
        height: 100%;
    }
</style>

<div class="container">
    <input type=range bind:value={scrollback} min=2 max=100>
    <Monitor {data} />
    <Terminal {scrollback} />
    <OperatorInput addr={cmdaddr}/>
</div>

<script>
    import {Stream} from './stream.js'
    import Terminal from './Terminal.svelte';
    let scrollback = 200;
    let thedata = {}

    let loc = window.location, new_uri;
    if (loc.protocol === "https:") {
        new_uri = "wss:";
    } else {
        new_uri = "ws:";
    }
    new_uri += "//" + loc.host;
    new_uri += loc.pathname;

    const subaddr = new_uri + "socks";

    const max_nodes = 1000;
    const s = new Stream(subaddr);
    s.perform_first_sync = true;
    s.on('data', (data) => {
        thedata = JSON.parse(data);
    });
    s.on('restart', (data) => {
    })

</script>

<style>

    table {
        table-layout: fixed;
        width: 400px;
    }
    td {
        border: 5px solid #333333;
        text-align: center;
    }

    td.red {
        color: #AA0000;
    }

    td.green {
        color: #005500;
    }

    .container {
        display: flex;
        flex-direction: column;
        height: 100%;
    }

</style>

<div class="container">
    <input type=range bind:value={scrollback} min=2 max=100>
    <table> 
        <tr>
            <td>
                {thedata.blag || ''}
            </td>
            <td class="{ thedata.r > 0 ? 'red' : 'green' }">
                {thedata.r || ''}
            </td>
            <td>
                {thedata.con || ''}
            </td>
            
    </table>
    <Terminal {scrollback} />
</div>

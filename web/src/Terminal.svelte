<script>
	import { beforeUpdate, afterUpdate } from 'svelte';
    import {Stream} from './stream.js'

    export let scrollback = 1000;
    export let addr = "socks";

	let div;
    let bottom_anchor;
    let terminal;

	let autoscroll = true;

    let new_uri;
    let loc = window.location;
    if (loc.protocol === "https:") {
        new_uri = "wss:";
    } else {
        new_uri = "ws:";
    }
    new_uri += "//" + loc.host;
    new_uri += loc.pathname;


    let subaddr = new_uri  + addr;
    let s = new Stream(subaddr);
    s.perform_first_sync = false;
    let k = 0;
    s.on('data', (data) => {
        k += 1;
        if (k == 10) {
            k = 0;
            const anchor = document.createElement('span');
            /* anchor.className = bottom_anchor.className; */
            anchor.appendChild(document.createTextNode(data));
            div.appendChild(anchor);

        } else {
            div.appendChild(document.createTextNode(data));
        }

        while (div.childNodes.length > scrollback) {
            div.removeChild(div.firstChild);
        }
		/* if (autoscroll) terminal.scrollTo(0, terminal.scrollHeight); */
    });

    //s.on('restart', (data) => {
    //    content.appendChild(document.createTextNode("RESTARTED\n"));
    //    if (content.childNodes.length > max_nodes) {
    //        content.removeChild(content.firstChild);
    //    }
    //})
    
    let onscroll = () => {
        let new_autoscroll = terminal && (terminal.offsetHeight + terminal.scrollTop) > (terminal.scrollHeight - 20);
        if (!(new_autoscroll^autoscroll)) {
            return;
        }

        if (new_autoscroll){ 
            div.classList.add("overflow-anchor-none");
            div.classList.remove("overflow-anchor-auto");
            console.log("On");
        } else {
            div.classList.add("overflow-anchor-auto");
            div.classList.remove("overflow-anchor-none");
            console.log("Off");
        }
        autoscroll = new_autoscroll;
    }


</script>

<style>
	.terminal {
		margin: 0 0 0.5em 0;
        white-space: pre;
        font-family: monospace;
        width: 80ch;
        color: green;
        overflow-y: scroll;
    }

    :global(.terminal *) {
        overflow-anchor: none;
    }

    :global(.overflow-anchor-none) {
        overflow-anchor: none;
    }

    :global(.overflow-anchor-auto) {
        overflow-anchor: auto;
    }

    .anchor {
        overflow-anchor: auto;
    }

</style>

<div class="terminal" bind:this={terminal} on:scroll={onscroll}>
    <div bind:this={div}></div>
    <div class="anchor" bind:this={bottom_anchor}></div>
</div>

import {Stream} from './stream.js'

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
const s = new Stream(subaddr);
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

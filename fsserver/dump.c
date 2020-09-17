#include <stdlib.h>
#include <unistd.h>
#include <jansson.h>

#include "display_data.h"
#include "display_data_json.h"

int main() {
    for (;;) {
        const display_data_t *data = display_data_fetch();
        json_t *j = json_object();
        if (!j) {
            printf("noalloc\n");
            return 1;
        }
        json_object_set_new(j, "blag", json_boolean(data->on_source));
        json_dumpf(j, stdout, JSON_INDENT(1));
        json_decref(j);
        sleep(1);
    }
}

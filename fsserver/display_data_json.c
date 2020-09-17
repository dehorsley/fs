#include <jansson.h>

#include "display_data.h"

json_t *marshal_json_display_data_t(const display_data_t *t)
{
json_t *root = json_object(); json_t *a; json_t *ret;
if (root == NULL) return NULL;
ret = json_string(t->source);
if (ret == NULL) return NULL;
json_object_set_new(root, "source", ret);
ret = json_boolean(t->halted);
if (ret == NULL) return NULL;
json_object_set_new(root, "halted", ret);
ret = json_boolean(t->on_source);
if (ret == NULL) return NULL;
json_object_set_new(root, "on_source", ret);
ret = json_real(t->azimuth);
if (ret == NULL) return NULL;
json_object_set_new(root, "azimuth", ret);
ret = json_real(t->elevation);
if (ret == NULL) return NULL;
json_object_set_new(root, "elevation", ret);
ret = json_real(t->right_ascension);
if (ret == NULL) return NULL;
json_object_set_new(root, "right_ascension", ret);
ret = json_real(t->declination);
if (ret == NULL) return NULL;
json_object_set_new(root, "declination", ret);
ret = json_string(t->host_time);
if (ret == NULL) return NULL;
json_object_set_new(root, "host_time", ret);
return root;}

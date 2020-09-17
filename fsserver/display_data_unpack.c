#include <stdint.h>
#include <sys/types.h>

#include "display_data.h"
const size_t len_display_data_t = 36;

ssize_t unmarshal_display_data_t(display_data_t *t, uint8_t *data, size_t n)
{
ssize_t ret; uint8_t *p=data;
if (n < len_display_data_t) return -1;
t->source = *p++; n--;
ret = unmarshal_bool(&t->halted, p, n);
p += ret; n -= ret;
ret = unmarshal_bool(&t->on_source, p, n);
p += ret; n -= ret;
ret = unmarshal_double(&t->azimuth, p, n);
p += ret; n -= ret;
ret = unmarshal_double(&t->elevation, p, n);
p += ret; n -= ret;
ret = unmarshal_double(&t->right_ascension, p, n);
p += ret; n -= ret;
ret = unmarshal_double(&t->declination, p, n);
p += ret; n -= ret;
t->host_time = *p++; n--;
return (p-data);}

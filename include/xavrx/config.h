#ifndef XAVRX_CONFIG_H
#define XAVRX_CONFIG_H

#include <stddef.h>

typedef struct {
    int wifi_enabled;
    unsigned int log_level;
} XavrxConfig;

/* Parses a small, bounded key=value configuration. Unknown keys are ignored. */
int xavrx_config_parse(const char *data, size_t length, XavrxConfig *out);
void xavrx_config_defaults(XavrxConfig *out);

#endif

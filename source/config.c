#include "xavrx/config.h"

void xavrx_config_defaults(XavrxConfig *out)
{
    if (!out) return;
    out->wifi_enabled = 0;
    out->log_level = 1;
}

static int match(const char *p, size_t n, const char *s)
{
    size_t i = 0;
    while (s[i] && i < n && p[i] == s[i]) ++i;
    return i == n && s[i] == '\0';
}

int xavrx_config_parse(const char *data, size_t length, XavrxConfig *out)
{
    size_t pos = 0;
    if (!data || !out) return 0;
    xavrx_config_defaults(out);

    while (pos < length) {
        size_t end = pos, eq, key_end, val_start, val_end;
        while (end < length && data[end] != '\n' && data[end] != '\r') ++end;
        eq = pos;
        while (eq < end && data[eq] != '=') ++eq;
        if (eq < end) {
            key_end = eq;
            while (key_end > pos && (data[key_end - 1] == ' ' || data[key_end - 1] == '\t')) --key_end;
            val_start = eq + 1;
            while (val_start < end && (data[val_start] == ' ' || data[val_start] == '\t')) ++val_start;
            val_end = end;
            while (val_end > val_start && (data[val_end - 1] == ' ' || data[val_end - 1] == '\t')) --val_end;

            if (match(data + pos, key_end - pos, "wifi_enabled")) {
                if (match(data + val_start, val_end - val_start, "0")) out->wifi_enabled = 0;
                else if (match(data + val_start, val_end - val_start, "1")) out->wifi_enabled = 1;
                else return 0;
            } else if (match(data + pos, key_end - pos, "log_level")) {
                if (match(data + val_start, val_end - val_start, "0")) out->log_level = 0;
                else if (match(data + val_start, val_end - val_start, "1")) out->log_level = 1;
                else if (match(data + val_start, val_end - val_start, "2")) out->log_level = 2;
                else return 0;
            }
        }
        pos = end;
        while (pos < length && (data[pos] == '\n' || data[pos] == '\r')) ++pos;
    }
    return 1;
}

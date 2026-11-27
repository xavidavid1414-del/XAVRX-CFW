#include <assert.h>
#include <string.h>
#include "xavrx/core.h"
#include "xavrx/config.h"
#include "xavrx/log.h"

int main(void)
{
    XavrxConfig cfg;
    XavrxLogger log;
    const char valid[] = "wifi_enabled=1\nlog_level=2\n";
    const char invalid[] = "wifi_enabled=yes\n";

    assert(xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_VALIDATING));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_READY));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_FAILED));
    assert(!xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_READY));
    assert(!xavrx_core_transition(XAVRX_STATE_READY, XAVRX_STATE_FAILED));

    xavrx_config_defaults(&cfg);
    assert(cfg.wifi_enabled == 0 && cfg.log_level == 1);
    assert(xavrx_config_parse(valid, sizeof(valid) - 1, &cfg));
    assert(cfg.wifi_enabled == 1 && cfg.log_level == 2);
    assert(!xavrx_config_parse(invalid, sizeof(invalid) - 1, &cfg));

    xavrx_log_init(&log);
    xavrx_log_write(&log, 1, "startup");
    assert(log.count == 1);
    assert(log.entries[0].level == 1);
    assert(strcmp(log.entries[0].message, "startup") == 0);

    return 0;
}

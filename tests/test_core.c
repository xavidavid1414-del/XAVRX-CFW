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
    const XavrxMemoryRange memory = {0x1000u, 0x1000u};
    const XavrxMemoryRange contained = {0x1800u, 0x0100u};
    const XavrxMemoryRange adjacent = {0x2000u, 0x0100u};
    const XavrxMemoryRange overlapping = {0x1ff0u, 0x0020u};
    const XavrxMemoryRange zero_size = {0x1000u, 0u};
    const XavrxMemoryRange overflow = {0xfffffff0u, 0x20u};
    const XavrxMemoryRange valid_map[] = {
        {0x1000u, 0x0100u}, {0x2000u, 0x0200u}, {0x3000u, 0x0100u}
    };
    const XavrxMemoryRange overlapping_map[] = {
        {0x1000u, 0x0200u}, {0x1100u, 0x0100u}
    };
    const XavrxMemoryRegion typed_valid[] = {
        {{0x4000u, 0x0100u}, XAVRX_MEMORY_AVAILABLE,
         XAVRX_MEMORY_READ | XAVRX_MEMORY_WRITE},
        {{0x5000u, 0x0100u}, XAVRX_MEMORY_RESERVED, XAVRX_MEMORY_READ},
        {{0x6000u, 0x0100u}, XAVRX_MEMORY_DEVICE,
         XAVRX_MEMORY_READ | XAVRX_MEMORY_WRITE}
    };
    const XavrxMemoryRegion typed_reserved_write = {
        {0x7000u, 0x0100u}, XAVRX_MEMORY_RESERVED,
        XAVRX_MEMORY_READ | XAVRX_MEMORY_WRITE
    };
    const XavrxMemoryRegion typed_device_exec = {
        {0x8000u, 0x0100u}, XAVRX_MEMORY_DEVICE,
        XAVRX_MEMORY_READ | XAVRX_MEMORY_EXEC
    };
    const XavrxMemoryRegion typed_unknown_kind = {
        {0x9000u, 0x0100u}, (XavrxMemoryKind)99, XAVRX_MEMORY_READ
    };
    const XavrxMemoryRegion typed_unknown_permission = {
        {0xa000u, 0x0100u}, XAVRX_MEMORY_AVAILABLE, 0x80u
    };
    const XavrxMemoryRegion typed_overlap[] = {
        {{0xb000u, 0x0200u}, XAVRX_MEMORY_AVAILABLE, XAVRX_MEMORY_READ},
        {{0xb100u, 0x0100u}, XAVRX_MEMORY_DEVICE, XAVRX_MEMORY_READ}
    };
    const XavrxMemoryRange invalid_map[] = {
        {0x1000u, 0u}
    };

    assert(xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_VALIDATING));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_READY));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_FAILED));
    assert(!xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_READY));
    assert(!xavrx_core_transition(XAVRX_STATE_READY, XAVRX_STATE_FAILED));

    assert(xavrx_memory_range_valid(memory));
    assert(!xavrx_memory_range_valid(zero_size));
    assert(!xavrx_memory_range_valid(overflow));
    assert(xavrx_memory_range_contains(memory, contained));
    assert(!xavrx_memory_range_contains(contained, memory));
    assert(!xavrx_memory_range_contains(memory, overflow));
    assert(xavrx_memory_ranges_overlap(memory, overlapping));
    assert(!xavrx_memory_ranges_overlap(memory, adjacent));
    assert(!xavrx_memory_ranges_overlap(memory, overflow));
    assert(xavrx_memory_map_valid(valid_map, 3));
    assert(!xavrx_memory_map_valid(overlapping_map, 2));
    assert(!xavrx_memory_map_valid(invalid_map, 1));
    assert(!xavrx_memory_map_valid(valid_map, 0));
    assert(!xavrx_memory_map_valid(0, 1));
    assert(!xavrx_memory_map_valid(valid_map, XAVRX_MEMORY_MAP_MAX_REGIONS + 1u));
    assert(xavrx_memory_region_valid(&typed_valid[0]));
    assert(xavrx_memory_region_valid(&typed_valid[1]));
    assert(xavrx_memory_region_valid(&typed_valid[2]));
    assert(!xavrx_memory_region_valid(0));
    assert(!xavrx_memory_region_valid(&typed_reserved_write));
    assert(!xavrx_memory_region_valid(&typed_device_exec));
    assert(!xavrx_memory_region_valid(&typed_unknown_kind));
    assert(!xavrx_memory_region_valid(&typed_unknown_permission));
    assert(xavrx_memory_region_map_valid(typed_valid, 3));
    assert(!xavrx_memory_region_map_valid(typed_overlap, 2));
    assert(!xavrx_memory_region_map_valid(0, 1));
    assert(!xavrx_memory_region_map_valid(typed_valid, 0));

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

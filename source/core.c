#include "xavrx/core.h"

#include <stdint.h>

int xavrx_core_transition(XavrxCoreState current, XavrxCoreState next)
{
    if (current == XAVRX_STATE_COLD && next == XAVRX_STATE_VALIDATING) {
        return 1;
    }

    if (current == XAVRX_STATE_VALIDATING &&
        (next == XAVRX_STATE_READY || next == XAVRX_STATE_FAILED)) {
        return 1;
    }

    return 0;
}

int xavrx_memory_range_valid(XavrxMemoryRange range)
{
    if (range.size == 0) {
        return 0;
    }

    return range.size <= UINT32_MAX - range.start;
}

int xavrx_memory_range_contains(XavrxMemoryRange outer, XavrxMemoryRange inner)
{
    uint32_t outer_end;
    uint32_t inner_end;

    if (!xavrx_memory_range_valid(outer) ||
        !xavrx_memory_range_valid(inner)) {
        return 0;
    }

    outer_end = outer.start + outer.size;
    inner_end = inner.start + inner.size;

    return inner.start >= outer.start && inner_end <= outer_end;
}

int xavrx_memory_ranges_overlap(XavrxMemoryRange a, XavrxMemoryRange b)
{
    uint32_t a_end;
    uint32_t b_end;

    if (!xavrx_memory_range_valid(a) || !xavrx_memory_range_valid(b)) {
        return 0;
    }

    a_end = a.start + a.size;
    b_end = b.start + b.size;

    return a.start < b_end && b.start < a_end;
}

int xavrx_memory_map_valid(const XavrxMemoryRange *regions, uint32_t count)
{
    uint32_t i;
    uint32_t j;

    if (regions == 0 || count == 0 || count > XAVRX_MEMORY_MAP_MAX_REGIONS) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (!xavrx_memory_range_valid(regions[i])) {
            return 0;
        }

        for (j = 0; j < i; ++j) {
            if (xavrx_memory_ranges_overlap(regions[i], regions[j])) {
                return 0;
            }
        }
    }

    return 1;
}

int xavrx_memory_region_valid(const XavrxMemoryRegion *region)
{
    if (region == 0 || !xavrx_memory_range_valid(region->range)) {
        return 0;
    }

    if ((region->permissions & ~XAVRX_MEMORY_PERMISSION_MASK) != 0) {
        return 0;
    }

    switch (region->kind) {
    case XAVRX_MEMORY_AVAILABLE:
        return 1;
    case XAVRX_MEMORY_RESERVED:
        return (region->permissions & (XAVRX_MEMORY_WRITE | XAVRX_MEMORY_EXEC)) == 0;
    case XAVRX_MEMORY_DEVICE:
        return (region->permissions & XAVRX_MEMORY_EXEC) == 0;
    default:
        return 0;
    }
}

int xavrx_memory_region_map_valid(const XavrxMemoryRegion *regions, uint32_t count)
{
    uint32_t i;
    uint32_t j;

    if (regions == 0 || count == 0 || count > XAVRX_MEMORY_MAP_MAX_REGIONS) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (!xavrx_memory_region_valid(&regions[i])) {
            return 0;
        }

        for (j = 0; j < i; ++j) {
            if (xavrx_memory_ranges_overlap(regions[i].range, regions[j].range)) {
                return 0;
            }
        }
    }

    return 1;
}

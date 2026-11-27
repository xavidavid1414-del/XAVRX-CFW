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

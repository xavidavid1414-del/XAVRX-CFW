#ifndef XAVRX_CORE_H
#define XAVRX_CORE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XAVRX_MEMORY_MAP_MAX_REGIONS 16u

typedef enum {
    XAVRX_STATE_COLD = 0,
    XAVRX_STATE_VALIDATING,
    XAVRX_STATE_READY,
    XAVRX_STATE_FAILED
} XavrxCoreState;

typedef struct {
    uint32_t start;
    uint32_t size;
} XavrxMemoryRange;

/* Returns non-zero only for an allowed one-way startup transition. */
int xavrx_core_transition(XavrxCoreState current, XavrxCoreState next);

/* Generic range helpers; these do not imply a physical hardware map. */
int xavrx_memory_range_valid(XavrxMemoryRange range);
int xavrx_memory_range_contains(XavrxMemoryRange outer, XavrxMemoryRange inner);
int xavrx_memory_ranges_overlap(XavrxMemoryRange a, XavrxMemoryRange b);

/* Validates a bounded list of non-empty, non-overlapping generic regions. */
int xavrx_memory_map_valid(const XavrxMemoryRange *regions, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif

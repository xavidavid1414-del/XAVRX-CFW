#ifndef XAVRX_CORE_H
#define XAVRX_CORE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

/*
 * Pure range helpers for host-side validation.
 * A range is valid only when size is non-zero and end does not overflow
 * the 32-bit address space. No hardware memory map is implied.
 */
int xavrx_memory_range_valid(XavrxMemoryRange range);
int xavrx_memory_range_contains(XavrxMemoryRange outer, XavrxMemoryRange inner);
int xavrx_memory_ranges_overlap(XavrxMemoryRange a, XavrxMemoryRange b);

#ifdef __cplusplus
}
#endif

#endif

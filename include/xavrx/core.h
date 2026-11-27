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

typedef enum {
    XAVRX_MEMORY_AVAILABLE = 1,
    XAVRX_MEMORY_RESERVED = 2,
    XAVRX_MEMORY_DEVICE = 3
} XavrxMemoryKind;

#define XAVRX_MEMORY_READ  0x01u
#define XAVRX_MEMORY_WRITE 0x02u
#define XAVRX_MEMORY_EXEC  0x04u
#define XAVRX_MEMORY_PERMISSION_MASK 0x07u

typedef struct {
    XavrxMemoryRange range;
    XavrxMemoryKind kind;
    uint32_t permissions;
} XavrxMemoryRegion;

/* Returns non-zero only for an allowed one-way startup transition. */
int xavrx_core_transition(XavrxCoreState current, XavrxCoreState next);

/* Generic range helpers; these do not imply a physical hardware map. */
int xavrx_memory_range_valid(XavrxMemoryRange range);
int xavrx_memory_range_contains(XavrxMemoryRange outer, XavrxMemoryRange inner);
int xavrx_memory_ranges_overlap(XavrxMemoryRange a, XavrxMemoryRange b);

/* Validates a bounded list of non-empty, non-overlapping generic regions. */
int xavrx_memory_map_valid(const XavrxMemoryRange *regions, uint32_t count);

/* Validates generic region kinds and conservative permission combinations. */
int xavrx_memory_region_valid(const XavrxMemoryRegion *region);
int xavrx_memory_region_map_valid(const XavrxMemoryRegion *regions, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif

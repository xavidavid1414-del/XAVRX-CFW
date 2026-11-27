#ifndef XAVRX_CORE_H
#define XAVRX_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    XAVRX_STATE_COLD = 0,
    XAVRX_STATE_VALIDATING,
    XAVRX_STATE_READY,
    XAVRX_STATE_FAILED
} XavrxCoreState;

/* Returns non-zero only for an allowed one-way startup transition. */
int xavrx_core_transition(XavrxCoreState current, XavrxCoreState next);

#ifdef __cplusplus
}
#endif

#endif

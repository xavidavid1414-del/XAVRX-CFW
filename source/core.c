#include "xavrx/core.h"

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

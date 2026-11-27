#include <assert.h>
#include "xavrx/core.h"

int main(void)
{
    assert(xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_VALIDATING));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_READY));
    assert(xavrx_core_transition(XAVRX_STATE_VALIDATING, XAVRX_STATE_FAILED));

    assert(!xavrx_core_transition(XAVRX_STATE_COLD, XAVRX_STATE_READY));
    assert(!xavrx_core_transition(XAVRX_STATE_READY, XAVRX_STATE_FAILED));
    assert(!xavrx_core_transition(XAVRX_STATE_FAILED, XAVRX_STATE_READY));
    assert(!xavrx_core_transition(XAVRX_STATE_READY, XAVRX_STATE_VALIDATING));

    return 0;
}

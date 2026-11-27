#include "xavrx/log.h"

void xavrx_log_init(XavrxLogger *logger)
{
    unsigned int i;
    if (!logger) return;
    logger->next = 0;
    logger->count = 0;
    for (i = 0; i < XAVRX_LOG_CAPACITY; ++i) {
        logger->entries[i].level = 0;
        logger->entries[i].message[0] = '\0';
    }
}

void xavrx_log_write(XavrxLogger *logger, unsigned int level, const char *message)
{
    unsigned int i = 0;
    XavrxLogEntry *entry;
    if (!logger || !message) return;
    entry = &logger->entries[logger->next];
    entry->level = level;
    while (i + 1 < XAVRX_LOG_MESSAGE_MAX && message[i]) {
        entry->message[i] = message[i];
        ++i;
    }
    entry->message[i] = '\0';
    logger->next = (logger->next + 1) % XAVRX_LOG_CAPACITY;
    if (logger->count < XAVRX_LOG_CAPACITY) ++logger->count;
}

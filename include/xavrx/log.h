#ifndef XAVRX_LOG_H
#define XAVRX_LOG_H

#define XAVRX_LOG_CAPACITY 8
#define XAVRX_LOG_MESSAGE_MAX 48

typedef struct {
    unsigned int level;
    char message[XAVRX_LOG_MESSAGE_MAX];
} XavrxLogEntry;

typedef struct {
    XavrxLogEntry entries[XAVRX_LOG_CAPACITY];
    unsigned int next;
    unsigned int count;
} XavrxLogger;

void xavrx_log_init(XavrxLogger *logger);
void xavrx_log_write(XavrxLogger *logger, unsigned int level, const char *message);

#endif

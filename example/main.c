#include <stdio.h>

#include <woodi.h>

// defining a wrapper

#define logger_wrapper(Self)                                                   \
    { int (*const log)(Self *const self, char *const str); }

WRAPPER(Logger, logger_wrapper);

#define logger_log(self, str) wrapper_call(log, self, str)

// defining implementations

typedef struct SimpleLogger {
    FILE *file;
} SimpleLogger;

void simple_logger_init(SimpleLogger *const self, FILE *file) {
    self->file = file;
}
void simple_logger_uninit(SimpleLogger *const self) { self->file = NULL; }

int simple_logger_log(SimpleLogger *const self, char *const str) {
    if (fputs(str, self->file) == EOF) return 1;

    return 0;
}

// wrapping

// wrap SimpleLogger (with) Logger (implementing) logger_wrapper, (call it)
// simple_logger_ww_logger, (with such functions:) { .log = simple_logger_log }
// if you wonder, 'ww' stands for 'wrap with'
WRAP(
    SimpleLogger,
    Logger,
    logger_wrapper,
    simple_logger_ww_logger,
    {
        .log = simple_logger_log,
    }
);

// usage

void log_helloworld(Logger *const logger) {
    logger_log(logger, "Hello world!");
}

int main() {
    SimpleLogger simple_logger;
    simple_logger_init(&simple_logger, stdout);

    // any logger can be injected here which is pretty cool
    Logger logger = simple_logger_ww_logger(&simple_logger);
    log_helloworld(&logger);

    simple_logger_uninit(&simple_logger);
    // logger should not be used from here, as it's object got uninited
}

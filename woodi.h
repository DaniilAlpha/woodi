#ifndef WOODI_H
#define WOODI_H

#define WRAPPER(Self, INTERFACE)                                               \
    typedef struct Self Self;                                                  \
    typedef struct Private##Self##Impl INTERFACE(Self) Private##Self##Impl;    \
    struct Self {                                                              \
        Private##Self##Impl const *vtbl;                                       \
        void *self;                                                            \
    }

#define WRAP_BODY(Wrapper, INTERFACE_FOR_SELF, ...)                            \
    {                                                                          \
        static struct INTERFACE_FOR_SELF const vtbl = __VA_ARGS__;             \
        return (Wrapper                                                        \
        ){.vtbl = (Private##Wrapper##Impl *)&vtbl, .self = self};              \
    }                                                                          \
    void ___i_want_you_to_put_semicolon_here_please(void)

#define WRAPPER_CALL(fn, wrapper, ...)                                         \
    (wrapper)->vtbl->fn((wrapper)->self, ##__VA_ARGS__)

#endif

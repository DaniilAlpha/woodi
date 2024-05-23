#ifndef WOODI_H
#define WOODI_H

#define WRAPPER(Self, interface_macro)                                         \
    typedef struct Self Self;                                                  \
    typedef struct Private##Self##Impl interface_macro(Self)                   \
        Private##Self##Impl;                                                   \
    struct Self {                                                              \
        Private##Self##Impl const *const vtbl;                                 \
        void *const self;                                                      \
    }

#define WRAP(Self, Wrapper, interface_macro, fn_name, ...)                     \
    Wrapper(fn_name)(Self *const self) {                                       \
        static struct interface_macro(Self) const vtbl = __VA_ARGS__;          \
        return (Wrapper                                                        \
        ){.vtbl = (Private##Wrapper##Impl *)&vtbl, .self = self};              \
    }                                                                          \
    void ___i_want_you_to_put_semicolon_here_please(void)

#define wrapper_call(fn, wrapper, ...)                                         \
    (wrapper)->vtbl->fn((wrapper)->self, ##__VA_ARGS__)

#endif

#define wrapper(Self, contents_macro)                                          \
    typedef struct Self Self;                                                  \
    typedef struct Self##Impl contents_macro(Self) Self##Impl;                 \
    struct Self {                                                              \
        Self##Impl const *const vtbl;                                          \
        void *const self;                                                      \
    }

#define wrap(Self, Wrapper, contents_macro, fn_name, ...)                      \
    Wrapper fn_name(Self *const self) {                                        \
        static struct contents_macro(Self) const vtbl = __VA_ARGS__;           \
        return (Wrapper){.vtbl = (Wrapper##Impl *)&vtbl, .self = self};        \
    }                                                                          \
    void ___i_want_you_to_put_semicolon_here_please()

#define wrapper_call(fn, wrapper, ...)                                         \
    (wrapper)->vtbl->fn((wrapper)->self, __VA_ARGS__)

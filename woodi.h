#ifndef WOODI_H
#define WOODI_H

#define WRAPPER(_SELF_T, _INTERFACE)                                           \
    typedef struct _SELF_T _SELF_T;                                            \
    struct Internal__##_SELF_T##Impl _INTERFACE(_SELF_T);                      \
    struct _SELF_T {                                                           \
        struct Internal__##_SELF_T##Impl const *__vtbl;                        \
        void *_self;                                                           \
    }

#define WRAP_BODY(_WRAPPER_T, _INTERFACE_FOR_SELF, ...)                        \
    {                                                                          \
        static struct _INTERFACE_FOR_SELF const vtbl = __VA_ARGS__;            \
        return (_WRAPPER_T){                                                   \
            .__vtbl = (struct Internal__##_WRAPPER_T##Impl *)&vtbl,            \
            ._self = self                                                      \
        };                                                                     \
    }                                                                          \
    void ___i_want_you_to_put_semicolon_here_please(void)

#define WRAPPER_CALL(_FN, _WRAPPER, ...)                                       \
    (_WRAPPER).__vtbl->_FN((_WRAPPER)._self, ##__VA_ARGS__)

#define WRAPPERS_EQUAL(_WRAPPER_A, _WRAPPER_B)                                 \
    ((_WRAPPER_A).__vtbl == (_WRAPPER_B).__vtbl &&                             \
     (_WRAPPER_A)._self == (_WRAPPER_B)._self)

#define WRAPPER_IS_NULL(_WRAPPER) (!(_WRAPPER).__vtbl && !(_WRAPPER)._self)

#endif

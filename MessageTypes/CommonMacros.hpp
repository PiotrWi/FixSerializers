#ifndef FIXSERIALIZERS_COMMONMACROS_HPP
#define FIXSERIALIZERS_COMMONMACROS_HPP

#define ADJUST_AND_RETURN_ON_ERROR( arg ) \
    bytesSerialized = arg;                \
    if (bytesSerialized < 0)              \
    {                                     \
        printf( #arg "\n");               \
        return -1;                        \
    }                                     \
    pos += bytesSerialized;               \

#define ADJUST_AND_RETURN_NULL_ON_ERROR( arg ) \
    bytesSerialized = arg;                \
    if (bytesSerialized < 0)              \
    {                                     \
        printf( #arg "\n");               \
        return NULL;                      \
    }                                     \
    pos += bytesSerialized;               \

#endif //FIXSERIALIZERS_COMMONMACROS_HPP

#include "utility.h"

int calculateCrc(const char* begin, int len)
{
    int crc = 0;
    const char* it = begin;

    for (; it != begin + len; ++it)
    {
        crc += *it;
    }
    return crc % 256;
}
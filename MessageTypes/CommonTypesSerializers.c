#include "CommonTypesSerializers.h"

#include <stdio.h>
#include <string.h>

int serializeTag(int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd)
{
    int bytesLeft = messageBufferEnd - messageBufferCurrentPosition;
    int bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%d=", fixTag);
    if (bytesToBeWritten >= bytesLeft)
    {
        return -1;
    }
    return bytesToBeWritten;
}

int serializeString(const char* inputString,
                       int fixTag,
                       char* messageBufferCurrentPosition,
                       const char* messageBufferEnd)
{
    int bytesWrittenByTag = serializeTag(fixTag, messageBufferCurrentPosition, messageBufferEnd);
    if (bytesWrittenByTag <= 0)
    {
        return -1;
    }

    messageBufferCurrentPosition += bytesWrittenByTag;
    int bytesLeft = messageBufferEnd - messageBufferCurrentPosition;
    int bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%s\001", inputString);
    if (bytesToBeWritten >= bytesLeft)
    {
        return -1;
    }
    return bytesWrittenByTag + bytesToBeWritten ;
}

int serializeOptionalString(OptionalString* inputString,
                            int fixTag,
                            char* messageBufferCurrentPosition,
                            const char* messageBufferEnd)
{
    if (inputString->isSet == 0)
    {
        return 0;
    }
    return serializeString(inputString->value, fixTag, messageBufferCurrentPosition, messageBufferEnd);
}

int serializeInt(int input,
                 int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd)
{
    int bytesWrittenByTag = serializeTag(fixTag, messageBufferCurrentPosition, messageBufferEnd);
    if (bytesWrittenByTag <= 0)
    {
        return -1;
    }

    messageBufferCurrentPosition += bytesWrittenByTag;
    int bytesLeft = messageBufferEnd - messageBufferCurrentPosition;
    int bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%d\001", input);
    if (bytesToBeWritten >= bytesLeft)
    {
        return -1;
    }
    return bytesWrittenByTag + bytesToBeWritten;
}

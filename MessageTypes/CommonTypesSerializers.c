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

int serializeOptionalInt(OptionalInt input,
                         int fixTag,
                         char* messageBufferCurrentPosition,
                         const char* messageBufferEnd)
{
    if (input.isSet == 0)
    {
        return 0;
    }
    return serializeInt(input.value, fixTag, messageBufferCurrentPosition, messageBufferEnd);
}

int serializeData(Data input,
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
    if (bytesLeft < input.lenght + 1)
    {
        return -1;
    }
    memcpy(messageBufferCurrentPosition, input.value, input.lenght);
    messageBufferCurrentPosition[input.lenght] = '\001';
    return bytesWrittenByTag + input.lenght + 1;
}

int serializeOptionalData(OptionalData input,
                          int fixTag,
                          char* messageBufferCurrentPosition,
                          const char* messageBufferEnd)
{
    if (input.isSet == 0)
    {
        return 0;
    }
    return serializeData(input.value, fixTag, messageBufferCurrentPosition, messageBufferEnd);
}

int serializeFixBoolean(FixBoolean input,
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
    if (bytesLeft < 2)
    {
        return -1;
    }

    if (input.value == 0)
    {
        messageBufferCurrentPosition[0] = 'N';
    }
    else
    {
        messageBufferCurrentPosition[0] = 'Y';
    }
    messageBufferCurrentPosition[1] = '\001';
    return bytesWrittenByTag + 2;
}

int serializeOptionalFixBoolean(OptionalFixBoolean input,
                                int fixTag,
                                char* messageBufferCurrentPosition,
                                const char* messageBufferEnd)
{
    if (input.isSet == 0)
    {
        return 0;
    }
    return serializeFixBoolean(input.value, fixTag, messageBufferCurrentPosition, messageBufferEnd);
}

int serializeUtcDate(UtcDate input,
                     char* messageBufferCurrentPosition,
                     const char* messageBufferEnd)
{
    int bytesLeft = messageBufferEnd - messageBufferCurrentPosition;
    int bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%04d%02d%02d",
                                    input.year, input.month, input.day);
    if (bytesToBeWritten >= bytesLeft)
    {
        return -1;
    }
    return bytesToBeWritten;
}

int serializeUTCTimeOnly(UTCTimeOnly input,
                         char* messageBufferCurrentPosition,
                         const char* messageBufferEnd)
{
    int bytesLeft = messageBufferEnd - messageBufferCurrentPosition;
    int bytesToBeWritten;
    if (input.milliseconds.isSet)
    {
        bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%02d:%02d:%02d.%03d",
                                        input.hour, input.minute, input.seconds, input.milliseconds.value);
    }
    else
    {
        bytesToBeWritten = snprintf(messageBufferCurrentPosition, bytesLeft, "%02d:%02d:%02d",
                                    input.hour, input.minute, input.seconds);
    }

    if (bytesToBeWritten >= bytesLeft)
    {
        return -1;
    }
    return bytesToBeWritten;
}

int serializeUtcTimeStamp(UtcTimeStamp input,
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

    int bytesWrittenByDate = serializeUtcDate(input.date, messageBufferCurrentPosition, messageBufferEnd);
    if (bytesWrittenByDate <= 0 || (messageBufferCurrentPosition + bytesWrittenByDate + 1) >= messageBufferEnd)
    {
        return -1;
    }
    messageBufferCurrentPosition[bytesWrittenByDate++] = '-';
    messageBufferCurrentPosition += bytesWrittenByDate;

    int bytesWrittenByTime = serializeUTCTimeOnly(input.time, messageBufferCurrentPosition, messageBufferEnd);
    if (bytesWrittenByTime <= 0 || (messageBufferCurrentPosition + bytesWrittenByTime + 1) >= messageBufferEnd)
    {
        return -1;
    }
    messageBufferCurrentPosition[bytesWrittenByTime++] = '\001';

    return bytesWrittenByTag + bytesWrittenByDate + bytesWrittenByTime;
}

int serializeOptionalUtcTimeStamp(OptionalUtcTimeStamp input,
                                 int fixTag,
                                 char* messageBufferCurrentPosition,
                                 const char* messageBufferEnd)
{
    if (input.isSet == 0)
    {
        return 0;
    }
    return serializeUtcTimeStamp(input.value, fixTag, messageBufferCurrentPosition, messageBufferEnd);
}
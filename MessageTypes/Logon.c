#include "Logon.h"

#include <stdio.h>
#include <string.h>

#include "Tags.h"
#include "CommonMacros.hpp"
#include "CommonTypesSerializers.h"

void fixs_logon_init(Logon* logon)
{
    memset(logon, 0, sizeof(Logon) );
}
int fixs_logon_serialize(Logon* logon,
                          char* messageBuffer,
                          const char* messageBufferEnd)
{
    int pos = 0;
    int bytesSerialized = 0;

    ADJUST_AND_RETURN_ON_ERROR(serializeInt(logon->encryptMethod, EncryptMethodTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeInt(logon->heartBtInt, HeartBtIntTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(logon->rawDataLength, RawDataLengthTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalData(logon->rawData, RawDataTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalFixBoolean(logon->resetSeqNumFlag, ResetSeqNumFlagTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(logon->nextExpectedMsgSeqNum, NextExpectedMsgSeqNumTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(logon->maxMessageSize, MaxMessageSizeTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalFixBoolean(logon->testMessageIndicator, TestMessageIndicatorTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&logon->username, UsernameTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&logon->password, PasswordTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&logon->defaultApplVerID, DefaultApplVerIDTag, messageBuffer + pos, messageBufferEnd));

    return pos;
}
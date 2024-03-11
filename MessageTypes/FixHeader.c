#include "FixHeader.h"

#include <stdio.h>
#include <string.h>
#include "CommonTypesSerializers.h"
#include "CommonMacros.hpp"
#include "Tags.h"

const int bytesReservedForBeginStringAndBodyLenght = 70;

void fixs_fixHeader_init(FixHeader* header)
{
    memset(header, 0, sizeof(FixHeader) );
}

int serializePastBodyLengthFields(FixHeader* header,
                                  char* messageBuffer,
                                  const char* messageBufferEnd)
{
    int pos = bytesReservedForBeginStringAndBodyLenght;
    int bytesSerialized = 0;

    ADJUST_AND_RETURN_ON_ERROR(serializeString(header->msgType, MsgTypeTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeString(header->senderCompID, SenderCompIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeString(header->targetCompID, TargetCompIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->onBehalfOfCompID, OnBehalfOfCompIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->deliverToCompID, DeliverToCompIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(header->secureDataLen, SecureDataLenTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalData(header->secureData, SecureDataTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeInt(header->msgSeqNum, MsgSeqNumTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->senderSubID, SenderSubIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->senderLocationID, SenderLocationIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->targetSubID, TargetSubIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->targetLocationID, TargetLocationIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->onBehalfOfSubID, OnBehalfOfSubIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->onBehalfOfLocationID, OnBehalfOfLocationIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->deliverToSubID, DeliverToSubIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->deliverToLocationID, DeliverToLocationIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalFixBoolean(header->possDupFlag, PossDupFlagTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalFixBoolean(header->possResend, PossResendTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeUtcTimeStamp(header->sendingTime, SendingTimeTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalUtcTimeStamp(header->origSendingTime, OrigSendingTimeTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(header->xmlDataLen, XmlDataLenTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalData(header->xmlData, XmlDataTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->messageEncoding, MessageEncodingTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalInt(header->lastMsgSeqNumProcessed, LastMsgSeqNumProcessedTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalUtcTimeStamp(header->timeStampOnBehalfOfSendingTime, OrigSendingTimeTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->applVerID, ApplVerIDTag, messageBuffer + pos, messageBufferEnd));
    ADJUST_AND_RETURN_ON_ERROR(serializeOptionalString(&header->cstmApplVerID, CstmApplVerIDTag, messageBuffer + pos, messageBufferEnd));

    return pos;
}

char* serializeAndFinalize(FixHeader* header,
                           int* messageLenght,
                           char* messageBufferBegin)
{
    int pos = 0;
    int bytesSerialized = 0;
    char* bufferEnd = messageBufferBegin + bytesReservedForBeginStringAndBodyLenght;

    header->bodyLength = *messageLenght - bytesReservedForBeginStringAndBodyLenght;

    ADJUST_AND_RETURN_NULL_ON_ERROR(serializeString(header->beginString, BeginStringTag, messageBufferBegin + pos, bufferEnd));
    ADJUST_AND_RETURN_NULL_ON_ERROR(serializeInt(header->bodyLength, BodyLengthTag, messageBufferBegin + pos, bufferEnd));

    int bytesToMove = bytesReservedForBeginStringAndBodyLenght - pos;
    char* newMessageBegin = messageBufferBegin + bytesToMove;
    memcpy(newMessageBegin, messageBufferBegin, pos);

    *messageLenght -= bytesToMove;
    messageLenght += pos;

    return newMessageBegin;
}

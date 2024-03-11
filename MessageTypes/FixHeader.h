#ifndef FIXSERIALIZERS_HEADER_H
#define FIXSERIALIZERS_HEADER_H

#include "Types.h"

typedef struct _FixHeader
{
    char beginString[50];
    int bodyLength;
    char msgType[3];
    char senderCompID[50];
    char targetCompID[50];
    OptionalString onBehalfOfCompID;
    OptionalString deliverToCompID;
    OptionalInt secureDataLen;
    OptionalData secureData;
    int msgSeqNum;
    OptionalString senderSubID;
    OptionalString senderLocationID;
    OptionalString targetSubID;
    OptionalString targetLocationID;
    OptionalString onBehalfOfSubID;
    OptionalString onBehalfOfLocationID;
    OptionalString deliverToSubID;
    OptionalString deliverToLocationID;
    OptionalFixBoolean possDupFlag;
    OptionalFixBoolean possResend;
    UtcTimeStamp sendingTime;
    OptionalUtcTimeStamp origSendingTime;
    OptionalInt	xmlDataLen;
    OptionalData xmlData;
    OptionalString messageEncoding;
    OptionalInt	lastMsgSeqNumProcessed;
    OptionalUtcTimeStamp timeStampOnBehalfOfSendingTime;
    OptionalString applVerID;
    OptionalString cstmApplVerID;
} FixHeader;

void fixs_fixHeader_init(FixHeader* header);

/**
 * \brief Serializes FixHeader
 *
 * Serializes all the fields fulfilled in header. It also reserves some bytes to begin of
 *      message (beginString and bodyLength)
 *
 * Null terminated character after SOH is not guaranteed.
 *
 * @param header pointer to FixHeader to be serialized.
 * @param messageBuffer Message buffer where to place whole serialized data.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer (\0 not counted).
 */
int serializePastBodyLengthFields(FixHeader* header,
                                   char* messageBuffer,
                                   const char* messageBufferEnd);

/**
 * \brief Serializes beginString and bodyLength fields
 *
 * Serializes beginString and bodyLength fields after whole message is serialized and bodyLength can be calculated.
 * Algorithm is like bellow:
 *  - Firstly fullfill messageBufferBegin tag at the begin of buffer
 *      (Assumption is that some fields was reserved for this purpose in serializePastBodyLengthFields call).
 *  - Then fullfill bodyLength tag.
 *  - Move created tags to other postion to remove gap.
 *  - New message start pointer is returned.
 *  - messageLenght is adjusted
 *
 *  User shall use messageLenght parameter set by this funtion.
 *
 * Null terminated character after SOH is not guaranteed.
 *
 * @param header pointer to FixHeader to be serialized.
 * @param messageLenght In/Out parameter. In input it shall contain serializePastBodyLengthFields + serializedBodyLen.
 *                      At output it contains header + body lenght after adjustment.
 *
 * @param messageBufferBegin pointer to position where message buffer starts.
 * \return pointer to new start position of message.
 */
char* serializeAndFinalize(FixHeader* header,
                          int* messageLenght,
                          char* messageBufferBegin);

#endif //FIXSERIALIZERS_HEADER_H

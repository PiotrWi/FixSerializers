#ifndef FIXSERIALIZERS_LOGON_HPP
#define FIXSERIALIZERS_LOGON_HPP

#include "Types.h"

typedef struct _Logon
{
    int encryptMethod;
    int heartBtInt;
    OptionalInt rawDataLength;
    OptionalData rawData;
    OptionalFixBoolean resetSeqNumFlag;
    OptionalInt nextExpectedMsgSeqNum;
    OptionalInt maxMessageSize;
    OptionalFixBoolean 	testMessageIndicator;
    OptionalString username;
    OptionalString 	password;
    OptionalString defaultApplVerID;
} Logon;

void fixs_logon_init(Logon* logon);
int fixs_logon_serialize(Logon* logon,
                          char* messageBuffer,
                          const char* messageBufferEnd);


#endif //FIXSERIALIZERS_LOGON_HPP

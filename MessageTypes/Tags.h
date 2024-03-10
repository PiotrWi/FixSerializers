//
// Created by pioter on 10.03.24.
//

#ifndef FIXSERIALIZERS_TAGS_H
#define FIXSERIALIZERS_TAGS_H

typename enum _FixTag
{
    BeginStringTag = 8,
    BodyLengthTag = 9,
    MsgSeqNumTag = 34,
    MsgTypeTag = 35,
    PossDupFlagTag = 43,
    SenderCompIDTag = 49,
    SenderSubIDTag = 50,
    SendingTimeTag = 52,
    TargetCompIDTag = 56,
    TargetSubIDTag = 57,
    SecureDataLenTag = 90,
    SecureDataTag = 91,
    PossResendTag = 97,
    OnBehalfOfCompIDTag = 115,
    OnBehalfOfSubIDTag = 116,
    OrigSendingTimeTag = 122,
    DeliverToCompIDTag = 128,
    DeliverToSubIDTag = 129,
    SenderLocationIDTag = 142,
    TargetLocationIDTag = 143,
    OnBehalfOfLocationIDTag = 144,
    DeliverToLocationIDTag = 145,
    XmlDataLenTag = 212,
    XmlDataTag = 213,
    MessageEncodingTag = 347,
    LastMsgSeqNumProcessedTag = 369,
    OnBehalfOfSendingTimeTag = 370,
    ApplVerIDTag = 1128,
    CstmApplVerIDTag = 1129,
} FixTag;

#endif //FIXSERIALIZERS_TAGS_H

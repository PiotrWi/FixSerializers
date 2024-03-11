//
// Created by pioter on 11.03.24.
//

#ifndef FIXSERIALIZERS_MESSAGE_H
#define FIXSERIALIZERS_MESSAGE_H

#include "FixHeader.h"

typedef struct _Tail
{
    OptionalInt SignatureLength;
    OptionalData Signature;
    int	CheckSum;
} Tail;

void fixs_tail_init(Tail* header);
int fixs_tail_serialize(Tail* header,
                        char* messageBuffer,
                        const char* messageBufferEnd);
char* fixs_tail_finalize(FixHeader* header,
                         int* messageLenght,
                         char* messageBufferBegin);

typedef struct _Message
{
    FixHeader header;
    void* body;
    Tail tail;
} Message;

void fixs_serialize(Message* message,
               char* messageBuffer,
               const char* messageBufferEnd);

#endif //FIXSERIALIZERS_MESSAGE_H

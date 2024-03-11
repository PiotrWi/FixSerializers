#ifndef FIXSERIALIZERS_TYPES_HPP
#define FIXSERIALIZERS_TYPES_HPP

typedef struct _OptionalInt
{
    int isSet;
    int value;
} OptionalInt;

typedef struct _OptionalString
{
    int isSet;
    char value[50];
} OptionalString;

typedef struct _Data
{
    int lenght;
    unsigned char* value;
} Data;

typedef struct _OptionalData
{
    int isSet;
    Data value;
} OptionalData;

typedef struct _FixBoolean
{
    char value;
} FixBoolean;

typedef struct _OptionalFixBoolean
{
    int isSet;
    FixBoolean value;
} OptionalFixBoolean;

typedef struct _UtcDate
{
    unsigned short year;
    unsigned char month;
    unsigned char day;
} UtcDate;

typedef struct _UTCTimeOnly
{
    unsigned char hour;
    unsigned char minute;
    unsigned char seconds;
    OptionalInt milliseconds;
} UTCTimeOnly;

typedef struct _UtcTimeStamp
{
    UtcDate date;
    UTCTimeOnly time;
} UtcTimeStamp;

typedef struct _OptionalUtcTimeStamp
{
    int isSet;
    UtcTimeStamp value;
} OptionalUtcTimeStamp;


#endif //FIXSERIALIZERS_TYPES_HPP

/*
 * NOTE: Once null terminated character will not be added to serialized string, buffer sizes can be decreased.
 */

#define BOOST_TEST_MODULE Common types serializers tests

#include <boost/test/included/unit_test.hpp>
#include <string.h>
#include <string>

extern "C"
{
    #include "../MessageTypes/CommonTypesSerializers.h"
}

using namespace std;

BOOST_AUTO_TEST_CASE(serializeTagSucessfully)
{
    const int bufferLen = 4;
    char buffer[bufferLen];
    int tag = 11;

    auto bytesWritten = serializeTag(tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11="s);
}

BOOST_AUTO_TEST_CASE(notSerialzeIfNotEnoughtPlaceBecauseOfNullTerminate)
{
    const int bufferLen = 3;
    char buffer[bufferLen];
    int tag = 11;

    auto bytesWritten = serializeTag(tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten == -1);
}

BOOST_AUTO_TEST_CASE(serializeNullTerminatedString)
{
    const int bufferLen = 12;
    char buffer[bufferLen];
    int tag = 11;
    auto inputStr = "example";

    auto bytesWritten = serializeString(inputStr, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=example\001"s);
}

BOOST_AUTO_TEST_CASE(notSerializeOptionalStringNotSet)
{
    const int bufferLen = 12;
    char buffer[bufferLen];
    int tag = 11;
    auto input = OptionalString{0, {}};

    auto bytesWritten = serializeOptionalString(&input, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten == 0);
}

BOOST_AUTO_TEST_CASE(shallNotSerializeNullTerminatedStringIfBufferIsToSmall)
{
    const int bufferLen = 11;
    char buffer[bufferLen];
    int tag = 11;
    auto inputStr = "example";

    auto bytesWritten = serializeString(inputStr, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten == -1);
}

BOOST_AUTO_TEST_CASE(serializeInteger)
{
    const int bufferLen = 7;
    char buffer[bufferLen];
    int tag = 11;
    auto value = 16;

    auto bytesWritten = serializeInt(value, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=16\001"s);
}

BOOST_AUTO_TEST_CASE(notSerializeOptionalIntegerIfNotSet)
{
    const int bufferLen = 7;
    char buffer[bufferLen];
    int tag = 11;
    OptionalInt value;
    value.isSet = false;

    auto bytesWritten = serializeOptionalInt(value, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten == 0);
}

BOOST_AUTO_TEST_CASE(serializeFixBooleans)
{
    const int bufferLen = 7;
    char buffer[bufferLen];
    int tag = 11;
    FixBoolean value;
    value.value = 0;

    auto bytesWritten = serializeFixBoolean(value, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=N\001"s);

    value.value = 1;
    bytesWritten = serializeFixBoolean(value, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=Y\001"s);
}

BOOST_AUTO_TEST_CASE(serializeUtcTimeStampWithNoMilliseconds)
{
    const int bufferLen = 30;
    char buffer[bufferLen];
    int tag = 11;
    UtcTimeStamp value;
    value.date.year = 1998;
    value.date.month = 2;
    value.date.day = 3;

    value.time.hour = 3;
    value.time.minute = 9;
    value.time.seconds = 2;
    value.time.milliseconds.isSet = 0;

    auto bytesWritten = serializeUtcTimeStamp(value, tag, buffer, buffer+bufferLen);
    BOOST_CHECK(bytesWritten >= 0);
    BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=19980203-03:09:02\001"s);
}

BOOST_AUTO_TEST_CASE(serializeUtcTimeStampWithMilliseconds)
{
        const int bufferLen = 30;
        char buffer[bufferLen];
        int tag = 11;
        UtcTimeStamp value;
        value.date.year = 1998;
        value.date.month = 2;
        value.date.day = 3;

        value.time.hour = 3;
        value.time.minute = 9;
        value.time.seconds = 2;
        value.time.milliseconds.isSet = 1;
        value.time.milliseconds.value = 2;
        auto bytesWritten = serializeUtcTimeStamp(value, tag, buffer, buffer+bufferLen);
        BOOST_CHECK(bytesWritten >= 0);
        BOOST_CHECK_EQUAL(std::string(buffer, bytesWritten), "11=19980203-03:09:02.002\001"s);
}

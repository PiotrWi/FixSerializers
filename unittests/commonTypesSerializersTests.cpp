/*
 * NOTE: Once null terminated character will not be added to serialized string, buffer sizes can be decreased.
 */

#define BOOST_TEST_MODULE Utility tests
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

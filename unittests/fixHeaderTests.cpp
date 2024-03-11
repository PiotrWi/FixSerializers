#define BOOST_TEST_MODULE FIX header tests

#include <boost/test/included/unit_test.hpp>
#include <string.h>
#include <string>

extern "C"
{
#include "../MessageTypes/FixHeader.h"
}

using namespace std;

BOOST_AUTO_TEST_CASE(serializeExampleHeaderSuccessfully)
{
    char msgBuffer[5000];

    FixHeader header;
    fixs_fixHeader_init(&header);
    sprintf(header.beginString, "%s", "FIX.4.2");
    sprintf(header.msgType, "%s", "A");
    sprintf(header.senderCompID, "%s", "BuySide");
    sprintf(header.targetCompID, "%s", "SellSide");
    header.msgSeqNum = 1;
    header.sendingTime = UtcTimeStamp {{2019, 6, 5}, {11, 27, 6, {1, 897}}};

    std::string fixHeaderExpectedPostPart = "35=A\00149=BuySide\00156=SellSide\00134=1\00152=20190605-11:27:06.897\001";
    std::string fixHeaderExpected = "8=FIX.4.2\0019=58\001"+fixHeaderExpectedPostPart;

    int len = serializePastBodyLengthFields(&header, msgBuffer, msgBuffer+5000);
    BOOST_CHECK(len >= 0);
    BOOST_CHECK_EQUAL(fixHeaderExpectedPostPart, std::string(msgBuffer + 70, len-70));

    char *msgBegin = serializeAndFinalize(&header, &len, msgBuffer);
    BOOST_CHECK(len >= 0);
    BOOST_CHECK_EQUAL(fixHeaderExpected, std::string(msgBegin, len));
}
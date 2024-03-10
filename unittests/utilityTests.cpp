#define BOOST_TEST_MODULE Utility tests
#include <boost/test/included/unit_test.hpp>
#include <string.h>

extern "C"
{
    #include "../utility.h"
}

BOOST_AUTO_TEST_CASE(first_test)
{
    const char* messageBody = "8=FIX.4.2\0019=76\00135=A\00149=BuySide\00156=SellSide\00134=1\00152=20190605-11:27:06.897\00198=0\001108=30\001141=Y\001";
    const int messageLen = strlen(messageBody);

    BOOST_CHECK_EQUAL(calculateCrc(messageBody, messageLen), 8);
}
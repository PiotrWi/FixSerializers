#ifndef FIXSERIALIZERS_UTILITY_H
#define FIXSERIALIZERS_UTILITY_H

/**
 * \brief calculate fix crc from message string
 *
 * Calculates FIX crc of message. See: https://www.onixs.biz/fix-dictionary/4.2/app_b.html
 *
 * Example of usage:
 * // SOH as \001
 * const char* messageBody = "8=FIX.4.2\0019=76\00135=A\00149=BuySide\00156=SellSide\00134=1\00152=20190605-11:27:06.897\00198=0\001108=30\001141=Y\001";
 * const int messageLen = strlen(messageBody);
 * int crc = calculateCrc(messageBody, messageLen);
 *
 * @param begin pointer to begin of a string
 * @param len lenght of a string.
 */
int calculateCrc(const char* begin, int len);

#endif //FIXSERIALIZERS_UTILITY_H

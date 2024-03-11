#ifndef FIXSERIALIZERS_COMMONTYPESSERIALIZERS_H_
#define FIXSERIALIZERS_COMMONTYPESSERIALIZERS_H_

#include "Types.h"

/**
 * \brief Serializes tag number plus '=' to message buffer.
 *
 * Serializes tag number plus '=' to message buffer.
 * EG: serializeString_50(14, buffer, ptr+100) shall append to message: 14=.
 *
 * Null terminated character after SOH is not guaranteed.
 *
 * @param fixTag fix tag to compose message.
 * @param messageBufferCurrentPosition position on message string where to append tag and value string.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer including SOH (null terminated won't be counted).
 */
int serializeTag(int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd);

/**
 * \brief Serializes string field to message buffer.
 *
 * Serializes string of length up to 50 into message in position given by argument.
 * EG: serializeString_50("Example", 14, buffer, ptr+100) shall append to message: 14=Example|.
 *
 * Message string after procedure will be SOH terminated. Null terminated character after SOH is not guaranteed.
 *
 * @param inputString Null terminated or SOH terminated string.
 * @param fixTag fix tag to compose message.
 * @param messageBufferCurrentPosition position on message string where to append tag and value string.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer including SOH (null terminated won't be counted).
 */
int serializeString(const char* inputString,
                       int fixTag,
                       char* messageBufferCurrentPosition,
                       const char* messageBufferEnd);

/**
 * \brief Serializes optional string field to message buffer.
 *
 * If field is not set, skip processing and 0 is returned
 */
int serializeOptionalString(OptionalString* inputString,
                    int fixTag,
                    char* messageBufferCurrentPosition,
                    const char* messageBufferEnd);

/**
 * \brief Serializes int field to message buffer.
 *
 * Serializes integer value into message in position given by argument.
 * EG: serializeInt(15, 14, buffer, ptr+100) shall append to message: 14=15|.
 *
 * Message string after procedure will be SOH terminated. Null terminated character after SOH is not guaranteed.
 *
 * @param input Null terminated or SOH terminated string.
 * @param fixTag fix tag to compose message.
 * @param messageBufferCurrentPosition position on message string where to append tag and value string.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer including SOH (null terminated won't be counted).
 */
int serializeInt(int input,
                 int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd);

/**
 * \brief Serializes optional Int field to message buffer.
 *
 * If field is not set, skip processing and 0 is returned
 */
int serializeOptionalInt(OptionalInt input,
                 int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd);

/**
 * \brief Serializes DATA field to message buffer.
 *
 * Message string after procedure will be SOH terminated. Null terminated character after SOH is not guaranteed.
 *
 * @param input Data to be serialized
 * @param fixTag fix tag to compose message.
 * @param messageBufferCurrentPosition position on message string where to append tag and value string.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer including SOH (null terminated won't be counted).
 */
int serializeData(Data input,
                 int fixTag,
                 char* messageBufferCurrentPosition,
                 const char* messageBufferEnd);

/**
 * \brief Serializes optional Data field to message buffer.
 *
 * If field is not set, skip processing and 0 is returned
 */
int serializeOptionalData(OptionalData input,
                         int fixTag,
                         char* messageBufferCurrentPosition,
                         const char* messageBufferEnd);

/**
 * \brief Serializes booleam field to message buffer.
 *
 * 0(FALSE) value is serialized as T,
 * 1(TRUE) value is serialized as Y,
 *
 * Message string after procedure will be SOH terminated. Null terminated character after SOH is not guaranteed.
 *
 * @param input Data to be serialized
 * @param fixTag fix tag to compose message.
 * @param messageBufferCurrentPosition position on message string where to append tag and value string.
 * @param messageBufferEnd pointer to position where message buffer ends. In case if message buffer is to little,
 *                          an error will occur.
 * \return number of characters written to buffer including SOH (null terminated won't be counted).
 */
int serializeFixBoolean(FixBoolean input,
                  int fixTag,
                  char* messageBufferCurrentPosition,
                  const char* messageBufferEnd);

/**
 * \brief Serializes optional Data field to message buffer.
 *
 * If field is not set, skip processing and 0 is returned
 */
int serializeOptionalFixBoolean(OptionalFixBoolean input,
                          int fixTag,
                          char* messageBufferCurrentPosition,
                          const char* messageBufferEnd);

int serializeUtcDate(UtcDate input,
                     char* messageBufferCurrentPosition,
                     const char* messageBufferEnd);

int serializeUTCTimeOnly(UTCTimeOnly input,
                     char* messageBufferCurrentPosition,
                     const char* messageBufferEnd);

int serializeUtcTimeStamp(UtcTimeStamp input,
                          int fixTag,
                          char* messageBufferCurrentPosition,
                          const char* messageBufferEnd);

int serializeOptionalUtcTimeStamp(OptionalUtcTimeStamp input,
                          int fixTag,
                          char* messageBufferCurrentPosition,
                          const char* messageBufferEnd);

#endif //FIXSERIALIZERS_COMMONTYPESSERIALIZERS_H

#include "const.h"

std::string uint32ToHex(uint32_t value)
{
    const char *hexChars = "0123456789ABCDEF";
    std::string hexStr;
    hexStr.reserve(8);
    for (int i = 3; i >= 0; --i)
    {
        uint8_t byte = (value >> (i * 8)) & 0xFF;
        hexStr.push_back(hexChars[(byte >> 4) & 0x0F]);
        hexStr.push_back(hexChars[byte & 0x0F]);
    }
    return hexStr;
}
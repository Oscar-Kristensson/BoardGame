#include "utils.h"
#include <climits>

bool BoardGame::utils::convertToBool(const std::string& str)
{
    if (str == "true")
        return true;

    return false;
}

bool BoardGame::utils::convertToUint16(const std::string& str, uint16_t& result) {
    try {
        unsigned long temp = std::stoul(str);
        if (temp > UINT16_MAX) {
            return false; // Out of range
        }
        result = static_cast<uint16_t>(temp);
        return true;
    }
    catch (...) {
        return false; // Invalid format or other error
    }
}

bool BoardGame::utils::convertToUint8(const std::string& str, uint8_t& result) {
    try {
        unsigned long temp = std::stoul(str);
        if (temp > UINT8_MAX) {
            return false; // Out of range
        }
        result = static_cast<uint8_t>(temp);
        return true;
    }
    catch (...) {
        return false; // Invalid format or other error
    }
}

bool BoardGame::utils::convertToInt(const std::string& str, int& result) {
    try {
        long temp = std::stol(str);  // std::stol returns a long
        if (temp < INT_MIN || temp > INT_MAX) {
            return false; // Out of int range
        }
        result = static_cast<int>(temp);
        return true;
    }
    catch (...) {
        return false; // Invalid format or other error
    }
}



Color BoardGame::utils::convertHEXToRGB(std::string& hex)
{
    unsigned int hexValue;
    std::stringstream ss;
    
    // Remove '#' if present
    if (hex[0] == '#') {
        ss << std::hex << hex.substr(1);
    }
    else {
        ss << std::hex << hex;
    }

    ss >> hexValue;

    // Extract RGB values
    uint8_t red = (hexValue >> 16) & 0xFF;   // Extract red component
    uint8_t green = (hexValue >> 8) & 0xFF;  // Extract green component
    uint8_t blue = hexValue & 0xFF;          // Extract blue component

    // If alpha exists in the hex code, use it; otherwise, default to 255 (fully opaque)
    int alpha = (hex.length() == 9) ? (hexValue >> 24) & 0xFF : 255;

    return Color{ (unsigned char)red, (unsigned char)green, (unsigned char)blue, (unsigned char)alpha };
}


int BoardGame::utils::abs(int value)
{
    if (value < 0)
        return -value;
    return value;
}

int BoardGame::utils::max(int a, int b)
{
    if (a < b)
        return b;
    return a;
}

int BoardGame::utils::min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

/*
201
201/100=2,01
2,01 -> 2
2,01 - 2 = 0,01
*/

int BoardGame::utils::ceil(int value, uint8_t base)
{
    float dividedValue = (float)value / base;
    int integerDivided = (int)(dividedValue);
    int newValue = integerDivided * base;

    return newValue + base;
}




int BoardGame::utils::floor(int value, uint8_t base)
{
    float dividedValue = (float)value / base;
    int integerDivided = (int)(dividedValue);
    int newValue = integerDivided * base;

    return newValue;
}

int BoardGame::utils::toClosestHigher(int value, uint8_t base)
{
    int rest = value % (int)base;

    if (rest == 0)
        return value;

    return value + (base - rest);
}

int BoardGame::utils::toClosestLower(int value, uint8_t base)
{
    int rest = value % (int)base;

    return value - rest;
}


Color BoardGame::utils::brighten(Color color, float factor) {
    if (factor < 0)
        return color;
    color.r = (unsigned char)fmin(color.r + 255 * factor, 255);
    color.g = (unsigned char)fmin(color.g + 255 * factor, 255);
    color.b = (unsigned char)fmin(color.b + 255 * factor, 255);
    return color;
}




std::string BoardGame::utils::convertRGBToHEX(Color color) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    ss << std::setw(2) << static_cast<int>(color.r);
    ss << std::setw(2) << static_cast<int>(color.g);
    ss << std::setw(2) << static_cast<int>(color.b);
    return ss.str();
}
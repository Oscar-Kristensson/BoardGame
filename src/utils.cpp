#include "utils.h"

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
};
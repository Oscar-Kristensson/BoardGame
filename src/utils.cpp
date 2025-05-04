#include "utils.h"



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
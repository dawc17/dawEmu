#include "Cartridge.h"

#include <algorithm>
#include <fstream>
#include <iterator>

namespace dawemu::cart {

bool Cartridge::loadFromFile(const std::string& path)
{
    std::ifstream input(path, std::ios::binary);
    if (!input) {
        return false;
    }

    std::vector<std::uint8_t> bytes(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>()
    );

    return loadFromBytes(std::move(bytes));
}

bool Cartridge::loadFromBytes(std::vector<std::uint8_t> data)
{
    if (data.size() < 0x150) {
        return false;
    }

    rom_ = std::move(data);
    return true;
}

std::uint8_t Cartridge::read(std::uint16_t address) const
{
    if (address < rom_.size()) {
        return rom_[address];
    }

    return 0xFF;
}

void Cartridge::write(std::uint16_t, std::uint8_t)
{
}

std::string Cartridge::title() const
{
    if (rom_.size() < 0x144) {
        return {};
    }

    std::string result;
    result.reserve(16);

    for (std::size_t i = 0x134; i <= 0x143 && i < rom_.size(); i++) {
        const char ch = static_cast<char>(rom_[i]);
        if (ch == '\0') {
            break;
        }
        result.push_back(ch);
    }

    return result;
}

std::uint8_t Cartridge::cartridgeType() const
{
    if (rom_.size() <= 0x147) {
        return 0x00;
    }
    return rom_[0x147];
}

std::uint8_t Cartridge::romSizeCode() const
{
    if (rom_.size() <= 0x148) {
        return 0x00;
    }
    return rom_[0x148];
}

std::uint8_t Cartridge::ramSizeCode() const
{
    if (rom_.size() <= 0x149) {
        return 0x00;
    }
    return rom_[0x149];
}

std::size_t Cartridge::romByteSize() const
{
    return rom_.size();
}

}
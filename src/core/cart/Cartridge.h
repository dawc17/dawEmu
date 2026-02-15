#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace dawemu::cart {

class Cartridge {
public:
    bool loadFromFile(const std::string& path);
    bool loadFromBytes(std::vector<std::uint8_t> data);

    std::uint8_t read(std::uint16_t address) const;
    void write(std::uint16_t address, std::uint8_t value);

    [[nodiscard]] std::string title() const;
    [[nodiscard]] std::uint8_t cartridgeType() const;
    [[nodiscard]] std::uint8_t romSizeCode() const;
    [[nodiscard]] std::uint8_t ramSizeCode() const;
    [[nodiscard]] std::size_t romByteSize() const;

private:
    std::vector<std::uint8_t> rom_{};
};

}
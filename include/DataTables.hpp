#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <string>
#include <vector>

namespace sf
{
    class Sprite;
    class Texture;
}

const unsigned int NUMBER_OF_IMAGES = 4;

struct ImageData
{
    std::string    m_path;
    sf::Sprite     m_sprite;
    sf::Texture    m_texture;
};

std::vector<ImageData> initializeImageData();

#endif // DATATABLES_HPP

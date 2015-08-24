#ifndef CAROUSEL_HPP
#define CAROUSEL_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

//forward declarations
namespace sf
{
class RenderWindow;
}

namespace CarouselMovement
{
enum
{
    FORWARD = 0,
    REVERSE = 1
};
}

namespace CarouselType
{
enum
{
    NORMAL = 0,
    FADE   = 1,
};
}

class Carousel : public sf::Drawable, sf::Transformable
{
public:
    explicit Carousel(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration=0.f);
    ~Carousel();

    void addItem(sf::Sprite& s);

    void requestMove(sf::Uint32 direction);

    sf::Uint32 const getNumberOfItems() const;
    sf::Uint32 const getCurrentItemNumber() const;

    void handleInput(const sf::Event& event);

    void autoScroll(const sf::Uint32 direction);

    void update(sf::Time dt);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    class impl;
    std::unique_ptr<impl> m_impl;
};

#endif // CAROUSEL_HPP

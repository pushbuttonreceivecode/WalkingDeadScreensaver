#ifndef SCREENSAVER_HPP
#define SCREENSAVER_HPP

#include <SFML/Graphics/Drawable.hpp>

#include <Carousel.hpp>
#include <DataTables.hpp>

class ScreenSaver : public sf::Drawable
{
    public:
        ScreenSaver(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration);
        ~ScreenSaver();

        void update(sf::Time dt);
        bool detectMotion(sf::Event e);

        void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<ImageData> m_imageData;
        Carousel m_carousel;

        sf::Time m_duration;
        float m_effectDuration;

        sf::Vector2i m_initPos;
        sf::Vector2i m_movement;
        sf::Vector2i m_fudgefactor;
};

#endif // SCREENSAVER_HPP

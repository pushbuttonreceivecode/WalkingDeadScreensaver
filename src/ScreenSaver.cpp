#include <ScreenSaver.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

ScreenSaver::ScreenSaver(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration)
: m_imageData(initializeImageData())
, m_carousel(window, scalingFactor, type, effectDuration)
, m_duration(sf::Time::Zero)
, m_effectDuration(effectDuration)
, m_initPos(400,300)
, m_movement(0,0)
, m_fudgefactor(sf::Vector2i(4,4))
{
    //center the mouse
    sf::Mouse::setPosition(sf::Vector2i(400,300));

    for(auto& i : m_imageData)
    {
        m_carousel.addItem(i.m_sprite);
    }
}

ScreenSaver::~ScreenSaver()
{

}

void ScreenSaver::update(sf::Time dt)
{
    m_carousel.update(dt);

    if(m_duration.asSeconds() >= m_effectDuration)
    {
        m_carousel.autoScroll(CarouselMovement::FORWARD);
        m_duration = sf::Time::Zero;
    }
    else
        m_duration += dt;
}

bool ScreenSaver::detectMotion(sf::Event e)
{
    if(e.type == sf::Event::MouseMoved)
    {
        m_movement = sf::Mouse::getPosition();
        //make sure to use the absolute value of the difference
        //between the initial mouse position and the movement
        //and compare it to the fudge factor
        //if this value is greater exit the screensaver
        if (abs(m_movement.x - m_initPos.x) > m_fudgefactor.x
            || abs(m_movement.y - m_initPos.y) > m_fudgefactor.y)
        {
            return true;
        }
    }

    return false;
}

void ScreenSaver::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_carousel);
}

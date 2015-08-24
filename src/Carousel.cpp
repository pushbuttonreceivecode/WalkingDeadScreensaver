#include <Carousel.hpp>
#include <interpolate.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

class Carousel::impl
{
    public:
        explicit impl(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration);

        bool moveForward();
        bool moveReverse();
    public:
        float m_duration;
        std::vector<sf::Sprite> m_sprites;
        std::size_t m_selector;
        sf::Vector2f m_screenSize;
        sf::Vector2f m_scaleFactor;
        bool m_canMove;
        bool m_requestForward;
        bool m_requestReverse;
        sf::Uint32 m_type;
        sf::Time m_effectDuration;
        sf::Time m_movementDuration;
        unsigned int m_alpha;
};

Carousel::impl::impl(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration)
: m_duration(effectDuration)
, m_selector(0)
, m_canMove(true)
, m_screenSize(sf::Vector2f(window.getSize().x, window.getSize().y))
, m_scaleFactor(scalingFactor)
, m_requestForward(true)
, m_requestReverse(false)
, m_type(type)
, m_effectDuration(sf::Time::Zero)
, m_movementDuration(sf::Time::Zero)
, m_alpha(0)
{

}

bool Carousel::impl::moveForward()
{
    if(this->m_requestForward)
    {
        switch(this->m_type)
        {
        case CarouselType::NORMAL:
        {
            if(this->m_selector >= this->m_sprites.size()-1)
                this->m_selector = 0;
            else
                ++this->m_selector;

            //std::cout<<"image number: "<<this->m_selector<<std::endl;

            return true;
        }
        break;

        case CarouselType::FADE:
        {
            if(this->m_selector >= this->m_sprites.size()-1)
                this->m_selector = 0;
            else
                ++this->m_selector;

            //std::cout<<"image number: "<<this->m_selector<<std::endl;

            return true;
        }
        break;

        default:
            break;
        }
    }
    else
        return false;
}

bool Carousel::impl::moveReverse()
{
    if(this->m_requestReverse)
    {
        switch(this->m_type)
        {
        case CarouselType::NORMAL:
        {
            if(this->m_selector <= 0)
                this->m_selector = 0;
            else
                --this->m_selector;

            //std::cout<<"image number: "<<this->m_selector<<std::endl;

            return true;
        }
        break;

        case CarouselType::FADE:
        {
            if(this->m_selector <= 0)
                this->m_selector = 0;
            else
                --this->m_selector;

            //std::cout<<"image number: "<<this->m_selector<<std::endl;

            return true;
        }
        break;

        default:
            break;
        }

    }
    else
        return false;
}

Carousel::Carousel(sf::RenderWindow& window, sf::Vector2f scalingFactor, sf::Uint32 type, float effectDuration)
: m_impl(new impl(window, scalingFactor, type, effectDuration))
{

}

Carousel::~Carousel()
{

}

sf::Uint32 const Carousel::getNumberOfItems() const
{
    return m_impl->m_sprites.size();
};

sf::Uint32 const Carousel::getCurrentItemNumber() const
{
    return m_impl->m_selector;
}

void Carousel::addItem(sf::Sprite& s)
{
    //scale each sprite
    s.scale(m_impl->m_scaleFactor);

    //set each sprite opacity according to type
    switch(m_impl->m_type)
    {
    case CarouselType::NORMAL:
    {
        s.setColor(sf::Color(255,255,255,255));
    }
    break;

    case CarouselType::FADE:
    {
        s.setColor(sf::Color(255,255,255,m_impl->m_alpha));
    }
    break;

    default:
        break;
    }

    //add them to the container
    m_impl->m_sprites.push_back(s);
    //std::cout<<"Number of items: "<<m_impl->m_sprites.size()<<std::endl;
}

void Carousel::requestMove(sf::Uint32 direction)
{
    switch(direction)
    {
        case CarouselMovement::FORWARD:
        {
            m_impl->m_requestForward = true;
            m_impl->m_requestReverse = false;
        }
        break;

        case CarouselMovement::REVERSE:
        {
            m_impl->m_requestForward = false;
            m_impl->m_requestReverse = true;
        }
        break;

        default:
        {
            m_impl->m_requestForward = false;
            m_impl->m_requestReverse = false;
        }
        break;
    }
}

void Carousel::autoScroll(const sf::Uint32 direction)
{
    m_impl->m_canMove = true;
    requestMove(direction);
}

void Carousel::handleInput(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {

        case sf::Keyboard::Right:
        {
            switch(m_impl->m_type)
            {
                case CarouselType::NORMAL:
                {
                    m_impl->m_canMove = !m_impl->m_canMove;
                    if(m_impl->m_canMove)
                        requestMove(CarouselMovement::FORWARD);
                }
                break;

                case CarouselType::FADE:
                {
                    m_impl->m_canMove = !m_impl->m_canMove;
                    if(m_impl->m_canMove)
                        requestMove(CarouselMovement::FORWARD);
                }
                break;

            default:
                break;
            }

        }
        break;

        case sf::Keyboard::Left:
        {
            switch(m_impl->m_type)
            {
                case CarouselType::NORMAL:
                {
                    m_impl->m_canMove = !m_impl->m_canMove;
                    if(m_impl->m_canMove)
                        requestMove(CarouselMovement::REVERSE);
                }
                break;

                case CarouselType::FADE:
                {
                    m_impl->m_canMove = !m_impl->m_canMove;
                    if(m_impl->m_canMove)
                        requestMove(CarouselMovement::REVERSE);
                }
                break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
        }
    }
}

void Carousel::update(sf::Time dt)
{
    switch(m_impl->m_type)
    {
        case CarouselType::NORMAL:
        {
            if(m_impl->m_effectDuration.asSeconds() >= m_impl->m_duration/4.f)
                m_impl->m_effectDuration = sf::Time::Zero;
            else
                m_impl->m_effectDuration += dt;

            if(m_impl->m_movementDuration.asSeconds() >= m_impl->m_duration)
                m_impl->m_movementDuration = sf::Time::Zero;
            else
                m_impl->m_movementDuration += dt;

            if(m_impl->m_movementDuration.asSeconds() >= m_impl->m_duration)
            {
                m_impl->m_effectDuration = sf::Time::Zero;
                m_impl->m_movementDuration = sf::Time::Zero;

                if(m_impl->moveForward())
                {
                    m_impl->m_requestForward = false;
                    m_impl->m_canMove = false;
                    //std::cout<<"move forward successful"<<std::endl;
                }

                else if(m_impl->moveReverse())
                {
                    m_impl->m_requestReverse = false;
                    m_impl->m_canMove = false;
                    //std::cout<<"move reverse successful"<<std::endl;
                }
                //else
                //std::cout<<"no move"<<std::endl;
            }
        }
        break;

        case CarouselType::FADE:
        {
            if(m_impl->m_effectDuration.asSeconds() >= m_impl->m_duration/4.f)
                m_impl->m_effectDuration = sf::Time::Zero;
            else
                m_impl->m_effectDuration += dt;

            if(m_impl->m_movementDuration.asSeconds() >= 4.f)
                m_impl->m_movementDuration = sf::Time::Zero;
            else
                m_impl->m_movementDuration += dt;

            if(m_impl->m_movementDuration.asSeconds() > 0.f && m_impl->m_movementDuration.asSeconds() <= m_impl->m_duration/4.f)
            {
                if(m_impl->m_alpha >= 255)
                {
                    m_impl->m_alpha = 255;
                }
                else
                    m_impl->m_alpha = (unsigned int)math::interpolate::sineEaseIn(m_impl->m_effectDuration.asSeconds(), 0.f, 255.f, m_impl->m_duration/4.f);
            }
            else if(m_impl->m_movementDuration.asSeconds() > (m_impl->m_duration/4.f) && m_impl->m_movementDuration.asSeconds() <= (m_impl->m_duration*.75f))
            {
                m_impl->m_alpha = 255;
                m_impl->m_effectDuration = sf::Time::Zero;
            }
            else if(m_impl->m_movementDuration.asSeconds() > (m_impl->m_duration*.75f) && m_impl->m_movementDuration.asSeconds() < m_impl->m_duration)
            {
                if(m_impl->m_alpha <= 0)
                {
                    m_impl->m_alpha = 0;
                }
                else
                    m_impl->m_alpha = 255-(unsigned int)math::interpolate::sineEaseIn(m_impl->m_effectDuration.asSeconds(), 0.f, 255.f, m_impl->m_duration/4.f);
            }
            else if(m_impl->m_movementDuration.asSeconds() >= m_impl->m_duration)
            {
                m_impl->m_effectDuration = sf::Time::Zero;
                m_impl->m_movementDuration = sf::Time::Zero;

                if(m_impl->moveForward())
                {
                    m_impl->m_requestForward = false;
                    m_impl->m_canMove = false;
                    //std::cout<<"move forward successful"<<std::endl;
                }

                else if(m_impl->moveReverse())
                {
                    m_impl->m_requestReverse = false;
                    m_impl->m_canMove = false;
                    //std::cout<<"move reverse successful"<<std::endl;
                }
                //else
                //std::cout<<"no move"<<std::endl;
            }

            m_impl->m_sprites[m_impl->m_selector].setColor(sf::Color(255,255,255,m_impl->m_alpha));
        }
        break;

        default:
            break;
    }
}

void Carousel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_impl->m_sprites[m_impl->m_selector], states);
}

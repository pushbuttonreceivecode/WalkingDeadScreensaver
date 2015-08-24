#include <iostream>

#include <SFML/Graphics.hpp>

#include <ScreenSaver.hpp>
#include <interpolate.hpp>

int main()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "The Walking Dead", sf::Style::Fullscreen);
    sf::Event e;

    //try to support as many resolutions as possible
    //using a scaling factor for all resources
    sf::Vector2f scaleFactor = sf::Vector2f(window.getSize().x/2560.f, window.getSize().y/1440.f);

    //set up the image carousel
    ScreenSaver myScreenSaver(window, scaleFactor, CarouselType::FADE, 4.f);

    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;

    while(window.isOpen())
    {
        while(window.pollEvent(e))
        {
            if(myScreenSaver.detectMotion(e))
                return 0;
        }

        timeElapsed += clock.restart();
        while (timeElapsed > timePerFrame)
        {
            timeElapsed -= timePerFrame;

            myScreenSaver.update(timePerFrame);
        }

        window.clear();

        window.draw(myScreenSaver);

        window.display();
    }

    return 0;
}

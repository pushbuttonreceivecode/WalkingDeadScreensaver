#include <assert.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <DataTables.hpp>

std::vector<ImageData> initializeImageData()
{
    std::vector<ImageData> data(NUMBER_OF_IMAGES);

    //http://1.bp.blogspot.com/-iYexJifkw1c/U_-koSCORkI/AAAAAAAAAGo/zR32f6hwPMY/s1600/twdS5.jpg
    data[0].m_path = "WalkingDeadScrRes/dead.jpg";
    assert(data[0].m_texture.loadFromFile(data[0].m_path));
    data[0].m_sprite.setTexture(data[0].m_texture);

    //http://7-themes.com/data_images/out/33/6881193-daryl-the-walking-dead.jpg
    data[1].m_path = "WalkingDeadScrRes/daryl.jpg";
    assert(data[1].m_texture.loadFromFile(data[1].m_path));
    data[1].m_sprite.setTexture(data[1].m_texture);

    //http://www.hdwallpapers.in/walls/the_walking_dead_season_5-wide.jpg
    data[2].m_path = "WalkingDeadScrRes/rick.jpg";
    assert(data[2].m_texture.loadFromFile(data[2].m_path));
    data[2].m_sprite.setTexture(data[2].m_texture);

    //http://www.wallconvert.com/wallpapers/tv-shows/michonne-the-walking-dead-9577.html
    data[3].m_path = "WalkingDeadScrRes/michonne.jpg";
    assert(data[3].m_texture.loadFromFile(data[3].m_path));
    data[3].m_sprite.setTexture(data[3].m_texture);

    return data;
}

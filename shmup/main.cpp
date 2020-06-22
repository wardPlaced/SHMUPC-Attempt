 
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 700), "SHMUP");
    sf::Sprite player;
    sf::Sprite enemy;
    sf::Sprite cloud;
    sf::Sprite cloud1;
    sf::Sprite explosion;
    sf::Sprite bkg;
    sf::Sprite emptyS;
    sf::Texture emptyT;
    sf::CircleShape bullet(5.f);
    bullet.setFillColor(sf::Color::Green);
    emptyT.create(20,20);
    
    sf::Texture tex1;
    sf::Texture tex2;
    sf::Texture tex3;
    sf::Texture tex4;
    sf::Texture tex5;
    sf::Texture tex6;
    sf::Vector2f vec2(400.f, 400.f);
    int frameExp = 0;

    tex1.loadFromFile("Graphics/cloud.png");
    cloud.setTexture(tex1);
    tex6.loadFromFile("Graphics/cloud1.png");
    cloud1.setTexture(tex6);

    tex2.loadFromFile("Graphics/explosion.png");
    explosion.setTexture(tex2);
    
    tex3.loadFromFile("Graphics/bkg.jpg");
    bkg.setTexture(tex3);

    tex4.loadFromFile("Graphics/ship.png");
    player.setTexture(tex4);

    tex5.loadFromFile("Graphics/enemy.png");
    enemy.setTexture(tex5);

    bool collision = false;

    float vel = 50.f;
    float cloudScroll = -100.f;

    struct bullet
    {
        float x[256];
        float y[256];
        bool destroy[256];
        bool active[256];
    } b;

    struct player
    {
        float x = 225.f;
        float y = 600.f;
        int health = 5;
    } p;

    struct enemy
    {
        int id[150];
        float x;
        float y;
        bool dead;
    } e;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(bkg);
        cloud.setScale(0.5f, 0.5f);
        cloud1.setScale(0.5f, 0.5f);

        for(int i = 0; i < 50; i++)
        {
            if(cloudScroll > 900.f)
            {
                cloudScroll = -200.f;
            }
            cloud.setPosition(100.f, cloudScroll+=vel*0.001f);
            window.draw(cloud);
            cloud1.setRotation(-180);
            cloud1.setPosition(400.f, cloudScroll+=vel*0.001f);
            window.draw(cloud1);
        }

        sf::sleep(sf::milliseconds(30));

        if (collision)
        {
            switch (frameExp)
            {
                case 0:
                    explosion.setTextureRect(sf::IntRect(0, 0, 130, 148));
                    frameExp = 1;
                    sf::sleep(sf::milliseconds(10));
                    break;
                case 1:
                    explosion.setTextureRect(sf::IntRect(139, 0, 130, 148));
                    frameExp = 2;
                    sf::sleep(sf::milliseconds(64));
                    break;
                case 2:
                    explosion.setTextureRect(sf::IntRect(278, 0, 130, 148));
                    frameExp = 3;
                    sf::sleep(sf::milliseconds(100));
                    break;
                case 3:
                    explosion.setTextureRect(sf::IntRect(416, 0, 130, 148));
                    frameExp = 4;
                    sf::sleep(sf::milliseconds(150));
                    break;
                case 4:
                    explosion.setTextureRect(sf::IntRect(0, 0, 20, 20));
                    frameExp = 0;
                    sf::sleep(sf::milliseconds(150));
                default:
                    break;
            }
            window.draw(explosion);
        }
        enemy.setPosition(150.f, 150.f);
        enemy.setRotation(180);
        enemy.setScale(0.5f, 0.5f);
        window.draw(enemy);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            p.x -= vel * 0.3f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            p.y -= vel * 0.3f;
                
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            p.x += vel * 0.3f;
                
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p.y += vel * 0.3f;
                
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            
        }
        window.draw(bullet);


        player.setPosition(p.x, p.y);
        window.draw(player);

        window.display();
    }

    return 0;
}



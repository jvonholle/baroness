
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <vector>
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include <sstream>
#include <fstream>
#include <iostream>


#include "tttGame.h"
#include "move.h"


int main(int, char const**)
{
    
    std::ifstream ifs;
    
    ifs.open("check");
    
    char chars[32];
    
    if(ifs.good())
    {
        for(int ii=0;ii<32;ii++)
        {
            ifs >> chars[ii];
        }
    }
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    
    sf::CircleShape triangle(50,3);
    triangle.setFillColor(sf::Color(240,30,10));
    triangle.setPosition(100, 100);
    
    
    // Play the music
    //music.play();
    
    std::vector<sf::RectangleShape> disLin; //lines that need to be displayed
    tttGame nEw(200,200,8);
    std::vector<char> ccc;
    for(int ii=0; ii<32; ii++)
    {
        ccc.push_back(chars[ii]);
    }
    nEw.readIn(ccc);

    ccc = moves(ccc,0, 'r');
    
    for(int ii=0; ii<10; ++ii)
    {
        std::cout << ccc[ii] <<",";
    }
    std::cout <<std::endl;
    
    
    tttGame moved(200,200,8,240,0);
    
    moved.readIn(ccc);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                nEw.click(sf::Mouse::getPosition(window));
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        triangle.rotate(10);
        
        disLin = nEw.displayBoard();
        
        // Clear screen
        window.clear();

//        // Draw the sprite
//        window.draw(sprite);
//
        // Draw the string
        //window.draw(text);
        
//        for(int ii=0; ii<disLin.size(); ii++)
//        {
//            window.draw(disLin[ii]);
//        }
        
        nEw.displayBoard2(window);
        
        moved.displayBoard2(window);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

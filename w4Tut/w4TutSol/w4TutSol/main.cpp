#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <tuple>


// change properties -> C/C++ -> genral -> additional inc dirs
// change properties -> linker -> genral -> additional lib dirs
// home pc inc dir: D:\school\libs\SFML-2.6.1-windows-vc17-64-bit\SFML-2.6.1\include
// home pc linker dir: D:\school\libs\SFML-2.6.1-windows-vc17-64-bit\SFML-2.6.1\lib
// school pc inc dir: C:\Users\c4024637\Desktop\SFML-2.6.1-windows-vc17-64-bit\SFML-2.6.1\include
// school pc linker dir: C:\Users\c4024637\Desktop\SFML-2.6.1-windows-vc17-64-bit\SFML-2.6.1\lib


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
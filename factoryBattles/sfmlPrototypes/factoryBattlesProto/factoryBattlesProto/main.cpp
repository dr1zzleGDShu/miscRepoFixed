#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;


//struct metaData {
// TODO struct this shit properly 
map<int, sf::Texture> entTypeTexPathLookupMap;// = { {5, "../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_teal_b.png"} };
//};


struct ent {
    int xPos, yPos;

    sf::Sprite entSpr;

    void initEnt(int entTypeLookup, int xPosIn, int yPosIn) {
        xPos = xPosIn; yPos = yPosIn;
        entSpr.setTexture(entTypeTexPathLookupMap[entTypeLookup]);
        entSpr.setPosition(xPos, yPos);
    }

    void renderEnt(sf::RenderWindow& winIn) {
        winIn.draw(entSpr);
    }


};


void instantiateEnt(vector<ent>&, int, int, int);
int toRenderLoop(vector<ent>&);
void populateTexLookup();


int main()
{
    populateTexLookup();
    vector<ent> entVect;
    instantiateEnt(entVect, 5, 800, 200);
    instantiateEnt(entVect, 5, 700, 200);
    instantiateEnt(entVect, 5, 600, 200);
    instantiateEnt(entVect, 5, 500, 200);
    

    return toRenderLoop(entVect);
}


void populateTexLookup() {
    sf::Texture entTex5;
    entTex5.loadFromFile("../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_teal_b.png");
    entTypeTexPathLookupMap[5] = entTex5;
}

void instantiateEnt(vector<ent> &entVectIn, int entType, int xPosIn, int yPosIn) {
    ent myEnt;
    myEnt.initEnt(entType, xPosIn, yPosIn);
    entVectIn.push_back(myEnt);
}


int toRenderLoop(vector<ent> &entVect) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    bool m1Down;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            instantiateEnt(entVect, 5, localPosition.x, localPosition.y);
        }

        window.clear();
        for (ent i : entVect) {
            i.renderEnt(window);
        }
        


        window.display();
    }

    return 0;
}
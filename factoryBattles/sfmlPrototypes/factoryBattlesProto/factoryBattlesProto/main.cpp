#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;


//struct metaData {
// TODO struct this shit properly 
map<int, sf::Texture> entTypeTexPathLookupMap;// = { {5, "../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_teal_b.png"} };




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


struct gridSpace {
    ent gridEnt;
    bool empty = true;

    void fillGridEnt(ent entIn){
        if (empty) {
            gridEnt = entIn;
            empty = false;
        }
    }

    bool isEmpty() {
        return empty;
    }

    int drawGridSpace(sf::RenderWindow& winIn) {
        gridEnt.renderEnt(winIn);
        return 0;

    }

};


struct grid {
    static const int gridSizeX = 4;
    static const int gridSizeY = 4;
    const int gridSpaceSizeX = 100;
    const int gridSpaceSizeY = 100;

    gridSpace gridArr[gridSizeX][gridSizeY];

    void populateGridArr() {
        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                gridSpace tempVar;
                gridArr[i][j] = tempVar;
            }
        }
    }

    int tryAddEntToNearestGridSpace(int entTypeLookup, int xPosIn, int yPosIn){
        int gridCoordX = xPosIn / gridSpaceSizeX;
        int gridCoordY = yPosIn / gridSpaceSizeY;
        cout << "\n" << xPosIn << " " << yPosIn << " " << gridCoordX << " " << gridCoordY;
        if ((gridCoordX >= gridSizeX) || (gridCoordY >= gridSizeY)) { cout << "gridOutOfRange"; return 1; }

        if (gridArr[gridCoordX][gridCoordY].isEmpty()) {
            ent myEnt;
            myEnt.initEnt(entTypeLookup, gridCoordX*gridSpaceSizeX, gridCoordY*gridSpaceSizeY);// xPosIn, yPosIn);
            gridArr[gridCoordX][gridCoordY].fillGridEnt(myEnt);
        }
        else { cout << "gridPosNotEmpty"; return 2; }
  
        


        return 0;
    }

    int drawAllGridSpaces(sf::RenderWindow& winIn) {
        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                gridArr[i][j].drawGridSpace(winIn);
            }
        }
        return 0;
    }
};

int toRenderLoop(grid&);
void populateTexLookup();


int main() {
    populateTexLookup();
    //grid gridIn;
    grid p1Grid; p1Grid.populateGridArr();
    //instantiateEnt(gridIn, 5, 800, 200);
    //instantiateEnt(gridIn, 5, 700, 200);
    //instantiateEnt(gridIn, 5, 600, 200);
    //instantiateEnt(gridIn, 5, 500, 200);
    

    return toRenderLoop(p1Grid);
}



void populateTexLookup() {
    sf::Texture entTex5;
    entTex5.loadFromFile("../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_teal_b.png");
    entTypeTexPathLookupMap[5] = entTex5;
}



/**void instantiateEnt(grid& gridInIn, int entType, int xPosIn, int yPosIn) {
    ent myEnt;
    myEnt.initEnt(entType, xPosIn, yPosIn);
    gridInIn.push_back(myEnt);
}**/



bool doM1Logic(bool& m1Down) {
    // return wether m1 was just down
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m1Down) {
            void;
        }
        else {
            m1Down = true;
            return true;
        }
    }
    else { if (m1Down) { m1Down = false; } }
    return false;
}



void placeBuildingDown(sf::RenderWindow& winIn, grid& gridIn) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(winIn);
    gridIn.tryAddEntToNearestGridSpace(5, localPosition.x, localPosition.y);
}



int toRenderLoop(grid &gridIn) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    bool m1Down = false;
    bool m1JustPressed = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        


        m1JustPressed = doM1Logic(m1Down);
        if (m1JustPressed) {
            placeBuildingDown(window, gridIn);
        }

        window.clear();
        gridIn.drawAllGridSpaces(window);
        


        window.display();
    }

    return 0;
}


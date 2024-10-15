#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;


// TODO struct this shit properly 
map<int, sf::Texture> entTypeTexPathLookupMap;


struct ui {
    sf::Texture uiBackroundTex;
    sf::Sprite uiBackroundSpr;
    
    void initUi() {
        uiBackroundTex.loadFromFile("../art/ui/uiBackround.png");
        uiBackroundSpr.setTexture(uiBackroundTex);
    }

    void drawUi(sf::RenderWindow& winIn) {
        winIn.draw(uiBackroundSpr);
    }

};


struct ent {
    int xPos, yPos;

    sf::Sprite entSpr;

    void initEnt(int entTypeLookup, int xPosIn, int yPosIn) {
        xPos = xPosIn; yPos = yPosIn;
        entSpr.setTexture(entTypeTexPathLookupMap[entTypeLookup]);
        entSpr.setPosition(xPos, yPos);
        entSpr.setScale(0.5, 0.5);
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
    static const int gridSizeX = 10; // total number of gridSpaces in the x axis
    static const int gridSizeY = 13;
    const int gridSpaceSizeX = 50; // size (px) of each gridSpace in the x axis
    const int gridSpaceSizeY = 50;
    int gridOffsetX = 0;
    int gridOffsetY = 0;

    gridSpace gridArr[gridSizeX][gridSizeY];

    void populateGridArr() { // fill the array with empty gridSpaces
        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                gridSpace tempVar;
                gridArr[i][j] = tempVar;
            }
        }
    }


    void setGridOffsets(int xOffIn, int yOffIn) {
        gridOffsetX = xOffIn;
        gridOffsetY = yOffIn;
    }


    int tryAddEntToNearestGridSpace(int entTypeLookup, int xPosIn, int yPosIn){
        // Tries to add a specified ent onto the grid
        // fails if clicking off the grid (err code 1) or if gridSpace is occupied (err code 2)
        // if possible will place an ent in that grid space
        if ((xPosIn < gridOffsetX) || (yPosIn < gridOffsetY)){return 1;}
        int gridCoordX = (xPosIn-gridOffsetX) / gridSpaceSizeX;
        int gridCoordY = (yPosIn-gridOffsetY) / gridSpaceSizeY;
        cout << "\n" << xPosIn << " " << yPosIn << " " << gridCoordX << " " << gridCoordY;
        if ((gridCoordX >= gridSizeX) || (gridCoordY >= gridSizeY)) { cout << "gridOutOfRange"; return 1; }

        if (gridArr[gridCoordX][gridCoordY].isEmpty()) {
            ent myEnt;
            myEnt.initEnt(entTypeLookup, (gridCoordX*gridSpaceSizeX)+ gridOffsetX, (gridCoordY*gridSpaceSizeY)+ gridOffsetY);// xPosIn, yPosIn);
            gridArr[gridCoordX][gridCoordY].fillGridEnt(myEnt);
        }
        else { cout << "gridPosNotEmpty"; return 2; }

        return 0;
    }



    int drawAllGridSpaces(sf::RenderWindow& winIn) {
        // Draw all the grid spaces on the window

        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                gridArr[i][j].drawGridSpace(winIn);
            }
        }
        return 0;
    }
};


struct btn {
    int xPos, yPos, xSize, ySize;

    sf::Sprite btnSpr;

    void initEnt(int btnTypeLookup, int xPosIn, int yPosIn, int xSizeIn, int ySizeIn) {
        xPos = xPosIn; yPos = yPosIn;
        xSize = xSizeIn; ySize = ySizeIn;
        btnSpr.setTexture(entTypeTexPathLookupMap[btnTypeLookup]);
        btnSpr.setPosition(xPos, yPos);
        btnSpr.setScale(0.5, 0.5);
    }

    void renderEnt(sf::RenderWindow& winIn) {
        winIn.draw(btnSpr);
    }
};


struct btnsContainer{
    vector<btn> btnVect;

    void addBtn(int btnTypeLookup, int xPosIn, int yPosIn, int xSizeIn, int ySizeIn) {
        btn myBtn

    }
}


int toRenderLoop(grid&, grid&, ui&);
void populateTexLookup();


int main() {
    populateTexLookup();
    grid p1Grid; p1Grid.populateGridArr(); p1Grid.setGridOffsets(596, 65); // Grid that contains all ents in the game
    grid p2Grid; p2Grid.populateGridArr(); p2Grid.setGridOffsets(32, 65); // Grid that contains all ents in the game

    ui ui; ui.initUi();
    

    return toRenderLoop(p1Grid, p2Grid, ui);
}



void populateTexLookup() {
    // fills the texLookupMap with the paths to various sprites, with a int as the lookup value
    sf::Texture entTex5;
    entTex5.loadFromFile("../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_teal_b.png");
    entTypeTexPathLookupMap[5] = entTex5;
    sf::Texture entTex6;
    entTex6.loadFromFile("../art/buildingSprites/mbs_icp_u423/icp_u423/Buildings/house_large_green_b.png");
    entTypeTexPathLookupMap[6] = entTex6;
}



bool doM1Logic(bool& m1Down) {
    // return wether m1 was just down, sets m1Down to wether m1 is down
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m1Down) {void;}
        else { m1Down = true; return true;}
    }
    else { if (m1Down) { m1Down = false; } }
    return false;
}


bool doM2Logic(bool& m2Down) {
    // return wether m1 was just down, sets m1Down to wether m1 is down
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (m2Down) { void; }
        else { m2Down = true; return true; }
    }
    else { if (m2Down) { m2Down = false; } }
    return false;
}


void placeBuildingDown(sf::RenderWindow& winIn, grid& gridIn, int& selectedBuilding) {
    // asks the grid to place a building at the grid position nearest the cursor
    sf::Vector2i localPosition = sf::Mouse::getPosition(winIn);
    gridIn.tryAddEntToNearestGridSpace(selectedBuilding, localPosition.x, localPosition.y);
}



void mouseLogic(sf::RenderWindow& winIn, grid& grid1In, grid& grid2In, bool &m1Down, bool& m2Down, bool &m1JustPressed, bool& m2JustPressed, int& selectedBuilding) {
    m1JustPressed = doM1Logic(m1Down);
    m2JustPressed = doM2Logic(m2Down);
    if (m1JustPressed) {
        placeBuildingDown(winIn, grid1In, selectedBuilding);
    }
    if (m2JustPressed) {
        placeBuildingDown(winIn, grid2In, selectedBuilding);
    }
}



int toRenderLoop(grid &grid1In, grid &grid2In, ui &uiIn) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");


    bool m1Down = false; // is m1Down rn (after doM1Logic())
    bool m1JustPressed = false; // has m1Just been pressed (after doM1Logic())
    bool m2Down = false;
    bool m2JustPressed = false;
    int selectedBuilding = 6;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        


        mouseLogic(window, grid1In, grid2In, m1Down, m2Down, m1JustPressed, m2JustPressed, selectedBuilding);

        window.clear();
        grid1In.drawAllGridSpaces(window);
        grid2In.drawAllGridSpaces(window);
        uiIn.drawUi(window);
        


        window.display();
    }

    return 0;
}


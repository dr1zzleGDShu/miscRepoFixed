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


using namespace std;


struct entTypeData {
    sf::Texture entTypeTex;
    float xScale, yScale;
    int entGridSizeX, entGridSizeY;

    void initData(string entTypeTexIn, float xScaleIn, float yScaleIn, int entSizeXIn, int entSizeYIn) {
        entTypeTex.loadFromFile(entTypeTexIn);
        xScale = xScaleIn; yScale = yScaleIn;
        entGridSizeX = entSizeXIn; entGridSizeY = entSizeYIn;
    }
};

map<int, entTypeData> entTypeDataPathLookupMap;


struct itemTypeData {
    sf::Texture itemTypeTex;
    float xScale, yScale;

    void initData(string itemTypeTexIn, float xScaleIn, float yScaleIn) {
        itemTypeTex.loadFromFile(itemTypeTexIn);
        xScale = xScaleIn; yScale = yScaleIn;
    }
};

map<int, itemTypeData> itemTypeDataPathLookupMap;




struct item {
    // TODO make moving items more performant
    int itemTypeLookup;

    sf::Sprite itemSpr;
    

};


struct recipe {
    int tickLen;
    int recpLen;
    vector<tuple<int,int>> recpComponents;
    vector<tuple<int, int>> recpOut;
    

    bool isItemInRecipe(int itemIn) {
        for (tuple<int, int> i : recpComponents) {
            if (get<0>(i) == itemIn) {
                return true;
            }
        }
        return false;
    }

    bool isRecipeComplete(vector<tuple<int, int>> inVar) {
        bool itemMissing = true;
        for (tuple<int, int> i : recpComponents) {
            itemMissing = true;
            for (tuple<int, int> j : inVar) {
                if (get<0>(i) == get<0>(j)) {// if item in recp == item in inVar
                    if (get<1>(i) <= get<1>(j)) {// if inputted item number <= number needed in recp
                        itemMissing = false;
                    }
                }
            }
            if (itemMissing) {
                return false;
            }
        }
        return true;

    }
};


struct ent {
    int entTypeLookup;
    int xPos, yPos;
    int xGridSize, yGridSize;
    vector <int> itemsVect; // stored as lookup
    recipe currentRecipe;
    int recpProgress;

    sf::Sprite entSpr;

    void initEnt(int entTypeLookupIn, int xPosIn, int yPosIn, int xGridSizeIn, int yGridSizeIn) {
        entTypeLookup = entTypeLookupIn;
        xPos = xPosIn; yPos = yPosIn;
        xGridSize = xGridSizeIn; yGridSize = yGridSizeIn;
        entSpr.setTexture(entTypeDataPathLookupMap[entTypeLookupIn].entTypeTex);
        entSpr.setPosition(xPos, yPos);
        entSpr.setScale(entTypeDataPathLookupMap[entTypeLookupIn].xScale, entTypeDataPathLookupMap[entTypeLookupIn].yScale);
    }

    void renderEnt(sf::RenderWindow& winIn) {
        winIn.draw(entSpr);
    }

    void addItem(int itemLookupIn) {
        itemsVect.push_back(itemLookupIn);
    }

    void tryRemItem(int itemLookupIn) {
        auto it = find(itemsVect.begin(), itemsVect.end(), itemLookupIn);
        if (it != itemsVect.end()) {
            itemsVect.erase(it);
        }
    }

    void debugPrintItemsVect() {
        cout << "\nDebugPrintingItemsVectOfEntAtPos" << xPos << "," << yPos << "\n";
        for (int i : itemsVect) {
            cout << i << ",";
        }
        cout << "\n";
    }


    void progressRecp() {
        recpProgress += 1;
        if (currentRecipe.recpLen >= recpProgress) {
            //TODO here
        }
    }

};




struct gridSpace {
    ent gridEnt; // grid ent not actually set if multispace child ent, empty still set to false
    bool empty = true;
    bool isMultispaceChild = false;
    int multispaceParentXCoord = 0;
    int multispaceParentYCoord = 0;
    vector<tuple<int, int>> multispaceChildrenCoords;


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

    void multispaceParentToGridCoord(int xCoordIn, int yCoordIn) {
        if (empty) {
            empty = false;
            bool isMultispaceChild = true;
            int multispaceParentXCoord = xCoordIn;
            int multispaceParentYCoord = yCoordIn;
        }
    }

    bool isMultispaceParent() {
        return !empty && !isMultispaceChild;
    }

};


struct grid {
    static const int gridSizeX = 24; // total number of gridSpaces in the x axis
    static const int gridSizeY = 31;
    const int gridSpaceSizeX = 20; // size (px) of each gridSpace in the x axis
    const int gridSpaceSizeY = 20;
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
        if ((xPosIn < gridOffsetX) || (yPosIn < gridOffsetY)){return 1;} // clicked off the grid (too low)
        int gridCoordX = (xPosIn-gridOffsetX) / gridSpaceSizeX;
        int gridCoordY = (yPosIn-gridOffsetY) / gridSpaceSizeY;
        cout << "\n" << xPosIn << " " << yPosIn << " " << gridCoordX << " " << gridCoordY;
        if ((gridCoordX >= gridSizeX) || (gridCoordY >= gridSizeY)) { cout << "gridOutOfRange"; return 1; } // clicked off the grid (too high)

        // checking all spaces for ent on grid r empty 
        bool allSpacesEmpty = true;
        for (int i = 0; i < entTypeDataPathLookupMap[entTypeLookup].entGridSizeX; i++) {
            for (int j = 0; j < entTypeDataPathLookupMap[entTypeLookup].entGridSizeY; j++) {
                if (!gridArr[gridCoordX + i][gridCoordY + j].isEmpty()) {
                    allSpacesEmpty = false;
                }
            }
        }


        if (allSpacesEmpty) {

            ent myParentEnt;
            myParentEnt.initEnt(entTypeLookup, (gridCoordX*gridSpaceSizeX)+ gridOffsetX, (gridCoordY*gridSpaceSizeY)+ gridOffsetY, entTypeDataPathLookupMap[entTypeLookup].entGridSizeX, entTypeDataPathLookupMap[entTypeLookup].entGridSizeY);// xPosIn, yPosIn);
            gridArr[gridCoordX][gridCoordY].fillGridEnt(myParentEnt);
            int c = 0;
            for (int i = 0; i < entTypeDataPathLookupMap[entTypeLookup].entGridSizeX; i++) {
                for (int j = 0; j < entTypeDataPathLookupMap[entTypeLookup].entGridSizeY; j++) {
                    if (c != 0) { // if not parent
                        gridArr[gridCoordX + i][gridCoordY + j].multispaceParentToGridCoord(gridCoordX, gridCoordY);
                    }
                    c += 1;
                }
            }

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


    void doItemGen() {
        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                if (gridArr[i][j].isMultispaceParent()) {
                    if (gridArr[i][j].gridEnt.entTypeLookup == 5) { // if miner
                        gridArr[i][j].gridEnt.addItem(15);
                        gridArr[i][j].gridEnt.debugPrintItemsVect();
                    }
                }
            }
        }
    }


    void doRecipesInGrid() {
        for (int i = 0; i < gridSizeX; i++) {
            for (int j = 0; j < gridSizeY; j++) {
                if (gridArr[i][j].isMultispaceParent()) {

                }
            }
        }
    }


};


struct btn : ent {
    int xSize, ySize;
    int btnValue = -1;

    void initBtn(int entTypeLookup, int xPosIn, int yPosIn, int xSizeIn, int ySizeIn, int btnValueIn) {
        initEnt(entTypeLookup, xPosIn, yPosIn, entTypeDataPathLookupMap[entTypeLookup].entGridSizeX, entTypeDataPathLookupMap[entTypeLookup].entGridSizeY);
        xSize = xSizeIn; ySize = ySizeIn; btnValue = btnValueIn;
    }

    bool isCoordInBtn(int xCoordIn, int yCoordIn) {
        return ((xPos <= xCoordIn) && ((xPos + xSize) >= xCoordIn)) && ((yPos <= yCoordIn) && ((yPos + ySize) >= yCoordIn));
    }

    int retBtnValue() {
        return btnValue;
    }

};


struct btnsContainer {
    vector<btn> btnVect;
    btn btnToRetStorage;

    void addBtn(int btnTypeLookup, int xPosIn, int yPosIn, int xSizeIn, int ySizeIn, int btnValueIn) {
        btn myBtn;
        myBtn.initBtn(btnTypeLookup, xPosIn, yPosIn, xSizeIn, ySizeIn, btnValueIn);
        btnVect.push_back(myBtn);
    }

    void drawAllBtns(sf::RenderWindow& winIn) {
        for (btn i : btnVect) {
            i.renderEnt(winIn);
        }
    }

    bool checkIfBtnsClicked(int xCoordIn, int yCoordIn) {
        bool toRet = false;
        for (btn i : btnVect) {
            if (i.isCoordInBtn(xCoordIn, yCoordIn)) {
                btnToRetStorage = i;
                toRet = true;
            }
        }
        return toRet;
    }

    btn retBtnToRetStorage() {
        return btnToRetStorage;
    }
};


struct ui {
    sf::Texture uiBackroundTex;
    sf::Sprite uiBackroundSpr;
    btnsContainer btnsContainer;


    void initUi() {
        uiBackroundTex.loadFromFile("../art/ui/uiBackround.png");
        uiBackroundSpr.setTexture(uiBackroundTex);
    }

    void drawUi(sf::RenderWindow& winIn) {
        winIn.draw(uiBackroundSpr);
        btnsContainer.drawAllBtns(winIn);
    }

    void initBtnContainer() {
        btnsContainer.addBtn(5, 1120, 70, 50, 50, 5);
        btnsContainer.addBtn(6, 1170, 70, 50, 50, 6);
        btnsContainer.addBtn(105, 1120, 120, 50, 50, 105);
    }
};


int toRenderLoop(grid&, grid&, ui&);
void populateTexLookup();


int main() {
    populateTexLookup();
    grid p1Grid; p1Grid.populateGridArr(); p1Grid.setGridOffsets(596, 65); // Grid that contains all ents in the game
    grid p2Grid; p2Grid.populateGridArr(); p2Grid.setGridOffsets(32, 65); // Grid that contains all ents in the game

    ui ui; ui.initUi(); ui.initBtnContainer();

    

    return toRenderLoop(p1Grid, p2Grid, ui);
}



void populateTexLookup() {
    // fills the texLookupMap with the paths to various sprites, with a int as the lookup value
    entTypeData entData5; entData5.initData("../art/buildingSprites/fromFactorio/burnerMiner.png",0.5,0.5,2,2);
    entTypeDataPathLookupMap[5] = entData5;
    entTypeData entData6; entData6.initData("../art/buildingSprites/fromFactorio/assemblyMachine.png", 0.5, 0.5, 2, 2);
    entTypeDataPathLookupMap[6] = entData6;
    entTypeData entData105; entData105.initData("../art/buildingSprites/fromFactorio/belt.png", 0.3, 0.3, 1, 1);
    entTypeDataPathLookupMap[105] = entData105;

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


void placeBuildingDown(sf::RenderWindow& winIn, grid& gridIn, int& selectedBuilding, int &xPosIn, int &yPosIn) {
    // asks the grid to place a building at the grid position nearest the cursor
    gridIn.tryAddEntToNearestGridSpace(selectedBuilding, xPosIn, yPosIn);
}



void mouseLogic(sf::RenderWindow& winIn, grid& grid1In, grid& grid2In, ui &uiIn, bool &m1Down, bool& m2Down, bool &m1JustPressed, bool& m2JustPressed, int& selectedBuilding) {
    m1JustPressed = doM1Logic(m1Down);
    m2JustPressed = doM2Logic(m2Down);
    sf::Vector2i localPosition = sf::Mouse::getPosition(winIn);
    if (m1JustPressed) {
        if (uiIn.btnsContainer.checkIfBtnsClicked(localPosition.x, localPosition.y)) {
            cout << "btn clicked";
            selectedBuilding = uiIn.btnsContainer.retBtnToRetStorage().retBtnValue();
        }
        placeBuildingDown(winIn, grid1In, selectedBuilding, localPosition.x, localPosition.y);
    }
    if (m2JustPressed) {
        placeBuildingDown(winIn, grid2In, selectedBuilding, localPosition.x, localPosition.y);
    }
}



int toRenderLoop(grid &grid1In, grid &grid2In, ui &uiIn) {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "factoryBattles");


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
        

        grid1In.doItemGen();
        grid2In.doItemGen();


        mouseLogic(window, grid1In, grid2In, uiIn, m1Down, m2Down, m1JustPressed, m2JustPressed, selectedBuilding);

        window.clear();
        grid1In.drawAllGridSpaces(window);
        grid2In.drawAllGridSpaces(window);
        uiIn.drawUi(window);
        


        window.display();
    }

    return 0;
}


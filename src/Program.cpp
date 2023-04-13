#include "Program.h"
#include "DistrictBrute.h"
#include "MunicipalitiesBrute.h"

/**
 * Program's constructor responsible for initializing the database and the menus
 * @brief Program's constructor
 */
Program::Program()
{
    /*
    auto region_map = Scraper::scrape_stations("../src/data/stations.csv", railway);
    Scraper::scrape_networks("../src/data/network.csv", railway);
    Scraper::fix_graph(railway);
    railway.setRegion(LINE);
    Scraper::findExtremes(region_map, railway);
    railway.setRegion(MUNICIPALITIES);
    Scraper::findExtremes(region_map, railway);
    railway.setRegion(DISTRICTS);
    Scraper::findExtremes(region_map, railway);
     */

    /* EXEMPLO 2.1
    railway = ExampleGraphs::Graph1();
     */

    /* EXEMPLO 2.2
    railway = ExampleGraphs::Graph7();
    */

    /* EXEMPLO 2.3
    railway = ExampleGraphs::Graph8();
    */

    /* EXEMPLO 2.4
    railway = ExampleGraphs::Graph9();
    */

    /* EXEMPLO 3
    railway = ExampleGraphs::costGraph2();
    */

    /* EXEMPLO 4.1/4.2
    railway = ExampleGraphs::Graph4();
    */

    currMenuPage = 0;
    createMainMenu();
    createMenu1();
    createMenu2();
    createMenu3();
    createMenu4();
    createMenu5();
    createMenuReducedConnectivity();

    railway.setConnectedComponents();
}

/**
 * @brief Keeps the program running while the user doesn't leave the main menu. Makes the mnu perform the action according to the user's inserted option
 */
void Program::run()
{
    int option;
    while (currMenuPage != -1)
    {
        menus[currMenuPage].draw();

        cout << "\033[32mInsert an option: ";
        while (getMenuOption(option, menus[currMenuPage].getButtons().size()))
            cout << "\033[31mPlease insert a valid option: \033[0m";
        cout<<"\033[0m";
        Menu menu = menus[currMenuPage];
        menu.doAction(option - 1);
    }

    cleanMenus();
}

/**
 * @brief Tries to read the user's input for the menu option
 * @param option variable that will store the option
 * @param nButtons number of buttons on the current menu
 * @return true if the input provided wasn't in the right format, false otherwise
 */
bool Program::getMenuOption(int &option, int nButtons)
{
    cin >> option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    if (option <= 0 || option > nButtons)
        return true;

    return false;
}

/**
 * @brief Creates the main menu
 */
void Program::createMainMenu()
{
    menus.emplace_back("../src/menus/mainMenu");
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 1));
    menus[menus.size() - 1].addMenuItem(new MinCostMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 3));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, -1));
}

/**
 * @brief Creates menu for the direct flights and reachable destinations
 */
void Program::createMenu1()
{
    menus.emplace_back("../src/menus/menu1");
    menus[menus.size() - 1].addMenuItem(new MaxFlowUserInput(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new PairsMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 4));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 5));
    menus[menus.size() - 1].addMenuItem(new SinglePointMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 0));
}

/**
 * @brief Creates menu for the direct flights and reachable destinations
 */

void Program::createMenu2()
{
    menus.emplace_back("../src/menus/menu2");
    menus[menus.size() - 1].addMenuItem(new MinCostMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 0));
}

/**
 * @brief Creates the show menu
 */
void Program::createMenu3() {
    menus.emplace_back("../src/menus/menu3");

    menus[menus.size() - 1].addMenuItem(new ReducedConnectivityMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new TopSegmentFailure(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 0));
}

void Program::createMenu4() {
    menus.emplace_back("../src/menus/menu4");

    menus[menus.size() - 1].addMenuItem(new DistrictBrute(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new District(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 1));
}

void Program::createMenu5() {
    menus.emplace_back("../src/menus/menu5");

    menus[menus.size() - 1].addMenuItem(new MunicipalitiesBrute(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new Municipalities(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 1));
}

/**
 * @brief deallocates memory that was allocated for each menuItem in each menu
 * Complexity: O(N*M) being N the number of menus and M the number of menuItems in each menu
 */
void Program::cleanMenus()
{
    for (Menu menu : menus)
    {
        for (MenuItem *menuItem : menu.getActions())
        {
            delete menuItem;
        }
    }
}

void Program::createMenuReducedConnectivity() {
    menus.emplace_back("../src/menus/reducedConnectivity");
    menus[menus.size() - 1].addMenuItem(new ReducedConnectivityMaxFlow(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new TopSegmentFailure(currMenuPage, railway));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, railway, 0));
}

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Ball.hpp"
#include "Map.hpp"
#include "Enemies.hpp"
#include "Light.hpp"

using namespace std;

class Menu
{
    public:
		Menu();
    private:
		void mainMenu();
		void gameMenu();
		void pauseMenu();
		sf::RenderWindow window;
		int windowX, windowY;
		sf::Font font;
		sf::Text text;
		sf::Clock clock;
		float eclipsed;
};

#endif

#include "Menu.hpp"

#define MATH_PI (3.14159265359)

Menu::Menu(){
	// create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	windowX = 1000, windowY = 1000;
    window.create(sf::VideoMode(windowX,windowY), "My window", sf::Style::Default, settings);
	window.setKeyRepeatEnabled(false);

	// create font
	font.loadFromFile("arial.ttf");

	// create text
	text.setFont(font);

	// define eclipsed time
	eclipsed = 1;
	
	//start the game
	mainMenu();
}

void Menu::mainMenu(){
	
	gameMenu();
}

void Menu::gameMenu(){
	
    string mapname = "map.txt";

    //create map
    Map level;
    level.loadMap(mapname, windowX, windowY);

    // create ball for player
    Ball player;
    player.spawnBall();

    Enemies enemy;
	
	enemy.setWindowSize(window.getSize());
	enemy.setWalls(level.getWalls());
	enemy.setBallPos(&player.getPos());

    Light light(windowX, windowY);
    light.getMap(level);
	light.createLight(player.getX(), player.getY());
	light.createLight(windowX/2, windowY/2, 1000);
		

	// start loop
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            player.listenMouse(event);
            light.listenMouse(event);
		}
		// wasd key events


		// clear window

        window.clear(sf::Color::Black);

		// do game stuff


		//draw map
		level.drawMap(window);
		level.setBallData(player);
		
		//draw player
		player.setFps(1.f/eclipsed);

		player.moveBall();
        player.drawBall(window);
        player.makeLightning(window);
		
		enemy.move(eclipsed);
		enemy.drawEnemy(window);
		
		light.setLightPos(0, player.getX(), player.getY());

		light.DrawEffects(window, player.getX(), player.getY());

		// end the current frame
		eclipsed = clock.restart().asSeconds();
		// display fps
		std::ostringstream s;
		s << 1.f/eclipsed << endl << player.getSpeedX() << " " << player.getSpeedY() << endl << player.getPower();
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);


		// draw stuff on window
        window.display();
        //wait();
    }
}

void Menu::pauseMenu(){
	
}
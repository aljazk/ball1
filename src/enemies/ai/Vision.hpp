#ifndef VISION_H
#define VISION_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <iostream>
#include <cmath>

//#include <SFML/Graphics.hpp>

class Vision{
		std::vector<sf::Vector2i> wall;
		sf::Vector2f *ballPos;
		sf::Vector2f pos;
	public:
		Vision();
		void setWall(std::vector<sf::Vector2i>);
		void setBallPos(sf::Vector2f*);
		sf::Vector2f getBallPos();
		void setPos(sf::Vector2f);
		void setPos(float, float);
		float getAngle();
		float getAngle(sf::Vector2f);
		bool check();
		bool check(sf::Vector2f);
		sf::Vector2f getBlock();
		sf::Vector2f getBlock(sf::Vector2f);
		/* draws vision lines for debugging 
		bool checkVision(sf::Vector2f, sf::RenderWindow&);
		sf::Vector2f checkObstacle(sf::Vector2f, sf::RenderWindow&);
		*/
};

#endif
#ifndef ASTAR_H
#define ASTAR_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#define GRID_SIZE (50)

class Astar{
		std::vector< std::vector<char> > grid;
		sf::Vector2u windowSize;
	public:
		Astar();
		void setWindowSize(sf::Vector2u);
		void setWall(std::vector<sf::Vector2i>);
		bool findPath(sf::Vector2f, sf::Vector2f);
};

#endif
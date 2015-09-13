#ifndef FINDPATH_H
#define FINDPATH_H

#include <SFML/System/Vector2.hpp>
#include "astar/Astar.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define GRID_SIZE (50)

class FindPath{
		std::vector< std::vector<char> > grid;
		sf::Vector2u windowSize;
	public:
		FindPath();
		void setWindowSize(sf::Vector2u);
		void setWall(std::vector<sf::Vector2i>);
		//bool FindPath(sf::Vector2f, sf::Vector2f);
};

#endif
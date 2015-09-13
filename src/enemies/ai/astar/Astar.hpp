#ifndef ASTAR_H
#define ASTAR_H

#include "Node.hpp"
#include <vector>
#include <iostream>
#include <cmath>

class Astar{
		std::vector< Node > nodes;
		unsigned int endX, endY;
	public:
		Astar();
		Astar(unsigned int, unsigned int, unsigned int, unsigned int);
		unsigned int getLowCost();
		void addNode(unsigned int, unsigned int, int, int, int);
};

#endif
#ifndef BOMB_H
#define BOMB_H

#include "ai/VertQuad.hpp"
#include "ai/Vision.hpp"
#include "ai/Astar.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

class Bomb{
		sf::Vector2f pos;
		float hp, dmg;
		VertQuad quad;
    public:
		Bomb();
		void getVertex(sf::VertexArray&);
		void draw();
		void move(float, Vision);
		void setPos(float, float);
}; 

#endif

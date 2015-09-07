#ifndef TURRET_H
#define TURRET_H

#include "ai/VertQuad.hpp"
#include "ai/Vision.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

class Turret{
		sf::Vector2f pos;
		float hp, dmg;
		VertQuad quad;
		float angle;
		float cooldown;
    public:
		Turret();
		void getVertex(sf::VertexArray&);
		void draw();
		void move(float, Vision);
		void setPos(float, float);
		bool shoot(sf::Vector2f&, sf::Vector2f&);
}; 

#endif

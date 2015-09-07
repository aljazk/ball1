#ifndef BULLET_H
#define BULLET_H

#include "VertQuad.hpp"

class Bullet{
		sf::Vector2f pos;
		sf::Vector2f vel;
		VertQuad quad;
	public:
		Bullet();
		Bullet(sf::Vector2f, sf::Vector2f);
		void setPos(sf::Vector2f);
		void setVel(sf::Vector2f);
		void set(sf::Vector2f, sf::Vector2f);
		void getVertex(sf::VertexArray&);
		void move(float);
		
};

#endif
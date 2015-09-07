#ifndef WERTQUAD_H
#define WERTQUAD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

class VertQuad{
		sf::Vector2f texPos;
		sf::Vector2f texSize;
		sf::Vector2f objPos;
		sf::Vector2f objSize;
		sf::Vector2f center;
		float angle;
	public:
		VertQuad();
		VertQuad(sf::Vector2f, sf::Vector2f, sf::Vector2f);
		VertQuad(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
		void set(sf::Vector2f, sf::Vector2f, sf::Vector2f);
		void set(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
		void setCenter();
		void setCenter(sf::Vector2f);
		void setAngle(float);
		void rotateVertex(float&, float&);
		void add(sf::VertexArray&);
		
}; 

#endif // WERTQUAD_H

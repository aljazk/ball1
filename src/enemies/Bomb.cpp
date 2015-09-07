#include "Bomb.hpp"

Bomb::Bomb(){
	pos.x = 0;
	pos.y = 0;
	hp = 10;
	dmg = 10;
}

void Bomb::getVertex(sf::VertexArray& vert){
	quad.set(sf::Vector2f(155,0), sf::Vector2f(40,40), pos);
	quad.add(vert);
}

void Bomb::draw(){
	cout << hp << endl;
}

void Bomb::move(float eclipsed, Vision vision){
	vision.setPos(pos);
}

void Bomb::setPos(float x, float y){
	pos.x = x;
	pos.y = y;
}
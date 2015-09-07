#include "Bullet.hpp"

Bullet::Bullet(){
	pos.x = 0;
	pos.y = 0;
	vel.x = 0;
	vel.y = 0;
}

Bullet::Bullet(sf::Vector2f newPos, sf::Vector2f newVel){
	pos = newPos;
	vel = newVel;
}

void Bullet::setPos(sf::Vector2f newPos){
	pos = newPos;
}

void Bullet::setVel(sf::Vector2f newVel){
	vel = newVel;
}

void Bullet::set(sf::Vector2f newPos, sf::Vector2f newVel){
	pos = newPos;
	vel = newVel;
}

void Bullet::getVertex(sf::VertexArray& vert){
	quad.set(sf::Vector2f(46,51), sf::Vector2f(8,8), pos);
	quad.add(vert);
}

void Bullet::move(float eclipsed){
	pos.x += vel.x * eclipsed;
	pos.y += vel.y * eclipsed;
}
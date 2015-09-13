#include "Enemies.hpp"

int random(int, int);

Enemies::Enemies(){
	if (!texture.loadFromFile("enemy.png")){
		std::cout << "Could not load enemy.png texture" << std::endl;
	}
	texture.setSmooth(true);
	Basick newBasick;
	for(int i=0; i<1; i++){
		newBasick.setPos(random(0,1000), random(0,1000));
		basick.push_back(newBasick);
	}
	Bomb newBomb;
	for(int i=0; i<10; i++){
		newBomb.setPos(random(0,1000), random(0,1000));
		bomb.push_back(newBomb);
	}
	Turret newTurret;
	for(int i=0; i<10; i++){
		newTurret.setPos(random(0,1000), random(0,1000));
		turret.push_back(newTurret);
	}
}

void Enemies::drawEnemy(sf::RenderWindow& window){
	sf::VertexArray vert;
	vert.setPrimitiveType(sf::Quads);
	vert.resize(0);
	for(unsigned int i=0; i<basick.size(); i++){
		basick[i].getVertex(vert);
	}
	for(unsigned int i=0; i<bomb.size(); i++){
		bomb[i].getVertex(vert);
	}
	for(unsigned int i=0; i<turret.size(); i++){
		turret[i].getVertex(vert);
	}
	for(unsigned int i=0; i<bullets.size(); i++){
		bullets[i].getVertex(vert);
	}
	
	window.draw(vert, &texture);
}

void Enemies::setWalls(std::vector<sf::Vector2i> newWall){
	vision.setWall(newWall);
	astar.setWall(newWall);
}

void Enemies::setWindowSize(sf::Vector2u newWindowSize){
	astar.setWindowSize(newWindowSize);
}

void Enemies::move(float eclipsed){
	for(unsigned int i=0; i<basick.size(); i++){
		basick[i].move(eclipsed, vision);
		sf::Vector2f bullPos, bullVel;
		if(basick[i].shoot(bullPos, bullVel)){
			Bullet newBullet;
			newBullet.set(bullPos, bullVel);
			bullets.push_back(newBullet);
		}
	}
	for(unsigned int i=0; i<bomb.size(); i++){
		bomb[i].move(eclipsed, vision);
	}
	for(unsigned int i=0; i<turret.size(); i++){
		turret[i].move(eclipsed, vision);
		sf::Vector2f bullPos, bullVel;
		if(turret[i].shoot(bullPos, bullVel)){
			Bullet newBullet;
			newBullet.set(bullPos, bullVel);
			bullets.push_back(newBullet);
		}
	}
	for(unsigned int i=0; i<bullets.size(); i++){
		bullets[i].move(eclipsed);
	}
}

void Enemies::setBallPos(sf::Vector2f *getBallPos){
	vision.setBallPos(getBallPos);
}
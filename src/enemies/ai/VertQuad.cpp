#include "VertQuad.hpp"

VertQuad::VertQuad(){
	texPos.x = 0;
	texPos.y = 0;
	texSize.x = 0;
	texSize.y = 0;
	objPos.x = 0;
	objPos.y = 0;
	objSize.x = 0;
	objSize.y = 0;
	center.x = 0;
	center.y = 0;
	angle = 0;
}

VertQuad::VertQuad(sf::Vector2f newTexPos, sf::Vector2f newTexSize, sf::Vector2f newObjPos){
	set(newTexPos, newTexSize, newObjPos);
	setCenter();
	angle = 0;
}

VertQuad::VertQuad(sf::Vector2f newTexPos, sf::Vector2f newTexSize, sf::Vector2f newObjPos, sf::Vector2f newObjSize){
	set(newTexPos, newTexSize, newObjPos, newObjSize);
	setCenter();
	angle = 0;
}

void VertQuad::set(sf::Vector2f newTexPos, sf::Vector2f newTexSize, sf::Vector2f newObjPos){
	texPos = newTexPos;
	texSize = newTexSize;
	objPos = newObjPos;
	objSize = newTexSize;
	setCenter();
	angle = 0;
}

void VertQuad::set(sf::Vector2f newTexPos, sf::Vector2f newTexSize, sf::Vector2f newObjPos, sf::Vector2f newObjSize){
	texPos = newTexPos;
	texSize = newTexSize;
	objPos = newObjPos;
	objSize = newObjSize;
	setCenter();
	angle = 0;
}

void VertQuad::setCenter(){
	center.x = objSize.x/2;
	center.y = objSize.y/2;
}

void VertQuad::setCenter(sf::Vector2f newCenter){
	center = newCenter;
}

void VertQuad::setAngle(float newAngle){
	angle = newAngle;
}
	
void VertQuad::rotateVertex(float &cx, float &cy){
	float f = atan2(cx,cy)+(float)angle*M_PI/180;
	float dist = sqrt(pow(cx, 2)+pow(cy, 2));
	cx = cos(f)*dist;
	cy = sin(f)*dist;
}
	
void VertQuad::add(sf::VertexArray &vert){
	sf::Vertex vertex;
	float cx, cy;
	cx = -center.x;
	cy = -center.y;
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x, texPos.y);
	vert.append(vertex);
	cx = -center.x+objSize.x;
	cy = -center.y; 
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x+texSize.x, texPos.y);
	vert.append(vertex);
	cx = -center.x+objSize.x;
	cy = -center.y+objSize.y; 
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x+texSize.x, texPos.y+texSize.y);
	vert.append(vertex);
	cx = -center.x;
	cy = -center.y+objSize.y; 
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x, texPos.y+texSize.y);
	vert.append(vertex);
	
}
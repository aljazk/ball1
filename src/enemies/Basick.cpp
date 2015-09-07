#include "Basick.hpp"

Basick::Basick(){
	pos.x = 0;
	pos.y = 0;
	hp = 10;
	dmg = 10;
	angle = 0;
	cooldown = 3;
}

void Basick::getVertex(sf::VertexArray& vert){
	quad.set(sf::Vector2f(45,0), sf::Vector2f(50,50), pos);
	quad.add(vert);
	
	quad.set(sf::Vector2f(0,0), sf::Vector2f(40,60), pos);
	quad.setCenter(sf::Vector2f(20,20));
	quad.setAngle(angle);
	quad.add(vert);
}

void Basick::draw(){
	cout << hp << endl;
}

float fixAngle(float ang){
	if (ang > 360){
		ang -= 360;
	} else if (ang < 0){
		ang += 360;
	}
	return ang;
}

void Basick::move(float eclipsed, Vision vision){
	angle = fixAngle(angle);
	vision.setPos(pos);
	
	if(vision.check()){
		cooldown -= eclipsed;
		float pref = vision.getAngle();
		pref = fixAngle(pref);
		float dist = pref - angle;
		dist = fixAngle(dist);
		if (dist < 180){
			angle += 100 * eclipsed;
		} else {
			angle -= 100 * eclipsed;
		}
	}
}

void Basick::setPos(float x, float y){
	pos.x = x;
	pos.y = y;
}

bool Basick::shoot(sf::Vector2f &bullPos, sf::Vector2f &bullVel){
	if (cooldown < 0){
		cooldown = 1;
		bullPos = pos;
		float ang = angle*M_PI/180;
		float power = 200;
		bullPos.x += cos(ang)*42;
		bullPos.y += sin(ang)*42;
		bullVel = sf::Vector2f(cos(ang)*power, sin(ang)*power);
		return 1;
	} else {
		return 0;
	}
}
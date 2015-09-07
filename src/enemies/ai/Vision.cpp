#include "Vision.hpp"

Vision::Vision(){
	pos.x = 0;
	pos.y = 0;
}

void Vision::setWall(std::vector<sf::Vector2i> newWall){
	wall = newWall;
}

void Vision::setBallPos(sf::Vector2f *getBallPos){
	ballPos = getBallPos;
}

sf::Vector2f Vision::getBallPos(){
	return *ballPos;
}

void Vision::setPos(sf::Vector2f getPos){
	pos = getPos;
}

void Vision::setPos(float x, float y){
	pos = sf::Vector2f(x,y);
}

float Vision::getAngle(){
	float f = atan2(ballPos-> y - pos.y, ballPos->x - pos.x);
	return f/M_PI*180;
}

float Vision::getAngle(sf::Vector2f getPos){
	float f = atan2(ballPos-> y - getPos.y, ballPos->x - getPos.x);
	return f/M_PI*180;
}

bool Vision::check(){
	float f = atan2(pos.x - ballPos->x, pos.y - ballPos->y);
	float dist = sqrt(pow(pos.x - ballPos->x,2) + pow(pos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	for(unsigned int i=0; i<joints; i++){
		float cx = pos.x-sin(f)*jointSize*i;
		float cy = pos.y-cos(f)*jointSize*i;
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				return 0;
			}
		}
	}
	return 1;
}

bool Vision::check(sf::Vector2f getPos){
	float f = atan2(getPos.x - ballPos->x, getPos.y - ballPos->y);
	float dist = sqrt(pow(getPos.x - ballPos->x,2) + pow(getPos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	for(unsigned int i=0; i<joints; i++){
		float cx = getPos.x-sin(f)*jointSize*i;
		float cy = getPos.y-cos(f)*jointSize*i;
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				return 0;
			}
		}
	}
	return 1;
}

sf::Vector2f Vision::getBlock(){
	float f = atan2(pos.x - ballPos->x, pos.y - ballPos->y);
	float dist = sqrt(pow(pos.x - ballPos->x,2) + pow(pos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	for(unsigned int i=0; i<joints; i++){
		float cx = pos.x-sin(f)*jointSize*i;
		float cy = pos.y-cos(f)*jointSize*i;
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				return sf::Vector2f(cx,cy);
			}
		}
	}
	return sf::Vector2f(pos.x,pos.y);
}

sf::Vector2f Vision::getBlock(sf::Vector2f getPos){
	float f = atan2(getPos.x - ballPos->x, getPos.y - ballPos->y);
	float dist = sqrt(pow(getPos.x - ballPos->x,2) + pow(getPos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	for(unsigned int i=0; i<joints; i++){
		float cx = getPos.x-sin(f)*jointSize*i;
		float cy = getPos.y-cos(f)*jointSize*i;
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				return sf::Vector2f(cx,cy);
			}
		}
	}
	return sf::Vector2f(getPos.x,getPos.y);
}

/* draws vision lines for debugging 

bool Vision::checkVision(sf::Vector2f getPos, sf::RenderWindow &window){
	float f = atan2(getPos.x - ballPos->x, getPos.y - ballPos->y);
	float dist = sqrt(pow(getPos.x - ballPos->x,2) + pow(getPos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	line.resize(joints+2);
	line[0].getPosition = getPos;
	for(unsigned int i=0; i<joints; i++){
		float cx = getPos.x-sin(f)*jointSize*i;
		float cy = getPos.y-cos(f)*jointSize*i;
		line[i+1].getPosition = sf::Vector2f(cx,cy);
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				line[i+1].color = sf::Color::Red;
				line.resize(i+2);
				window.draw(line);
				return 1;
			}
		}
		if(i%2 == 0)
			line[i+1].color = sf::Color::Yellow;
	}
	line[joints+1].getPosition = *ballPos;
	window.draw(line);
	return 0;
}

sf::Vector2f Vision::checkObstacle(sf::Vector2f getPos, sf::RenderWindow &window){
	sf::VertexArray line;
	line.setPrimitiveType(sf::LinesStrip);
	
	float f = atan2(getPos.x - ballPos->x, getPos.y - ballPos->y);
	float dist = sqrt(pow(getPos.x - ballPos->x,2) + pow(getPos.y - ballPos->y,2));
	const unsigned int jointSize = 10;
	const unsigned int joints = dist/jointSize;
	
	line.resize(joints+2);
	line[0].getPosition = getPos;
	for(unsigned int i=0; i<joints; i++){
		float cx = getPos.x-sin(f)*jointSize*i;
		float cy = getPos.y-cos(f)*jointSize*i;
		line[i+1].getPosition = sf::Vector2f(cx,cy);
		for(unsigned int j=0; j<wall.size(); j+=2){
			if(cx > wall[j].x && cx < wall[j+1].x && cy > wall[j].y && cy < wall[j+1].y){
				line[i+1].color = sf::Color::Red;
				line.resize(i+2);
				window.draw(line);
				return sf::Vector2f(cx,cy);
			}
		}
		if(i%2 == 0)
			line[i+1].color = sf::Color::Yellow;
	}
	line[joints+1].getPosition = *ballPos;
	window.draw(line);
	return sf::Vector2f(getPos.x,getPos.y);
} */
#include "Node.hpp"

Node::Node(){
	posx = 0;
	posy = 0;
	gcost = -1;
	hcost = -1;
	parent = -1;
}

Node::Node(unsigned int setPosX, unsigned int setPosY){
	posx = setPosX;
	posy = setPosY;
	gcost = -1;
	hcost = -1;
	parent = -1;
}

void Node::set(unsigned int setPosX, unsigned int setPosY){
	posx = setPosX;
	posy = setPosY;
}

void Node::setCost(int costG){
	gcost = costG;
}

void Node::setCost(int costG, int costH){
	gcost = costG;
	hcost = costH;
}

void Node::setParent(int newParent){
	parent = newParent;
}

int Node::getCost(){
	return gcost + hcost;
}
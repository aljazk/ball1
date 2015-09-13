#include "Astar.hpp"

Astar::Astar(){
	nodes.push_back(Node(0,0));
	endX = 0;
	endY = 0;
}

Astar::Astar(unsigned int startX, unsigned int startY, unsigned int setEndX, unsigned int setEndY){
	nodes.push_back(Node(startX,startY));
	endX = setEndX;
	endY = setEndY;
}

void Astar::addNode(unsigned int posX, unsigned int posY, int costG, int costH, int parent){
	nodes.push_back(Node(posX, posY));
	nodes[nodes.size()-1].setCost(costG, costH);
	nodes[nodes.size()-1].setParent(parent);
}

unsigned int Astar::getLowCost(){
	int lowCost = -1;
	unsigned int li = 0;
	for(unsigned int i=0; i<nodes.size(); i++){
		int cost = nodes[i].getCost();
		if (lowCost == -1){
			lowCost = cost;
			li = i;
		} else if (lowCost > cost){
			lowCost = cost;
			li = i;
		}
	}
	return li;	
}
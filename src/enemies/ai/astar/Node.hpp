#ifndef NODE_H
#define NODE_H

class Node{
		unsigned int posx, posy;
		int gcost, hcost;
		int parent;
	public:
		Node();
		Node(unsigned int, unsigned int);
		void set(unsigned int, unsigned int);
		void setCost(int);
		void setCost(int, int);
		void setParent(int);
		int getCost();
};

#endif
#include "FindPath.hpp"

FindPath::FindPath(){
	
}

void FindPath::setWindowSize(sf::Vector2u newWindowSize){
	windowSize = newWindowSize;
}

void printMap(std::vector< std::vector<char> > map){
	for (unsigned int i = 0; i < map.size(); i++){
		for (unsigned int j = 0; j < map[i].size(); j++){
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "map printed" << std::endl;
}

void FindPath::setWall(std::vector<sf::Vector2i> newWall){
	std::vector<sf::Vector2i> wall;
	wall = newWall;
	grid.resize(windowSize.x/GRID_SIZE+2);
	for (unsigned int i = 0; i < grid.size(); i++){
		if (i == 0 || i == grid.size()-1){
			grid[i].resize(windowSize.y/GRID_SIZE+2, 120);
		} else {
			grid[i].resize(windowSize.y/GRID_SIZE+2, 0);
		}
		grid[i][0] = 120;
		grid[i][grid[i].size()-1] = 120;
	}
	printMap(grid);
	for (unsigned int i = 0; i < wall.size(); i+=2){
		unsigned int posX = int(wall[i].x/GRID_SIZE);
		unsigned int posY = int(wall[i].y/GRID_SIZE);
		unsigned int sizeX = int(wall[i+1].x/GRID_SIZE);
		unsigned int sizeY = int(wall[i+1].y/GRID_SIZE);
		for (unsigned int i = posX; i < sizeX; i++){
			for (unsigned int j = posY; j < sizeY; j++){
				grid[i][j] = 120;
			}
		}
	}
	printMap(grid);
}

int calcCost(int nx, int ny, int ex, int ey){
	float dist = sqrt(pow(nx - ex, 2) + pow(ny - ey, 2));
	return dist*10;
}

/*
bool FindPath::findPath(sf::Vector2f sTarget, sf::Vector2f sStart){
	sf::Vector2u target = sf::Vector2u((int)sTarget.x/GRID_SIZE+1, (int)sTarget.y/GRID_SIZE+1);
	sf::Vector2u start = sf::Vector2u((int)sStart.x/GRID_SIZE+1, (int)sStart.y/GRID_SIZE+1);
	grid[start.x][start.y] = 1;
	
	printMap(grid);
	
	std::vector<Node> nodes;
	Node newNode;
	newNode.pos = start;
	newNode.gcost = 0;
	newNode.cost = -1;
	newNode.parent = -1;
	nodes.push_back(newNode);
	
	while(true){
		sf::Vector2u pos;
		int hcost = 1000, hi = 0;
		for(unsigned int n=0; n<nodes.size(); n++){
			if(nodes[n].cost != -1){
				if (nodes[n].cost < hcost){
					hcost = nodes[n].cost;
					hi = n;
				}
			}
		}
		nodes[hi].cost = -1;
		pos = nodes[hi].pos;
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				bool makeNew = true;
				if (i == 0 && j == 0){
					makeNew = false;
				}
				for(unsigned int n=0; n<nodes.size(); n++){
					if (nodes[n].pos.x == pos.x+i && nodes[n].pos.y == pos.y+j){
						makeNew = false;
						int cost = 0;
						if (i == 0 || j == 0){
							cost = 10;
						} else {
							cost = 14;
						}
						if(nodes[n].gcost > nodes[hi].gcost + cost){
							nodes[n].gcost = nodes[hi].gcost + cost;
							nodes[n].parent = hi;
						}
					}
				}
				if(grid[pos.x+i][pos.y+j] == 'x'){
					makeNew = false;
				}
				if (makeNew){
					newNode.pos.x = pos.x+i;
					newNode.pos.y = pos.y+j;
					newNode.cost = calcCost(newNode.pos.x, newNode.pos.y, target.x, target.y);
					if (newNode.cost == 0){
						
						for (unsigned int x = 0; x < grid.size(); x++){
							for (unsigned int y = 0; y < grid[i].size(); y++){
								if (grid[x][y] != 'x'){
									grid[x][y] = 0;
								}
							}
						}
						int finalNode = nodes.size()-1;
						while(finalNode != -1){
							std::cout << finalNode << std::endl;
							grid[nodes[finalNode].pos.x][nodes[finalNode].pos.y] = 'o';
							finalNode = nodes[finalNode].parent;
						} 
						printMap(grid);
						
						return 1;
					}
					newNode.parent = hi;
					if (i == 0 || j == 0){
						newNode.gcost = nodes[hi].gcost + 10;
					} else {
						newNode.gcost = nodes[hi].gcost + 14;
					}
					newNode.cost += newNode.gcost;
					nodes.push_back(newNode);
				}
			}
		}
		int os = 0;
		for(unsigned int n=0; n<nodes.size(); n++){
			if(nodes[n].cost != -1){
				grid[nodes[n].pos.x][nodes[n].pos.y] = 'o';
				os++;
			} else {
				grid[nodes[n].pos.x][nodes[n].pos.y] = 'O';
			}
		}
		if(os == 0){
			std::cout << "Path cannot be found" << std::endl;
			return 0;
		}
	}
	return 0;
}
*/
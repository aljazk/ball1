#ifndef ENEMIES_H
#define ENEMIES_H

#include "Map.hpp"
#include "enemies/Basick.hpp"
#include "enemies/Bomb.hpp"
#include "enemies/Turret.hpp"
#include "enemies/ai/Bullet.hpp"
#include "enemies/ai/FindPath.hpp"

class Enemies{
		std::vector<Basick> basick;
		std::vector<Bomb> bomb;
		std::vector<Turret> turret;
		Vision vision;
		FindPath astar;
		std::vector<Bullet> bullets;
		sf::Texture texture;
		sf::Sprite sprite;
    public:
        Enemies();
		void drawEnemy(sf::RenderWindow&);
		void setWalls(std::vector<sf::Vector2i>);
		void setWindowSize(sf::Vector2u);
		void move(float);
		void setBallPos(sf::Vector2f*);
		/*
        void drawEnemies(sf::RenderWindow&);
        void moveEnemies(Ball &, int, Map &);
        void attackEnemies(Ball &);
        void loadEnemies(string);
        void drawDmg(sf::RenderWindow&);
		*/
};

#endif // ENEMIES_H

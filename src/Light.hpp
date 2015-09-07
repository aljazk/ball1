#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class Light
{
    public:
        Light(int,int);
		unsigned int createLight(int x, int y, int lRad = 500, sf::Vector3f color = sf::Vector3f(1,1,.9), int lResize = 50);
		void removeLight(unsigned int id);
		void setLightPos(unsigned int id, float x, float y);
        void getMap(Map);
        void DrawEffects(sf::RenderWindow&, float, float);
        void listenMouse(sf::Event);
        void intrasectLines(float, float, int);
    private:
		vector<float> lightX, lightY;
		vector<int> lightRadius, lightResize, lightSpeed;
		vector<sf::Vector3f> lightColor;
        sf::VertexArray lineVertex;
        sf::VertexArray lightBall;
        sf::VertexArray lightTriangles;
        sf::RenderTexture lightBlend;
        sf::RenderTexture lightsBlend;
        sf::Sprite displayLight;
        sf::Sprite addLight;
        sf::RenderStates states;
        sf::Shader shader;
        vector<int> triangleX, triangleX1;
        vector<int> triangleY, triangleY1;
        vector<int> quadX, quadX1;
        vector<int> quadY, quadY1;
        float mousex, mousey;
        float time;
};

#endif // LIGHT_H


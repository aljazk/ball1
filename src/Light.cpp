#include "Light.hpp"

#define MATH_PI (3.14159265359)


Light::Light(int wx, int wy){
    lineVertex.setPrimitiveType(sf::Lines);
    lightBall.setPrimitiveType(sf::Quads);
    lightTriangles.setPrimitiveType(sf::Triangles);
    if (!lightBlend.create(wx,wy)){
        cout << "Cant create texture lightBlend" << endl;
    }
    if (!lightsBlend.create(wx,wy)){
        cout << "Cant create texture lightBlend" << endl;
    }
    lightBlend.setSmooth(true);
    lightsBlend.setSmooth(true);
    addLight.setTexture(lightsBlend.getTexture());
    displayLight.setPosition(sf::Vector2f(0,0));
    displayLight.setTexture(lightBlend.getTexture());
    shader.loadFromFile("a.vert", "a.frag");
    //shader.loadFromFile("a.frag", sf::Shader::Fragment);
    time = 0;
}

unsigned int Light::createLight(int x, int y, int lRad, sf::Vector3f color,  int lResize){
	lightX.push_back(x);
	lightY.push_back(y);
	lightRadius.push_back(lRad);
	lightColor.push_back(color);
	lightResize.push_back(lResize);
	return lightX.size()-1;
}

void Light::removeLight(unsigned int id){
	lightX.erase(lightX.begin()+id);
	lightY.erase(lightY.begin()+id);
	lightRadius.erase(lightRadius.begin()+id);
	lightColor.erase(lightColor.begin()+id);
	lightResize.erase(lightResize.begin()+id);
}

void Light::setLightPos(unsigned int id, float x, float y){
	lightX[id] = x;
	lightY[id] = y;
}

void Light::getMap(Map level){
    vector<int> wallX, wallY, doorX, doorY;
    level.getWalls(wallX, wallY, doorX, doorY);
    vector<int> linesX;
    vector<int> linesY;
    linesX.resize(wallX.size()/2*4);
    linesY.resize(wallY.size()/2*4);
    for(unsigned int i=0; i<wallX.size(); i+=2){
        linesX[i/2*4] = wallX[i];
        linesY[i/2*4] = wallY[i];
        linesX[i/2*4+1] = wallX[i+1];
        linesY[i/2*4+1] = wallY[i];
        linesX[i/2*4+2] = wallX[i+1];
        linesY[i/2*4+2] = wallY[i+1];
        linesX[i/2*4+3] = wallX[i];
        linesY[i/2*4+3] = wallY[i+1];
    }
    triangleX.resize(linesX.size()); triangleX1.resize(linesX.size());
    triangleY.resize(linesY.size()); triangleY1.resize(linesY.size());
    /*
    triangleX.resize(linesX.size()+4); triangleX1.resize(linesX.size()+4);
    triangleY.resize(linesY.size()+4); triangleY1.resize(linesY.size()+4);
    int screenX = 1000, screenY = 1000;
    triangleX[0] = 0; triangleX1[0] = screenX;
    triangleY[0] = 0; triangleY1[0] = 0;
    triangleX[1] = screenX; triangleX1[1] = screenX;
    triangleY[1] = 0; triangleY1[1] = screenY;
    triangleX[2] = screenX; triangleX1[2] = 0;
    triangleY[2] = screenY; triangleY1[2] = screenY;
    triangleX[3] = 0; triangleX1[3] = 0;
    triangleY[3] = screenY; triangleY1[3] = 0;
    */
    for(unsigned int i=0; i<linesX.size();i++){
        triangleX[i] = linesX[i];
        triangleY[i] = linesY[i];
        if ((i+1)%4 != 0){
            triangleX1[i] = linesX[i+1];
            triangleY1[i] = linesY[i+1];
        } else {
            triangleX1[i] = linesX[i-3];
            triangleY1[i] = linesY[i-3];
        }
    }
    quadX.resize(triangleX.size()); quadX1.resize(triangleX1.size());
    quadY.resize(triangleY.size()); quadY1.resize(triangleY1.size());
}
/*
void Light::intrasectLines(){
    for (float i=0; i<lightX.size(); i++){
        float f = i*6.28/lightX.size();
        int lightCenterX = mousex;
        int lightCenterY = mousey;
        lightX[i] = lightCenterX + (sin(f) * 500);
        lightY[i] = lightCenterY + (cos(f) * 500);
        for(int c=0; c<linesX.size()-1; c++){
            if (c%5 != 4){
                float s1_x = lightX[i] - lightCenterX;
                float s1_y = lightY[i] - lightCenterY;
                float s2_x = linesX[c+1] - linesX[c];
                float s2_y = linesY[c+1] - linesY[c];
                float s = (-s1_y * (lightCenterX - linesX[c]) + s1_x  * (lightCenterY - linesY[c])) / (-s2_x * s1_y + s1_x * s2_y);
                float t = ( s2_x * (lightCenterY - linesY[c]) - s2_y * (lightCenterX - linesX[c])) / (-s2_x * s1_y + s1_x * s2_y);
                if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
                    lightX[i] = lightCenterX + (t * s1_x);
                    lightY[i] = lightCenterY + (t * s1_y);
                }
            }
        }
    }
}*/
void Light::intrasectLines(float lightPosX, float lightPosY, int lightDistance){
    lightDistance += 50;
	bool inside = false;
	for(unsigned int i=0; i<triangleX.size(); i+=4){
		if (lightPosX > triangleX[i] && lightPosX < triangleX[i+2] && lightPosY > triangleY[i] && lightPosY < triangleY[i+2]){
			inside = true;
		}
	}
	if (!inside){
		for(unsigned int i=0; i<triangleX.size();i++){
			float dist = sqrt(pow(lightPosX-triangleX[i], 2)+pow(lightPosY-triangleY[i], 2));
			float addDistance = -lightDistance + dist;
			float f;
			if (addDistance < 0){
				f = atan2(lightPosY - triangleY[i], lightPosX - triangleX[i]);
				quadX[i] = cos(f)*addDistance + triangleX[i];
				quadY[i] = sin(f)*addDistance + triangleY[i];
			} else {
				quadX[i] = triangleX[i];
				quadY[i] = triangleY[i];
			}
			dist = sqrt(pow(lightPosX-triangleX1[i], 2)+pow(lightPosY-triangleY1[i], 2));
			addDistance = -lightDistance + dist;
			if (addDistance < 0){
				f = atan2(lightPosY - triangleY1[i], lightPosX - triangleX1[i]);
				quadX1[i] = cos(f)*addDistance + triangleX1[i];
				quadY1[i] = sin(f)*addDistance + triangleY1[i];
			} else {
				quadX1[i] = triangleX1[i];
				quadY1[i] = triangleY1[i];
			}
		}
	}
}


void Light::DrawEffects(sf::RenderWindow &window, float ballx, float bally){
    time += .1;
    int lightNumber = lightX.size();
    for(int i=0; i<lightNumber; i++){

        lightsBlend.clear(sf::Color::Black);
        states.blendMode = sf::BlendAdd;
        float lightPosX = 0;
        float lightPosY = 0;
		lightPosX = lightX[i];
		lightPosY = lightY[i];
		shader.setParameter("lightColor", lightColor[i]);
		/*
        if (i == 0){
            lightPosX = ballx;
            lightPosY = bally;
            shader.setParameter("lightColor", sf::Vector3f(1,1,.9));
        } else if (i==1) {
            lightPosX = mousex;
            lightPosY = mousey;
            shader.setParameter("lightColor", sf::Vector3f(1,1,.9));
        } else {
            lightPosX = 500;
            lightPosY = 500;
            shader.setParameter("lightColor", sf::Vector3f(1,1,.9));
		}
		*/
		bool inside = false;
		for(unsigned int j=0; j<triangleX.size(); j+=4){
			if (lightPosX > triangleX[j] && lightPosX < triangleX[j+2] && lightPosY > triangleY[j] && lightPosY < triangleY[j+2]){
				inside = true;
			}
		}
		if (!inside){
        /*
        float f = 6.28/lightNumber * i;
        lightPosX -= cos(f)*300;
        lightPosY -= sin(f)*300;
        */
		sf::Vector2u wsize = window.getSize();
        shader.setParameter("mousePos", sf::Vector2f(lightPosX, wsize.y-lightPosY));
        shader.setParameter("time", time);

        lightBall.resize(4);
        int lightDistance = lightRadius[i];
        shader.setParameter("lightDistance", lightDistance);
        shader.setParameter("lightResize", 10);
        shader.setParameter("lightSpeed", 100);
        lightBall[0].position = sf::Vector2f(lightPosX-lightDistance, lightPosY-lightDistance);
        lightBall[1].position = sf::Vector2f(lightPosX+lightDistance, lightPosY-lightDistance);
        lightBall[2].position = sf::Vector2f(lightPosX+lightDistance, lightPosY+lightDistance);
        lightBall[3].position = sf::Vector2f(lightPosX-lightDistance, lightPosY+lightDistance);
        lightsBlend.draw(lightBall, &shader);
        lightBall.resize(quadX.size()*4);
        intrasectLines(lightPosX, lightPosY, lightDistance);
        for (unsigned int i=0; i<quadX.size(); i++){
            sf::Vertex *quads = &lightBall[i*4];
            quads[0].position = sf::Vector2f(triangleX[i], triangleY[i]);
            quads[1].position = sf::Vector2f(triangleX1[i], triangleY1[i]);
            quads[2].position = sf::Vector2f(quadX1[i], quadY1[i]);
            quads[3].position = sf::Vector2f(quadX[i], quadY[i]);
            for (int c=0; c<4; c++) quads[c].color = sf::Color(0,0,0,255);
        }
        states.blendMode = sf::BlendNone;
        lightsBlend.draw(lightBall, states);
        lightBall.clear();
        lightsBlend.display();
        states.blendMode = sf::BlendAdd;
        lightBlend.draw(addLight, states);
		}
    }
    lightBlend.display();
    states.blendMode = sf::BlendMultiply;

    window.draw(displayLight, states);
    lightBlend.clear(sf::Color::Transparent);

    /*
    lineVertex.resize(lightX.size()*2);
    for (int i=0; i<lightX.size()*2; i+=2){
        lineVertex[i].position = sf::Vector2f(mousex,mousey);
        lineVertex[i+1].position = sf::Vector2f(lightX[i/2],lightY[i/2]);
        lineVertex[i].color = sf::Color::Blue;
        lineVertex[i+1].color = sf::Color::Blue;
    }
    window.draw(lineVertex);
    lineVertex.resize(linesX.size()*2);
    for (int i=0; i<linesX.size()*2-2; i+=2){
        lineVertex[i].position = sf::Vector2f(linesX[i/2],linesY[i/2]);
        lineVertex[i+1].position = sf::Vector2f(linesX[i/2+1],linesY[i/2+1]);
        if (i%5 != 3){
            lineVertex[i].color = sf::Color::Blue;
            lineVertex[i+1].color = sf::Color::Blue;
        } else {
            lineVertex[i].color = sf::Color::Transparent;
            lineVertex[i+1].color = sf::Color::Transparent;
        }
    }

    window.draw(lineVertex);
    lightBall.resize(lightX.size()+2);
    lightBall[0].position = sf::Vector2f(mousex, mousey);
    lightBall[0].color = sf::Color(255,255,255,100);
    for(int i=0; i<lightX.size(); i++){
        lightBall[i+1].position = sf::Vector2f(lightX[i],lightY[i]);
        float dist = sqrt(pow(mousex-lightX[i], 2)+pow(mousey-lightY[i], 2));
        lightBall[i+1].color = sf::Color(255,255,255,(float)100/(float)500*(float)((float)500-dist));
    }
    lightBall[lightX.size()+1].position = sf::Vector2f(lightX[0], lightY[0]);
    float dist = sqrt(pow(mousex-lightX[0], 2)+pow(mousey-lightY[0], 2));
    lightBall[lightX.size()+1].color = sf::Color(255,255,255,(float)100/(float)500*(float)((float)500-dist));
    window.draw(lightBall);*/
    lightTriangles.resize(triangleX.size()*3);
    for(unsigned int i=0; i<triangleX.size(); i++){
        sf::Vertex *triangles = &lightTriangles[i*3];
        triangles[0].position = sf::Vector2f(mousex, mousey);
        triangles[0].color = sf::Color::Green;
        triangles[1].position = sf::Vector2f(triangleX[i], triangleY[i]);
        triangles[1].color = sf::Color::Black;
        triangles[2].position = sf::Vector2f(triangleX1[i], triangleY1[i]);
        triangles[2].color = sf::Color::Black;
        //for(int i=0; i<3; i++) triangles[i].color = sf::Color(0,0,255,155);
    }
    //window.draw(lightTriangles);


}

void Light::listenMouse(sf::Event event){
    if (event.type == sf::Event::MouseMoved){
        mousex = event.mouseMove.x;
        mousey = event.mouseMove.y;
    }
}

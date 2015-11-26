#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "structs.h"
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <windows.h>
#include <math.h>

#include <string>
#include <sstream>
#include <iostream>


using namespace sf;

template< class C > std::string ToString(C obj){
	return std::to_string(obj);
}

std::string ToString(char * cp){
	return std::string(cp);
}



void configPrepare(config & conf){
	conf.enemyImg.loadFromFile(conf.imageAdres);
	conf.friendImg.loadFromFile(conf.imageAdresF);
	conf.startBottomImg.loadFromFile(conf.startBottomAdrress);
	conf.exiteBottomImg.loadFromFile(conf.exiteBottomAdrress);
	conf.font.loadFromFile(conf.fontStyle);
	conf.text.setFont(conf.font);
	conf.text.setCharacterSize(conf.textCharacterSize);
	conf.text.setColor(sf::Color::Red);
	conf.text.setStyle(sf::Text::Bold);
	conf.text.setPosition(20, 20);
};

void gameInitializeSprite(config & conf, gameData & gData){
	gData.window.create(sf::VideoMode(800, 600), "Shooting");

	gData.enemyTexture.loadFromImage(conf.enemyImg);
	gData.enemy.setTexture(gData.enemyTexture);
	gData.enemyRect.height = conf.enemyImg.getSize().y;
	gData.enemyRect.width = conf.enemyImg.getSize().x;

	gData.friendTexture.loadFromImage(conf.friendImg);
	gData.friendd.setTexture(gData.friendTexture);
	gData.friendRect.height = conf.friendImg.getSize().y;
	gData.friendRect.width = conf.friendImg.getSize().x;

	gData.startBottomTex.loadFromImage(conf.startBottomImg);
	gData.startBottomSprite.setTexture(gData.startBottomTex);
	gData.startRect.height = conf.startBottomImg.getSize().y;
	gData.startRect.width = conf.startBottomImg.getSize().x;

	gData.exiteBottomTex.loadFromImage(conf.exiteBottomImg);
	gData.exiteBottomSprite.setTexture(gData.exiteBottomTex);
	gData.exiteRect.height = conf.exiteBottomImg.getSize().y;
	gData.exiteRect.width = conf.exiteBottomImg.getSize().x;
	
};
void gameDeinitialize(config & conf, gameData & gData){
	gData.window.close();
	if (gData.enemys != 0 )
		delete[] gData.enemys;
}

void gameDataInitialize(config & conf, gameData & gData){
	gData.enemys = new enemy[conf.namberEnemy];
	for (int i = 0; i < conf.namberEnemy; i++)	{
		gData.enemys[i].sprite = gData.enemy;
		gData.enemys[i].flagIsReal = false;
		gData.enemys[i].isEnemy = true;
		gData.enemys[i].Ymove = 0.0;
	}
	gData.end = true;
	gData.heal = 3;
	gData.score = 0;
	gData.flagClose = 0;
}

void coordinateCreat(float & timeCreate, config & conf, gameData & gData){	
	if (timeCreate <= 0){
		for (int i = 0; i < conf.namberEnemy; i++){
			if (!(gData.enemys[i].flagIsReal)){
				float coorX, coorY;                                                                                                       
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dist(0, 32700); // 	
				coorY = (float)(dist(gen) % (gData.window.getSize().y - gData.enemyRect.height));
				if ((dist(gen) % 3) == 2){
					gData.enemys[i].sprite = gData.friendd;
					gData.enemys[i].isEnemy = false;
				}
				else{ 
					gData.enemys[i].sprite = gData.enemy; gData.enemys[i].isEnemy = true; 
				}
				if (dist(gen) % 2){ 
					coorX = (float)gData.window.getSize().x - gData.enemyRect.width;
				}
				else{
					coorX = 0;
				}
				gData.enemys[i].coordinateX = (int)coorX;
				gData.enemys[i].coordinateY = (int)coorY;
				gData.enemys[i].speed = 0.0001 * (dist(gen) % 6 + 4);
				gData.enemys[i].moveTaktic = dist(gen) % 2;
				gData.enemys[i].flagIsReal = true;
				gData.enemys[i].flagStartSprite = true;
				break;
			}
		}
		timeCreate = conf.timeDistanceCreate;
	}
};

void moveEnemy(config & conf, gameData & gData, float & time, int & i){	
	if (gData.enemys[i].flagStartSprite){
		gData.enemys[i].sprite.setPosition((float)gData.enemys[i].coordinateX, (float)gData.enemys[i].coordinateY);
		gData.enemys[i].flagStartSprite = false;
	}		 
	if (gData.enemys[i].moveTaktic == 0){
		if (gData.enemys[i].coordinateX > 0) { 
			(gData.enemys[i].sprite).move((float)-gData.enemys[i].speed*time, 0.0); (gData.enemys[i].sprite).setTextureRect(IntRect(0, 0, gData.enemyRect.width, gData.enemyRect.height));
		}      ////////
		if (gData.enemys[i].coordinateX == 0) {
			(gData.enemys[i].sprite).move((float)gData.enemys[i].speed*time, 0.0); (gData.enemys[i].sprite).setTextureRect(IntRect(gData.enemyRect.width, 0, -gData.enemyRect.width, gData.enemyRect.height)); 
		}           ////////
	}
	else{	
		if (gData.enemys[i].coordinateX > 0) { 
			(gData.enemys[i].sprite).move((float)-gData.enemys[i].speed*time, 0.0); (gData.enemys[i].sprite).setTextureRect(IntRect(0, 0, gData.enemyRect.width, gData.enemyRect.height));
		}
		if (gData.enemys[i].coordinateX == 0) {
			(gData.enemys[i].sprite).move((float)gData.enemys[i].speed*time, 0.0); (gData.enemys[i].sprite).setTextureRect(IntRect(gData.enemyRect.width, 0, -gData.enemyRect.width, gData.enemyRect.height)); 
		}
		gData.enemys[i].Ymove = 0.001*sin(0.01 * gData.enemys[i].sprite.getPosition().x) - gData.enemys[i].Ymove;
		if (gData.enemys[i].coordinateX > 0) {
			(gData.enemys[i].sprite).move(0.0, (float)gData.enemys[i].Ymove*time); (gData.enemys[i].sprite).setTextureRect(IntRect(0, 0, gData.enemyRect.width, gData.enemyRect.height));
		}
		if (gData.enemys[i].coordinateX == 0) {
			(gData.enemys[i].sprite).move(0.0, (float)gData.enemys[i].Ymove*time); (gData.enemys[i].sprite).setTextureRect(IntRect(gData.enemyRect.width, 0, -gData.enemyRect.width, gData.enemyRect.height));
		}
	}
};

//
bool isVisibelEnemy(config & conf, gameData & gData, int & i){	
	gData.window.draw(conf.text);
	if (gData.enemys[i].sprite.getPosition().x <= 0 || gData.enemys[i].sprite.getPosition().x >= gData.window.getSize().x){
		gData.enemys[i].flagIsReal = false;		
		return false;
	}
	else if (Mouse::isButtonPressed(sf::Mouse::Left))	{
		int mousX = Mouse::getPosition(gData.window).x;
		int mousY = Mouse::getPosition(gData.window).y;
		if ((((mousX > gData.enemys[i].sprite.getPosition().x) && (mousX < gData.enemys[i].sprite.getPosition().x + gData.enemyRect.width))
			&& ((mousY > gData.enemys[i].sprite.getPosition().y) && (mousY < gData.enemys[i].sprite.getPosition().y + gData.enemyRect.height)))){
			gData.enemys[i].flagIsReal = false;
			if (gData.enemys[i].isEnemy){
				gData.score++;	
			}
			else{
				gData.heal = gData.heal - 1;
			}
		}
		return true;
	}
	return true;
};

bool menu(config & conf, gameData & gData){		
	gData.window.clear();
	gData.startBottomSprite.setPosition(gData.posXStartS, gData.posYStartS);
	gData.exiteBottomSprite.setPosition(gData.posXExiteS, gData.posYExiteS);
	gData.startBottomSprite.setTextureRect(IntRect(0, 0, gData.startRect.width, gData.startRect.height));
	gData.exiteBottomSprite.setTextureRect(IntRect(0, 0, gData.exiteRect.width, gData.exiteRect.height));
	gData.window.draw(gData.startBottomSprite);
	gData.window.draw(gData.exiteBottomSprite);		

	conf.text.setString(conf.score + ToString(gData.score) );
	gData.window.draw(conf.text);

	gData.window.display();
	while (gData.window.isOpen()){
		sf::Event event;
		while (gData.window.pollEvent(event)){
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
				return false;
			}
			if (event.type == sf::Event::GainedFocus) {
				gData.window.draw(gData.startBottomSprite);
				gData.window.draw(gData.exiteBottomSprite);
				gData.window.draw(conf.text);
				gData.window.display();
			}
		}
		if (Mouse::isButtonPressed(sf::Mouse::Right)){
			int mousX = Mouse::getPosition(gData.window).x;
			int mousY = Mouse::getPosition(gData.window).y;
			if ((((mousX > gData.startBottomSprite.getPosition().x) && (mousX < gData.startBottomSprite.getPosition().x + gData.startRect.width))
				&& ((mousY > gData.startBottomSprite.getPosition().y) && (mousY < gData.startBottomSprite.getPosition().y + gData.startRect.height)))){
				return true;
			}
			else if ((((mousX > gData.exiteBottomSprite.getPosition().x) && (mousX < gData.exiteBottomSprite.getPosition().x + gData.exiteRect.width))
				&& ((mousY > gData.exiteBottomSprite.getPosition().y) && (mousY < gData.exiteBottomSprite.getPosition().y + gData.exiteRect.height)))){
				return false;
			}
		}
	}
};

bool gameRun(config & conf, gameData & gData){
	Clock clock;
	float timeCreate = conf.timeDistanceCreate;
		
	while (gData.window.isOpen()){
		gData.window.clear();
		conf.text.setString(conf.healHave + ToString(gData.heal));
		gData.window.draw(conf.text);
		float time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timeCreate -= time;
					
		sf::Event event;
		while (gData.window.pollEvent(event)){
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
				return true;
			}
		}
		coordinateCreat(timeCreate, conf, gData);

		if (gData.heal > 0){
			for (int i = 0; i < conf.namberEnemy; i++){
				if (gData.enemys[i].flagIsReal){
					moveEnemy(conf, gData, time, i);
					if (!(isVisibelEnemy(conf, gData, i))){
						continue;
					};
					if (gData.enemys[i].flagIsReal){
						gData.window.draw(gData.enemys[i].sprite);
					}
				}
			}
		}
		else{
			return false;
		}
		gData.window.display();
	}	
}
	


int main(){
	config conf;
	gameData gData;
	configPrepare(conf);
	gameInitializeSprite(conf, gData);
	while (menu(conf, gData) == 1)	{		
		gameDataInitialize(conf, gData);
		if (gameRun(conf, gData)){
			break;
		}
	}
	gameDeinitialize(conf, gData);
	return 0;
}
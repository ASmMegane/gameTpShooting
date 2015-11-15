#pragma once
#include <SFML/Graphics.hpp>

struct enemy {
	sf::Sprite sprite;
	double speed;
	int coordinate1;
	int coordinate2;
	bool flagStartSprite;
	bool flagIsReal;
	bool isEnemy;
	int moveTaktic;
	double Ymove;
};


struct config{
	const int namberEnemy = 10;
	const float timeDistanceCreate = 400000;
	int textCharacterSize = 24;
	std::string fontStyle = "image/arial.ttf";
	std::string score = "Your score: ";
	std::string healHave = "Life left: ";
	std::string imageAdres = "image/enemy.png";
	std::string imageAdresF = "image/friend.png";
	std::string startBottomAdrress = "image/btnstartstd.jpg";
	std::string exiteBottomAdrress = "image/btnexitstd.png";
	sf::Image enemyImg;
	sf::Image friendImg;
	sf::Image startBottomImg;
	sf::Image exiteBottomImg;
	sf::Font font;
	sf::Text text;
};

struct gameData{
	enemy *enemys = 0;
	bool end;
	int flagClose;
	int score = 0;
	int heal;
	sf::RenderWindow window;
	sf::Texture enemyTexture;
	sf::Sprite  enemy;
	sf::IntRect enemyRect;
	sf::Texture friendTexture;
	sf::Sprite  friendd;
	sf::IntRect friendRect;
	sf::Texture startBottomTex;
	sf::Sprite  startBottomSprite;
	sf::IntRect startRect;
	sf::Texture exiteBottomTex;
	sf::Sprite  exiteBottomSprite;
	sf::IntRect exiteRect;
};

#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "HealthBar.h"

class Game {

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool endGame;
	unsigned points;
	float health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float gravity;
	bool mouseHeld;

	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	sf::Text pointsText;
	sf::Font font;

	HealthBar healthbar;

	void initVariables();
	void initWindow();
	void initEnemies();
	void initUI();

public:
	Game();
	virtual ~Game();

	const bool isRunning() const;
	const bool isGameEnded() const;

	void spawnEnemy();

	void pollEvents();

	void updateMousePositions();
	void updateEnemies();
	void updateUI();
	void update();

	void renderEnemies();
	void renderUI();
	void render();

};


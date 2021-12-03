#include "Game.h"

// Initialize variables
void Game::initVariables() {
	window = nullptr;

	health = 25.0F;
	enemySpawnTimerMax = 10.0F;
	enemySpawnTimer = enemySpawnTimerMax;
	maxEnemies = 15;
	gravity = 9.8F;
	points = 0;
	mouseHeld = false;
	endGame = false;

	if (!font.loadFromFile("Resources/Fonts/arial.ttf")) std::cout << "Failed to load arial.ttf font!" << std::endl;
}

// Initialize window
void Game::initWindow() {
	videoMode.height = 600;
	videoMode.width = 800;

	window = new sf::RenderWindow(videoMode, "Test Window", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(60);
}

// Initialize enemies
void Game::initEnemies() {
	enemy.setPosition(10.0F, 10.0F);
	enemy.setSize(sf::Vector2f(75.0F, 75.0F));
}

// Initialize UI
void Game::initUI() {
	pointsText.setFont(font);
	pointsText.setCharacterSize(14);
	pointsText.setPosition(5.0F, 25.0F);
	pointsText.setString("Points: " + std::to_string(points));
	pointsText.setFillColor(sf::Color::White);
}

// Constructor
Game::Game() : healthbar(100.0F, font) {
	initVariables();
	initWindow();
	initEnemies();
	initUI();
}

// Destructor
Game::~Game() {
	delete window;
}

// Check if game is running
const bool Game::isRunning() const {
	return window->isOpen();
}

const bool Game::isGameEnded() const {
	return endGame;
}

// Spawns an enemy
void Game::spawnEnemy() {
	enemy.setPosition(static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)), 0.0F);
	enemy.setFillColor(sf::Color::Color(rand() % 255, rand() % 255, rand() % 255));

	enemies.push_back(enemy);
}

// Poll SFML events
void Game::pollEvents() {
	while (window->pollEvent(event)) {
		switch (event.type) {
			// Handle window closing
			case sf::Event::Closed:
				window->close();
				break;
			// Handle key presses
			case sf::Event::KeyPressed:
				// Close window using escape key
				if (event.key.code == sf::Keyboard::Escape) window->close();
				break;
			default:
				break;
		}
	}
}

// Update mouse positions
void Game::updateMousePositions() {
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}


// Updates the enemy spawn timer and spawns enemies when needed
void Game::updateEnemies() {
	// Handle enemy spawning
	if (enemies.size() < maxEnemies) {
		if (enemySpawnTimer >= enemySpawnTimerMax) {
			spawnEnemy();
			enemySpawnTimer = 0.0F;
		} else enemySpawnTimer += 1.0F;
	}

	// Handle mouse clicking
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!mouseHeld) {
			mouseHeld = true;

			for (int i = 0; i < enemies.size(); ++i) {
				sf::RectangleShape& e = enemies[i];

				if (e.getGlobalBounds().contains(mousePosView)) {
					enemies.erase(enemies.begin() + i);
					points += 1;
					break;
				}
			}
		}
	} else {
		mouseHeld = false;
	}

	// Apply enemy movement & restrict to window bounds
	for (int i = 0; i < enemies.size(); ++i) {
		sf::RectangleShape& e = enemies[i];

		// Move enemy
		e.move(0.0F, gravity);

		// Handle bounds, health, & game ending
		sf::Vector2u windowSize = window->getSize();
		sf::Vector2f enemySize = e.getSize();
		sf::Vector2f enemyPos = e.getPosition();
		if (enemyPos.x > windowSize.x - (enemySize.x / 2) || enemyPos.x < 0 || enemyPos.y > windowSize.y - (enemySize.y / 2) || enemyPos.y < 0) {
			enemies.erase(enemies.begin() + i);
			i -= 1;
			health -= 1.0F;
			if (health <= 0) {
				health = 0;
				endGame = true;
			}
			healthbar.update(25.0F, health);
		}
	}

	
}

void Game::updateUI() {
	pointsText.setString("Points: " + std::to_string(points));
}

// Update game
void Game::update() {
	pollEvents();

	if (!endGame) {
		updateMousePositions();
		updateEnemies();
	} else {

	}
	
	updateUI();
}

void Game::renderEnemies() {
	for (sf::RectangleShape& e : enemies) {
		window->draw(e);
	}
}

void Game::renderUI() {
	window->draw(pointsText);
	healthbar.render(*window);
}

// Render game
void Game::render() {
	window->clear(sf::Color::Color(70, 50, 140));
	renderEnemies();
	renderUI();
	window->display();
}


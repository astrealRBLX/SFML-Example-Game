#pragma once

#include <iomanip>
#include <sstream>
#include <cmath>

#include <SFML/Graphics.hpp>

class HealthBar {

private:
	sf::RectangleShape background;
	sf::RectangleShape health;
	sf::Text healthText;
	sf::Font font;

	float maxSize;

public:
	HealthBar(float maxSize, const sf::Font& font, sf::Vector2f position = sf::Vector2f(5.0F, 5.0F));

	void update(float maxHealth, float newHealth);
	void render(sf::RenderWindow& window);

};


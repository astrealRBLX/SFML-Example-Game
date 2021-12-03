#include "HealthBar.h"

HealthBar::HealthBar(float maxSize, const sf::Font& font, sf::Vector2f position) {
	this->maxSize = maxSize;
	this->font = font;

	background.setFillColor(sf::Color::Black);
	background.setPosition(position);
	background.setSize(sf::Vector2f(maxSize, 15.0F));

	health.setFillColor(sf::Color::Green);
	health.setPosition(position);
	health.setSize(sf::Vector2f(maxSize, 15.0F));

	healthText.setString("100%");
	healthText.setCharacterSize(12);
	healthText.setFont(font);
	healthText.setPosition(position + sf::Vector2f(2.5F, 0.0F));
	healthText.setFillColor(sf::Color::Black);
}

void HealthBar::update(float maxHealth, float newHealth) {
	if (newHealth < 0.0F) newHealth = 0;

	health.setSize(sf::Vector2f((newHealth / maxHealth) * maxSize, 15.0F));

	if (newHealth >= 0.7F * maxHealth) {
		health.setFillColor(sf::Color::Green);
		healthText.setFillColor(sf::Color::Black);
	} else if (newHealth >= 0.4F * maxHealth) {
		health.setFillColor(sf::Color::Yellow);
		healthText.setFillColor(sf::Color::Black);
	} else {
		health.setFillColor(sf::Color::Red);
		healthText.setFillColor(sf::Color::White);
	}

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << (newHealth / maxHealth) * 100.0F;
	healthText.setString(stream.str() + "%");
}

void HealthBar::render(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(health);
	window.draw(healthText);
}


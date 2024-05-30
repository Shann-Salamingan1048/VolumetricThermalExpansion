#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include "Globals.h"
#include "..\Shapes\Headers\Shape.h"
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window; // use smart pointers
	sf::Event event;
	sf::VideoMode videoMode;
	void initWindow();
	sf::Font font;
private:
	shapes::Cube* cube1;
private:
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
private:
	sf::Clock dtClock;
	float delta;
public:
	Game();
	~Game();
	const bool isRunning() const;
	void pollEvents();

	void updateDT();
	void update();
	void render();

	void updateMousePos();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include "Globals.h"
#include "..\GUI\GUI.h"
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window; // use smart pointers
	sf::Event event;
	sf::VideoMode videoMode;
	void initWindow();
	sf::Font font;
	
	gui::Button* but_Enter;
	
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public:
	Game();
	~Game();
	const bool isRunning() const;
	void pollEvents();

	void update();
	void render();

	void updateMousePos();
};
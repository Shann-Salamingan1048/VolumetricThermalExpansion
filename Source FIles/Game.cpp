#include "..\Header Files\Game.h"
void Game::initWindow()
{
	this->videoMode.height = 1320;
	this->videoMode.width = 1200;
	this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Minesweeper", sf::Style::Titlebar | sf::Style::Close); // smart ptr
	this->window->setFramerateLimit(60);

}
void Game::pollEvents()
{

	while (this->window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{

			case sf::Keyboard::D:

				break;
			case sf::Keyboard::W:

				break;
			case sf::Keyboard::S:

				break;
			}

			break;
		default:
			break;
		}
	}
}
Game::Game()
{
	this->initWindow();
}
Game::~Game() // destructor
{
	std::cout << "Game.h Destructor!\n";
}
const bool Game::isRunning() const
{
	return this->window->isOpen();
}
void Game::update()
{
	this->pollEvents();
}
void Game::render()
{
	this->window->clear();
	// render
	this->window->display();
}
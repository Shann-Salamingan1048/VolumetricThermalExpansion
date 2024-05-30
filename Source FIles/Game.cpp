#include "..\Header Files\Game.h"
void Game::initWindow()
{
	this->videoMode.height = Screen_Height;
	this->videoMode.width = Screen_Width;
	this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Volumetric Thermal Expansion Simulation", sf::Style::Titlebar | sf::Style::Close); // smart ptr
	this->window->setFramerateLimit(60);
	//this->font.loadFromFile("C:/Users/USER/Documents/1. Batak Time!!!/1. Coding/CPP/Visual Studio/VolumetricThermalExpansion/Font Files/Rosela.ttf");
	this->font.loadFromFile("Font Files/Rosela.ttf"); 

	// for cube
	this->but_Enter = new gui::Button(400,400, 300,100, "Enter", &this->font, sf::Color::Red, sf::Color::Blue , sf::Color::Yellow, 50);
	std::vector<std::string> items =
	{
		"Meter", "Centimeter"
	};
	this->drop1 = new gui::DropList(600, 600, 100, 100, this->font, items, 30);
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
void Game::updateMousePos()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::update()
{
	this->updateMousePos();
	this->pollEvents();
	this->updateDT();
	// for cube
	this->but_Enter->updateBut(this->mousePosView);
	if (this->but_Enter->isClicked()) // to know if it only clicked once
	{
		std::cout << "Clicked Button\n";
	}
	
	//std::cout << "DropList: " << this->drop1->getText() << "\n";
	this->drop1->updateDL(this->mousePosView, this->delta);
}
void Game::updateDT()
{
	// updates delta 
	this->delta = this->dtClock.restart().asSeconds();

}
void Game::render()
{
	this->window->clear();
	this->update();
	// render
	this->but_Enter->renderBut(*this->window); // for cube

	this->drop1->drawDL(*this->window);
	this->window->display();
}
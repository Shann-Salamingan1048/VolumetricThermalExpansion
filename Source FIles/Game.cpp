#include "..\Header Files\Game.h"
void Game::initWindow()
{
	this->videoMode.height = Screen_Height;
	this->videoMode.width = Screen_Width;
	this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Volumetric Thermal Expansion Simulation", sf::Style::Default); // smart ptr
	this->window->setFramerateLimit(60);
	////
	this->font.loadFromFile("Font Files/Coffee Spark.ttf"); 
	this->textureBut.loadFromFile("Picture Sprites/Pixel Art Buttons.png"); // init texture
	this->imageTemp.loadFromFile("Picture Sprites/Pixel Art Buttons.png");//init image
	// colors
	this->colorButOrig = this->imageTemp.getPixel(17, 8);
	this->hoverColorBut = sf::Color::Yellow;; // rgb = sf::Color(int,int,int);
	////
	this->intrectBut = sf::IntRect(5,2,55,50);
	//////
	this->cube1 = new shapes::Cube(measure_Units, this->font, this->textureBut, this->intrectBut, this->colorButOrig, this->hoverColorBut);
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
		case sf::Event::TextEntered:
			this->cube1->Inputs(this->event);
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
	//delete this->cube1;
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
	this->cube1->Update(this->mousePosView, this->delta);

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

	// render Cube Shape
	this->cube1->Render(*this->window);
	///
	this->window->display();
}
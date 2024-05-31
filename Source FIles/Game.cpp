#include "..\Header Files\Game.h"
void Game::initWindow()
{
	/* super expensive lol mag fullscreen
	this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Volumetric Thermal Expansion Simulation", sf::Style::Fullscreen );
	*/
	// this->videoMode = sf::VideoMode::getDesktopMode(); sa final na ini IMPORTANT!
	this->videoMode.height = Screen_Height;
	this->videoMode.width = Screen_Width;
	this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Volumetric Thermal Expansion Simulation", sf::Style::Close | sf::Style::Titlebar); // smart ptr
	this->window->setFramerateLimit(60);
	////
	this->font.loadFromFile("Font Files/Coffee Spark.ttf"); 
	this->texture.loadFromFile("Picture Sprites/Pixel Art Buttons.png"); // init texture
	this->imageTemp.loadFromFile("Picture Sprites/Pixel Art Buttons.png");//init image
	// colors
	this->colorButOrig = this->imageTemp.getPixel(17, 8);
	this->hoverColorBut = sf::Color::Yellow;; // rgb = sf::Color(int,int,int);
	////
	this->intrectBut = sf::IntRect(5,2,55,50);
	this->intrectTB = sf::IntRect(383, 268, 64, 26);
	//////
	this->cube1 = new shapes::Cube(measure_Units, this->font, this->texture, this->intrectBut, this->colorButOrig, this->hoverColorBut, this->intrectTB, temp_Units);
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
	this->window->clear(sf::Color::Green);
	this->update();
	// render

	// render Cube Shape
	this->cube1->Render(*this->window);
	///
	this->window->display();
}
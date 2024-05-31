
#include "..\Headers\Shape.h"

shapes::Cube::~Cube()
{
	delete this->but_Enter;
	delete this->drop1;
	delete this->textbox1;
}
shapes::Cube::Cube(const std::vector<std::string>& measure_Units, sf::Font& font,sf::Texture& textureBut, sf::IntRect& intrectBut,
	sf::Color& origColorBut, sf::Color& hoverColorBut)
{
	// for cube
	this->but_Enter = new gui::Button(400, 400, 300, 100, "Enter", &font, origColorBut, hoverColorBut, 50, &textureBut, &intrectBut);

	this->drop1 = new gui::DropList(600, 600, 100, 100, font, measure_Units, 30, textureBut, intrectBut);
	this->textbox1 = new gui::TextBox(700, 700, 100, 100, &font, 30);
}

void shapes::Cube::Render(sf::RenderTarget& target)
{
	this->but_Enter->renderBut(target); // for cube
	this->drop1->drawDL(target);
	this->textbox1->renderTextBox(target);
}
void shapes::Cube::Inputs(sf::Event& evt)
{
	if (this->textbox1->isClicked())
	{
		this->textbox1->inputTextBox(evt);
	}
}
void shapes::Cube::Update(const sf::Vector2f& mousePos, const float& dt)
{
	this->but_Enter->updateBut(mousePos);
	if (this->but_Enter->isClicked()) // to know if it only clicked once
	{
		std::cout << "Value Unit: " << this->drop1->getText() << "\n";
	}
	//std::cout << "DropList: " << this->drop1->getText() << "\n";
	this->drop1->updateDL(mousePos, dt);
	this->textbox1->updateTextBox(mousePos);
}
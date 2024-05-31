
#include "..\Headers\Shape.h"

shapes::Cube::~Cube()
{
	delete this->but_Enter;
	delete this->drop1;
	delete this->textbox1;

	delete this->drop2;
	delete this->textbox2;

	delete this->drop3;
	delete this->textbox3;

	delete this->textbox4;
}
shapes::Cube::Cube(const std::vector<std::string>& measure_Units, sf::Font& font,sf::Texture& texture, sf::IntRect& intrectBut,
	sf::Color& origColorBut, sf::Color& hoverColorBut, sf::IntRect& intrectTB, const std::vector<std::string>& temp_Units)
{
	// for cube
	this->but_Enter = new gui::Button(1000, 1200, 200, 100, "Enter", &font, origColorBut, hoverColorBut, 50, &texture, &intrectBut);
	// initial Volume
	this->drop1 = new gui::DropList(350, 1000, 300, 100, font, measure_Units, 40, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox1 = new gui::TextBox(50, 1000, 300, 100, &font, &texture, &intrectTB);

	// initial Temp
	this->drop2 = new gui::DropList(950, 1000, 300, 100, font, temp_Units, 40, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox2 = new gui::TextBox(650, 1000, 300, 100, &font, &texture, &intrectTB);

	// final temp
	this->drop3 = new gui::DropList(1550, 1000, 300, 100, font, temp_Units, 40, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox3 = new gui::TextBox(1250, 1000, 300, 100, &font, &texture, &intrectTB);

	// Beta or coefficient of volume expansion
	this->textbox4 = new gui::TextBox(1850, 1000, 300, 100, &font, &texture, &intrectTB);

	// Texts
	this->initVol.setFont(font);
	this->initVol.setString("Initial Volume");
	this->initVol.setPosition(sf::Vector2f(70.0f, 1100.0f));
	this->initVol.setFillColor(sf::Color::Black);
	this->initVol.setCharacterSize(40);

	this->initTemp.setFont(font);
	this->initTemp.setString("Initial Temp");
	this->initTemp.setPosition(sf::Vector2f(680.0f, 1100.0f));
	this->initTemp.setFillColor(sf::Color::Black);
	this->initTemp.setCharacterSize(40);

	this->finalTemp.setFont(font);
	this->finalTemp.setString("Final Temp");
	this->finalTemp.setPosition(sf::Vector2f(1290.0f, 1100.0f));
	this->finalTemp.setFillColor(sf::Color::Black);
	this->finalTemp.setCharacterSize(40);

	this->Beta.setFont(font);
	this->Beta.setString("Coefficient \nof \nvolume \nexpansion");
	this->Beta.setPosition(sf::Vector2f(1900.0f, 1100.0f));
	this->Beta.setFillColor(sf::Color::Black);
	this->Beta.setCharacterSize(40);
}

void shapes::Cube::Render(sf::RenderTarget& target)
{
	this->but_Enter->renderBut(target); // for cube

	this->drop1->drawDL(target);
	this->drop2->drawDL(target);
	this->drop3->drawDL(target);

	this->textbox1->renderTextBox(target);
	this->textbox2->renderTextBox(target);
	this->textbox3->renderTextBox(target);

	this->textbox4->renderTextBox(target);

	target.draw(this->initVol);
	target.draw(this->initTemp);
	target.draw(this->finalTemp);
	target.draw(this->Beta);
}
void shapes::Cube::Inputs(sf::Event& evt)
{
	if (this->textbox1->isClicked())
	{
		this->textbox1->inputTextBox(evt);
	}
	if (this->textbox2->isClicked())
	{
		this->textbox2->inputTextBox(evt);
	}
	if (this->textbox3->isClicked())
	{
		this->textbox3->inputTextBox(evt);
	}
	if (this->textbox4->isClicked())
	{
		this->textbox4->inputTextBox(evt);
	}
}
void shapes::Cube::Update(const sf::Vector2f& mousePos, const float& dt)
{
	this->but_Enter->updateBut(mousePos);
	if (this->but_Enter->isClicked()) // to know if it only clicked once
	{
		std::cout << "Volume initial: " << this->textbox1->getText() << " " << this->drop1->getText() << "\n";
		if (this->textbox2->getText() == "0") // initial idea
		{
			std::cout << "Tewmp initial: " << "32" << " " << this->drop2->getText() << "\n";
		}
		else
		{
			std::cout << "Tewmp initial: " << this->textbox2->getText() << " " << this->drop2->getText() << "\n";
		}
		std::cout << "Tewmp final: " << this->textbox3->getText() << " " << this->drop3->getText() << "\n";
		std::cout << "Beta: " << this->textbox4->getText() << "\n";
	}
	//std::cout << "DropList: " << this->drop1->getText() << "\n";

	this->drop1->updateDL(mousePos, dt); // DL means Drop List
	this->drop2->updateDL(mousePos, dt);
	this->drop3->updateDL(mousePos, dt);
	
	this->textbox1->updateTextBox(mousePos); 
	this->textbox2->updateTextBox(mousePos);
	this->textbox3->updateTextBox(mousePos);
	this->textbox4->updateTextBox(mousePos);


}
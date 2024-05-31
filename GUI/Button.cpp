#include "GUI.h"
gui::Button::~Button()
{
	std::cout << "Button destructor!\n";
	
}
gui::Button::Button(float x, float y, float width, float height, const std::string& text, sf::Font* font,
	sf::Color idleColor, sf::Color hoverColor, uint16_t characterSize, sf::Texture* texture, sf::IntRect* intrect)
{
	this->isLeftClicked = false;
	this->butState = gui::btn_idle;
	/// button shape
	this->textureBut = texture;
	this->intrect = intrect;
	this->butShape.setPosition(x, y);
	this->butShape.setSize(sf::Vector2f(width, height));
	this->butShape.setTexture(this->textureBut); // set the texture in rectangle shape or butshape
	this->butShape.setTextureRect(*this->intrect); // set the intrect in rectangle shape or butshape
	/////
	// text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(
		this->butShape.getPosition().x + (this->butShape.getSize().x - this->text.getGlobalBounds().width) / 2.0f,
		this->butShape.getPosition().y + (this->butShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
	); // centered
	// colors
	this->idleColor = idleColor;
	this->hoverColor = hoverColor; 

	this->butShape.setFillColor(this->idleColor);
}

void gui::Button::updateBut(const sf::Vector2f& mousePos)
{

	this->butState = btn_idle; // idle
	if (this->butShape.getGlobalBounds().contains(mousePos))
	{
		this->butState = btn_hover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!this->isLeftClicked) // prevent long pressed or clicked
			{
				this->butState = btn_clicked;
				this->isLeftClicked = true;
			}
		}
		else
		{
			this->isLeftClicked = false;
		}
	}
	// change colors
	switch (this->butState)
	{
	case btn_idle:
		this->butShape.setFillColor(this->idleColor);
		break;
	case btn_hover:
		this->butShape.setFillColor(this->hoverColor);
		break;
	default:
		this->butShape.setFillColor(sf::Color::Red); // just in case if it errors
		break;
	}
}
const bool gui::Button::isClicked() const
{
	if (this->butState == btn_clicked)
	{
		return true;
	}
	return false;
}
void gui::Button::setText(const std::string& item)
{
	this->text.setString(item);
	this->text.setPosition(
		this->butShape.getPosition().x + (this->butShape.getSize().x - this->text.getGlobalBounds().width) / 2.0f,
		this->butShape.getPosition().y + (this->butShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
	); // centered
}
const std::string gui::Button::getText() const
{

	return this->text.getString();
}
void gui::Button::renderBut(sf::RenderTarget& target)
{
	target.draw(this->butShape);
	target.draw(this->text);
}
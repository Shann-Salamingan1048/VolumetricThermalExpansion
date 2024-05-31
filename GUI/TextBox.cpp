#include "GUI.h"
#define NumberOnly
gui::TextBox::~TextBox()
{
	std::cout << "TextBox Destructor!\n";
}
gui::TextBox::TextBox(float x, float y, float width, float height, sf::Font* font, sf::Texture* textureTB, sf::IntRect* intrectTB)
{
    //
	this->clickedDot = false;
	this->isLeftClicked = false;
	this->butState = gui::btn_idle;
	// init  texture and intrect
	this->textureTB = textureTB;
	this->intrectTB = intrectTB;
	// init shape of the text box
	this->textShape.setPosition(x, y);
	this->textShape.setSize(sf::Vector2f( width, height));
	this->textShape.setTexture(this->textureTB); // set the texture in rectangle shape or butshape
	this->textShape.setTextureRect(*this->intrectTB); // set the intrect in rectangle shape or butshape
	/// font and text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setCharacterSize(static_cast<uint16_t> (width * 0.1));
	this->text.setString("");
	this->text.setFillColor(sf::Color::Black); // font color
	this->text.setPosition(
		this->textShape.getPosition().x + this->textShape.getSize().x - this->text.getGlobalBounds().width,
		this->textShape.getPosition().y + (this->textShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
	); // very right
    //
    // Initialize cursor
    this->cursor.setSize(sf::Vector2f(2.f, text.getCharacterSize()));
    this->cursor.setFillColor(sf::Color::White);
    this->cursor.setPosition(textShape.getPosition().x, text.getPosition().y);
    // 
    this->cursorVisible = false;

	// max characters in the box
	this->maxChars = static_cast<uint16_t>(this->textShape.getGlobalBounds().width / (this->text.getCharacterSize())) + 5;

}

void gui::TextBox::updateTextBox(const sf::Vector2f& mousePos)
{
	// check if it click the textbox if it click then allow the input
	if (this->textShape.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!this->isLeftClicked) // prevent long pressed or long clicked
			{
				this->isLeftClicked = true;
				this->butState = btn_clicked;
			}
		}
	}
	// if it is outside of the text box and it click outside the text box then dont input anymore
	else if(!this->textShape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isLeftClicked = false;
		this->butState = btn_idle;
	}
}
void gui::TextBox::inputTextBox(sf::Event& evt)
{
	// lacks on the blinking cursor...... please do this later because it will waste your time
	// 
	//                              / \
	// IMPORTANT!!!!!!!!!!!!!!!!! Up |    arrow Up
// 
// 
// 
// 
// 
// 
	// input process
	// Please implement the text box limit character 
	switch (evt.type)
	{
	case sf::Event::TextEntered:
		if (evt.text.unicode < 128)
		{
			char enteredChar = static_cast<char>(evt.text.unicode);
			if (enteredChar == 8) // backspace or erase
			{
				if (!this->textSTR.empty())
				{
					if (this->textSTR[this->textSTR.size() - 1] == '.')
					{
						this->clickedDot = false;
					}
					this->textSTR.pop_back();
				}
			}
			else if ( enteredChar <= 126 && this->textSTR.size() < this->maxChars) // Printable characters and limit its characters that depend in the textbox size
			{
#ifdef NumberOnly
				if (isdigit(static_cast<unsigned char>(enteredChar)))
				{

					this->textSTR += enteredChar;
				}
				else if (enteredChar == '.' && !this->clickedDot)
				{
					this->textSTR += enteredChar;
					this->clickedDot = true;
				}
#else
				this->textSTR += enteredChar;
#endif
			}
			this->text.setString(this->textSTR);
			this->text.setPosition(
				(this->textShape.getPosition().x + this->textShape.getSize().x - this->text.getGlobalBounds().width) - this->text.getCharacterSize(),
				this->textShape.getPosition().y + (this->textShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
			); // very right
		}
	}
}
const bool gui::TextBox::isClicked() const
{
	if (this->butState == btn_clicked)
	{
		return true;
	}
	return false;
}
void gui::TextBox::renderTextBox(sf::RenderTarget& target)
{
	target.draw(this->textShape);
	target.draw(this->text);
    if (this->cursorVisible)
    {
        target.draw(this->cursor);
    }
}
const std::string gui::TextBox::getText() const
{
	if (this->textSTR.empty())
	{
		return "0";
	}
	return this->text.getString();
}
#include "GUI.h"
gui::TextBox::~TextBox()
{
	std::cout << "TextBox Destructor!\n";
}
gui::TextBox::TextBox(float x, float y, float width, float height, sf::Font* font, uint16_t characterSize)
{
    //
	this->isLeftClicked= false;
	this->butState = gui::btn_idle;
	// init shape of the text box
	this->textShape.setPosition(x, y);
	this->textShape.setSize(sf::Vector2f( width, height));
	this->textShape.setFillColor(sf::Color::Red);
	/// font and text
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setCharacterSize(characterSize);
	this->text.setString("");
	this->text.setFillColor(sf::Color::White);
    this->text.setPosition(
        this->textShape.getPosition().x + (this->textShape.getSize().x - this->text.getGlobalBounds().width) / 2.0f,
        this->textShape.getPosition().y + (this->textShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
    ); // centered
    //
    // Initialize cursor
    this->cursor.setSize(sf::Vector2f(2.f, text.getCharacterSize()));
    this->cursor.setFillColor(sf::Color::White);
    this->cursor.setPosition(textShape.getPosition().x, text.getPosition().y);
    // 
    this->cursorVisible = false;
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
	// input process
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
					this->textSTR.pop_back();
				}
			}
			else if (enteredChar >= 32 && enteredChar <= 126) // Printable characters
			{
				this->textSTR += enteredChar;
			}
			this->text.setString(this->textSTR);
			this->text.setPosition(
				this->textShape.getPosition().x + (this->textShape.getSize().x - this->text.getGlobalBounds().width) / 2.0f,
				this->textShape.getPosition().y + (this->textShape.getSize().y - this->text.getGlobalBounds().height) / 2.0f
			); // centered
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
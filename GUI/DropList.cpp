#include "GUI.h"
gui::DropList::~DropList()
{
	delete this->activeDL;
	for (auto &i : this->listItems)
	{
		delete i;
	}
}
gui::DropList::DropList(float x, float y, float width, float height,
	sf::Font& font, const std::vector<std::string>& items, uint16_t characterSize)
	: font(font), isExpanded(false), keyTimeMax(1.0f), keyTime(keyTimeMax)
{
	for (uint16_t i = 0; i < items.size(); i++)
	{
		this->listItems.push_back(
			new gui::Button(x, y + (i * height), width, height,
				items[i], &this->font, 
				sf::Color::Red, sf::Color::Blue, 
				sf::Color::Yellow, characterSize));
	}
	this->activeDL = new Button(*this->listItems[0]); //default or initial
}
void gui::DropList::drawDL(sf::RenderTarget& target)
{
	this->activeDL->renderBut(target);
	if (this->isExpanded)
	{
		for (const auto& i : this->listItems)
		{
			i->renderBut(target);
		}
	}
}
void gui::DropList::updateDL(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeyTime(dt);

	this->activeDL->updateBut(mousePos);
	// show and hide the list
	// the purpose of the keytime is to prevent multiple clicks
	if (this->activeDL->isClicked() && this->getKeyTime())
	{
		this->isExpanded = !this->isExpanded;
	}
	if (this->isExpanded)
	{
		for (uint16_t i = 0; i < this->listItems.size(); i++)
		{
			this->listItems[i]->updateBut(mousePos);
			if (this->listItems[i]->isClicked() && this->getKeyTime())
			{
				const std::string& temp = this->activeDL->getText();
				this->activeDL->setText(this->listItems[i]->getText());
				this->listItems[i]->setText(temp);
				this->listItems[0]->setText(this->activeDL->getText());
				this->isExpanded = false;
				std::cout << "clicked DL: " << this->activeDL->getText() << "\n";
			}
		}
	}
}
const bool gui::DropList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.0f;
		return true;
	}
	return false;
}
void gui::DropList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.0f * dt;
	}
}
const std::string gui::DropList::getText() const
{
	return this->activeDL->getText();
}
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
	sf::Font& font, const std::vector<std::string>& items, uint16_t characterSize, sf::Texture& texture, sf::IntRect& intrect, sf::Color& origColorBut, sf::Color& hoverColorBut)
	: font(font), isExpanded(false), keyTimeMax(1.0f), keyTime(1.0f)
{
	 // initialize the buttons that will become the drop list choices 
	// y + (i * height) because so when expanded it will locate locate lower
	/*
		but1 => active Droplist or the chosen one
		but2
		but3 
		but4
	*/
	for (uint16_t i = 0; i < items.size(); i++)
	{
		this->listItems.push_back(
			new gui::Button(x, y + (i * height), width, height,
				items[i], &this->font, 
				origColorBut, hoverColorBut, 
				characterSize, &texture, &intrect));
	}
	this->activeDL = new Button(*this->listItems[0]); //default or initial
}
void gui::DropList::drawDL(sf::RenderTarget& target)
{
	// render the chosen drop List choices 
	this->activeDL->renderBut(target);
	if (this->isExpanded)
	{
		// if expanded then render all the choices
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
		/*
			when you clicked the choices then it will swap the activeDL text or the first choose
			and the chosen item\
		*/
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
				//std::cout << "clicked DL: " << this->activeDL->getText() << "\n";
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
const bool gui::DropList::get_isExpanded() const
{
	return this->isExpanded;
}
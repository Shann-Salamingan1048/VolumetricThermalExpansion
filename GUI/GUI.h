#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
namespace gui
{
	enum but_states { btn_idle = 0, btn_hover, btn_clicked };
	class DropList
	{
	private:
		
		bool isExpanded;
		std::string Unit_Val; // units like meter, ft, Celcius, Farenheit, etc
		
		sf::RectangleShape activeDL;
		std::vector<sf::RectangleShape> listItems;
		//sf::Font& font;

	public:
		DropList();
		void updateDL(const sf::Vector2f& mousePos);
		void drawDL(sf::RenderTarget& window); 
		const std::string getUnit_Val() const;
	};
	//const std::vector<std::string>& items, float _CB_X_Pos, float _CB_Y_Pos, uint16_t characterSize

	class Button
	{
	private:
		unsigned short butState;
	private:
		sf::RectangleShape butShape;
		sf::Font* font;
		sf::Text text;
	private:
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;
	public:
		Button(float x, float y, float width, float height, const std::string& text, sf::Font* font, 
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, uint16_t characterSize);
		~Button();
		void updateBut(const sf::Vector2f& mousePos);
		void renderBut(sf::RenderTarget& target);

		const bool isClicked() const;
	};
}
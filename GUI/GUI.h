#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
namespace gui
{
	enum but_states { btn_idle = 0, btn_hover, btn_clicked };
	class Button
	{
	private:
		unsigned short butState;
		bool isLeftClicked;
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
	public:
		void updateBut(const sf::Vector2f& mousePos);
		void renderBut(sf::RenderTarget& target);
	public:
		void setText(const std::string& item);
		const std::string getText() const;
		const bool isClicked() const;
	};
	class DropList
	{
	private:
		float keyTime;
		float keyTimeMax;
		bool isExpanded;
		gui::Button* activeDL;
		std::vector<gui::Button*> listItems;
		sf::Font& font;
	public:
		DropList(float x, float y, float width, float height, sf::Font& font, const std::vector<std::string>& items, uint16_t characterSize);
		~DropList();
	public:
		void updateDL(const sf::Vector2f& mousePos, const float& dt);
		void drawDL(sf::RenderTarget& target);
	public:
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
		const std::string getText() const;
	};
}
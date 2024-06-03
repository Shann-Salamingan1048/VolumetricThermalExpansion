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
		sf::Texture* textureBut;
		sf::Font* font;
		sf::IntRect* intrect;
		sf::Text text;
	private:
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;
	public:
		Button(float x, float y, float width, float height, const std::string& text, sf::Font* font, 
			sf::Color idleColor, sf::Color hoverColor, uint16_t characterSize, sf::Texture* texture, sf::IntRect* intrect);
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
		DropList(float x, float y, float width, float height, sf::Font& font, const std::vector<std::string>& items, uint16_t characterSize, 
			sf::Texture& texture, sf::IntRect& intrect, sf::Color& origColorBut, sf::Color& hoverColorBut);
		~DropList();
	public:
		void updateDL(const sf::Vector2f& mousePos, const float& dt);
		void drawDL(sf::RenderTarget& target);
	private:
		const bool getKeyTime();
		void updateKeyTime(const float& dt);
	public:
		const std::string getText() const;
		const bool get_isExpanded() const;
	};
	class TextBox
	{
	private:
		sf::Texture* textureTB; // TB TextBox
		sf::IntRect* intrectTB;
	private:
		bool clickedDot;
		bool clickedNegative;
	private:
		bool isLeftClicked;
		unsigned short butState;
		std::string textSTR;
		uint16_t maxChars;
	private:
		bool cursorVisible;            // Visibility of the cursor
		sf::Clock cursorTimer;         // Timer to control cursor blinking
		sf::RectangleShape cursor;     // blinking cursor when enter the text box
	private:
		sf::RectangleShape textShape;
		sf::Font* font;
		sf::Text text;
	public:
		TextBox(float x, float y, float width, float height, sf::Font* font, sf::Texture* textureTB, sf::IntRect* intrectTB);
		~TextBox();
	public:
		void updateTextBox(const sf::Vector2f& mousePos);
		void inputTextBox(sf::Event& evt);
		void renderTextBox(sf::RenderTarget& target);
	public:
		const bool isClicked() const;
		const std::string getText() const;
		void setText(const std::string& text);
	};
}
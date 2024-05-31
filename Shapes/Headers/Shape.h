#pragma once

#include "../../GUI/GUI.h"
namespace shapes
{
	class Shape
	{
	public:
		virtual ~Shape() = default;

		virtual void Update(const sf::Vector2f& mousePos, const float& dt) = 0;
		virtual void Render(sf::RenderTarget& target) = 0;
		virtual void Inputs(sf::Event& evt) = 0;
	};
	class Cube : public shapes::Shape
	{
	private:
		gui::Button* but_Enter;
	private:
		gui::DropList* drop1;
		gui::TextBox* textbox1;
	private:
		gui::DropList* drop2;
		gui::TextBox* textbox2;
	private:
		gui::DropList* drop3;
		gui::TextBox* textbox3;
	private:
		gui::TextBox* textbox4;
	private:
		sf::Text initVol;
		sf::Text initTemp; // temp = temprature
		sf::Text finalTemp;
		sf::Text Beta;
	public:
		Cube(const std::vector<std::string>& measure_Units, sf::Font& font, sf::Texture& textureBut, sf::IntRect& intrectBut, sf::Color& origColorBut, 
			sf::Color& hoverColorBut,sf::IntRect& intrectTB, const std::vector<std::string>& temp_Units);
		~Cube();

	public:
		void Update(const sf::Vector2f& mousePos, const float& dt) override;
		void Render(sf::RenderTarget& target) override;
		void Inputs(sf::Event& evt) override;
	};
}
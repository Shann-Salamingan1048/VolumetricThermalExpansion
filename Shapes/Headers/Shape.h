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
		gui::DropList* drop1;
		gui::TextBox* textbox1;
	public:
		Cube(const std::vector<std::string>& measure_Units, sf::Font& font, sf::Texture& textureBut, sf::IntRect& intrectBut, sf::Color& origColorBut, sf::Color& hoverColorBut);
		~Cube();

	public:
		void Update(const sf::Vector2f& mousePos, const float& dt) override;
		void Render(sf::RenderTarget& target) override;
		void Inputs(sf::Event& evt) override;
	};
}
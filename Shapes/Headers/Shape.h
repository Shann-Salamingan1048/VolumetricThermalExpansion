#pragma once

#include "../../GUI/GUI.h"
#include <sstream>
#include <format>
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
		gui::DropList* DL_On_Off;
	private:
		sf::Text initVol;
		sf::Text initTemp; // temp = temprature
		sf::Text finalTemp;
		sf::Text Beta;
		sf::Text RotateTxt;
		sf::Text f_VolTxt;
		sf::Text delta_VolTxt;
	private: // try
		std::vector<sf::Vector3f> vertices =  std::vector<sf::Vector3f>(8);
		std::vector<sf::Vector3f> copy_OrigVertices = std::vector<sf::Vector3f>(8);
		std::vector<sf::Vector2i> edges; 
		void drawCube(sf::RenderTarget& target);
		void initVertices();
	private: // this needs to be optimize together with indicateStop
		float cubeSize;
		float cubeSizeLimit;
		float copyCubeSize;
		float indicateStop;
	private:
		const float rotationSpeed;
		void rotate(sf::Vector3f& point);
	private: // calculation sa formula ng volumetric thermal expansion
		void calculationProcess();
		float delta_Vol;
		float i_temp;
		float f_temp;
		float delta_temp;
		float beta;
		float i_vol;
		float f_vol;
		const float FarToCel(const std::string& Fahre) const;
	public:
		Cube(const std::vector<std::string>& measure_Units, sf::Font& font, sf::Texture& textureBut, sf::IntRect& intrectBut, sf::Color& origColorBut, 
			sf::Color& hoverColorBut,sf::IntRect& intrectTB, const std::vector<std::string>& temp_Units, const std::vector<std::string>& On_off);
		~Cube();

	public:
		void Update(const sf::Vector2f& mousePos, const float& dt) override;
		void Render(sf::RenderTarget& target) override;
		void Inputs(sf::Event& evt) override;
	};
}
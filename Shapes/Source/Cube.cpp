
#include "..\Headers\Shape.h"

shapes::Cube::~Cube()
{
	delete this->but_Enter;
	delete this->drop1;
	delete this->textbox1;

	delete this->drop2;
	delete this->textbox2;

	delete this->drop3;
	delete this->textbox3;

	delete this->textbox4;
	delete this->DL_On_Off;
}
shapes::Cube::Cube(const std::vector<std::string>& measure_Units, sf::Font& font,sf::Texture& texture, sf::IntRect& intrectBut,
	sf::Color& origColorBut, sf::Color& hoverColorBut, sf::IntRect& intrectTB, const std::vector<std::string>& temp_Units, const std::vector<std::string>& on_off)
	: rotationSpeed(0.05)
{
	// for cube
	this->but_Enter = new gui::Button(1000, 1200, 200, 100, "Enter", &font, origColorBut, hoverColorBut, 50, &texture, &intrectBut);
	// initial Volume
	this->drop1 = new gui::DropList(350, 1000, 300, 100, font, measure_Units, 35, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox1 = new gui::TextBox(50, 1000, 300, 100, &font, &texture, &intrectTB);

	// initial Temp
	this->drop2 = new gui::DropList(950, 1000, 300, 100, font, temp_Units, 40, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox2 = new gui::TextBox(650, 1000, 300, 100, &font, &texture, &intrectTB);

	// final temp
	this->drop3 = new gui::DropList(1550, 1000, 300, 100, font, temp_Units, 40, texture, intrectBut, origColorBut, hoverColorBut);
	this->textbox3 = new gui::TextBox(1250, 1000, 300, 100, &font, &texture, &intrectTB);

	// Beta or coefficient of volume expansion
	this->textbox4 = new gui::TextBox(1850, 1000, 300, 100, &font, &texture, &intrectTB);

	// on or off rotate
	this->DL_On_Off = new gui::DropList(1550, 1200, 300, 100, font, on_off, 40, texture, intrectBut, origColorBut, hoverColorBut);
	// Texts
	this->initVol.setFont(font);
	this->initVol.setString("Initial Volume");
	this->initVol.setPosition(sf::Vector2f(70.0f, 1100.0f));
	this->initVol.setFillColor(sf::Color::Black);
	this->initVol.setCharacterSize(40);

	this->initTemp.setFont(font);
	this->initTemp.setString("Initial Temp");
	this->initTemp.setPosition(sf::Vector2f(680.0f, 1100.0f));
	this->initTemp.setFillColor(sf::Color::Black);
	this->initTemp.setCharacterSize(40);

	this->finalTemp.setFont(font);
	this->finalTemp.setString("Final Temp");
	this->finalTemp.setPosition(sf::Vector2f(1290.0f, 1100.0f));
	this->finalTemp.setFillColor(sf::Color::Black);
	this->finalTemp.setCharacterSize(40);

	this->Beta.setFont(font);
	this->Beta.setString("Coefficient \nof \nvolume \nexpansion");
	this->Beta.setPosition(sf::Vector2f(1900.0f, 1100.0f));
	this->Beta.setFillColor(sf::Color::Black);
	this->Beta.setCharacterSize(40);

	this->RotateTxt.setFont(font);
	this->RotateTxt.setString("Rotate: ");
	this->RotateTxt.setPosition(sf::Vector2f(1400.0f, 1230.0f));
	this->RotateTxt.setFillColor(sf::Color::Black);
	this->RotateTxt.setCharacterSize(40);

	this->f_VolTxt.setFont(font);
	this->f_VolTxt.setString("Final Volume:");
	this->f_VolTxt.setPosition(sf::Vector2f(400.0f, 300.0f));
	this->f_VolTxt.setFillColor(sf::Color::Black);
	this->f_VolTxt.setCharacterSize(40);

	this->delta_VolTxt.setFont(font);
	this->delta_VolTxt.setString("Delta Volume:");
	this->delta_VolTxt.setPosition(sf::Vector2f(400.0f, 400.0f));
	this->delta_VolTxt.setFillColor(sf::Color::Black);
	this->delta_VolTxt.setCharacterSize(40);
	// try ra anay kuman
	// front face
	this->edges.push_back(sf::Vector2i(0, 1)); // 0 ----- > 1
	this->edges.push_back(sf::Vector2i(1, 2)); // |         |
	this->edges.push_back(sf::Vector2i(2, 3)); // |         |
	this->edges.push_back(sf::Vector2i(3, 0)); // 3 < ----- 2

	// back face
	this->edges.push_back(sf::Vector2i(4, 5)); // 4 --> 5
	this->edges.push_back(sf::Vector2i(5, 6)); // 5 --> 6
	this->edges.push_back(sf::Vector2i(6, 7)); // 6 --> 7
	this->edges.push_back(sf::Vector2i(7, 4)); // 7 --> 4

	// connect back face and front face
	/*
				    4 ------------------------- 5
				  / |						   /|
				 /  |						  / |
	 			/	|						 /  |
			   /   	|						/   |
			  0---------------------------1 	|					
			  |	    |					  |	    |
			  | 	7 --------------------|---- 6
	          |	   /					  |    /
			  |   /                       |   /
			  |  /                        |  /
			  | /						  | /	
			  3---------------------------2
	
	*/
	this->edges.push_back(sf::Vector2i(0, 4)); // 0 --> 4
	this->edges.push_back(sf::Vector2i(1, 5)); // 1 --> 5
	this->edges.push_back(sf::Vector2i(2, 6)); // 2 --> 6
	this->edges.push_back(sf::Vector2i(3, 7)); // 3 --> 7

	this->cubeSize = 200;
	this->initVertices();

	/// set texts
	this->textbox1->setText("0");
	this->textbox2->setText("32");
	this->textbox3->setText("32");
	this->textbox4->setText("0");
}
void shapes::Cube::initVertices()
{
	float halfc_Size = this->cubeSize / 2;
	this->vertices[0] = { -halfc_Size, -halfc_Size,-halfc_Size };
	this->vertices[1] = { halfc_Size, -halfc_Size,-halfc_Size };
	this->vertices[2] = { halfc_Size, halfc_Size,-halfc_Size };
	this->vertices[3] = { -halfc_Size, halfc_Size,-halfc_Size };

	this->vertices[4] = { -halfc_Size, -halfc_Size,halfc_Size };
	this->vertices[5] = { halfc_Size, -halfc_Size,halfc_Size };
	this->vertices[6] = { halfc_Size, halfc_Size,halfc_Size };
	this->vertices[7] = { -halfc_Size, halfc_Size,halfc_Size };

	// copy vertices
	this->copy_OrigVertices = this->vertices;
}
void shapes::Cube::Render(sf::RenderTarget& target)//
{
	// button
	this->but_Enter->renderBut(target); // for cube
	// render droplists
	this->drop1->drawDL(target);
	this->drop2->drawDL(target);
	this->drop3->drawDL(target);
	this->DL_On_Off->drawDL(target);
	//render textboxes
	this->textbox1->renderTextBox(target);
	this->textbox2->renderTextBox(target);
	this->textbox3->renderTextBox(target);
	this->textbox4->renderTextBox(target);
	// render texts
	target.draw(this->initVol);
	target.draw(this->initTemp);
	target.draw(this->finalTemp);
	target.draw(this->Beta);
	target.draw(this->RotateTxt);
	target.draw(this->f_VolTxt);
	target.draw(this->delta_VolTxt);
	this->drawCube(target);
}
void shapes::Cube::Inputs(sf::Event& evt)
{
	if (this->textbox1->isClicked())
	{
		this->textbox1->inputTextBox(evt);
	}
	if (this->textbox2->isClicked())
	{
		this->textbox2->inputTextBox(evt);
	}
	if (this->textbox3->isClicked())
	{
		this->textbox3->inputTextBox(evt);
	}
	if (this->textbox4->isClicked())
	{
		this->textbox4->inputTextBox(evt);
	}
}
void shapes::Cube::Update(const sf::Vector2f& mousePos, const float& dt)
{
	this->but_Enter->updateBut(mousePos);
	if (this->but_Enter->isClicked()) // to know if it only clicked once
	{
		// reset the vertices
		this->vertices = this->copy_OrigVertices;
		this->calculationProcess();
	}
	//std::cout << "DropList: " << this->drop1->getText() << "\n";

	this->drop1->updateDL(mousePos, dt); // DL means Drop List
	this->drop2->updateDL(mousePos, dt);
	this->drop3->updateDL(mousePos, dt);
	this->DL_On_Off->updateDL(mousePos, dt);

	this->textbox1->updateTextBox(mousePos); 
	this->textbox2->updateTextBox(mousePos);
	this->textbox3->updateTextBox(mousePos);
	this->textbox4->updateTextBox(mousePos);
	// try
	if (this->DL_On_Off->getText() == "ON") // on or off the rotating feature
	{
		for (uint16_t i = 0; i < 8; i++)
		{
			rotate(this->vertices[i]);
		}
	}
	if (this->delta_Vol != 0 && this->indicateStop != this->f_temp) // if delta volume is not zero then add the value of expanding or shrinking
	{ // from initial temp to final temo
		this->cubeSize += 0.0001; // value of expanding or shrinking
		float addVal = 0.0055; // for indicatestop
		if (this->f_temp > this->i_temp) // if it reaches the f_temp then stop
			// the logic here is that from inital temp to final temp, keep adding the indicatestop till it reaches final temp
			// if it is not equal to final temp then keep on expanding or shrinking
		{
			this->indicateStop += addVal;
			if (this->indicateStop > this->f_temp || this->indicateStop == this->f_temp)
			{
				this->indicateStop = this->f_temp;
			}
		}
		else if (this->f_temp < this->i_temp)
		{
			this->indicateStop += -addVal;
			if (this->indicateStop < this->f_temp || this->indicateStop == this->f_temp)
			{
				this->indicateStop = this->f_temp;
			}
		}
	}
	//std::cout << "Indicate Stop: " << this->indicateStop << "\n";
}
void shapes::Cube::calculationProcess()
{
	if (this->drop2->getText() == "Fahrenheit")
	{
		this->i_temp = this->FarToCel(this->textbox2->getText());
		std::cout << "Far to cel Initial: " << this->i_temp << "\n";
	}
	else
	{
		this->i_temp = std::stof(this->textbox2->getText());
	}
	if (this->drop3->getText() == "Fahrenheit")
	{
		this->f_temp = this->FarToCel(this->textbox3->getText());
		std::cout << "Far to cel Final: " << this->f_temp << "\n";
	}
	else
	{
		this->f_temp = std::stof(this->textbox3->getText());
	}
	this->delta_temp = this->f_temp - this->i_temp;
	this->indicateStop = this->i_temp; // start from initial temp to the final temp
	this->i_vol = std::stof(this->textbox1->getText());
	this->beta = std::stof(this->textbox4->getText());
	this->delta_Vol = this->delta_temp * this->i_vol * this->beta;
	this->f_vol = this->delta_Vol + this->i_vol;
	// this can be deleted
	std::cout << "Volume start: " << this->i_vol << "\nDelta Temp (final - initial): " << this->delta_temp << ", " << this->f_temp << ", " << this->i_temp << "\nBeta: " << this->beta 
		<< "\nDelta Volume: " << this->delta_Vol << "\nFinal Volume: " << this->f_vol << "\n";
	
	// set text the final volume and delta volume
	std::string formattedF_vol = std::format("{:.2f}", this->f_vol);
	std::string formattedDelta_vol = std::format("{:.2f}", this->delta_Vol);
	this->f_VolTxt.setString("Final Volume: " + formattedF_vol + this->drop1->getText());
	this->delta_VolTxt.setString("Delta Volume: " + formattedDelta_vol + this->drop1->getText());
}
const float shapes::Cube::FarToCel(const std::string& Fahre) const // convert farenheit to celcius
{
	std::stringstream ss;
	ss << Fahre;
	float fahrenheit;
	ss >> fahrenheit;
	return (fahrenheit - 32) * 5.0 / 9.0;
}

void shapes::Cube::drawCube(sf::RenderTarget& target)
{
	// if delta volume is not zero then do expanding or shrinking
	if (this->indicateStop != this->f_temp) // if it reaches f_temp then stop exapnding or shrinking
	{
		if (this->delta_Vol != 0 && this->f_temp > this->i_temp) // if f_temp is > i_temp then expand
		{
			for (auto& i : this->vertices)
			{
				i *= this->cubeSize / 200.0f; // Scale vertices based on cube size ,,, expanding
			}
		}
		else if (this->delta_Vol != 0 && this->f_temp < this->i_temp) // if f_temp is < i_temp then shrink
		{
			for (auto& i : this->vertices)
			{
				i *= 200.0f / this->cubeSize; // shrinking or getting small
			}
		}
	}
	///////////////////////
	// get the dimensions of the windows
	const uint16_t WIDTH = target.getSize().x;
	const uint16_t HEIGHT = target.getSize().y;
	const uint16_t dividedByY = 4;
	const uint16_t dividedByX = 2;
	for (int i = 0; i < 12; i++) 
	{
		sf::Vertex line[] = 
		{
				sf::Vertex(sf::Vector2f(this->vertices[edges[i].x].x + WIDTH / dividedByX, this->vertices[edges[i].x].y + HEIGHT / dividedByY), sf::Color::Blue),
				sf::Vertex(sf::Vector2f(this->vertices[edges[i].y].x + WIDTH / dividedByX, this->vertices[edges[i].y].y + HEIGHT / dividedByY), sf::Color::Blue)
		};
		target.draw(line, 2, sf::Lines);
		// Draw additional lines to make it appear bold
		sf::Vertex boldLine1[] = 
		{
			sf::Vertex(sf::Vector2f(vertices[edges[i].x].x + WIDTH / dividedByX - 1, vertices[edges[i].x].y + HEIGHT / dividedByY - 1), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(vertices[edges[i].y].x + WIDTH / dividedByX - 1, vertices[edges[i].y].y + HEIGHT / dividedByY - 1), sf::Color::Blue)
		};

		sf::Vertex boldLine2[] =
		{
			sf::Vertex(sf::Vector2f(vertices[edges[i].x].x + WIDTH / dividedByX + 1, vertices[edges[i].x].y + HEIGHT / dividedByY + 1), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(vertices[edges[i].y].x + WIDTH / dividedByX + 1, vertices[edges[i].y].y + HEIGHT / dividedByY + 1), sf::Color::Blue)
		};
		sf::Vertex boldLine3[] =
		{
			sf::Vertex(sf::Vector2f(vertices[edges[i].x].x + WIDTH / dividedByX + 2, vertices[edges[i].x].y + HEIGHT / dividedByY + 2), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(vertices[edges[i].y].x + WIDTH / dividedByX + 2, vertices[edges[i].y].y + HEIGHT / dividedByY + 2), sf::Color::Blue)
		};
		sf::Vertex boldLine4[] =
		{
			sf::Vertex(sf::Vector2f(vertices[edges[i].x].x + WIDTH / dividedByX - 2, vertices[edges[i].x].y + HEIGHT / dividedByY - 2), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(vertices[edges[i].y].x + WIDTH / dividedByX - 2, vertices[edges[i].y].y + HEIGHT / dividedByY - 2), sf::Color::Blue)
		};
		// Draw the additional lines to make it appear bold
		target.draw(boldLine1, 2, sf::Lines);
		target.draw(boldLine2, 2, sf::Lines);
		target.draw(boldLine3, 2, sf::Lines);
		target.draw(boldLine4, 2, sf::Lines);
	}
	
	//this->updateSize();
}
void shapes::Cube::rotate(sf::Vector3f& p)
{
	double cosX = std::cos(this->rotationSpeed);
	double sinX = std::sin(this->rotationSpeed);
	double cosY = std::cos(this->rotationSpeed);
	double sinY = std::sin(this->rotationSpeed);

	double tempX = p.x;
	p.x = cosY * p.x - sinY * p.z;
	p.z = sinY * tempX + cosY * p.z;

	tempX = p.x;
	p.x = cosX * p.x - sinX * p.y;
	p.y = sinX * tempX + cosX * p.y;

}
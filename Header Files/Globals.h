#pragma once
#include <vector>
constexpr unsigned int Screen_Height = 1400;
constexpr unsigned int Screen_Width = 2200;

inline const std::vector<std::string> measure_Units
{
	"Cu Meter" , "Cu Centimeter", "Cu Feet"
};
inline const std::vector<std::string> temp_Units
{
	"Celcius", "Fahrenheit"
};
inline const  std::vector<std::string> On_off
{
	"OFF", "ON"
};
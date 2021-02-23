#pragma once

#include <iostream>
#include <Vector3.h>

//\===========================================================
//\Set Up ColourRGB to be an alias for Vector3
//\===========================================================
using ColourRGB = Vector3;

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour)
{
	///cast float colour values to int for output to file
	a_ostream << static_cast<int>(255.999f * a_colour.x) << ' ' <<
				 static_cast<int>(255.999f * a_colour.y) << ' ' <<
				 static_cast<int>(255.999f * a_colour.z) << ' ';
}
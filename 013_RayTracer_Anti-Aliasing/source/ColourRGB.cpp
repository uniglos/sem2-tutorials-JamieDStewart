#include "ColourRGB.h"

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour)
{
	///cast float colour values to int for output to file
	a_ostream << static_cast<int>(255.999f * a_colour.x) << ' ' <<
		static_cast<int>(255.999f * a_colour.y) << ' ' <<
		static_cast<int>(255.999f * a_colour.z) << ' ';
}
//\===========================================================
//\ Function to transform ray from world space direction to colour value
//\   Direction is in space -1 -> 1, Colour data in space 0 -> 1
//\===========================================================
ColourRGB RayToColour(const Ray& a_ray)
{
	return (a_ray.Direction() + 1.f) * 0.5f;
}
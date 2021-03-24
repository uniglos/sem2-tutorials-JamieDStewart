#pragma once

#include <iostream>
#include <Vector3.h>
#include <Ray.h>

//\===========================================================
//\Set Up ColourRGB to be an alias for Vector3
//\===========================================================
using ColourRGB = Vector3;

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour);
//\===========================================================
//\ Function to transform ray from world space direction to colour value
//\   Direction is in space -1 -> 1, Colour data in space 0 -> 1
//\===========================================================
ColourRGB RayToColour(const Ray& a_ray);
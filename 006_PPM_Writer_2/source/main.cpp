
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "ColourRGB.h"

typedef enum input_args
{
	OUTPUT_FILE = 1,
	OUTPUT_WIDTH,
	OUTPUT_HEIGHT,
}input_args;


void displayUsage(char* a_path)
{
	std::string fullpath = a_path; //get the full path as a string
		//strip off the path part of the string to only keep the executable name
	std::string exeName = fullpath.substr(fullpath.find_last_of('\\') + 1, fullpath.length());
	//display a message to the user indicating usage of the executable
	std::cout << "usage: " << exeName << " [output image name] [image width] [image height]" << std::endl;
	std::cout << "\t-h or --help\t\tShow this message" << std::endl;
}

int main(int argv, char* argc[])
{
	//Set up the dimensions of the image
	int imageWidth = 256;
	int imageHeight = 256;
	int channelColours = 255;
	//output file name
	std::string outputFilename;

#pragma region Process Variadic Args
	if (argv < 2) //less than 2 as the path and executable name are always present
	{
		displayUsage(argc[0]);
		return EXIT_SUCCESS;
	}
	else //Some variadic arguments have been passed
	{
		for (int i = 1; i < argv; ++i)
		{
			std::string arg = argc[i];
			if (arg == "-h" || arg == "--help")
			{
				displayUsage(argc[0]);
				return EXIT_SUCCESS;
			}
			switch (i)
			{
			case OUTPUT_FILE:
			{
				outputFilename = argc[OUTPUT_FILE];
				//check to see if the extension was included
				if (outputFilename.find_last_of(".") == std::string::npos)
				{
					//no extension better add one
					outputFilename.append(".ppm");
				}
				break;
			}
			case OUTPUT_WIDTH:
			{
				imageWidth = atoi(argc[OUTPUT_WIDTH]);
				break;
			}
			case OUTPUT_HEIGHT:
			{
				imageHeight = atoi(argc[OUTPUT_HEIGHT]);
				break;
			}
			default:
			{
				continue;
			}
			}
		}

	}
#pragma endregion
	//Need to change std::cout to outputFileName
	std::streambuf* backup = std::cout.rdbuf();	//backup std::cout's stream buffer
	std::ofstream outbuff(outputFilename.c_str());	//create an out file stream and set it to our output file name
	std::cout.rdbuf(outbuff.rdbuf());	//set the stream buffer for cout to the file out stream buffer

	//output the Image Header data
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << channelColours << std::endl;

	//for each row of the image
	for (int i = 0; i < imageHeight; ++i)
	{
		std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
		//for each pixel in a row
		for (int j = 0; j < imageWidth; ++j)
		{
			//calculate colour value as a float in range 0 -> 1 to produce a gradient
			ColourRGB colour = ColourRGB( float(j) / (imageWidth - 1),
									  float(i) / (imageHeight - 1), 
									  1.f - (float(j) / (imageWidth - 1)) * (float(i) / (imageHeight - 1)));

			//Write colour data out to file
			WriteColourRGB(std::cout, colour);
		}
		std::cout << std::endl;
	}

	//set the output stream buffer back to what it was previously
	std::cout.rdbuf(backup);
	return EXIT_SUCCESS;
}
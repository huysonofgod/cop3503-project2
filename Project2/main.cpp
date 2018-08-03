#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include "Image.h"
using namespace std;

// Declarations
Image MultiplyBlend(Image &A, Image &B);
Image SubtractionBlend(Image &A, Image &B);
Image ScreenBlend(Image &A, Image &B);
float scaleValue(float _float);
uint clampValues(int result);

int main()
{
	// Part 1
	Image layer1, pattern1;
	layer1.LoadImageFile("layer1");
	pattern1.LoadImageFile("pattern1");
	
	Image part1 = MultiplyBlend(layer1, pattern1);
	//part1.WriteImage("part1");

	// Part 2
	Image layer2, car;
	layer2.LoadImageFile("layer2");
	car.LoadImageFile("car");

	Image part2 = SubtractionBlend(car, layer2);
	//part2.WriteImage("part2");


	// Part 3
	Image temp, text;
	Image pattern2;
	pattern2.LoadImageFile("pattern2");
	temp = MultiplyBlend(layer1, pattern2);

	text.LoadImageFile("text");
	Image part3 = ScreenBlend(text , temp);
	//part3.WriteImage("part3");

	// Part 4
	Image circles;
	circles.LoadImageFile("circles");
	Image temp1 = MultiplyBlend(layer2, circles);
	Image part4 = SubtractionBlend(temp1, pattern2);

	//part4.WriteImage("part4");
	return 0;
}


Image MultiplyBlend(Image &A, Image &B)
{
	Image C;
	// Set the header
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);
	A.setUints();
	B.setUints();
	
	// Load vectors for A and B blend them
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	// Iterate through each pixel and blend them
	vector<Pixel> Cvect;
	for (uint i = 0; i < Avect.size(); i++)
	{
		Pixel Cpixel;

		uint rInt = (uint) (scaleValue(Avect[i].rInt * Bvect.at(i).rInt / 255.0f));
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;

		uint gInt = (uint) (scaleValue(Avect[i].gInt * Bvect.at(i).gInt / 255.0f));
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;

		uint bInt = (uint) (scaleValue(Avect[i].bInt * Bvect.at(i).bInt / 255.0f));
		uchar bChar = A.ConvertInttoChar(bInt);
		Cpixel.blue = bChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);

	return C;

}

Image SubtractionBlend(Image & A, Image & B)
{
	Image C;
	// Set the header
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);
	A.setUints();
	B.setUints();

	// Load vectors for A and B blend them
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	// Iterate through each pixel and blend them
	vector<Pixel> Cvect;
	int result;
	for (uint i = 0; i < Avect.size(); i++)
	{
		Pixel Cpixel;

		// Check for overflow or underflow
		result = Avect[i].rInt - Bvect[i].rInt;
		uint rInt = clampValues(result);
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;

		result = Avect[i].gInt - Bvect[i].gInt;
		uint gInt = clampValues(result);
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;

		result = Avect[i].bInt - Bvect[i].bInt;
		uint bInt = clampValues(result);
		uchar bChar = A.ConvertInttoChar(bInt);
		Cpixel.blue = bChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);

	return C;
}

Image ScreenBlend(Image & A, Image & B)
{
	Image C;
	// Set the header
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);
	A.setUints();
	B.setUints();

	// Load vectors for A and B blend them
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	// Iterate through each pixel and blend them
	vector<Pixel> Cvect;
	for (uint i = 0; i < Avect.size(); i++)
	{
		Pixel Cpixel;

		float fRed = 1.0f - (1.0f - (((float)(Avect[i].rInt) / 255.0f))) * ((1.0f - ((float)(Bvect[i].rInt) / 255.0f)));
		uint rInt = (uint)scaleValue(fRed * 255.0f);
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;

		float fGreen = 1.0f - (1.0f - (((float)(Avect[i].gInt) / 255.0f))) * ((1.0f - ((float)(Bvect[i].gInt) / 255.0f)));
		uint gInt = (uint)scaleValue(fGreen * 255.0f);
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;

		float fBlue = 1.0f - (1.0f - (((float)(Avect[i].bInt) / 255.0f))) * ((1.0f - ((float)(Bvect[i].bInt) / 255.0f)));
		uint bInt = (uint)scaleValue(fBlue * 255.0f);
		uchar bChar = A.ConvertInttoChar(bInt);
		Cpixel.blue = bChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);

	return C;
}

float scaleValue(float _float)
{
	_float += 0.5f;
	return _float;
}

uint clampValues(int result)
{
	uint finalVal;

	if (result < 0)
	{
		finalVal = 0;
	}
	else if (result > 255)
	{
		finalVal = 255;
	}
	else
	{
		finalVal = result;
	}

	return finalVal;
}


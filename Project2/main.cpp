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
Image OverlayBlend(Image &A, Image &B);
Image Part6(Image &A);
Image Part7(Image &A);
Image Part8(string channel, Image &A);
Image Part9(Image &A, Image &B, Image &C);

float scaleValue(float _float);
uint clampValues(int result);
float screenHelper(float factor,uint Aval, uint Bval);
bool isDarker(uint val);

int main()
{
	//// Part 1
	//Image layer1, pattern1;
	//layer1.LoadImageFile("layer1");
	//pattern1.LoadImageFile("pattern1");
	//
	//Image part1 = MultiplyBlend(layer1, pattern1);
	////part1.WriteImage("part1");

	// Part 2
	Image layer2, car;
	layer2.LoadImageFile("layer2");
	car.LoadImageFile("car");

	//Image part2 = SubtractionBlend(car, layer2);
	////part2.WriteImage("part2");


	//// Part 3
	//Image temp, text;
	//Image pattern2;
	//pattern2.LoadImageFile("pattern2");
	//temp = MultiplyBlend(layer1, pattern2);

	//text.LoadImageFile("text");
	//Image part3 = ScreenBlend(text , temp);
	////part3.WriteImage("part3");

	//// Part 4
	//Image circles;
	//circles.LoadImageFile("circles");
	//Image temp1 = MultiplyBlend(layer2, circles);
	//Image part4 = SubtractionBlend(temp1, pattern2);
	////part4.WriteImage("part4");

	//// Part 5
	//Image part5 = OverlayBlend(layer1, pattern1);
	////part5.WriteImage("part5");

	//// Part 6
	//Image part6 = Part6(car);
	////part6.WriteImage("part6");


	//// Part 7
	//Image part7 = Part7(car);
	//part7.WriteImage("part7");

	//// Part 8
	//Image part8_r, part8_g, part8_b;
	//part8_r = Part8("red", car);
	//part8_r.WriteImage("part8_r");

	//part8_g = Part8("green", car);
	//part8_g.WriteImage("part8_g");

	//part8_b = Part8("blue", car);
	//part8_b.WriteImage("part8_b");
	
	// Part 9
	Image part9, layer_red, layer_green, layer_blue;
	layer_red.LoadImageFile("layer_red");
	layer_green.LoadImageFile("layer_green");
	layer_blue.LoadImageFile("layer_blue");
	
	part9 = Part9(layer_red, layer_green, layer_blue);
	part9.WriteImage("part9");

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

Image Part7(Image &A)
{
	Image C;
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);

	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Cvect;

	for (uint i = 0; i < Avect.size(); i++)
	{

		Pixel Cpixel;
		// Scale red channel by 4
		uint rInt;
		float rFloat = ((float)Avect[i].rInt / 255.0f) * 4.0f;
		rInt = (uint)scaleValue(rFloat * 255.0f);
		// Clamp values to stop overflow
		rInt = clampValues(rInt);
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;
		
		Cpixel.green = Avect[i].green;

		// Scale blue channel by 0
		Cpixel.blue = (uchar) '\0';
		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);
	C.setUints();

	return C;
}

Image Part8(string channel, Image &A)
{
	Image C;
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);

	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Cvect;

	for (uint i = 0; i < Avect.size(); i++)
	{
		Pixel Cpixel;
		uchar channelChar;

		// Assign pixel vals bassed on channel passed

		if (channel == "red")
		{
			channelChar = Avect[i].red;
		}
		else if (channel == "green")
		{
			channelChar = Avect[i].green;
		}
		else if (channel == "blue")
		{
			channelChar = Avect[i].blue;
		}

		Cpixel.red = channelChar;
		Cpixel.green = channelChar;
		Cpixel.blue = channelChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);
	C.setUints();

	return C;

}

Image Part9(Image & rLayer, Image & gLayer, Image & bLayer)
{
	Image D;
	// Set the header
	Image::Header newHeader = rLayer.getHeader();
	D.setHeader(newHeader);

	// Load vectors for A, B and C
	vector<Pixel> rvect = rLayer.getPixelVector();
	vector<Pixel> gvect = gLayer.getPixelVector();
	vector <Pixel> bvect = bLayer.getPixelVector();

	// Iterate through each pixel and blend them
	vector<Pixel> Dvect;
	for (uint i = 0; i < rvect.size(); i++)
	{
		Pixel Dpixel;
		Dpixel.red = rvect[i].red;
		Dpixel.green = gvect[i].green;
		Dpixel.blue = bvect[i].blue;

		Dvect.push_back(Dpixel);
	}

	D.setPixelVector(Dvect);

	return D;
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

		float fRed = screenHelper(1.0f, Avect[i].rInt, Bvect[i].rInt);
		uint rInt = (uint)scaleValue(fRed * 255.0f);
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;

		float fGreen = screenHelper(1.0f, Avect[i].gInt, Bvect[i].gInt);
		uint gInt = (uint)scaleValue(fGreen * 255.0f);
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;

		float fBlue = screenHelper(1.0f, Avect[i].bInt, Bvect[i].bInt);
		uint bInt = (uint)scaleValue(fBlue * 255.0f);
		uchar bChar = A.ConvertInttoChar(bInt);
		Cpixel.blue = bChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);

	return C;
}

float screenHelper(float factor, uint Aval, uint Bval)
{
	// Factor determines result for either Screen blend or overlay blend
	float fVal = 1.0f - factor * ((1.0f - (((float)(Aval) / 255.0f))) * ((1.0f - ((float)(Bval) / 255.0f))));
	return fVal;
}

Image OverlayBlend(Image & A, Image & B)
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
		uint rInt;
		uint gInt;
		uint bInt;

		// Check the bakground value for each pixel component
		if (isDarker(Bvect[i].rInt))
		{
			rInt = (uint)(2.0f * scaleValue(Avect[i].rInt * Bvect.at(i).rInt / 255.0f));
		}
		else
		{
			float fRed = screenHelper(2.0f, Avect[i].rInt, Bvect[i].rInt);
			rInt = (uint)scaleValue(fRed * 255.0f);
		}
		uchar rChar = A.ConvertInttoChar(rInt);
		Cpixel.red = rChar;

		// Green val
		if (isDarker(Bvect[i].gInt))
		{
			gInt = (uint)(2.0f * scaleValue(Avect[i].gInt * Bvect.at(i).gInt / 255.0f));
		}
		else
		{
			float fGreen = screenHelper(2.0f, Avect[i].gInt, Bvect[i].gInt);
			gInt = (uint)scaleValue(fGreen * 255.0f);
		}
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;


		// Blue Val
		if (isDarker(Bvect[i].bInt))
		{
			bInt = (uint)(2.0f * scaleValue(Avect[i].bInt * Bvect.at(i).bInt / 255.0f));
		}
		else
		{
			float fBlue = screenHelper(2.0f, Avect[i].bInt, Bvect[i].bInt);
			bInt = (uint)scaleValue(fBlue * 255.0f);
		}
		uchar bChar = A.ConvertInttoChar(bInt);
		Cpixel.blue = bChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);


	return C;
}


Image Part6(Image & A)
{

	Image C;
	vector<Pixel> Avect = A.getPixelVector();
	// Set the header
	Image::Header newHeader = A.getHeader();
	C.setHeader(newHeader);

	// Iterate through each pixel and blend them
	vector<Pixel> Cvect;
	int result;
	for (uint i = 0; i < Avect.size(); i++)
	{
		Pixel Cpixel;
		Cpixel.red = Avect[i].red;
		Cpixel.blue = Avect[i].blue;

		// Add 200 to the green channel and clamp values
		result = Avect[i].gInt + 200;
		uint gInt = clampValues(result);
		uchar gChar = A.ConvertInttoChar(gInt);
		Cpixel.green = gChar;

		Cvect.push_back(Cpixel);
	}

	C.setPixelVector(Cvect);

	return C;
}


bool isDarker(uint val)
{
	return (val < (uint)127);
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


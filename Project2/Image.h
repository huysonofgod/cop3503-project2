#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <conio.h>
#include <fstream>
using namespace std;
typedef unsigned int uint;
typedef unsigned char uchar;

// Pixel Struct
struct Pixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;

	uint rInt, bInt, gInt;
};


class Image {
public:
	// Image Header Struct
	struct Header
	{
		char idLength;
		char colourMapType;
		char imageType;
		short colourMapOrigin;
		short colourMapLength;
		char colourMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};

	// Load data from the tga file
	void LoadImageFile(string fileName);

	// Write data to another file
	void WriteImage(string outFileName);

	// Convert from uchar to uint
	uint ConvertCharToInt(uchar _char);
	uchar ConvertInttoChar(uint _int);

	void setUints();


	/*		Accessors and Mutators		*/
	// Get Header struct
	Header getHeader();

	// Set Header values
	void setHeader(Header &headerData);

	// Get pixel vector
	vector<Pixel> getPixelVector();

	// Set pixel vector
	void setPixelVector(vector<Pixel> &vect);

private:
	Header header;
	Pixel pixel;
	vector<Pixel> pixelVector;
	
};









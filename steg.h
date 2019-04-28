#ifndef __STEG
#define __STEG

#include "CImg.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace cimg_library;
using namespace std;

class StegImg
{
private:
	vector<vector<unsigned int>> PixelMatrix;

public:
	StegImg() {}
	StegImg(unsigned int width, unsigned int height, unsigned int spectrum) { EncImg.assign(width, height, 1, spectrum, 0); }
	StegImg(CImg<unsigned char> img) { EncImg.assign(img); }
	~StegImg() { ~EncImg; }

	CImg<unsigned char> EncImg;

	void StorePixelVals(CImg<unsigned char> img); //Reads pixel values from an image and stores it into PixelMatrix.
	void StoreTSPixelVals(CImg<unsigned char> img, string text); //Reads Transformed pixel values from an image and stores it into PixelMatrix.
	void CreateStegImg(); //Creates image from PixelMatrix. Text only
	void CreateStegPicImg(CImg<unsigned char> img); //Creates image from another image. Image only
	void CreateStegTextPicImg(CImg<unsigned char> img, string text); //Creates image from PixelMatrix and another image. Text and Image combined
	void ExportImg(string name); //Exports Stored EncImg
	void DisplayImg(); //Displays EncImg
};

#endif
#ifndef __DECRYPTER
#define __DECRYPTER

#include "CImg.h"
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace cimg_library;
using namespace std;

class ImgReader
{
private:
	CImg<unsigned char> EncImg;
	CImg<unsigned char> RevealedImg;
	vector<unsigned char> message;

public:
	ImgReader() {}
	ImgReader(CImg<unsigned char> img) { EncImg.assign(img); }
	~ImgReader() { ~EncImg; }

	void DecryptStegImg();
	void RevealHiddenPic();
	void RevealHiddenPicWithText();
	void ReadMessage();
	void DisplayImg();
	void ExportImg(string name);
};

#endif
#include "steg.h"

void StegImg::StorePixelVals(CImg<unsigned char> img)
{
	for (int r = 0; r < EncImg.width(); r++)
	{
		vector<unsigned int> temp;
		int pixel = 0;

		for (int c = 0; c < EncImg.height(); c++)
		{
			pixel = 0;
			pixel += img(r, c, 0, 0); //Red
			pixel = pixel << 8;
			pixel += img(r, c, 0, 1); //Blue
			pixel = pixel << 8;
			pixel += img(r, c, 0, 2); //Green

			temp.push_back(pixel);
		}

		PixelMatrix.push_back(temp);
	}
}

void StegImg::StoreTSPixelVals(CImg<unsigned char> img, string text)
{
	/*
	We're changing the two least sig bits from RGB values.
	Count goes to 4 because 8bits/2bits = 4
	*/
 
	unsigned int count = 0; 
	unsigned int NullFill = 0; //Fills the next 8 bits with 0x00 to indicate sentinel, counts to 4

	string::iterator CurLetter = text.begin(); 
	
	for (int r = 0; r < EncImg.width(); r++)
	{
		vector<unsigned int> temp;
		int pixel = 0;

		for (int c = 0; c < EncImg.height(); c++) //TODO: Make helper function
		{
			//RED
			pixel = 0;
			pixel += img(r, c, 0, 0);
			if (CurLetter != text.end())
			{ 
				pixel = pixel & 0xFFFFFFFC;
				pixel |= *CurLetter & 0x00000003;
				*CurLetter = *CurLetter >> 2;
				count++;
			}
			if (count >= 4 && (CurLetter != text.end()))
			{
				count = 0;
				CurLetter++;
			}
			else if (CurLetter == text.end() && NullFill < 4)
			{
				pixel = pixel & 0xFFFFFFFC;
				NullFill++;
			}
			pixel = pixel << 8;
			
			//BLUE
			pixel += img(r, c, 0, 1);
			if (CurLetter != text.end())
			{
				pixel = pixel & 0xFFFFFFFC;
				pixel |= *CurLetter & 0x00000003;
				*CurLetter = *CurLetter >> 2;
				count++;
			}
			if (count >= 4 && (CurLetter != text.end()))
			{
				count = 0;
				CurLetter++;
			}
			else if (CurLetter == text.end() && NullFill < 4)
			{
				pixel = pixel & 0xFFFFFFFC;
				NullFill++;
			}
			pixel = pixel << 8;

			//GREEN
			pixel += img(r, c, 0, 2);
			if (CurLetter != text.end())
			{
				pixel = pixel & 0xFFFFFFFC;
				pixel |= *CurLetter & 0x00000003;
				*CurLetter = *CurLetter >> 2;
				count++;
			}
			if (count >= 4 && (CurLetter != text.end()))
			{
				count = 0;
				CurLetter++;
			}
			else if (CurLetter == text.end() && NullFill < 4)
			{
				pixel = pixel & 0xFFFFFFFC;
				NullFill++;
			}

			temp.push_back(pixel);
		}

		PixelMatrix.push_back(temp);
	}
}

void StegImg::CreateStegImg() 
{
	for (int r = 0; r < EncImg.width(); r++)
	{
		for (int c = 0; c < EncImg.height(); c++)
		{
			EncImg(r, c, 0, 0) = (PixelMatrix[r][c] & 0x00FF0000) >> 16;
			EncImg(r, c, 0, 1) = (PixelMatrix[r][c] & 0x0000FF00) >> 8;
			EncImg(r, c, 0, 2) = (PixelMatrix[r][c] & 0x000000FF);
		}
	}
}

void StegImg::CreateStegPicImg(CImg<unsigned char> img)
{
	int RowCount = 1;
	int ColCount = 1;
	int mod = 2;

	for (int r = 0; r < img.width(); r++)
	{
		if (RowCount % mod == 0)
		{
			for (int c = 0; c < img.height(); c++)
			{
				if (ColCount % mod == 0)
				{
					unsigned char temp = img(r, c, 0, 0) & 0xF0;
					temp = temp >> 4; 
					EncImg(r, c, 0, 0) = EncImg(r, c, 0, 0) & 0xF0; 
					EncImg(r, c, 0, 0) |= temp;
					
					temp = img(r, c, 0, 1) & 0xF0;
					temp = temp >> 4;
					EncImg(r, c, 0, 1) = EncImg(r, c, 0, 1) & 0xF0;
					EncImg(r, c, 0, 1) |= temp;

					temp = img(r, c, 0, 2) & 0xF0;
					temp = temp >> 4;
					EncImg(r, c, 0, 2) = EncImg(r, c, 0, 2) & 0xF0;
					EncImg(r, c, 0, 2) |= temp;
				}
				ColCount++;
			}
		}
		RowCount++;
	}
}

void StegImg::CreateStegTextPicImg(CImg<unsigned char> img, string text)
{
	int RowCount = 1;
	int ColCount = 1;
	int mod = 2;

	for (int r = 0; r < img.width(); r++)
	{
		if (RowCount % mod == 0)
		{
			for (int c = 0; c < img.height(); c++)
			{
				if (ColCount % mod == 0)
				{
					unsigned char temp = img(r, c, 0, 0) & 0xE0;
					temp = temp >> 3;
					EncImg(r, c, 0, 0) = EncImg(r, c, 0, 0) & 0xE3;
					EncImg(r, c, 0, 0) |= temp;

					temp = img(r, c, 0, 1) & 0xE0;
					temp = temp >> 3;
					EncImg(r, c, 0, 1) = EncImg(r, c, 0, 1) & 0xE3;
					EncImg(r, c, 0, 1) |= temp;

					temp = img(r, c, 0, 2) & 0xE0;
					temp = temp >> 3;
					EncImg(r, c, 0, 2) = EncImg(r, c, 0, 2) & 0xE3;
					EncImg(r, c, 0, 2) |= temp;
				}
				ColCount++;
			}
		}
		RowCount++;
	}

	StoreTSPixelVals(EncImg, text);
	CreateStegImg();
}

void StegImg::ExportImg(string name)
{
	name = name + ".png";
	EncImg.save_png(name.c_str());
}

void StegImg::DisplayImg()
{
	CImgDisplay display(EncImg, "Test Image");
	while (!display.is_closed())
	{
		display.wait();
	}
}
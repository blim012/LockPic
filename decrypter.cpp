#include "decrypter.h"

void ImgReader::DecryptStegImg()
{
	int count = 0; //Counts up to 4 as the message is separated 2 bits each (8/2 = 4)
	bool isDone = false;
	unsigned char symbol = 0;

	for (int r = 0; r < EncImg.width(); r++)
	{
		for (int c = 0; c < EncImg.height(); c++)
		{
			//RED
			if (!isDone)
			{
				if (count >= 4 && symbol == 0)
				{
					isDone = true;
				}
				else if (count >= 4 && symbol != 0)
				{
					count = 1;
					message.push_back(symbol);
					symbol = 0;
					symbol |= ((EncImg(r, c, 0, 0) & 0x00000003));
				}
				else
				{
					if (count == 0)
					{
						symbol |= (EncImg(r, c, 0, 0) & 0x00000003);
					}
					else
					{
						symbol |= ((EncImg(r, c, 0, 0) & 0x00000003) << 2*count);
					}
					count++;
				}
			}
		
			//GREEN
			if (!isDone)
			{
				if (count >= 4 && symbol == 0)
				{
					isDone = true;
				}
				else if (count >= 4 && symbol != 0)
				{
					count = 1;
					message.push_back(symbol);
					symbol = 0;
					symbol |= (EncImg(r, c, 0, 1) & 0x00000003);
				}
				else
				{
					if (count == 0)
					{
						symbol |= (EncImg(r, c, 0, 1) & 0x00000003);
					}
					else
					{
						symbol |= ((EncImg(r, c, 0, 1) & 0x00000003) << 2 * count);
					}
					count++;
				}
			}

			//BLUE
			if (!isDone)
			{
				if (count >= 4 && symbol == 0)
				{
					isDone = true;
				}
				else if (count >= 4 && symbol != 0)
				{
					count = 1;
					message.push_back(symbol);
					symbol = 0;
					symbol |= (EncImg(r, c, 0, 2) & 0x00000003);
				}
				else
				{
					if (count == 0)
					{
						symbol |= (EncImg(r, c, 0, 2) & 0x00000003);
					}
					else
					{
						symbol |= ((EncImg(r, c, 0, 2) & 0x00000003) << 2 * count);
					}
					count++;
				}
			}
		}
	}
}

void ImgReader::RevealHiddenPic()
{
	CImg<unsigned char> NewImg(EncImg.width(), EncImg.height(), 1, 3, 0);

	int RowCount = 1;
	int ColCount = 1;
	int mod = 2; 

	for (int r = 0; r < EncImg.width(); r++)
	{
		if (RowCount % mod == 0)
		{
			for (int c = 0; c < EncImg.height(); c++)
			{
				if (ColCount % mod == 0)
				{
					unsigned char temp = EncImg(r, c, 0, 0) & 0x0F; 
					temp = temp << 4; 
					NewImg(r, c, 0, 0) = temp;

					temp = EncImg(r, c, 0, 1) & 0x0F;
					temp = temp << 4;
					NewImg(r, c, 0, 1) = temp;

					temp = EncImg(r, c, 0, 2) & 0x0F;
					temp = temp << 4;
					NewImg(r, c, 0, 2) = temp;

				}
				ColCount++;
			}
		}
		RowCount++;
	}

	RevealedImg.assign(NewImg);
}

void ImgReader::RevealHiddenPicWithText()
{
	CImg<unsigned char> NewImg(EncImg.width(), EncImg.height(), 1, 3, 0);

	int RowCount = 1;
	int ColCount = 1;
	int mod = 2;

	for (int r = 0; r < EncImg.width(); r++)
	{
		if (RowCount % mod == 0)
		{
			for (int c = 0; c < EncImg.height(); c++)
			{
				if (ColCount % mod == 0)
				{
					unsigned char temp = EncImg(r, c, 0, 0) & 0x1C;
					temp = temp << 3;
					NewImg(r, c, 0, 0) = temp;

					temp = EncImg(r, c, 0, 1) & 0x1C;
					temp = temp << 3;
					NewImg(r, c, 0, 1) = temp;

					temp = EncImg(r, c, 0, 2) & 0x1C;
					temp = temp << 3;
					NewImg(r, c, 0, 2) = temp;

				}
				ColCount++;
			}
		}
		RowCount++;
	}

	RevealedImg.assign(NewImg);
}

void ImgReader::ReadMessage()
{
	for (unsigned int i = 0; i < message.size(); i++)
	{
		cout << message[i];
	}
	cout << endl;
}

void ImgReader::DisplayImg()
{
	CImgDisplay display(RevealedImg);
	while (!display.is_closed())
	{
		display.wait();
	}
}
void ImgReader::ExportImg(string name)
{
	name = name + ".png";
	RevealedImg.save_png(name.c_str());
}
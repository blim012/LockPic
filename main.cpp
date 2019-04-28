#include "steg.h"
#include "decrypter.h"
#include <iostream>
#include <experimental/filesystem>

using namespace cimg_library;
using namespace std;
using namespace experimental::filesystem::v1;

bool CheckExtension(string input)
{
	if (experimental::filesystem::path("images/" + input).extension() != ".png" &&
		experimental::filesystem::path("images/" + input).extension() != ".jpg" &&
		experimental::filesystem::path("images/" + input).extension() != ".jpeg" &&
		experimental::filesystem::path("images/" + input).extension() != ".bmp")
	{
		return false;
	}
	return true;
}

int main()
{
	bool quit = false;
	bool ImgFound = false;
	string input;

	cout << R"(
		

 __                            __        _______   __           
/  |                          /  |      /       \ /  |          
$$ |        ______    _______ $$ |   __ $$$$$$$  |$$/   _______ 
$$ |       /      \  /       |$$ |  /  |$$ |__$$ |/  | /       |
$$ |      /$$$$$$  |/$$$$$$$/ $$ |_/$$/ $$    $$/ $$ |/$$$$$$$/ 
$$ |      $$ |  $$ |$$ |      $$   $$<  $$$$$$$/  $$ |$$ |      
$$ |_____ $$ \__$$ |$$ \_____ $$$$$$  \ $$ |      $$ |$$ \_____ 
$$       |$$    $$/ $$       |$$ | $$  |$$ |      $$ |$$       |
$$$$$$$$/  $$$$$$/   $$$$$$$/ $$/   $$/ $$/       $$/  $$$$$$$/ 
                                                                
                                                                                                                                          
	)" << endl << endl;

	while (!quit)
	{
		cout << endl << "Type (steg) to create a steganographic image." << endl
			 << "Type (read) to decypher a steganographic image made by LockPic." << endl
			 << "Type (quit) to exit, and (back) to go back an option." << endl
			 << "Type (info) for information about Steganography" << endl;

		getline(cin, input);

		if (input == "steg")
		{
			//if (input != "quit") { input.clear(); }
			while (input != "quit" && input != "back")
			{
				cout << endl <<"Type the name of the image to transform from the images folder" << endl;
				getline(cin, input);

				ImgFound = experimental::filesystem::exists("images/" + input);
				if (!ImgFound && input != "quit" && input != "back")
				{
					cout << endl << "No image named " << input << " was found" << endl;
				}
				else if (!CheckExtension(input) && input != "quit" && input != "back")
				{
					cout << endl << "Invalid image type. Must be .png, .jpg, or .bmp" << endl;
				}
				else if (input == "quit") { quit = true; }
				else if (input != "back")
				{
					input = "images/" + input;
					CImg<unsigned char> img(input.c_str());
					while (input != "quit" && input != "back")
					{
						cout << endl << "Hide an (image), (text), or (both)?" << endl;
						getline(cin, input);

						if (input == "quit") { quit = true; }

						else if (input == "image")
						{
							while (input != "quit" && input != "back")
							{
								cout << endl << "Type the name of the image to hide that is from the images folder." << endl;
								getline(cin, input);

								ImgFound = experimental::filesystem::exists("images/" + input);
								if (!ImgFound && input != "quit" && input != "back")
								{
									cout << endl << "No image named " << input << " was found" << endl;
								}
								else if (!CheckExtension(input) && input != "quit" && input != "back")
								{
									cout << endl << "Invalid image type. Must be .png, .jpg, or .bmp" << endl;
								}
								else if (input == "quit") { quit = true; }
								else if (input != "back")
								{
									input = "images/" + input;
									CImg<unsigned char> hidden(input.c_str());
									if ((img.width() < hidden.width()) || img.height() < hidden.height())
									{
										input = "back";
										cout << endl << "The image you wish to hide is too large" << endl;
									}
									else
									{
										StegImg NewImg(img);
										NewImg.CreateStegPicImg(hidden);

										cout << endl << "Please name the image" << endl;
										getline(cin, input);
										NewImg.ExportImg(input);

										cout << endl << "Done. Display image? (y/n)" << endl;
										getline(cin, input);
										if (input == "y" || input == "yes")
										{
											NewImg.DisplayImg();
										}
										input = "quit";
									}
								}
							}
						}
						else if (input == "text")
						{
							while (input != "quit" && input != "back")
							{
								cout << endl << "Type the text to hide in the image" << endl;
								getline(cin, input);

								if (input.size() > (img.width() * img.height()))
								{
									input = "back";
									cout << endl << "String is too long and will not fit into the image." << endl;
								}
								else
								{
									StegImg NewImg(img);
									NewImg.StoreTSPixelVals(NewImg.EncImg, input);
									NewImg.CreateStegImg();

									cout << endl << "Please name the image" << endl;
									getline(cin, input);
									NewImg.ExportImg(input);

									cout << endl << "Done. Display image? (y/n)" << endl;
									getline(cin, input);
									if (input == "y" || input == "yes")
									{
										NewImg.DisplayImg();
									}
									input = "quit";
								}
							}
						}
						else if (input == "both")
						{
							while (input != "quit" && input != "back")
							{
								cout << endl << "Type the name of the image to hide that is from the images folder" << endl;
								getline(cin, input);

								ImgFound = experimental::filesystem::exists("images/" + input);
								if (!ImgFound && input != "quit" && input != "back")
								{
									cout << endl << "No image named " << input << " was found" << endl;
								}
								else if (!CheckExtension(input) && input != "quit" && input != "back")
								{
									cout << endl << "Invalid image type. Must be .png, .jpg, or .bmp" << endl;
								}
								else if (input == "quit") { quit = true; }
								else if (input != "back")
								{
									input = "images/" + input;
									CImg<unsigned char> hidden(input.c_str());
									if ((img.width() < hidden.width()) || img.height() < hidden.height())
									{
										input = "back";
										cout << endl << "The image you wish to hide is too large" << endl;
									}
									else
									{
										while (input != "quit" && input != "back")
										{
											cout << endl << "Type the text to hide in the image" << endl;
											getline(cin, input);

											if (input.size() > (img.width() * img.height()))
											{
												input = "back";
												cout << endl << "String is too long and will not fit into the image." << endl;
											}
											else
											{
												StegImg NewImg(img);
												NewImg.CreateStegTextPicImg(hidden, input);

												cout << endl << "Please name the image" << endl;
												getline(cin, input);
												NewImg.ExportImg(input);

												cout << endl << "Done. Display image? (y/n)" << endl;
												getline(cin, input);
												if (input == "y" || input == "yes")
												{
													NewImg.DisplayImg();
												}
												input = "quit";
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if (input == "read")
		{
			while (input != "quit" && input != "back")
			{
				cout << endl << "Reveal (text) or reveal (image)?" << endl;
				getline(cin, input);

				if (input == "quit") { quit = true; }

				else if (input == "text")
				{
					while (input != "quit" && input != "back")
					{
						cout << endl << "Type the name of the image to examine that is in the images folder" << endl;
						getline(cin, input);
						
						ImgFound = experimental::filesystem::exists("images/" + input);
						if (!ImgFound && input != "quit" && input != "back")
						{
							cout << endl << "No image named " << input << " was found" << endl;
						}
						else if (!CheckExtension(input) && input != "quit" && input != "back")
						{
							cout << endl << "Invalid image type. Must be .png, .jpg, or .bmp" << endl;
						}
						else if (input == "quit") { quit = true; }
						else if (input != "back")
						{
							input = "images/" + input;
							CImg<unsigned char> img(input.c_str());
							ImgReader ir(img);
							ir.DecryptStegImg();
							ir.ReadMessage();

							input = "quit";
						}
					}
				}
				else if (input == "image")
				{
					while (input != "quit" && input != "back")
					{
						cout << endl << "Type the name of the image to examine that is from the images folder" << endl;
						getline(cin, input);

						ImgFound = experimental::filesystem::exists("images/" + input);
						if (!ImgFound && input != "quit" && input != "back")
						{
							cout << endl << "No image named " << input << " was found" << endl;
						}
						else if (!CheckExtension(input) && input != "quit" && input != "back")
						{
							cout << endl << "Invalid image type. Must be .png, .jpg, or .bmp" << endl;
						}
						else if (input == "quit") { quit = true; } 
						else if(input != "back")
						{
							input = "images/" + input;
							CImg<unsigned char> img(input.c_str());
							ImgReader ir(img);
							ir.RevealHiddenPic();
							ir.DisplayImg();

							cout << endl << "Export image? (y,n)" << endl;
							getline(cin, input);

							if (input == "y" || input == "yes")
							{
								cout << endl << "Please name the image" << endl;
								getline(cin, input);
								ir.ExportImg(input.c_str());
							}

							input = "quit";
						}
					}
				}
			}
		}
		else if (input == "info")
		{
			cout << endl << "Steganography deals with confidential communication, and in the world of " 
				 << endl << "computers usually refers to the practice of concealing messages " 
				 << endl << "or images within another file. LockPic aims to do just that, allowing "
				 << endl << "a user to hide an image or message within an image, and decode it all the same," 
				 << endl << " allowing for discrete communcation between two individuals with LockPic." << endl;
		}
		else if (input == "quit")
		{
			quit = true;
		}
	}

	return 0;
}
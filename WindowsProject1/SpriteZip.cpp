#include "SpriteZip.h"


SpriteZip::SpriteZip() : SetMyImage()
{
	fileNames.push_back("ImageNames.txt");
	//fileNames.push_back("PlayerImageNames.txt");//exmaple
}

SpriteZip::~SpriteZip()
{

}

void SpriteZip::LoadImage(SetMyImage* _myImage, const char* filename, int count)
{
	_myImage[count].Load(filename);
}


int SpriteZip::ReadTextSetImage(std::string fileName)
{
	std::string line;
	std::string fileFath = "./ImageNames/";
	std::ifstream file(fileFath + fileName); // 파일을 연다. 없으면 생성. 
	getline(file, line);
	int count = 0;
	int size = atoi(line.c_str());
	playerImages = new SetMyImage[size];

	if (file.is_open()) {
		while (getline(file, line)) {
			LoadImage(playerImages, line.c_str(), count++);
		}
		file.close(); // 열었떤 파일을 닫는다. 
	}
	else {
		printf("Unable to open file");
		return -1;
	}
	return 0;
}

void SpriteZip::SetImage()
{
	size_t fileSize = fileNames.size();

	for (int i = 0; i < fileSize; i++)
	{
		if (ReadTextSetImage(fileNames[i].c_str()) == -1)
		{
			printf("Fail FileName : %s", fileNames[i].c_str());
		}
	}

}
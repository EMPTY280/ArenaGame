#pragma once
#include "SetMyImage.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
class SpriteZip :
    public SetMyImage
{

public:
    SpriteZip();
    virtual ~SpriteZip();

    std::vector<std::string> fileNames;
    //std::string* fileNames;
    SetMyImage* playerImages;
    void LoadImage(SetMyImage* _myImage, const char* filename, int count); // 이미지용.

    int ReadTextSetImage(std::string fileName);
    void SetImage();
};


#pragma once

#include "opencv2/objdetect.hpp"
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <map>

#include "Actor.h"

using namespace std;
using namespace cv;

class ImageInterpreter {
private:
	VideoCapture cap;
	pair<int, int> boardsize;
public:
	ImageInterpreter(pair<int,int> boardsize);
	Mat retrieveImage();
	void qrCodeDetector(vector<string> *decodedInfo, vector<Point> *corners);
	void updateActors(map<string,Actor*>* actors);
};

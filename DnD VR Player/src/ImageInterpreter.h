#pragma once

#include "opencv2/objdetect.hpp"
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <map>

#include "Actor.h"

using namespace std;
using namespace cv;

typedef struct
{
	string type;
	string data;
	vector <Point> location;
} DecodedObject;

class ImageInterpreter {
private:
	VideoCapture cap;
	pair<int, int> boardsize;
public:
	ImageInterpreter(pair<int,int> boardsize);
	Mat retrieveImage();
	void qrCodeDetector(vector<string> *decodedInfo, vector<Point> *corners);
	//void qrCodeDetector2(vector<DecodedObject> *decoded_objects);
	void updateActors(map<string,Actor*>* actors);
};

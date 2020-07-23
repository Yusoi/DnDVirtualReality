#include "ImageInterpreter.h"

ImageInterpreter::ImageInterpreter(pair<int,int> boardsize) {
	this->boardsize = boardsize;

	int deviceID = 0;
	int apiID = cv::CAP_ANY;

	cap.open(deviceID, apiID);
	if (!cap.isOpened()) {
		cerr << "ERROR: Camera Unavailable" << endl;
	}

	cv::namedWindow("Camera", WINDOW_AUTOSIZE);
}

Mat ImageInterpreter::retrieveImage() {
	Mat frame;

	cap.read(frame);
	if (frame.empty()) {
		cerr << "ERROR: Blank frame grabbed" << endl;
	}

	imshow("Camera", frame);
	waitKey(1);

	return frame;
}

void ImageInterpreter::qrCodeDetector(vector<string> *decodedInfo, vector<Point> *corners) {
	QRCodeDetector det;

	det.detectAndDecodeMulti(retrieveImage(), *decodedInfo, *corners);
}

void ImageInterpreter::updateActors(map<string,Actor*>* actors) {
	vector<string> decodedInfo;
	vector<Point> corners;

	qrCodeDetector(&decodedInfo, &corners);

	Point sw_bound, ne_bound;
	sw_bound = { 0,0 };
	ne_bound = { 0,0 };
	pair<int, int> actor_pos;
	int count = 0;

	map<string, pair<int, int>> actor_centers;

	for (vector<string>::iterator it = decodedInfo.begin(); it != decodedInfo.end(); it++) {
		if (!(*it).compare("SW")) {
			//Get northeastern corner
			sw_bound = corners.at(count * 4 + 1);
		}
		else if (!(*it).compare("NE")) {
			//Get southwestern corner
			ne_bound = corners.at(count * 4 + 3);
		}
		else {
			Point p1 = corners.at(count * 4);
			Point p2 = corners.at(count * 4 + 1);
			Point p3 = corners.at(count * 4 + 2);
			Point p4 = corners.at(count * 4 + 3);
			actor_pos = { (p1.x + p2.x + p3.x + p4.x) / 4, (p1.y + p2.y + p3.y + p4.y) / 4 };
			actor_centers.insert({ (*it),actor_pos });
		}
		count++;
	}

	int board_x = ne_bound.x - sw_bound.x;
	int board_y = sw_bound.y = ne_bound.y;
	int square_x = board_x / boardsize.first;
	int square_y = board_y / boardsize.second;

	if (board_x != 0 && board_y != 0) {
		for (map<string, Actor*>::iterator it = actors->begin(); it != actors->end(); it++) {
			if (actor_centers.count((*it).first)) {
				pair<int, int> actor_center = actor_centers.at((*it).first);

				(*it).second->setPos({ (actor_center.first - board_x) / square_x,
									   (actor_center.second - board_y) / square_y });

				(*it).second->resetInactiveCounter();
			}
			else {
				(*it).second->incrementInactiveCounter();
			}
		}
	}
}
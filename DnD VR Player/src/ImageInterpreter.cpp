#include "ImageInterpreter.h"

ImageInterpreter::ImageInterpreter() {
	int deviceID = 0;
	int apiID = cv::CAP_ANY;

	cap.open(deviceID, apiID);
	if (!cap.isOpened()) {
		cerr << "ERROR: Camera Unavailable" << endl;
	}
}

Mat ImageInterpreter::retrieveImage() {
	Mat frame;

	cap.read(frame);
	if (frame.empty()) {
		cerr << "ERROR: Blank frame grabbed" << endl;
	}

	return frame;
}

void ImageInterpreter::qrCodeDetector(vector<string> *decodedInfo, vector<Point> *corners) {
	QRCodeDetector det;

	det.detectAndDecodeMulti(retrieveImage(), *decodedInfo, *corners);

	for (vector<string>::iterator it = decodedInfo->begin(); it != decodedInfo->end(); it++) {
		cout << (*it) << " ";
	}

	for (vector<Point>::iterator it = corners->begin(); it != corners->end(); it++) {
		cout << (*it).x << " " <<  (*it).y << "//";
	}

	cout << endl;
}

void ImageInterpreter::updateActors(vector<Actor*>* actors) {
	vector<string> decodedInfo;
	vector<Point> corners;

	qrCodeDetector(&decodedInfo, &corners);
}
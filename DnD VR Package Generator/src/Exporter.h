#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <bitset>

#include "QrCode.hpp"
#include "opencv2/opencv.hpp"
#include "tinyxml2.h"
#include "glm/glm.hpp"

using namespace qrcodegen;
using namespace std;
using namespace glm;
using namespace tinyxml2;
using namespace cv;

class Board {
private:
	vec2 size;
	vector<vector<int>> board;
	string name;
	string theme;

public:
	void addWall(vec2 coord, int wall) { board[coord.x][coord.y] += wall; }
	string getName() { return name; }
	void setName(string n) { name.assign(n); }
	string getTheme() { return theme; }
	void setTheme(string n) { theme.assign(n); }
	vec2 getSize() { return size; }
	void setSize(vec2 s) { size = s; }
	vector<vector<int>> getBoard() { return board; }
	void setBoard(vector<vector<int>> b) { board = b; }
};

class Model {
private:
	string modelPath;
	string texturePath;
public:
	string getMPath() { return modelPath; }
	void setMPath(string s) { modelPath.assign(s); }
	string getTPath() { return texturePath; }
	void setTPath(string s) { texturePath.assign(s); }
};

class Actor {
private:
	string name;
	int modelID;

public:
	string getName() { return name; }
	void setName(string s) { name.assign(s); }
	int getID() { return modelID; }
	void setID(int i) { modelID = i; }
};

class Game {
private:
	Board board;
	vector<Model> models;
	vector<Actor> actors;

public:
	void exportBoard(string path);
	void createXML(string path);
	void setActors(vector<Actor> a) { actors = a; }
	void setModels(vector<Model> m) { models = m; }
	void setBoard(Board b) { board = b; }
	void createIMG(string path);
	void createQR(string path);
	void drawQR(string id, string path, QrCode qr);
};

class Exporter {
private:
	vector<Game> games;

public:
	void port(string path);
	Exporter();
};
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include "tinyxml2\tinyxml2.h"
#include "tinyxml2\tinyxml2.cpp"

#include "glm/glm.hpp"

using namespace std;
using namespace glm;
using namespace tinyxml2;


class Board {
private:
	vec2 size;
	vector<vector<int>> board;
	string name;
	string theme;

public:
	void addWall(vec2 coord, int wall) { board[coord.x][coord.y] += wall; }
	void setName(string n) { name.assign(n); }
	string getName() { return name; }
	string getTheme() { return theme; }
	vec2 getSize() { return size; }
	vector<vector<int>> getBoard() { return board; }
};

class Model {
private:
	string modelPath;
	string texturePath;
public:
	string getMPath() { return modelPath; }
	string getTPath() { return texturePath; }
};

class Actor {
private:
	string name;
	int modelID;

public:
	string getName() { return name; }
	int getID() { return modelID; }
};

class Game {
private:
	Board board;
	vector<Model> models;
	vector<Actor> actors;

public:
	void exportBoard(string path);
	void createXML(string path);
};

class Exporter {
private:
	vector<Game> games;

public:
	void port(string path);
};
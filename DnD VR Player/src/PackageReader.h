#pragma once

#include "Model.h"
#include "Tile.h"
#include "Actor.h"
#include "tinyxml2.h"

#include <map>
#include <cstring>
#include <string>

using namespace std;
using namespace tinyxml2;

class PackageReader {
private:
	string project_path;
	pair<int, int> boardsize;
public:
	PackageReader(string packagefile_path);
	vector<Tile*> loadBoardFile(string boardfile_path);
	pair<int,int> loadPackage(map<string,Model*>* models, map<string, Actor*>* actors, vector<Tile*>* tiles);
};
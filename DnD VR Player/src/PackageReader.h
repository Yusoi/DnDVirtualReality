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
	string packagefile_path;
public:
	PackageReader(string packagefile_path);
	vector<Tile*> loadBoardFile(string boardfile_path);
	void loadPackage(map<string,Model*>* models, vector<Actor*>* actors, vector<Tile*>* tiles);
};
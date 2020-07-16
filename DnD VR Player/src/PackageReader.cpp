#include "PackageReader.h"

regex t("[a-zA-Z0-9]*:");

PackageReader::PackageReader(string packagefile_path) {
	this->packagefile_path = packagefile_path;
}



vector<Tile*> PackageReader::loadBoardFile(string boardfile_path) {
	string line;
	ifstream file(boardfile_path);
	const sregex_token_iterator end;
	 
	int i = 0;
	int j = 0;

	vector<Tile*> tiles;

	if (file.is_open()) {
		while(getline(file,line)) {
			for (sregex_token_iterator it(line.begin(), line.end(), t); it != end; it++) {
				string cur = (*it).str();
				cur.pop_back();
				if (!cur.empty()) {
					Tile* curTile = new Tile(pair<int, int>(i, j), stoi(*it));
					tiles.push_back(curTile);
				}
				i++;
			}
			j++;
			i = 0;
		}
	}

	return tiles;
}

//TODO: Read XML
void PackageReader::loadPackage(map<string,Model*>* models, vector<Actor*>* actors, vector<Tile*>* tiles) {
	XMLDocument doc;
	doc.LoadFile(packagefile_path.c_str());

	if (doc.ErrorID()) {
		cout << "Error loading package file!\n" << endl;
	}

	XMLElement* boardElement = doc.FirstChildElement("board");

	//Read Models
	XMLElement* modelElement = boardElement->FirstChildElement("models")->FirstChildElement("model");

	while (modelElement) {
		//Fill Model vector
		const char* model_id = modelElement->Attribute("id");
		const char* model_path = modelElement->Attribute("model");
		const char* texture_path = modelElement->Attribute("texture");

		char* m_id = strdup(model_id);
		char* m_path = strdup(model_path);
		char* tex_path = strdup(texture_path);

		Model* cur_model = new Model(m_id, m_path, tex_path);

		models->insert({ model_id, cur_model });

		modelElement = modelElement->NextSiblingElement();
	}
	
	XMLElement* actorElement = boardElement->FirstChildElement("actors")->FirstChildElement("actor");

	while (actorElement) {
		//Fill Actor vector
		const char* actor_id = actorElement->Attribute("id");
		const char* actor_name = actorElement->Attribute("name");
		const char* actor_model_id = actorElement->Attribute("model_id");

		actorElement = actorElement->NextSiblingElement();

		Actor* cur_actor = new Actor(models->at(actor_model_id), actor_id, actor_name);

		actors->push_back(cur_actor);
	}

	XMLElement* boardFileElement = boardElement->FirstChildElement("boardFile");

	//Fill Tile Vector
	const char* boardFilePath = boardFileElement->Attribute("path");
	*tiles = loadBoardFile(boardFilePath);
}



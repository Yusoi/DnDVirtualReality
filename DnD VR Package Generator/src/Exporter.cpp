#include "Exporter.h"

// For testing purposes
Exporter::Exporter() {

	// Setup board
	Board board;
	board.setSize(vec2(4, 4));
	vector<vector<int>> v(4, vector<int>(4));
	srand(time(NULL));

	for (int i = 0; i < 4; i++) {
		for(int ii = 0; ii < 4; ii++){
			v[i][ii] = rand() % 9;
		}
	}

	board.setBoard(v);
	board.setName("Example Board");
	board.setTheme("Gothic");

	// Setup Models
	Model model;
	model.setMPath("Example MPath");
	model.setTPath("Example TPath");

	//Setup Actors
	Actor actor;
	actor.setID(1);
	actor.setName("Example Name");

	vector<Model> m;
	m.push_back(model);

	vector<Actor> a;
	a.push_back(actor);

	Game game;
	game.setActors(a);
	game.setModels(m);
	game.setBoard(board);

	games.push_back(game);
}

void Game::exportBoard(string path) {
	ofstream board_file;
	board_file.open(path + "/" + board.getName() + ".brd");
	vec2 size = board.getSize();
	vector<vector<int>> b = board.getBoard();


	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			if (b[x][y] == 0)
				board_file << ":";
			else
				board_file << b[x][y] << ":";
		}
		board_file << endl;
	}

	board_file.close();
}

void Game::createXML(string path) {
	XMLDocument doc;
	string name = board.getName();
	string theme = board.getTheme();

	//Board

	XMLElement* xgame = doc.NewElement("board");
	xgame->SetAttribute("name", name.c_str());
	xgame->SetAttribute("theme", theme.c_str());

	//Models

	XMLNode* xmodels = doc.NewElement("models");
	
	int i = 0;
	for (Model model : models) {
		string mpath = model.getMPath();
		string tpath = model.getTPath();

		XMLElement* xmodel = doc.NewElement("model");
		xmodel->SetAttribute("id", to_string(i).c_str());
		xmodel->SetAttribute("model", mpath.c_str());
		xmodel->SetAttribute("texture", tpath.c_str());

		xmodels->InsertEndChild(xmodel);
		i++;
	}

	xgame->InsertEndChild(xmodels);

	//Actors
	XMLNode* xactors = doc.NewElement("actors");

	i = 0;
	for (Actor actor : actors) {
		string name = actor.getName();
		int id = actor.getID();

		XMLElement* xactor = doc.NewElement("model");
		xactor->SetAttribute("id", to_string(i).c_str());
		xactor->SetAttribute("name", name.c_str());
		xactor->SetAttribute("model_id", to_string(id).c_str());

		xactors->InsertEndChild(xactor);
		i++;
	}

	xgame->InsertEndChild(xactors);

	// Board Path
	XMLElement* boardFile = doc.NewElement("boardFile");
	string boardPath = path + "/" + board.getName() + ".brd";
	boardFile->SetAttribute("path", boardPath.c_str());
	xgame->InsertEndChild(boardFile);

	// Save the File
	doc.InsertFirstChild(xgame);
	doc.SaveFile((path + "/" + board.getName() + ".xml").c_str());
}

void Exporter::port(string path) {
	for (Game game : games) {
		game.createXML(path);
		game.exportBoard(path);
	}
}
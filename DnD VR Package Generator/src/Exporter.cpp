#include "Exporter.h"

// For testing purposes
Exporter::Exporter() {

	// Setup board
	Board board;
	board.setSize(vec2(8, 8));
	vector<vector<int>> v(8, vector<int>(8));
	srand(time(NULL));

	for (int i = 0; i < 8; i++) {
		for(int ii = 0; ii < 8; ii++){
			v[i][ii] = 15;
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

void Game::createIMG(string path) {
	vec2 size = board.getSize();
	vector<vector<int>> b = board.getBoard();
	Mat img = Mat::ones((size.y+2) * 57, (size.x+2) * 57, CV_8UC1)*255;
	int val;
	Mat cell;
	Mat destRoi;

	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			val = b[x][y];
			switch (val) {
				case 0:
					cell = imread((path + "/Tiles/0000.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 1:
					cell = imread((path + "/Tiles/0001.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 2:
					cell = imread((path + "/Tiles/0010.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 3:
					cell = imread((path + "/Tiles/0011.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 4:
					cell = imread((path + "/Tiles/0100.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 5:
					cell = imread((path + "/Tiles/0101.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 6:
					cell = imread((path + "/Tiles/0110.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 7:
					cell = imread((path + "/Tiles/0111.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 8:
					cell = imread((path + "/Tiles/1000.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 9:
					cell = imread((path + "/Tiles/1001.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 10:
					cell = imread((path + "/Tiles/1010.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 11:
					cell = imread((path + "/Tiles/1011.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 12:
					cell = imread((path + "/Tiles/1100.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 13:
					cell = imread((path + "/Tiles/1101.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 14:
					cell = imread((path + "/Tiles/1110.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
				case 15:
					cell = imread((path + "/Tiles/1111.png").c_str(), IMREAD_GRAYSCALE);
					destRoi = img(Rect(57 * (x + 1), 57 * (y + 1), cell.cols, cell.rows));
					cell.copyTo(destRoi);
					break;
			}
		}
	}

	Mat ne = imread((path + "/NE.png").c_str(), IMREAD_GRAYSCALE);
	Mat sw = imread((path + "/SW.png").c_str(), IMREAD_GRAYSCALE);
	
	destRoi = img(Rect((size.x+1)*57, 0, ne.cols, ne.rows));
	ne.copyTo(destRoi);

	destRoi = img(Rect(0, (size.y+1)*57, sw.cols, sw.rows));
	sw.copyTo(destRoi);

	imwrite((path + "/" + board.getName() + ".jpg").c_str(), img);
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

		XMLElement* xactor = doc.NewElement("actor");
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
		game.createIMG(path);
	}
}
#include "Engine.h"

Engine::Engine() {
	camera = new Camera(vec3(0.0f, 1.0f, 2.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	boardsize = { 0,0 };
}


Engine* Engine::getInstance() {
	if (engine == 0) {
		engine = new Engine();
	}
	return engine;
}

void Engine::renderScene(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	camera->lookAt();

	for (vector<Tile*>::iterator it = tiles.begin(); it < tiles.end(); ++it) {
		(*it)->draw();
	}

	//TODO: Draw Actors (Não é suposto serem drawn assim)

	for (map<string, Actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
		(*it).second->getModel()->drawVAO();
	}
	/*
	for (map<string,Actor*>::iterator it = actors.begin(); it != actors.end(); ++it) {
		(*it).second->draw();
	}
	*/

	glutSwapBuffers();
}

void Engine::renderSceneWrapper(void) {
	Engine* e = Engine::getInstance();
	e->renderScene();
}

void Engine::reshapeWindow(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0 * w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Engine::reshapeWindowWrapper(int w, int h) {
	Engine* e = Engine::getInstance();
	e->reshapeWindow(w,h);
}

void Engine::processNormalKeys(unsigned char key, int x, int y) {
	vec3 cameraPos = camera->getCameraPos();
	vec3 cameraTarget = camera->getCameraTarget();

	vec3 toTarget = cameraPos - cameraTarget;
	float distanceToCenterXZ = sqrt(pow(cameraPos.x, 2) + pow(cameraPos.z, 2));
	float distanceToCenter = distance(toTarget, vec3(0.0f, 0.0f, 0.0f));

	vec3 cameraFront = normalize(camera->getCameraTarget() - camera->getCameraPos());
	vec3 cameraRight = normalize(cross(cameraFront,camera->getUpVector()));

	float fraction = 0.5f;

	switch (key) {
	case 'w':
		camera->setCameraPos(vec3(cameraPos.x + cameraFront.x * fraction,
			cameraPos.y + cameraFront.y * fraction,
			cameraPos.z + cameraFront.z * fraction));
		camera->setCameraTarget(vec3(cameraTarget.x + cameraFront.x * fraction,
			cameraTarget.y + cameraFront.y * fraction,
			cameraTarget.z + cameraFront.z * fraction));
		break;
	case 's':
		camera->setCameraPos(vec3(cameraPos.x - cameraFront.x * fraction,
			cameraPos.y - cameraFront.y * fraction,
			cameraPos.z - cameraFront.z * fraction));
		camera->setCameraTarget(vec3(cameraTarget.x - cameraFront.x * fraction,
			cameraTarget.y - cameraFront.y * fraction,
			cameraTarget.z - cameraFront.z * fraction));
		break;
	case 'a':
		camera->setCameraPos(vec3(cameraPos.x - cameraRight.x * fraction,
			cameraPos.y - cameraRight.y * fraction,
			cameraPos.z - cameraRight.z * fraction));
		camera->setCameraTarget(vec3(cameraTarget.x - cameraRight.x * fraction,
			cameraTarget.y - cameraRight.y * fraction,
			cameraTarget.z - cameraRight.z * fraction));
		break;
	case 'd':
		camera->setCameraPos(vec3(cameraPos.x + cameraRight.x * fraction,
			cameraPos.y + cameraRight.y * fraction,
			cameraPos.z + cameraRight.z * fraction));
		camera->setCameraTarget(vec3(cameraTarget.x + cameraRight.x * fraction,
			cameraTarget.y + cameraRight.y * fraction,
			cameraTarget.z + cameraRight.z * fraction));
		break;
	}
}

void Engine::mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {

		}
		else {// state = GLUT_DOWN
			camera->setLastX(x);
			camera->setLastY(y);
		}
	}
}

void Engine::mouseButtonWrapper(int button, int state, int x, int y) {
	Engine* e = Engine::getInstance();
	e->mouseButton(button, state, x, y);
}

void Engine::mouseMove(int x, int y) {

	int lastx = camera->getLastX();
	int lasty = camera->getLastY();

	float yaw = camera->getYaw();
	float pitch = camera->getPitch();

	float xoffset = float(x - lastx);
	float yoffset = float(lasty - y);

	camera->setLastX(x);
	camera->setLastY(y);

	float sensitivity = 1.0f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));

	camera->setYaw(yaw);
	camera->setPitch(pitch);
	camera->setCameraTarget(camera->getCameraPos()+normalize(direction));
}

void Engine::mouseMoveWrapper(int x, int y) {
	Engine* e = Engine::getInstance();
	e->mouseMove(x,y);
}

void Engine::processNormalKeysWrapper(unsigned char key, int x, int y) {
	Engine* e = Engine::getInstance();
	e->processNormalKeys(key,x,y);
}

void Engine::processSpecialKeys(int key, int x, int y) {
	
}

void Engine::processSpecialkeysWrapper(int key, int x, int y) {
	Engine* e = Engine::getInstance();
	e->processSpecialKeys(key, x, y);
}

void Engine::addModel(Model* model) {
	this->models.insert({ model->getName() , model });
}

void Engine::addPresetLight(PresetLight* presetLight) {
	this->presetLights.push_back(presetLight);
}

void Engine::addCustomLight(CustomLight* customLight) {
	this->customLights.push_back(customLight);
}

void Engine::setPackageFile(string packagefile_path) {
	this->packagefile_path = packagefile_path;
}

void Engine::loadModels() {
	Model* floor = new Model("Floor", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/floor.vbo", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/Textures/Floor.jpg");
	Model* north_wall = new Model("North Wall", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/north_wall.vbo", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/Textures/Wall.png");
	Model* south_wall = new Model("South Wall", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/south_wall.vbo", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/Textures/Wall.png");
	Model* east_wall = new Model("East Wall", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/east_wall.vbo", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/Textures/Wall.png");
	Model* west_wall = new Model("West Wall", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/west_wall.vbo", "C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/Textures/Wall.png");

	tile_models.insert({ "Floor",floor });
	tile_models.insert({ "North Wall",north_wall });
	tile_models.insert({ "South Wall",south_wall });
	tile_models.insert({ "East Wall",east_wall });
	tile_models.insert({ "West Wall",west_wall });

	PackageReader* pr = new PackageReader(packagefile_path);
	boardsize = pr->loadPackage(&models, &actors, &tiles);

	//4 bit code in which each bit represents the positions of the walls on the tile
	// 0000 - Tile without walls
	// 0001 - Tile with north wall
	// 0010 - Tile with south wall
	// 0100 - Tile with east wall
	// 1000 - Tile with west wall
	for (vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		(*it)->addModel(floor);
		int code = (*it)->getCode();
		if ((code & 1) == 1) (*it)->addModel(north_wall);
		if ((code & 2) == 2) (*it)->addModel(south_wall);
		if ((code & 4) == 4) (*it)->addModel(east_wall);
		if ((code & 8) == 8) (*it)->addModel(west_wall);
	}
}

static void runQRCodeDetection(map<string,Actor*>* actors, pair<int,int> boardsize) {
	ImageInterpreter ii(boardsize);
	for (;;) {
		this_thread::sleep_for(chrono::seconds(1));
		ii.updateActors(actors);
	}
}

void Engine::run(int argc, char *argv[]) {
	//Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DnD VR");
	//TODO read the generated file and upload it to the scene.

	//GLEW init
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	loadModels();
	
	thread cameraThread = thread(&runQRCodeDetection,&actors, boardsize);

	gluPerspective(90.0f,1,0.0001f,500.0f);

	//OpenGL init
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	//Register callbacks
	glutDisplayFunc(renderSceneWrapper);
	glutIdleFunc(renderSceneWrapper);
	glutReshapeFunc(reshapeWindowWrapper);

	glutKeyboardFunc(processNormalKeysWrapper);
	glutSpecialFunc(processSpecialkeysWrapper);

	glutMouseFunc(mouseButtonWrapper);
	glutMotionFunc(mouseMoveWrapper);
	
	//enter GLUT event processing
	glutMainLoop();

	cout << "Window out!" << endl;
}


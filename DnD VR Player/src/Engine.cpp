#include "Engine.h"

Engine::Engine() {
	camera = new Camera(vec3(0.0f, 1.0f, 2.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}


Engine* Engine::getInstance() {
	if (engine == 0) {
		engine = new Engine();
	}
	return engine;
}

void Engine::renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	camera->lookAt();

	//Plane
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(200.0f, 0.0f, 200.0f);
	glVertex3f(200.0f, 0.0f, -200.0f);
	glVertex3f(-200.0f, 0.0f, -200.0f);
	glVertex3f(-200.0f, 0.0f, 200.0f);
	glEnd();

	glColor3f(0.5f, 0.0f, 0.0f);

	//Draw models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it) {
		(*it)->drawVAO();
	}

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

	float xzangle = camera->getXZAngle();
	float yangle = camera->getYAngle();

	vec3 toTarget = cameraPos - cameraTarget;
	float distanceToCenterXZ = sqrt(pow(cameraPos.x, 2) + pow(cameraPos.z, 2));
	float distanceToCenter = distance(toTarget, vec3(0.0f, 0.0f, 0.0f));

	vec3 cameraFront = normalize(camera->getCameraTarget() - camera->getCameraPos());
	vec3 cameraRight = normalize(cross(camera->getUpVector(), camera->getCameraPos()));

	float fraction = 0.1f;

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
	this->models.push_back(model);
}

void Engine::addPresetLight(PresetLight* presetLight) {
	this->presetLights.push_back(presetLight);
}

void Engine::addCustomLight(CustomLight* customLight) {
	this->customLights.push_back(customLight);
}

void Engine::loadModels() {
	Model* knight = new Model("Knight", "D:/Desktop/1.vbo", "D:/Desktop/Models/Caballero/Texture/Diffuse.png");
	models.push_back(knight);

	//knight->print();
}

void Engine::run(int argc, char *argv[]) {
	//Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
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

	//OpenGL init
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//Register callbacks
	glutDisplayFunc(renderSceneWrapper);
	glutIdleFunc(renderSceneWrapper);
	glutReshapeFunc(reshapeWindowWrapper);

	glutKeyboardFunc(processNormalKeysWrapper);
	glutSpecialFunc(processSpecialkeysWrapper);

	

	//enter GLUT event processing
	glutMainLoop();
}


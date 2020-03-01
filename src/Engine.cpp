#include "Engine.h"

Engine::Engine() {
	camera = new Camera(vec3(0.0f, 50.0f, 200.0f), vec3(0.0f, 50.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	Model* barrel = new Model("Barrel", "../../../../res/demos/metal_barrel.obj");
	models.push_back(barrel);
}


Engine* Engine::getInstance() {
	if (engine == 0) {
		engine = new Engine();
	}
	return engine;
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
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
		(*it)->draw();
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
	float distanceToCenterXZ = sqrt(pow(cameraPos.x, 2)+pow(cameraPos.z, 2));
	float distanceToCenter = distance(toTarget,vec3(0.0f,0.0f,0.0f));

	float fraction = 1.0f;

	switch (key) {
	case 'w':
		yangle += 0.1f;
		camera->setYAngle(yangle);
		camera->setCameraPos(vec3(cameraPos.x,abs(distanceToCenter*sin(yangle)),cameraPos.z));
		break;
	case 's':
		yangle -= 0.1f;
		camera->setYAngle(yangle);
		camera->setCameraPos(vec3(cameraPos.x, abs(distanceToCenter * sin(yangle)), cameraPos.z));
		break;
		break;
	case 'a':
		xzangle -= 0.1f;
		camera->setXZAngle(xzangle);
		camera->setCameraPos(vec3(distanceToCenterXZ*sin(xzangle),cameraPos.y,distanceToCenterXZ*+cos(xzangle)));
		break;
	case 'd':
		xzangle += 0.1f;
		camera->setXZAngle(xzangle);
		camera->setCameraPos(vec3(distanceToCenterXZ*sin(xzangle), cameraPos.y, distanceToCenterXZ*+cos(xzangle)));
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

void Engine::run(int argc, char *argv[]) {
	
	//Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DnD VR");

	//GLEW init
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	//TODO read the generated file and upload it to the scene.

	//Register callbacks
	glutDisplayFunc(renderSceneWrapper);
	glutIdleFunc(renderSceneWrapper);
	glutReshapeFunc(reshapeWindowWrapper);

	glutKeyboardFunc(processNormalKeysWrapper);
	glutSpecialFunc(processSpecialkeysWrapper);

	//OpenGL init
	glEnable(GL_DEPTH_TEST);

	//enter GLUT event processing
	glutMainLoop();
}


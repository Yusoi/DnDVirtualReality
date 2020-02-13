#include "Engine.h"

Engine::Engine() {
	scene = new Scene;
}


Engine* Engine::getInstance() {
	if (engine == 0) {
		engine = new Engine();
	}
	return engine;
}

void Engine::renderScene(void) {
	scene->renderScene();
}

void Engine::renderSceneWrapper(void) {
	Engine* e = Engine::getInstance();
	e->renderScene();
}

void Engine::processNormalKeys(unsigned char key, int x, int y) {

}

void Engine::processSpecialKeys(int key, int x, int y) {

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

	//OpenGL init
	glEnable(GL_DEPTH_TEST);

	//enter GLUT event processing
	glutMainLoop();
}


#include "Engine.h"

Engine::Engine() {

}


Engine* Engine::getInstance() {
	if (engine == 0) {
		engine = new Engine();
	}
	return engine;
}

void Engine::renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3d(-0.5, -0.5, 0.0);
	glVertex3d(0.5, 0.0, 0.0);
	glVertex3d(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

void Engine::renderSceneWrapper(void) {
	Engine* e = Engine::getInstance();
	e->renderScene();
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

	//Register callbacks
	glutDisplayFunc(renderSceneWrapper);
	glutIdleFunc(renderSceneWrapper);

	//OpenGL init
	glEnable(GL_DEPTH_TEST);

	//enter GLUT event processing
	glutMainLoop();
}
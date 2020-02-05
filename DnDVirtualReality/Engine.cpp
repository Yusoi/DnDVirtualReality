#include "Engine.h"

void Engine::renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3d(-0.5, -0.5, 0.0);
	glVertex3d(0.5, 0.0, 0.0);
	glVertex3d(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

void Engine::run() {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DnD VR");

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutMainLoop();
}
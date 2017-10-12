#include <GL/glut.h>
#include <math.h>

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POLYGON);
		glVertex3f(-0.9,-0.9,0.0);
		glVertex3f(0.9,0.0,0.0);
		glVertex3f(0.0,0.9,0.0);
		glVertex3f(-0.9,-0.9,0.0);
	glEnd();
	glutSwapBuffers();
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("teste");
  glutDisplayFunc(renderScene);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}

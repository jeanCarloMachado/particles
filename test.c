#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

double PARTICLE_SIZE = 0.9;

void renderScene(void) {
    FILE *fp;
    fp = fopen("/tmp/foo", "a");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * 3.1415; i += 3.1415 / 4) {
            fprintf(fp, "i=%f\n", i);
            glVertex3f(cos(i) * PARTICLE_SIZE, sin(i) * PARTICLE_SIZE, 0.0);
        }
        fprintf(fp, "END===\n");
    glEnd();

    glutSwapBuffers();
    fclose(fp);
}

void update(void) {
    /* PARTICLE_SIZE-= PARTICLE_SIZE*0.01; */
    /* glutPostRedisplay (); */
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("Particles");
  glutDisplayFunc(renderScene);
  glutIdleFunc(update);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}

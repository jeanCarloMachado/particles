#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define DEBUG 0

FILE *fp;

struct particle {
    double x;
    double y;
    double radius;
};

typedef struct particle Particle ;

Particle currentParticle;

void drawParticle(Particle particle)
{
    glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * 3.1415; i += 3.1415 / 18) {
            if (DEBUG) {
                fprintf(fp, "i=%f\n", i);
            }
            glVertex3f(particle.x +  (cos(i) * particle.radius), particle.y + (sin(i) * particle.radius), 0.0);
        }
        if (DEBUG) {
            fprintf(fp, "END===\n");
        }
}

void renderScene(void) {
    if (DEBUG)  {
        fp = fopen("/tmp/debug", "a");
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawParticle(currentParticle);
    glEnd();

    glutSwapBuffers();
    if (DEBUG ) {
        fclose(fp);
    }
}

void update(void) {
    /* currentParticle.radius+= currentParticle.radius*0.1; */
    currentParticle.x+=0.01;
    glutPostRedisplay();
}

int
main(int argc, char **argv)
{
  currentParticle.x = 0.7;
  currentParticle.y = 0.2;
  currentParticle.radius = 0.01;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutCreateWindow("Particles");
  glutDisplayFunc(renderScene);
  glutIdleFunc(update);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "random.c"

#define PARTICLES_COUNT 150
#define GRAVITY_EFFECT  0.0001

FILE *fp;

struct particle {
    double velocityX;
    double velocityY;
    double positionX;
    double positionY;
    double mass;
};

typedef struct particle Particle ;

Particle currentParticleCollection[100];

double calc_distance(Particle p1, Particle p2)
{
    double X = p1.positionX - p2.positionX;
    double Y = p1.positionY - p2.positionY;

    return sqrt(X*X + Y*Y);
}

void drawParticle(Particle particle)
{
    glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * 3.1415; i += 3.1415 / 18) {
            glVertex3f(particle.positionX +  (cos(i) * particle.mass), particle.positionY + (sin(i) * particle.mass), 0.0);
        }
    glEnd();
}

void renderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      for (int i = 0; i < PARTICLES_COUNT;  i++) {
          drawParticle(currentParticleCollection[i]);
      }


    glutSwapBuffers();
}

void update(void) {

  for (int i = 1; i < PARTICLES_COUNT;  i++) {
      for (int j = 0; j < PARTICLES_COUNT;  j++) {
        double distance =  calc_distance(currentParticleCollection[i], currentParticleCollection[j]);
        double gravityFactor = currentParticleCollection[j].mass * (1 / (distance*distance));
        if (isnan(gravityFactor) || isinf(gravityFactor) || gravityFactor > 1.0) {
            gravityFactor = 0.0;
        }

        if (currentParticleCollection[i].positionY > currentParticleCollection[j].positionY) {
            currentParticleCollection[i].velocityY-= GRAVITY_EFFECT * gravityFactor;
        } else {
            currentParticleCollection[i].velocityY+= GRAVITY_EFFECT * gravityFactor;
        }

        if (currentParticleCollection[i].positionX > currentParticleCollection[j].positionX) {
            currentParticleCollection[i].velocityX-= GRAVITY_EFFECT * gravityFactor;
        } else {
            currentParticleCollection[i].velocityX+= GRAVITY_EFFECT * gravityFactor;
        }

      }
  }

  //update positions
  for (int i = 1; i < PARTICLES_COUNT;  i++) {
    currentParticleCollection[i].positionY = currentParticleCollection[i].positionY + currentParticleCollection[i].velocityY;
    currentParticleCollection[i].positionX = currentParticleCollection[i].positionX + currentParticleCollection[i].velocityX;
  }
    glutPostRedisplay();
}


int
main(int argc, char **argv)
{
  MT_seed();
  for (int i = 0; i < PARTICLES_COUNT;  i++) {
      currentParticleCollection[i].positionX = my_rand(-0.5, 0.5);
      currentParticleCollection[i].positionY = my_rand(-0.5, 0.5);
      currentParticleCollection[i].velocityX = my_rand(-0.005, 0.005);
      currentParticleCollection[i].velocityY = my_rand(-0.005, 0.005);
      currentParticleCollection[i].mass = my_rand(0.00, 0.005);
  }
      currentParticleCollection[0].positionX = 0.0;
      currentParticleCollection[0].positionY = 0.0;
      currentParticleCollection[0].velocityX = 0.0;
      currentParticleCollection[0].velocityY = 0.0;
      currentParticleCollection[0].mass = 0.04;


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1440,900);
  glutCreateWindow("Particles");
  glutDisplayFunc(renderScene);
  glutIdleFunc(update);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


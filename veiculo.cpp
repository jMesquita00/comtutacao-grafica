#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLdouble pos_carro = 0;
GLdouble rot_rodas = 0;
int cam_view = 0;

void render_floor()
{
  glBegin(GL_LINES);
  for (GLfloat i = -100; i <= 100; i += 10)
  {
    glVertex3f(i, -5, 100);
    glVertex3f(i, -5, -100);
    glVertex3f(100, -5, i);
    glVertex3f(-100, -5, i);
  }
  glEnd();
}

void display(void)
{
  glColor3f(1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0.0f, 0.7f, 0.0f);
  render_floor();

  glPushMatrix();

  glPushMatrix();
  glColor3f(1.0f, 0.0f, 0.0f); // colorindo a base do carro
  glScalef(40, 1, 20);         // aplicando uma escala no cubo para aumentar seu tamando nos eixos
  glutSolidCube(1);            // criando o cubo
  glPopMatrix();

  glColor3f(0.3f, 0.3f, 0.3f); // colorindo as rodas

  glTranslatef(20.0f, 0.0f, 10.0f); // realizando a translação para posicionar a roda na frente do veiculo
  glutSolidTorus(1.0, 3, 15, 30);   //  criando a roda do veiculo
  glTranslatef(0.0f, 0.0f, -20.0f); // realizando a translação para posicionar a outra roda na frente do veiculo
  glutSolidTorus(1.0, 3, 15, 30);   // criando a  segunda roda do veiculo
  glTranslatef(-40.0f, 0.0f, 0.0f);
  glutSolidTorus(1.0, 3, 15, 30); // criando a  segunda roda do veiculo
  glTranslatef(0.0f, 0.0f, 20.0f);
  glutSolidTorus(1.0, 3, 15, 30); // criando a  segunda roda do veiculo

  glPopMatrix();

  glutSwapBuffers();
}

void change_cam_view()
{
  switch (cam_view)
  {
  case 0:
    gluLookAt(100, 0, 0, 0, 0, 0, 0, 1, 0);
    break;
  case 1:
    gluLookAt(0, 250, 0, 0, 0, 0, 1, 0, 0);
    break;
  case 2:
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
    break;
  }
}

void configView()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glViewport(0, 0, 800, 600);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45, 800 / 600.0, 0.5, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  change_cam_view();

  glDisable(GL_DEPTH_TEST);
}

void resize(GLsizei w, GLsizei h)
{
  if (h == 0)
    h = 1;
}

void specialkeys(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_UP:
    pos_carro += 2;
    break;
  case GLUT_KEY_DOWN:
    pos_carro -= 2;
    break;
  case GLUT_KEY_LEFT:
    rot_rodas -= 5;
    rot_rodas = (rot_rodas < -30) ? -30 : rot_rodas;
    break;
  case GLUT_KEY_RIGHT:
    rot_rodas += 5;
    rot_rodas = (rot_rodas > 30) ? 30 : rot_rodas;
    break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
    break;
  case 32:
    cam_view = (++cam_view % 3);
    pos_carro = 0;
    rot_rodas = 0;
    configView();
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Visualizacao 3D");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialkeys);
  configView();
  glutMainLoop();
  return 0;
}

#include <windows.h>
#include "GL/glut.h"
#include "stdio.h"

 float view_rotx = 20.0f, view_roty = 30.0f;
 int oldMouseX, oldMouseY;

 float R_Z=0.0f, R_X=0.0f, R_Y=0.0f;
 float T_Z=0.0f, T_X=0.0f, T_Y=0.0f;

 void initGL(){
 glShadeModel(GL_FLAT);

 float ambient[] = {1.0f,1.0f,1.0f,1.0f};
 float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
 float specular[] = {0.2f,1.0f,0.2f,1.0f};
 float position[] = {20.0f,30.0f,20.0f,0.0f};

 glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
 glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
 glLightfv(GL_LIGHT0, GL_POSITION, position);
 glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

 float mambient[] ={0.1745f, 0.01175f, 0.01175f, 0.55f};
 float mdiffuse[] ={0.1f, 0.1f, 0.1f, 0.1f };
 float mspecular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
 float mshine =76.8f;

 glMaterialfv(GL_FRONT,GL_AMBIENT,mambient);
 glMaterialfv(GL_FRONT,GL_DIFFUSE,mdiffuse);

 glMaterialfv(GL_FRONT,GL_SPECULAR,mspecular);
 glMaterialf (GL_FRONT,GL_SHININESS,mshine);

 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 }



void konekpiston()
{
        GLUquadric *q = gluNewQuadric();
        glPushMatrix();
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glRotatef(45, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, 0.475f);
        gluCylinder(q, 0.1f, 0.2f, 1.5f, 4.0f, 4.0f);
        glPopMatrix();
}

void konekpiston1()
{
    float BODY_LENGTH=0.3f;
    float BODY_RADIUS=0.2f;
    float BODY_RADIUS2=0.1f;
    float BODY_RADIUS3=0.5f;
    float BODY_RADIUS4=0.1f;
    int SLICES=60;
    int STACKS=60;
        GLUquadric *q = gluNewQuadric();
        glPushMatrix();
        glTranslatef(-0.3f, 0.0f, 0.1f);
        konekpiston();
        glPopMatrix();
        gluDisk(q, 0.4f, BODY_RADIUS, SLICES, STACKS);
        gluCylinder(q, BODY_RADIUS, BODY_RADIUS, 0.2f, SLICES, STACKS);
        gluCylinder(q, BODY_RADIUS2, BODY_RADIUS2, 0.2f, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, 0.6f);
        gluDisk(q, 0.2f, BODY_RADIUS, SLICES, STACKS);

}
void PistonRing()
{
    float BODY_LENGTH=0.2f;
    float BODY_RADIUS=0.1f;
    float BODY_RADIUS2=0.0f;
    float BODY_RADIUS3=0.4f;
    float BODY_RADIUS4=0.0f;
    int SLICES=60;
    int STACKS=60;
        GLUquadric *q = gluNewQuadric();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.3f);
        glPopMatrix();
        glTranslatef(2.3f, 0.0f, -1.0f);
        gluDisk(q, BODY_RADIUS3, BODY_RADIUS4, SLICES, STACKS);
        gluCylinder(q, BODY_RADIUS4, BODY_RADIUS4, 0.2f, SLICES, STACKS);
        gluCylinder(q, BODY_RADIUS3, BODY_RADIUS3, 0.2f, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, 0.2f);
        gluDisk(q, BODY_RADIUS3, BODY_RADIUS4, SLICES, STACKS);

}



void Tabungpiston(){

 float BODY_LENGTH=0.5f;
 float BODY_RADIUS=0.4f;
 int SLICES=20;
 int STACKS=20;
 GLUquadric *q = gluNewQuadric();
 gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
 gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup atas
 glTranslatef(0.0f, 0.0f, BODY_LENGTH);

 }



 void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4,4,4, // eye pos
    0,0,0, // look at
    0,0,1); // up
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(1.0f, 1.0f, 0.1f);
    glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(view_roty, 0.0f, 1.0f, 0.0f);


    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glRotatef(360, 0.0f, -1.0f, 0.0f);
    Tabungpiston();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.0f, 0.0f, 0.2f);
    glRotatef(90, 0.0f, -1.0f, 0.0f);
    konekpiston1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -0.0f);
    glRotatef(90, 0.0f, -1.0f, 0.0f);
    PistonRing();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1f,0.0f, 5.0f);
    glRotatef(180, -0.0f, 1.0f, -0.0f);
    Tabungpiston();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, 4.4f);
    glRotatef(-90, 0.0f, -1.0f, 0.0f);
    konekpiston1();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}


 void timer(int value){
 glutPostRedisplay();
 glutTimerFunc(15, timer, 0);
 }

 void reshape(GLsizei width, GLsizei height){
 if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 glViewport(30, 6, width, height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0f, aspect, 1.0f, 20.0f);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 }

 void mouseControl(int button, int state, int x, int y){
 oldMouseX = x;
 oldMouseY = y;
 }

 void mouseMotion(int x, int y){
 int getX = x;
 int getY = y;
 float thetaY = 360.0f*(getX - oldMouseX)/640;
 float thetaX = 360.0f*(getY - oldMouseY)/480;
 oldMouseX = getX;
 oldMouseY = getY;
 view_rotx += thetaX;
 view_roty += thetaY;
 }

 void keyFunction(unsigned char key, int x, int y){
 switch(key){
 case 74: // Rotasi sumbu Z dengan tombol O
 R_Z = R_Z - 30.0f;
 break;
 case 75: // Rotasi sumbu Y dengan tombol I
 R_Y = R_Y - 30.0f;
 break;
 case 85: // Rotasi sumbu X dengan tombol L
 R_X = R_X - 30.0f;
 break;
 case 65: // Translasi sumbu Z dengan tombol A
 T_Z = T_Z - 1.0f;
 break;
 case 83: // Translasi sumbu Y dengan tombol S
 T_Y = T_Y - 1.0f;
 break;
 case 81: // Translasi sumbu X dengan tombol Q
 T_X = T_X - 1.0f;
 break;
 }
 }

 int main(int argc, char **argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
 glutInitWindowSize(640, 480);
 glutInitWindowPosition(50, 50);
 glutCreateWindow("Piston IVAN");
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyFunction);
 initGL();
 glutMouseFunc(mouseControl);
 glutMotionFunc(mouseMotion);
 glutTimerFunc(1, timer, 0);
 glutMainLoop();
 return 0;
 }

/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#endif

#include <stdlib.h>
#include "windows.h"
#include "GL/glut.h"
#include "stdio.h"
#include "math.h"

    float R_Z=0.0f, R_X=0.0f, R_Y=0.0f;
    float T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;
    float view_rotx = 90.0f, view_roty = 180.0f;
    int oldMouseX, oldMouseY;

    float Cx = 1, Cy = 1.10, Cz = 0.5;
    float Lx = 1, Ly = 1, Lz = 0;
    float Tx = 0, Ty = 1, Tz = 0;

    float sudut_x = 0.0f, sudut_y = 0.0f, sudut_z = 0.0f;
    float sudut_x2 = 0.0f, sudut_y2 = 0.0f, sudut_z2 = 0.0f;

    float angle_depanBelakang = 0.0f;
    float angle_depanBelakang2 = 0.0f;
    float angle_samping = 0.0f;
    float angle_samping2 = 0.0f;
    float angle_vertikal = 0.0f;
    float angle_vertikal2 = 0.0f;

    float linear[] = {0.0f, 0.0f, -1.0f};
    float lateral[] = {-1.0f, 0.0f, 0.0f};
    float vertical[] = {0.0f, 1.0f, 0.0f};

    float toRadians(float angle){
        return angle * M_PI / 180;
    }

    class Vector{
        public: float x, y, z;

        void set_values (float startX, float startY, float startZ){
            x = startX;
            y = startY;
            z = startZ;
        }

        void vectorRotation(Vector refs, float angle){
            Vector temp = refs;
            float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
            temp.x = temp.x / magnitude;
            temp.y = temp.y / magnitude;
            temp.z = temp.z / magnitude;
            float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
            float cross_product_x = (y * temp.z) - (temp.z * z);
            float cross_product_y = -((x * temp.z) - (z * temp.x));
            float cross_product_z = (x * temp.y) - (y * temp.x);
            float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
            x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
            y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
            z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
        }
    };
    Vector depanBelakang, samping, vertikal;

    void initGL()
    {
        glShadeModel(GL_FLAT);

        depanBelakang.set_values(0.0f, 0.0f, -1.0f);
        samping.set_values(1.0f, 0.0f, 0.0f);
        vertikal.set_values(0.0f, 1.0f, 0.0f);

        float ambient[] = {1.0f,1.0f,1.0f,1.0f};
        float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
        float specular[] = {0.2f,1.0f,0.2f,1.0f};
        float position[] = {20.0f,30.0f,20.0f,0.0f};

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

        float mambient[] ={0.294f, 0.294f, 0.294f, 1.0f };
        float mdiffuse[] ={0.46f, 0.46f, 0.46f, 0.55f };
        float mspecular[] ={0.662f, 0.662f, 0.662f, 0.55f };
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

    void ConnectingRod01()
    {
            GLUquadric *q = gluNewQuadric();
            glPushMatrix();
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            glRotatef(45, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, 0.0f, 0.475f);
            gluCylinder(q, 0.2f, 0.4f, 2.25f, 4.0f, 4.0f);
            glPopMatrix();
    }

    void ConnectingRod()
    {
        float BODY_LENGTH=0.6f;
        float BODY_RADIUS=0.5f;
        float BODY_RADIUS2=0.4f;
        float BODY_RADIUS3=0.8f;
        float BODY_RADIUS4=1.0f;
        int SLICES=120;
        int STACKS=120;
            GLUquadric *q = gluNewQuadric();
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.3f);
            ConnectingRod01();
            glPopMatrix();
            gluDisk(q, 0.4f, BODY_RADIUS, SLICES, STACKS);
            gluCylinder(q, BODY_RADIUS, BODY_RADIUS, 0.6f, SLICES, STACKS);
            gluCylinder(q, BODY_RADIUS2, BODY_RADIUS2, 0.6f, SLICES, STACKS);
            glTranslatef(0.0f, 0.0f, 0.6f);
            gluDisk(q, 0.4f, BODY_RADIUS, SLICES, STACKS);

    }

    void Ring()
    {
        float BODY_LENGTH=0.6f;
        float BODY_RADIUS=0.5f;
        float BODY_RADIUS2=0.4f;
        float BODY_RADIUS3=0.8f;
        float BODY_RADIUS4=1.0f;
        int SLICES=120;
        int STACKS=120;
            GLUquadric *q = gluNewQuadric();
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.3f);
            glPopMatrix();
            glTranslatef(3.6f, 0.0f, -0.6f);
            gluDisk(q, BODY_RADIUS3, BODY_RADIUS4, SLICES, STACKS);
            gluCylinder(q, BODY_RADIUS4, BODY_RADIUS4, 0.6f, SLICES, STACKS);
            gluCylinder(q, BODY_RADIUS3, BODY_RADIUS3, 0.6f, SLICES, STACKS);
            glTranslatef(0.0f, 0.0f, 0.6f);
            gluDisk(q, BODY_RADIUS3, BODY_RADIUS4, SLICES, STACKS);

    }

    void Piston01()
        {
        float amb[] = {0.34f, 0.34f, 0.34f, 1.0f};
        float diff[] = {0.41f, 0.41f, 0.41f, 1.0f};
        float spec[] = {0.11f, 0.11f, 0.11f, 1.0f};
        float shine = 200.0f;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        float BODY_LENGTH = 0.25f;
        float BODY_RADIUS = 1.5f;
        int SLICES = 360;
        int STACKS = 360;
        GLUquadric *q= gluNewQuadric();
        gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        glTranslatef(0.0f, 0.0f, BODY_LENGTH);
        gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
        }

    void Piston02()
        {
        float BODY_LENGTH=1.0f;
        float BODY_RADIUS=1.5f;
        double clip_plane[]= {0.0,0.0,1.0,0.0};
        int SLICES=180;
        int STACKS=180;
            GLUquadric *q = gluNewQuadric();
            gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
            glClipPlane(GL_CLIP_PLANE0,clip_plane);
            glEnable(GL_CLIP_PLANE0);
            gluDeleteQuadric(q);
            glDisable(GL_CLIP_PLANE0);
        }

    void vectorMovement(float toMove[], float magnitude, float direction){
        float speedX = toMove[0]*magnitude*direction;
        float speedY = toMove[1]*magnitude*direction;
        float speedZ = toMove[2]*magnitude*direction;
        Cx += speedX;
        Cy += speedY;
        Cz += speedZ;
        Lx += speedX;
        Ly += speedY;
        Lz += speedZ;
    }

    void cameraRotation(Vector refer, double angle){
        float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
        float Up_x1 = refer.x / M;
        float Up_y1 = refer.y / M;
        float Up_z1 = refer.z / M;
        float VLx = Lx - Cx;
        float VLy = Ly - Cy;
        float VLz = Lz - Cz;
        float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
        float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
        float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
        float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
        float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
        float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLx);
        float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLy);
        float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians(angle))) + (dot_product * last_factor_rodrigues * VLz);

        Lx = Lx1+Cx;
        Ly = Ly1+Cy;
        Lz = Lz1+Cz;
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glLoadIdentity();

            gluLookAt(Cx, Cy, Cz,
                    Lx, Ly, Lz,
                    Tx, Ty, Tz);

        glTranslatef(-T_X, T_Y, T_Z);
        glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
        glRotatef(view_roty, 0.0f, 0.0f, 1.0f);

        glRotatef(R_X, 1.0f, 0.0f, 0.0f);
        glRotatef(R_Y, 0.0f, 1.0f, 0.0f);
        glRotatef(R_Z, 0.0f, 0.0f, 1.0f);

        glPushMatrix();
        glTranslatef(5.5f, 0.0f, 1.25f);
        glRotatef(-90, 0.0f, -1.0f, 0.0f);
        Piston01();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(5.0f, 0.0f, 1.25f);
        glRotatef(90, 0.0f, -1.0f, 0.0f);
        Piston02();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4.0f, 0.0f, 1.6f);
        glRotatef(180, 0.0f, -1.0f, 0.0f);
        ConnectingRod();
        glPopMatrix();



        glPushMatrix();
        glTranslatef(-3.6f, 0.0f, 1.6f);
        glRotatef(0, 0.0f, 0.0f, 0.0f);
        Ring();
        glPopMatrix();



        glPushMatrix();
        glTranslatef(-5.5f, 0.0f, 1.25f);
        glRotatef(90, 0.0f, -1.0f, 0.0f);
        Piston01();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-4.0f, 0.0f, 1.25f);
        glRotatef(90, 0.0f, -1.0f, 0.0f);
        Piston02();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-4.0f, 0.0f, 1.0f);
        glRotatef(0, 0.0f, -1.0f, 0.0f);
        ConnectingRod();
        glPopMatrix();

        glFlush();
        glutSwapBuffers();
    }

    void timer(int value)
    {
        glutPostRedisplay();
        glutTimerFunc(15, timer, 0);
    }

    void reshape(GLsizei width, GLsizei height)
    {
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
        float thetaY = 360.0f*(getX - oldMouseX)/1280;
        float thetaX = 360.0f*(getY - oldMouseY)/720;
        oldMouseX = getX;
        oldMouseY = getY;
        view_rotx += thetaX;
        view_roty += thetaY;
    }

        void keyFunction(unsigned char key, int x, int y){
        switch(key){
            case 79: // Rotasi sumbu Z+ dengan tombol O
                    R_Z = R_Z + 15.0f;
                break;
            case 85: // Rotasi sumbu Z- dengan tombol U
                    R_Z = R_Z - 15.0f;
                break;
            case 73: // Rotasi sumbu Y+ dengan tombol I
                    R_Y = R_Y + 15.0f;
                break;
            case 75: // Rotasi sumbu Y- dengan tombol K
                    R_Y = R_Y - 15.0f;
                break;
            case 76: // Rotasi sumbu X+ dengan tombol L
                    R_X = R_X + 15.0f;
                break;
            case 74: // Rotasi sumbu X- dengan tombol J
                    R_X = R_X - 15.0f;
                break;


            case 81: // Translasi sumbu Z+ dengan tombol Q
                    T_Z = T_Z + 0.5f;
                break;
            case 69: // Translasi sumbu Z- dengan tombol E
                    T_Z = T_Z - 0.5f;
                break;
            case 87: // Translasi sumbu Y+ dengan tombol W
                    T_Y = T_Y + 0.5f;
                break;
            case 83: // Translasi sumbu Y- dengan tombol S
                    T_Y = T_Y - 0.5f;
                break;
            case 68: // Translasi sumbu X- dengan tombol D
                    T_X = T_X - 0.5f;
                break;
            case 65: // Translasi sumbu X+ dengan tombol A
                    T_X = T_X + 0.5f;
                break;

            case 32: // space (reset)
                    R_Z=0.0f, R_X=0.0f, R_Y=0.0f;
                    T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;

                    view_rotx = 90.0f, view_roty = 180.0f;

                    Cx = 1, Cy = 1.10, Cz = 0.5;
                    Lx = 1, Ly = 1, Lz = 0;
                    Tx = 0, Ty = 1, Tz = 0;

                    angle_depanBelakang = 0.0f;
                    angle_depanBelakang2 = 0.0f;
                    angle_samping = 0.0f;
                    angle_samping2 = 0.0f;
                    angle_vertikal = 0.0f;
                    angle_vertikal2 = 0.0f;

                    depanBelakang.set_values(0.0f, 0.0f, -1.0f);
                    samping.set_values(1.0f, 0.0f, 0.0f);
                    vertikal.set_values(0.0f, 1.0f, 0.0f);
                break;
            }
        }

      void keyControl(int k, int x, int y) {
            switch(k) {
            case GLUT_KEY_RIGHT: // Arah Kanan
                    angle_vertikal += 1.5f;
                    samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
                    //memutar vector sumbu z terhadap x (target, patokan)
                    depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
                    cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
                    angle_vertikal2 = angle_vertikal;
                break;
            case GLUT_KEY_LEFT: // Arah Kiri
                    angle_vertikal -= 1.5f;
                    samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
                    depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
                    cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
                    angle_vertikal2 = angle_vertikal;
                break;
            case GLUT_KEY_DOWN: // Arah Bawah
                    angle_samping += 1.5f;
                    depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
                    cameraRotation(samping, angle_samping - angle_samping2);
                    angle_samping2 = angle_samping;
                break;
            case GLUT_KEY_UP: // Arah Atas
                    angle_samping -= 1.5f;
                    depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
                    cameraRotation(samping, angle_samping - angle_samping2);
                    angle_samping2 = angle_samping;
                break;
            case GLUT_KEY_PAGE_UP: // Page UP
                    angle_depanBelakang += 1.5f;
                    vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
                    cameraRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
                    angle_depanBelakang2 = angle_depanBelakang;
                break;
            case GLUT_KEY_PAGE_DOWN: // Page DOWN
                    angle_depanBelakang -= 1.5f;
                    vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
                    cameraRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
                    angle_depanBelakang2 = angle_depanBelakang;
                break;
          }
      }


    int main(int argc, char **argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(1280, 720);
        glutInitWindowPosition(50, 50);
        glutCreateWindow("PLANE PISTON");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutSpecialFunc(keyControl);
        glutKeyboardFunc(keyFunction);
        initGL();
        glutMouseFunc(mouseControl);
        glutMotionFunc(mouseMotion);
        glutTimerFunc(0, timer, 0);
        glutMainLoop();
        return 0;
    }

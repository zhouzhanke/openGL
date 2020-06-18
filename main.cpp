#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>

GLfloat light_color[] = {0, 0, 0, 1.0};
int r_spin = 0;
int m_spin = 0;
int n_light = 0;
int y_light = 0;
double t_trans = 0;
double u_trans = 0;
double w_scale = 1;
int w_spin = 0;
double e_scale = 1;
int e_spin = 0;
double h_trans = 0;
int h_spin = 0;
int c_pressed = 0;

void init(void) {

    GLfloat amb[] = {0.2, 0.3, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    //material colours
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    //    mat_specular[2] = 1;
    GLfloat mat_shininess[] = {50.0};

    //light position
    GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};

    //light colors
    GLfloat amb0[] = {0.3, 0.3, 0.1, 1};
    GLfloat spec0[] = {0.1, 0.1, 0.1, 1};


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    // 1st light change
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
    glEnable(GL_LIGHT0);

    // 2nd ambient light
    //light position
    GLfloat light_position1[] = {-1.0, 1.0, -1.0, 1.0};

    //light colors
    GLfloat amb1[] = {1, 1, 0, 1};

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    if (n_light == 1) {
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHT1);
    }

    // 3rd diffuse light
    //light position
    GLfloat light_position2[] = {1.0, 1.0, 1.0, 1.0};

    //light colors
    GLfloat diffuse2[] = {1, 1, 1, 1};
    //        GLfloat spec1[] = {0.1,0.1,0.1,1};

    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    //        glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

    if (y_light == 1) {
        glEnable(GL_LIGHT2);
    } else {
        glDisable(GL_LIGHT2);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // r
    glRotated(r_spin, 0, 1, 0);

    // m
    glRotated(m_spin, 0.5, 0.2, 0.7);

    // t
    float t_move = sqrt(pow(t_trans, 2) / 2);
    glTranslated(t_move, t_move, 0);
    // u
    float u_move = sqrt(pow(u_trans, 2) / 2);
    glTranslated(-u_move, -u_move, 0);

    // w
    glScaled(w_scale, w_scale, w_scale);
    glRotated(w_spin, 0.8, 0.7, 0.1);

    // e
    glScaled(e_scale, e_scale, e_scale);
    glRotated(e_spin, 0.8, 0.7, 0.1);

    // h
    glTranslated(0, h_trans, 0);
    glRotated(h_spin, 0, 1, 1);

    // c
    if (c_pressed) {
        glViewport(0, 0, 100, 100);
    } else {
        glViewport(0, 0, 500, 500);
    }

    glutSolidSphere(1.0, 20, 16);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w,
                1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat) w / (GLfloat) h,
                1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// mouse
void myMouse(int button, int state, int x, int y) {
    // left button, change shading to smooth
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glShadeModel(GL_SMOOTH);
    }

    // right button, change shading to flat
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        glShadeModel(GL_FLAT);
    }

    glutPostRedisplay();
}

// keyboard
void myKeyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'b':
            // blue color
            light_color[0] = 0;
            light_color[1] = 0;
            light_color[2] = 0;

            light_color[2] = 1;
            break;

        case 'g':
            // green color
            light_color[0] = 0;
            light_color[1] = 0;
            light_color[2] = 0;

            light_color[1] = 1;
            break;

        case 'r':
            // spin 30 degree about y axis
            r_spin += 30;
            break;

        case 'm':
            // spin 50 degree about 0.5, 0.2, 0.7
            m_spin += 50;
            break;

        case 'n':
            if (n_light == 0) {
                n_light = 1;
            } else {
                n_light = 0;
            }
            break;

        case 'y':
            if (y_light == 0) {
                y_light = 1;
            } else {
                y_light = 0;
            }
            break;

        case 't':
            t_trans += 0.25;
            break;

        case 'u':
            u_trans += 0.25;
            break;

        case 'w':
            w_scale *= 0.75;
            w_spin += 90;
            break;

        case 'e':
            e_scale *= 1.333;
            e_spin += 270;
            break;

        case 'h':
            h_trans += 0.15;
            h_spin += 60;
            break;

        case 'c':
            if (c_pressed == 0) {
                c_pressed = 1;
            } else {
                c_pressed = 0;
            }
            break;
    }

    // re-draw
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
}

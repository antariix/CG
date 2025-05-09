#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>
using namespace std;

int edge;
vector<int> xpoint;
vector<int> ypoint;
int ch;

double round(double d) {
    return floor(d + 0.5);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void translation() {
    int tx, ty;
    cout << "\t Enter Tx, Ty \n";
    cin >> tx >> ty;
    for (int i = 0; i < edge; i++) {
        xpoint[i] += tx;
        ypoint[i] += ty;
    }
    glBegin(GL_POLYGON); glColor3f(0, 0, 1);
    for (int i = 0; i < edge; i++)
        glVertex2i(xpoint[i], ypoint[i]);
    glEnd(); glFlush();
}

void rotaion() {
    int cx, cy;
    cout << "\n Enter arbitrary point x , y ";
    cin >> cx >> cy;
    cx += 320; cy += 240;

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS); glVertex2i(cx, cy); glEnd(); glFlush();

    double the;
    cout << "\n Enter theta (degrees): ";
    cin >> the;
    the = the * 3.14 / 180;

    glColor3f(0, 0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(
            round(((xpoint[i] - cx) * cos(the) - ((ypoint[i] - cy) * sin(the))) + cx),
            round(((xpoint[i] - cx) * sin(the) + ((ypoint[i] - cy) * cos(the))) + cy)
        );
    }
    glEnd(); glFlush();
}

void scale() {
    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++)
        glVertex2i(xpoint[i] - 320, ypoint[i] - 240);
    glEnd(); glFlush();

    cout << "\n\tIn Scaling, whole screen is 1st Quadrant \n";
    int sx, sy;
    cout << "\t Enter sx, sy \n";
    cin >> sx >> sy;

    for (int i = 0; i < edge; i++) {
        xpoint[i] = (xpoint[i] - 320) * sx;
        ypoint[i] = (ypoint[i] - 240) * sy;
    }

    glColor3f(0, 0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++)
        glVertex2i(xpoint[i], ypoint[i]);
    glEnd(); glFlush();
}

void reflection() {
    char reflection;
    cout << "Enter Reflection Axis (x or y): ";
    cin >> reflection;

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    if (reflection == 'x' || reflection == 'X') {
        for (int i = 0; i < edge; i++)
            glVertex2i(xpoint[i], (ypoint[i] * -1) + 480);
    } else if (reflection == 'y' || reflection == 'Y') {
        for (int i = 0; i < edge; i++)
            glVertex2i((xpoint[i] * -1) + 640, ypoint[i]);
    }
    glEnd(); glFlush();
}

void Draw() {
    if (ch == 2 || ch == 3 || ch == 4) {
        glColor3f(1.0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(0, 240); glVertex2i(640, 240);
        glVertex2i(320, 0); glVertex2i(320, 480);
        glEnd(); glFlush();

        glColor3f(1.0, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < edge; i++)
            glVertex2i(xpoint[i], ypoint[i]);
        glEnd(); glFlush();
    }

    if (ch == 1) scale();
    else if (ch == 2) rotaion();
    else if (ch == 3) reflection();
    else if (ch == 4) translation();
}

int main(int argc, char **argv) {
    cout << "\n \t Enter 1) Scaling ";
    cout << "\n \t Enter 2) Rotation about arbitrary point";
    cout << "\n \t Enter 3) Reflection";
    cout << "\n \t Enter 4) Translation \n \t";
    cin >> ch;

    if (ch >= 1 && ch <= 4) {
        cout << "Enter No of edges: ";
        cin >> edge;

        int xpointnew, ypointnew;
        cout << "Enter " << edge << " points of polygon:\n";
        for (int i = 0; i < edge; i++) {
            cout << "Enter Point " << i << ": ";
            cin >> xpointnew >> ypointnew;
            xpoint.push_back(xpointnew + 320);
            ypoint.push_back(ypointnew + 240);
        }

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(640, 480);
        glutInitWindowPosition(200, 200);
        glutCreateWindow("2D Transformations");
        init();
        glutDisplayFunc(Draw);
        glutMainLoop();
    } else {
        cout << "\n \t Invalid Input. Please run again.";
    }
    return 0;
}


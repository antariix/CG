
#include <GL/glut.h>
#include <math.h>

// Function to draw the Koch Curve
void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    // Points dividing the line into 3 segments
    float xA = x1 + dx;
    float yA = y1 + dy;
    float xB = x1 + 2 * dx;
    float yB = y1 + 2 * dy;

    // Coordinates of the peak of the equilateral triangle
    float px = xA + (dx * cos(M_PI / 3)) - (dy * sin(M_PI / 3));
    float py = yA + (dx * sin(M_PI / 3)) + (dy * cos(M_PI / 3));

    // Recursive calls for each new segment
    drawKoch(x1, y1, xA, yA, depth - 1);
    drawKoch(xA, yA, px, py, depth - 1);
    drawKoch(px, py, xB, yB, depth - 1);
    drawKoch(xB, yB, x2, y2, depth - 1);
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.7, 1.0); // Set line color
    glBegin(GL_LINES);
    drawKoch(-0.8f, 0.0f, 0.8f, 0.0f, 4); // Koch curve from left to right
    glEnd();
    glFlush();
}

// OpenGL initialization
void init() {
    glClearColor(0, 0, 0, 1);         // Background color: black
    glColor3f(1, 1, 1);               // Default drawing color: white
    gluOrtho2D(-1, 1, -1, 1);         // 2D coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve - Depth 4");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

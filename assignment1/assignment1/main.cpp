/***
 assignment1.cpp
 Assignment-1: Cartoonify
 Name: Dibbern, Natalia
 Collaborators: -
 ** Note: although the assignment should be completed individually
 you may speak with classmates on high level algorithmic concepts. Please
 list their names in this section
 Project Summary: A short paragraph (3-4 sentences) describing the work you
 did for the project: e.g. did you use the iterative or recursive approach?
 ***/
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
using namespace std;
class Vertex {
    GLfloat x, y;
public:
    Vertex(GLfloat, GLfloat);
    GLfloat get_y() { return y; };
    GLfloat get_x() { return x; };
};
Vertex::Vertex(GLfloat X, GLfloat Y) {
    x = X;
    y = Y; }
void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
vector<Vertex> generate_points(vector<Vertex> control_points) {
    vector<Vertex> points;
    // Iterate through our initial control points by pairs
    for (int p = 0; p < control_points.size()-1; p++) {
        Vertex v_0 = control_points[p];
        Vertex v_1 = control_points[p+1];
        // First point at the 1/4 position along the line from v_0 and v_1
        GLfloat y1 = (3.0/4.0)*v_0.get_y()+(1.0/4.0)*v_1.get_y();
        GLfloat x1 = (3.0/4.0)*v_0.get_x()+(1.0/4.0)*v_1.get_x();
        // Second point at the 3/4 position along the line from v_0 and v_1
        GLfloat y2 = (1.0/4.0)*v_0.get_y()+(3.0/4.0)*v_1.get_y();
        GLfloat x2 = (1.0/4.0)*v_0.get_x()+(3.0/4.0)*v_1.get_x();
        // push_back simply adds a new element to the back of your vector (list)
        points.push_back(Vertex(x1, y1));
        points.push_back(Vertex(x2, y2));
    }
    return points;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {
    // Draw a Bezier curve based on the given control points
    
    vector<Vertex> previous = generate_points(control_points);
    for (int i = 0; i <= n_iter; i++) {
        vector<Vertex> new_points = generate_points(previous);
        previous = new_points;
    }
    vector<Vertex> final_points = previous;
    glBegin(GL_POINTS);
    for (int i = 0; i <= final_points.size(); i++) {
        glVertex2f(final_points[i].get_x(), final_points[i].get_y());
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set our color to black (R, G, B)
    glColor3f(0.0f, 0.0f, 0.0f);
    //Right eye
    vector<Vertex> eye_r;
    eye_r.push_back(Vertex(0.00f, 0.25f));
    eye_r.push_back(Vertex(0.5f, 0.75f));
    eye_r.push_back(Vertex(1.00f, 0.25f));
    draw_curve(eye_r, 10);
    // Left eye
    vector<Vertex> eye_l;
    eye_l.push_back(Vertex(-0.00f, 0.25f));
    eye_l.push_back(Vertex(-0.5f, 0.75f));
    eye_l.push_back(Vertex(-1.00f, 0.25f));
    draw_curve(eye_l, 10);
    // M
    
    glutSwapBuffers();
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800,600); // Set your own window size
    glutCreateWindow("Assignment 1");
    setup();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


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
    points.push_back(control_points[0]);
        for (int m = 0; m < control_points.size() - 1; m++) {
            //step through points
            //take mid points
            Vertex v_0 = control_points[m];
            Vertex v_1 = control_points[m+1];
            // First point at the 1/2 position along the line from v_0 and v_1
            GLfloat y = (0.5)*v_0.get_y()+(0.5)*v_1.get_y();
            GLfloat x = (0.5)*v_0.get_x()+(0.5)*v_1.get_x();
            points.push_back(Vertex(x, y));
        }
    points.push_back(control_points[control_points.size()-1]);
    return points;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {
    // Draw a Bezier curve based on the given control points
    
    vector<Vertex> previous = control_points;
    for (int i = 0; i <= n_iter; i++) {
        vector<Vertex> new_points = generate_points(previous);
        previous = new_points;
    }
    vector<Vertex> final_points = previous;
    
    for (long i = final_points.size()-2; i >= 0; i--) {
        glBegin(GL_LINES);
        glVertex2f(final_points[i+1].get_x(), final_points[i+1].get_y());
        glVertex2f(final_points[i].get_x(), final_points[i].get_y());
        glEnd();
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set our color to black (R, G, B)
    glColor3f(0.0f, 0.0f, 0.0f);
    //Right face
    vector<Vertex> face_r;
    face_r.push_back(Vertex(0.4635f, 1.0000f));
    face_r.push_back(Vertex(0.5971f, 0.9332f));
    face_r.push_back(Vertex(0.7026f, 0.7911f));
    face_r.push_back(Vertex(0.7371f, 0.5778f));
    face_r.push_back(Vertex(0.7220f, 0.3430f));
    face_r.push_back(Vertex(0.5906f, 0.2095f));
    face_r.push_back(Vertex(0.4571f, 0.1858f));
    draw_curve(face_r, 20);
    
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










////Right eye
//vector<Vertex> eye_r;
//eye_r.push_back(Vertex(0.00f, 0.25f));
//eye_r.push_back(Vertex(0.5f, 0.75f));
//eye_r.push_back(Vertex(1.00f, 0.25f));
//draw_curve(eye_r, 10);
//// Left eye
//vector<Vertex> eye_l;
//eye_l.push_back(Vertex(-0.00f, 0.25f));
//eye_l.push_back(Vertex(-0.5f, 0.75f));
//eye_l.push_back(Vertex(-1.00f, 0.25f));
//draw_curve(eye_l, 10);
//
//vector<Vertex> stash;
//vector<Vertex> stash1;
//vector<Vertex> stash2;
//stash.push_back(Vertex(0.40f, -0.45f));
//stash.push_back(Vertex(0.30f, -0.20f));
//stash.push_back(Vertex(0.20f, -0.45f));
//stash.push_back(Vertex(0.10f, -0.20f));
//stash.push_back(Vertex(0.00f, -0.45f));
//stash.push_back(Vertex(-0.10f, -0.20f));
//stash.push_back(Vertex(-0.20f, -0.45f));
//stash.push_back(Vertex(-0.30f, -0.20f));
//stash.push_back(Vertex(-0.40f, -0.45f));
//draw_curve(stash, 10);


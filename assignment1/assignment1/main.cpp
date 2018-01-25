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

Vertex bezier_curve(Vertex p0, Vertex p1, Vertex p2, float t ) {
    GLfloat x = (1 - t) * ((1 - t) * p0.get_x() + t * p1.get_x() ) + t* ((1 - t) * p1.get_x() + p2.get_x());
    GLfloat y = (1 - t) * ((1 - t) * p0.get_y() + t * p1.get_y() ) + t* ((1 - t) * p1.get_y() + p2.get_y());
    return Vertex(x,y);
}

vector<Vertex> generate_points(vector<Vertex> control_points) {
    vector<Vertex> points;
    // Iterate through our initial control points
    for (int p = 0; p < control_points.size()-2; p+=2) {
        Vertex p_0 = control_points[p];
        Vertex p_1 = control_points[p+1];
        Vertex p_2 = control_points[p+2];
        
        for (int t = 0; t<=1; t+= 0.5){
            Vertex new_point =  bezier_curve(p_0,p_1,p_2, t);
            // push_back simply adds a new elements to the back of your vector (list)
            points.push_back(new_point);
            
        }
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
    
    for (long i = final_points.size()-2; i >= 0; i--) {
        glBegin(GL_LINES);
        glVertex2f(final_points[i].get_x(), final_points[i].get_y());
        glVertex2f(final_points[i+1].get_x(), final_points[i+1].get_y());
        glEnd();
    }
   
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


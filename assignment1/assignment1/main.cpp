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
#include <cmath>
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
Vertex::Vertex(GLfloat X, GLfloat Y){
    x = X;
    y = Y; }
void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int n_choose_i(int n, int i){
    int result = 1;
    for (int k = 1; k <= i; k++){
        result *= n - (i - k);
        result /= i;
    }
    return result;
}

Vertex bezier_curve(vector<Vertex> control_points, float t) {
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    int n = (int) control_points.size()-1;
    
    for (int i = 0; i < n; i++) {
        x += n_choose_i(n,i) * std::pow(1-t, n-i) *std::pow(t, i)*control_points[i].get_x();
        y += n_choose_i(n,i) * std::pow(1-t, n-i) *std::pow(t, i)*control_points[i].get_y();
    }
    return Vertex(x,y);
}

vector<Vertex> generate_points(vector<Vertex> control_points) {
    vector<Vertex> points;
    for (float t = 0; t<=1; t+= 0.5){
        Vertex new_point =  bezier_curve(control_points, t);
        points.push_back(new_point);
    }
    return points;
}

void draw_curve(vector<Vertex> control_points, int n_iter) {
    // Draw a Bezier curve based on the given control points
    vector<Vertex> final_points = generate_points(control_points);
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

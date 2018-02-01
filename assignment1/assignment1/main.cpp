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
    
    // Right face side
    vector<Vertex> face_right;
    face_right.push_back(Vertex(-0.0064f, -0.4886f));
    face_right.push_back(Vertex(0.0209, -0.4903f));
    face_right.push_back(Vertex(0.0500,  -0.4903f));
    face_right.push_back(Vertex(0.0876f,  -0.4834f));
    face_right.push_back(Vertex(0.1132f, -0.4766f));
    face_right.push_back(Vertex(0.1439f,  -0.4595f));
    face_right.push_back(Vertex(0.1781f, -0.4424f));
    face_right.push_back(Vertex(0.2174f, -0.4151f));
    face_right.push_back(Vertex(0.2396f, -0.45f));
    face_right.push_back(Vertex(0.2738f, -0.3912f));
    face_right.push_back(Vertex(0.2994f, -0.3553f));
    face_right.push_back(Vertex(0.3182f, -0.3246f));
    face_right.push_back(Vertex(0.3387f, -0.2990f));
    face_right.push_back(Vertex(0.3523f, -0.2409f));
    face_right.push_back(Vertex(0.3694f, -0.2084f));
    face_right.push_back(Vertex(0.3746f, -0.1760f));
    face_right.push_back(Vertex(0.3694f, -0.1469f));
    face_right.push_back(Vertex(0.3814f, -0.1179f));
    face_right.push_back(Vertex(0.3865f, -0.0905f));
    face_right.push_back(Vertex(0.3865f, -0.2084f));
    face_right.push_back(Vertex(0.3865f, -0.0717f));
    face_right.push_back(Vertex(0.3797f, -0.0547f));
    draw_curve(face_right, 30);
    
    // face left
    vector<Vertex> face_left;
    face_left.push_back(Vertex(-0.0064f, -0.4886f));
    face_left.push_back(Vertex(-0.0209, -0.4903f));
    face_left.push_back(Vertex(-0.0500,  -0.4903f));
    face_left.push_back(Vertex(-0.0876f,  -0.4834f));
    face_left.push_back(Vertex(-0.1132f, -0.4766f));
    face_left.push_back(Vertex(-0.1439f,  -0.4595f));
    face_left.push_back(Vertex(-0.1781f, -0.4424f));
    face_left.push_back(Vertex(-0.2174f, -0.4151f));
    face_left.push_back(Vertex(-0.2396f, -0.45f));
    face_left.push_back(Vertex(-0.2738f, -0.3912f));
    face_left.push_back(Vertex(-0.2994f, -0.3553f));
    face_left.push_back(Vertex(-0.3182f, -0.3246f));
    face_left.push_back(Vertex(-0.3387f, -0.2990f));
    face_left.push_back(Vertex(-0.3523f, -0.2409f));
    face_left.push_back(Vertex(-0.3694f, -0.2084f));
    face_left.push_back(Vertex(-0.3746f, -0.1760f));
    face_left.push_back(Vertex(-0.3694f, -0.1469f));
    face_left.push_back(Vertex(-0.3814f, -0.1179f));
    face_left.push_back(Vertex(-0.3865f, -0.0905f));
    face_left.push_back(Vertex(-0.3865f, -0.2084f));
    face_left.push_back(Vertex(-0.3865f, -0.0717f));
    face_left.push_back(Vertex(-0.3797f, -0.0547f));
    draw_curve(face_left, 30);
    
    // ear right
    vector<Vertex> ear_right;
    ear_right.push_back(Vertex(0.3797f, -0.0547f));
    ear_right.push_back(Vertex(0.4075f, -0.0600f));
    ear_right.push_back(Vertex(0.4257f, -0.0836f));
    ear_right.push_back(Vertex(0.4529f, -0.0872f));
    ear_right.push_back(Vertex(0.4802f, -0.0636f));
    ear_right.push_back(Vertex(0.5002f, -0.0309f));
    ear_right.push_back(Vertex(0.4929f,  0.0327f));
    ear_right.push_back(Vertex(0.4675f,  0.0781f));
    ear_right.push_back(Vertex(0.4330f,  0.0890f));
    ear_right.push_back(Vertex(0.4093f,  0.0818f));
    ear_right.push_back(Vertex(0.3912f,  0.0654f));
    draw_curve(ear_right, 30);
    
    // ear right interior
    GLfloat delta = 0.04f;
    vector<Vertex> ear_right_interior;
    ear_right_interior.push_back(Vertex(0.4436f - delta, -0.0302f));
    ear_right_interior.push_back(Vertex(0.4549f - delta, -0.0415f));
    ear_right_interior.push_back(Vertex(0.4719f - delta, -0.0396f));
    ear_right_interior.push_back(Vertex(0.4795f - delta, -0.0245f));
    ear_right_interior.push_back(Vertex(0.4813f - delta, -0.0019f));
    ear_right_interior.push_back(Vertex(0.4813f - delta,  0.0207f));
    ear_right_interior.push_back(Vertex(0.4700f - delta,  0.0453f));
    ear_right_interior.push_back(Vertex(0.4493f - delta,  0.0566f));
    ear_right_interior.push_back(Vertex(0.4323f - delta,  0.0453f));
    draw_curve(ear_right_interior, 30);
    
    // ear left
    vector<Vertex> ear_left;
    ear_left.push_back(Vertex(-0.3797f, -0.0547f));
    ear_left.push_back(Vertex(-0.4075f, -0.0600f));
    ear_left.push_back(Vertex(-0.4257f, -0.0836f));
    ear_left.push_back(Vertex(-0.4529f, -0.0872f));
    ear_left.push_back(Vertex(-0.4802f, -0.0636f));
    ear_left.push_back(Vertex(-0.5002f, -0.0309f));
    ear_left.push_back(Vertex(-0.4929f,  0.0327f));
    ear_left.push_back(Vertex(-0.4675f,  0.0781f));
    ear_left.push_back(Vertex(-0.4330f,  0.0890f));
    ear_left.push_back(Vertex(-0.4093f,  0.0818f));
    ear_left.push_back(Vertex(-0.3912f,  0.0654f));
    draw_curve(ear_left, 30);
    
    // ear left interior
    vector<Vertex> ear_left_interior;
    ear_left_interior.push_back(Vertex(-0.4436f + delta, -0.0302f));
    ear_left_interior.push_back(Vertex(-0.4549f + delta, -0.0415f));
    ear_left_interior.push_back(Vertex(-0.4719f + delta, -0.0396f));
    ear_left_interior.push_back(Vertex(-0.4795f + delta, -0.0245f));
    ear_left_interior.push_back(Vertex(-0.4813f + delta, -0.0019f));
    ear_left_interior.push_back(Vertex(-0.4813f + delta,  0.0207f));
    ear_left_interior.push_back(Vertex(-0.4700f + delta,  0.0453f));
    ear_left_interior.push_back(Vertex(-0.4493f + delta,  0.0566f));
    ear_left_interior.push_back(Vertex(-0.4323f + delta,  0.0453f));
    draw_curve(ear_left_interior, 30);
    
    // Right mouth side
    vector<Vertex> mouth_right;
    GLfloat delta_mouth = 0.12f;
    mouth_right.push_back(Vertex(0.0107f, -0.3903f + delta_mouth));
    mouth_right.push_back(Vertex(0.0475,  -0.3903f + delta_mouth));
    mouth_right.push_back(Vertex(0.0884,  -0.3821f + delta_mouth));
    mouth_right.push_back(Vertex(0.1211f, -0.3658f + delta_mouth));
    mouth_right.push_back(Vertex(0.1681f, -0.3515f + delta_mouth));
    mouth_right.push_back(Vertex(0.1946f, -0.3372f + delta_mouth));
    mouth_right.push_back(Vertex(0.2253f, -0.3167f + delta_mouth));
    mouth_right.push_back(Vertex(0.2519f, -0.2902f + delta_mouth));
    mouth_right.push_back(Vertex(0.2743f, -0.2656f + delta_mouth));
    mouth_right.push_back(Vertex(0.2927f, -0.2452f + delta_mouth));
    mouth_right.push_back(Vertex(0.2911f, -0.2146f + delta_mouth));
    mouth_right.push_back(Vertex(0.2975f, -0.1839f + delta_mouth));
    mouth_right.push_back(Vertex(0.2918f, -0.1492f + delta_mouth));
    mouth_right.push_back(Vertex(0.2959f, -0.1206f + delta_mouth));
    mouth_right.push_back(Vertex(0.2920f, -0.0960f + delta_mouth));
    mouth_right.push_back(Vertex(0.2961f, -0.0899f + delta_mouth));
    draw_curve(mouth_right, 30);
    
    // Left mouth side
    vector<Vertex> mouth_left;
    mouth_left.push_back(Vertex(0.0107f, -0.3903f + delta_mouth));
    mouth_left.push_back(Vertex(-0.0475,  -0.3903f + delta_mouth));
    mouth_left.push_back(Vertex(-0.0884,  -0.3821f + delta_mouth));
    mouth_left.push_back(Vertex(-0.1211f, -0.3658f + delta_mouth));
    mouth_left.push_back(Vertex(-0.1681f, -0.3515f + delta_mouth));
    mouth_left.push_back(Vertex(-0.1946f, -0.3372f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2253f, -0.3167f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2519f, -0.2902f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2743f, -0.2656f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2927f, -0.2452f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2911f, -0.2146f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2975f, -0.1839f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2918f, -0.1492f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2959f, -0.1206f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2920f, -0.0960f + delta_mouth));
    mouth_left.push_back(Vertex(-0.2961f, -0.0899f + delta_mouth));
    draw_curve(mouth_left, 30);

    // cheek right
    vector<Vertex> right_cheek;
    GLfloat deltaX_cheek = -0.075f;
    GLfloat deltaY_cheek = 0.144f;

    right_cheek.push_back(Vertex(0.3587f + deltaX_cheek, -0.0641f + deltaY_cheek));
    right_cheek.push_back(Vertex(0.3764f + deltaX_cheek, -0.0818f + deltaY_cheek));
    right_cheek.push_back(Vertex(0.3875f + deltaX_cheek, -0.0995f + deltaY_cheek));
    right_cheek.push_back(Vertex(0.3919f + deltaX_cheek, -0.1172f + deltaY_cheek));
    right_cheek.push_back(Vertex(0.3919f + deltaX_cheek, -0.1393f + deltaY_cheek));
    right_cheek.push_back(Vertex(0.3919f + deltaX_cheek, -0.1570f + deltaY_cheek));
    draw_curve(right_cheek, 30);


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












//
//
////Right eye top
//vector<Vertex> eye_r;
//eye_r.push_back(Vertex(0.05f, 0.00f));
//eye_r.push_back(Vertex(0.2f, 0.85f));
//eye_r.push_back(Vertex(0.4f, 0.00f));
//draw_curve(eye_r, 30);
//
//vector<Vertex> eye_r_bot;
//eye_r_bot.push_back(Vertex(0.05f, -0.00f));
//eye_r_bot.push_back(Vertex(0.2f, -0.85f));
//eye_r_bot.push_back(Vertex(0.4f, -0.00f));
//draw_curve(eye_r_bot, 30);
//
//vector<Vertex> eye_r_interior;
//eye_r_interior.push_back(Vertex(0.2f, 0.12f));
//eye_r_interior.push_back(Vertex(-0.3f, 0.00f));
//eye_r_interior.push_back(Vertex(0.2f, -0.12f));
//draw_curve(eye_r_interior, 30);
//
//vector<Vertex> eye_r_interior_l;
//eye_r_interior_l.push_back(Vertex(0.25f, 0.12f));
//eye_r_interior_l.push_back(Vertex(0.7f, 0.00f));
//eye_r_interior_l.push_back(Vertex(0.25f, -0.12f));
//draw_curve(eye_r_interior_l, 30);
//
//vector<Vertex> eye_l_interior_l;
//eye_l_interior_l.push_back(Vertex(-0.2f, 0.12f));
//eye_l_interior_l.push_back(Vertex(0.3f, 0.00f));
//eye_l_interior_l.push_back(Vertex(-0.2f, -0.12f));
//draw_curve(eye_l_interior_l, 30);
//
//vector<Vertex> eye_l_interior_r;
//eye_l_interior_r.push_back(Vertex(-0.24f, 0.12f));
//eye_l_interior_r.push_back(Vertex(-0.7f, 0.00f));
//eye_l_interior_r.push_back(Vertex(-0.24f, -0.12f));
//draw_curve(eye_l_interior_r, 30);
////    // Left eye
//vector<Vertex> eye_l;
//eye_l.push_back(Vertex(-0.05f, 0.00f));
//eye_l.push_back(Vertex(-0.2f, 0.85f));
//eye_l.push_back(Vertex(-0.40f, 0.00f));
//draw_curve(eye_l, 30);
//
//vector<Vertex> eye_l_bot;
//eye_l_bot.push_back(Vertex(-0.05f, -0.00f));
//eye_l_bot.push_back(Vertex(-0.2f, -0.85f));
//eye_l_bot.push_back(Vertex(-0.4f, -0.00f));
//draw_curve(eye_l_bot, 30);
//
//vector<Vertex> stash;
//vector<Vertex> stash1;
//vector<Vertex> stash2;
//vector<Vertex> stash3;
//stash.push_back(Vertex(0.40f, -0.45f));
//stash.push_back(Vertex(0.30f, -0.80f));
//stash.push_back(Vertex(0.20f, -0.45f));
//stash1.push_back(Vertex(0.20f, -0.45f));
//stash1.push_back(Vertex(0.10f, 0.50f));
//stash1.push_back(Vertex(0.00f, -0.45f));
//stash2.push_back(Vertex(0.00f, -0.45f));
//stash2.push_back(Vertex(-0.10f, -0.80f));
//stash2.push_back(Vertex(-0.20f, -0.45f));
//stash3.push_back(Vertex(-0.20f, -0.45f));
//stash3.push_back(Vertex(-0.30f, 0.50f));
//stash3.push_back(Vertex(-0.40f, -0.45f));
//draw_curve(stash, 20);
//draw_curve(stash1, 20);
//draw_curve(stash2, 20);
//draw_curve(stash3, 20);


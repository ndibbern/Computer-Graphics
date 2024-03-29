/***
 assignment1.cpp
 Assignment-1: Cartoonify
 Name: Dibbern, Natalia
 Collaborators: -
 ** Note: although the assignment should be completed individually
 you may speak with classmates on high level algorithmic concepts. Please
 list their names in this section
 Project Summary:
 In this project I took two approaches: the iterative version and the generalized iterative version of Bezier Algorithm.
 The first algorithm iterates through the control points finiding the midpoints between those points and repeating this process an
 n_iter number of times. The generalized bezier instead makes use of the formal generalized equation from Bezier's algorithm which is
 basically a binomial expansion. I reproduced this code by writing an n choose i function (to generate pascal triangle values) and then
 using this function in my B function, which generates the bezier point for a given t and a set of control points. The generate_points function
 then takes the initial given control points and calles the B function for  t values in the range [0,1] with dt being a parameter given to the function.
 This now will give us a good approximation of the curve. Finally the draw curve function calls the generate_points function giving it the values
 of the control points and the value for dt. The generate_points will now return the list of new values and then we are all good to plot it. The
 way points are ploting is by joining them together with lines. The iterative method works really similar, but it is less precise since
 it just is a special case of the generalized Bezier.
 
To get my initial contorl points I used a code writen by myself in MATLAB that takes a picture and user inputs (in the form of clicks)
of places on the image and returns the coordinates of such chosen points.These points are then normalized such that they are on the range that
I want to ([0,1] in my case with the origin on the center of the image). These points are inputed to the init_sketch() function which
generates a vector of vectors of vertices. This function is finally called through the display function.
On the display function we then iterate through the vectors of vectors and we call draw function in order to plot them!
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
    // push the first point
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
    // push the last point
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
        glLineWidth(4.0f);
        glBegin(GL_LINES);
        glVertex2f(final_points[i+1].get_x(), final_points[i+1].get_y());
        glVertex2f(final_points[i].get_x(), final_points[i].get_y());
        glEnd();
    }
}

vector<vector<Vertex>> init_sketch() {
    vector<vector<Vertex>> sketch_points;
    
    // Right face side
    vector<Vertex> face_right;
    face_right.push_back(Vertex(-0.0064f, -0.4886f));
    face_right.push_back(Vertex(0.0209f, -0.4903f));
    face_right.push_back(Vertex(0.0500f,  -0.4903f));
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
    
    sketch_points.push_back(face_right);
    
    // face left
    vector<Vertex> face_left;
    face_left.push_back(Vertex(-0.0064f, -0.4886f));
    face_left.push_back(Vertex(-0.0209f, -0.4903f));
    face_left.push_back(Vertex(-0.0500f,  -0.4903f));
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
    
    sketch_points.push_back(face_left);
    
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
    
    sketch_points.push_back(ear_right);
    
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
    
    sketch_points.push_back(ear_right_interior);
    
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
    
    sketch_points.push_back(ear_left);
    
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
    
    sketch_points.push_back(ear_left_interior);
    
    // Right mouth side
    vector<Vertex> mouth_right;
    GLfloat delta_mouth = 0.12f;
    mouth_right.push_back(Vertex(0.0107f, -0.3903f + delta_mouth));
    mouth_right.push_back(Vertex(0.0475f,  -0.3903f + delta_mouth));
    mouth_right.push_back(Vertex(0.0884f,  -0.3821f + delta_mouth));
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
    
    sketch_points.push_back(mouth_right);
    
    // Left mouth side
    vector<Vertex> mouth_left;
    mouth_left.push_back(Vertex(0.0107f, -0.3903f + delta_mouth));
    mouth_left.push_back(Vertex(-0.0475f,  -0.3903f + delta_mouth));
    mouth_left.push_back(Vertex(-0.0884f,  -0.3821f + delta_mouth));
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
    
    sketch_points.push_back(mouth_left);
    
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
    
    sketch_points.push_back(right_cheek);
    
    // cheek left
    vector<Vertex> left_cheek;
    left_cheek.push_back(Vertex(-0.3587f - deltaX_cheek, -0.0641f + deltaY_cheek));
    left_cheek.push_back(Vertex(-0.3764f - deltaX_cheek, -0.0818f + deltaY_cheek));
    left_cheek.push_back(Vertex(-0.3875f - deltaX_cheek, -0.0995f + deltaY_cheek));
    left_cheek.push_back(Vertex(-0.3919f - deltaX_cheek, -0.1172f + deltaY_cheek));
    left_cheek.push_back(Vertex(-0.3919f - deltaX_cheek, -0.1393f + deltaY_cheek));
    left_cheek.push_back(Vertex(-0.3919f - deltaX_cheek, -0.1570f + deltaY_cheek));
    
    sketch_points.push_back(left_cheek);
    
    // right eye top
    vector<Vertex> right_eye_top;
    right_eye_top.push_back(Vertex(0.1119f, 0.1480f));
    right_eye_top.push_back(Vertex(0.1119f, 0.2097f));
    right_eye_top.push_back(Vertex(0.0995f, 0.2128f));
    right_eye_top.push_back(Vertex(0.1501f, 0.2128f));
    right_eye_top.push_back(Vertex(0.1409f, 0.1603f));
    
    sketch_points.push_back(right_eye_top);
    
    // right eye bottom
    GLfloat deltaY_eye = 0.28f;
    GLfloat deltaX_eye = 0.255f;
    vector<Vertex> right_eye_bottom;
    right_eye_bottom.push_back(Vertex(0.1409f, 0.1603f));
    right_eye_bottom.push_back(Vertex(-0.1119f + deltaX_eye, -0.1480f +deltaY_eye));
    right_eye_bottom.push_back(Vertex(-0.1119f + deltaX_eye, -0.2097f + deltaY_eye));
    right_eye_bottom.push_back(Vertex(-0.0995f + deltaX_eye, -0.2128f + deltaY_eye));
    right_eye_bottom.push_back(Vertex(-0.1501f + deltaX_eye, -0.2128f + deltaY_eye));
    right_eye_bottom.push_back(Vertex(-0.1409f + deltaX_eye, -0.1603f + deltaY_eye));
    right_eye_bottom.push_back(Vertex(0.1119f, 0.1480f));
    
    sketch_points.push_back(right_eye_bottom);
    
    // left eye top
    vector<Vertex> left_eye_top;
    left_eye_top.push_back(Vertex(-0.1119f, 0.1480f));
    left_eye_top.push_back(Vertex(-0.1119f, 0.2097f));
    left_eye_top.push_back(Vertex(-0.0995f, 0.2128f));
    left_eye_top.push_back(Vertex(-0.1501f, 0.2128f));
    left_eye_top.push_back(Vertex(-0.1409f, 0.1603f));
    
    sketch_points.push_back(left_eye_top);
    
    // left eye bottom
    vector<Vertex> left_eye_bottom;
    left_eye_bottom.push_back(Vertex(-0.1409f, 0.1603f));
    left_eye_bottom.push_back(Vertex(0.1119f - deltaX_eye, -0.1480f +deltaY_eye));
    left_eye_bottom.push_back(Vertex(0.1119f - deltaX_eye, -0.2097f + deltaY_eye));
    left_eye_bottom.push_back(Vertex(0.0995f - deltaX_eye, -0.2128f + deltaY_eye));
    left_eye_bottom.push_back(Vertex(0.1501f - deltaX_eye, -0.2128f + deltaY_eye));
    left_eye_bottom.push_back(Vertex(0.1409f - deltaX_eye, -0.1603f + deltaY_eye));
    left_eye_bottom.push_back(Vertex(-0.1119f, 0.1480f));
    
    sketch_points.push_back(left_eye_bottom);
    
    //  hair right
    vector<Vertex> hair_right;
    hair_right.push_back(Vertex(0.3912f, 0.0654f));
    hair_right.push_back(Vertex(0.4224f, 0.0739f));
    hair_right.push_back(Vertex(0.4438f, 0.1050f));
    hair_right.push_back(Vertex(0.4574f, 0.1517f));
    hair_right.push_back(Vertex(0.4652f, 0.1964f));
    hair_right.push_back(Vertex(0.4652f, 0.2392f));
    hair_right.push_back(Vertex(0.4633f, 0.2819f));
    hair_right.push_back(Vertex(0.4516f, 0.3228f));
    hair_right.push_back(Vertex(0.4360f, 0.3675f));
    hair_right.push_back(Vertex(0.3894f, 0.4219f));
    hair_right.push_back(Vertex(0.3602f, 0.4589f));
    hair_right.push_back(Vertex(0.3194f, 0.4822f));
    hair_right.push_back(Vertex(0.1774f, 0.5114f));
    hair_right.push_back(Vertex(0.1230f, 0.5308f));
    hair_right.push_back(Vertex(0.0822f, 0.5483f));
    hair_right.push_back(Vertex(0.0316f, 0.5503f));
    hair_right.push_back(Vertex(-0.0189f, 0.5716f));
    hair_right.push_back(Vertex(-0.0656f, 0.5678f));
    hair_right.push_back(Vertex(-0.0656f, 0.5658f));
    hair_right.push_back(Vertex(-0.1142f, 0.5678f));
    hair_right.push_back(Vertex(-0.1551f, 0.5678f));
    hair_right.push_back(Vertex(-0.1978f, 0.5561f));
    hair_right.push_back(Vertex(-0.2659f, 0.5483f));
    hair_right.push_back(Vertex(-0.2912f, 0.5483));
    hair_right.push_back(Vertex(-0.3125f, 0.4569f));
    hair_right.push_back(Vertex(-0.3164f, 0.4453f));
    
    sketch_points.push_back(hair_right);
    
    //hair right down
    vector<Vertex> hair_right_down;
    GLfloat deltaX_r_hair = -0.00f;
    GLfloat deltaY_r_hair = -0.00f;
    hair_right_down.push_back(Vertex(0.3912f,  0.0654f));
    //hair_right_down.push_back(Vertex(0.4224f, 0.0739f));
    hair_right_down.push_back(Vertex(0.4402f + deltaX_r_hair, 0.0875f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.4259f + deltaX_r_hair, 0.1058f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.4574f + deltaX_r_hair, 0.1343f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.4117f + deltaX_r_hair, 0.1730f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.3913f + deltaX_r_hair, 0.2056f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.3791f + deltaX_r_hair, 0.2443f + deltaY_r_hair));
    hair_right_down.push_back(Vertex(0.3608f + deltaX_r_hair, 0.2626f + deltaY_r_hair));
    
    sketch_points.push_back(hair_right_down);
    
    //hair right down
    vector<Vertex> hair_left_down;
    GLfloat deltaX_l_hair = -0.00f;
    GLfloat deltaY_l_hair = -0.10f;
    hair_left_down.push_back(Vertex(0.3608f, 0.2626f));
    hair_left_down.push_back(Vertex( 0.3795f + deltaX_l_hair, 0.2933f + deltaY_l_hair));
    hair_left_down.push_back(Vertex( 0.3141f + deltaX_l_hair, 0.2978f + deltaY_l_hair));
    hair_left_down.push_back(Vertex( 0.2442f + deltaX_l_hair, 0.3000f + deltaY_l_hair));
    hair_left_down.push_back(Vertex( 0.1585f + deltaX_l_hair, 0.3045f + deltaY_l_hair));
    hair_left_down.push_back(Vertex( 0.0908f + deltaX_l_hair, 0.3293f + deltaY_l_hair));
    hair_left_down.push_back(Vertex( 0.0100f + deltaX_l_hair, 0.3406f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.0423f + deltaX_l_hair, 0.3587f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.1077f + deltaX_l_hair, 0.3790f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.2363f + deltaX_l_hair, 0.4015f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.2972f + deltaX_l_hair, 0.4331f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.3355f + deltaX_l_hair, 0.4579f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.3626f + deltaX_l_hair, 0.4940f + deltaY_l_hair));
    hair_left_down.push_back(Vertex(-0.3164f, 0.4453f));
    
    sketch_points.push_back(hair_left_down);
    
    //  hair left
    vector<Vertex> hair_left;
    GLfloat deltaX_left = 0.52f;
    GLfloat deltaY_left = -0.40f;
    hair_left.push_back(Vertex(-0.3164f, 0.4453f));
    hair_left.push_back(Vertex(-0.7922f + deltaX_left, 0.8449f + deltaY_left));
    hair_left.push_back(Vertex(-0.8724f + deltaX_left, 0.8449f + deltaY_left));
    hair_left.push_back(Vertex(-0.9526f + deltaX_left, 0.8247f + deltaY_left));
    hair_left.push_back(Vertex(-1.0106f + deltaX_left, 0.7842f + deltaY_left));
    hair_left.push_back(Vertex(-0.3912f, 0.0654f));
    
    sketch_points.push_back(hair_left);
    
    //  hair left symmetry
    vector<Vertex> hair_left_symmetry;
    hair_left_symmetry.push_back(Vertex(-0.3164f, 0.4453f));
    hair_left_symmetry.push_back(Vertex(-0.2164f, 0.4453f - 0.4f));
    hair_left_symmetry.push_back(Vertex(-0.3912f, 0.0654f));
    
    sketch_points.push_back(hair_left_symmetry);
    
    //  eyebrow_right
    GLfloat deltaY_eyebrow = -0.04f;
    vector<Vertex> eyebrow_right;
    eyebrow_right.push_back(Vertex(0.1918f, 0.2233f + deltaY_eyebrow));
    eyebrow_right.push_back(Vertex(0.1359f, 0.4568f + deltaY_eyebrow));
    eyebrow_right.push_back(Vertex(0.0683f, 0.2498f + deltaY_eyebrow));
    
    sketch_points.push_back(eyebrow_right);
    
    // eyebrow left
    vector<Vertex> eyebrow_left;
    eyebrow_left.push_back(Vertex(-0.1918f, 0.2233f + deltaY_eyebrow));
    eyebrow_left.push_back(Vertex(-0.1359f, 0.4568f + deltaY_eyebrow));
    eyebrow_left.push_back(Vertex(-0.0683f, 0.2498f + deltaY_eyebrow));
    
    sketch_points.push_back(eyebrow_left);
    
    return sketch_points;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set our color to black (R, G, B)
    glColor3f(0.0f, 0.0f, 0.0f);
    vector<vector<Vertex>> initial_points = init_sketch();
    
    // Iterate through the vector of vextors and draw the curves
    for (int i = 0; i < initial_points.size(); i++) {
        vector<Vertex> points_i = initial_points[i];
        draw_curve(points_i, 30);
    }
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

/***
 Assignment-2: Geometric Modeling of a Scene
 
 Name: Wong, Alex (Please write your name in Last Name, First Name format)
 
 Collaborators: Doe, John; Doe, Jane
 ** Note: although the assignment should be completed individually
 you may speak with classmates on high level algorithmic concepts. Please
 list their names in this section
 
 Project Summary: A short paragraph (3-4 sentences) describing the work you
 did for the project.
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

#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

/**************************************************
 *  Rectangular Prisms via Hierarchical Modeling  *
 *                                                *
 *  using planes as building blocks, build a unit *
 *  cube with transformations that will serve as  *
 *  a primitive for modeling objects in the scene *
 *                                                *
 *************************************************/

// Initializes a square plane of unit lengths
vector<GLfloat> init_plane() {
    vector<GLfloat> vertices = {
        +0.5,   +0.5,   +0.0,
        -0.5,   +0.5,   +0.0,
        -0.5,   -0.5,   +0.0,
        +0.5,   -0.5,   +0.0
    };
    return vertices;
}

// Converts a vector to an array
GLfloat* vector2array(vector<GLfloat> vec) {
    GLfloat* arr = new GLfloat[vec.size()];
    for (int i = 0; i < vec.size(); i++) {
        arr[i] = vec[i];
    }
    return arr;
}

// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_homogenous_coord(vector<GLfloat> cartesian_coords) {
    vector<GLfloat> result = cartesian_coords; // initialize with original coordinates
    // Append the 1 in the 4th dimension to generate homoegenous coordinates
    
    // if it is a vector:
    if (cartesian_coords.size() == 3) {
        result.push_back(1.00f);
        return result;
    }
    // if it is a 3x3 matrix
    for (int i = 3; i <=8; i += 4){
        result.insert(result.begin()+i, 1, 0.00f);
    }
    // add last value
    result.push_back(0.00f);
    // add last row
    result.push_back(0.00f);
    result.push_back(0.00f);
    result.push_back(0.00f);
    result.push_back(1.00f);
    return result;
}


// Converts Cartesian coordinates to homogeneous coordinates
vector<GLfloat> to_cartesian_coord(vector<GLfloat> homogenous_coords) {
    vector<GLfloat> result = homogenous_coords; // initialize with original coordinates
    
    // Remove the 1 in the 4th dimension to generate Cartesian coordinates
    
    // if it is a vector:
    if (homogenous_coords.size() == 4) {
        result.pop_back();
        return result;
    }
    
    // if it is a 3x3 matrix
    for (int i = 3; i <=3*3; i += 3){
        result.erase(result.begin()+i);
    }
    // add last value
    result.push_back(0.00f);
    // add last row
    result.pop_back();
    result.pop_back();
    result.pop_back();
    result.pop_back();
    result.pop_back();
    return result;
    
    return result;
}

// Definition of a translation matrix
vector<GLfloat> translation_matrix (float dx, float dy, float dz) {
    vector<GLfloat> translate_mat = {1.0f, 0.0f, 0.0f, dx,
                                     0.0f, 1.0f, 0.0f, dy,
                                     0.0f, 0.0f, 1.0f, dz,
                                     0.0f, 0.0f, 0.0f, 1.0f};
    return translate_mat;
}

// Definition of a scaling matrix
vector<GLfloat> scaling_matrix (float sx, float sy, float sz) {
    vector<GLfloat> scale_mat = {sx,   0.0f, 0.0f, 0.0f,
                                 0.0f, sy,   0.0f, 0.0f,
                                 0.0f, 0.0f, sz,   0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f};

    return scale_mat;
}

// Definition of a rotation matrix along the x-axis theta degrees
vector<GLfloat> rotation_matrix_x (float theta) {
    vector<GLfloat> rotate_mat_x= {1.0f,        0.0f,        0.0f,        0.0f,
                                   0.0f,        cos(theta), -sin(theta),  0.0f,
                                   0.0f,        sin(theta),  cos(theta),  0.0f,
                                   0.0f,        0.0f,        0.0f,        1.0f};
    return rotate_mat_x;
}


// Definition of a rotation matrix along the y-axis by theta degrees
vector<GLfloat> rotation_matrix_y (float theta) {
    vector<GLfloat> rotate_mat_y= { cos(theta), 0.0f, sin(theta), 0.0f,
                                    0.0f,       1.0f, 0.0f      , 0.0f,
                                   -sin(theta), 0.0f, cos(theta), 0.0f,
                                    0.0f,       0.0f, 0.0f      , 1.0f};
    return rotate_mat_y;
}


// Definition of a rotation matrix along the z-axis by theta degrees
vector<GLfloat> rotation_matrix_z (float theta) {
    vector<GLfloat> rotate_mat_z= {cos(theta), -sin(theta), 0.0f,   0.0f,
                                   sin(theta),  cos(theta), 0.0f,   0.0f,
                                   0.0f,        0.0f,       1.0f,   0.0f,
                                   0.0f,        0.0f,       0.0f,   1.0f};
    return rotate_mat_z;
}

// Perform matrix multiplication for A B
vector<GLfloat> mat_mult(vector<GLfloat> A, vector<GLfloat> B) {
    vector<GLfloat>::iterator it1, it2;
    int i = 0;
    int j = 0;
    for(it1 = A.begin(); it1 != A.end() - 4; it1 += 4, i += 4){
        GLfloat result_value = 0.0f;
        for(it2 = B.begin(); it2 != B.end() - 8; it2++, j+= 1){
            result_value += A[i] * B[j] + A[i+1] *B[i+4] + A[i+2] * B[i+2*4] + A[i+3]*B[i];
            
        }
    }
    vector<GLfloat> result;
    
    // Perform matrix multiplication for A B
    
    return result;
}

// Builds a unit cube centered at the origin
vector<GLfloat> build_cube() {
    vector<GLfloat> result;
    
    // Creates a unit cube by transforming a set of planes
    
    return result;
}

/**************************************************
 *            Camera and World Modeling           *
 *                                                *
 *  create a scene by applying transformations to *
 *  the objects built from planes and position    *
 *  the camera to view the scene by using setting *
 *  the projection viewing matrices               *
 *                                                *
 *************************************************/

void setup() {
    // Enable the vertex array functionality
    glEnableClientState(GL_VERTEX_ARRAY);
    // Enable the color array functionality (so we can specify a color for each vertex)
    glEnableClientState(GL_COLOR_ARRAY);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Set up some default base color
    glColor3f(0.5, 0.5, 0.5);
    // Set up white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init_camera() {
    // Camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

// Construct the scene using objects built from cubes/prisms
GLfloat* init_scene() {
    return nullptr;
}

// Construct the color mapping of the scene
GLfloat* init_color() {
    return nullptr;
}

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Perform display functions
    
    glFlush();            //Finish rendering
    glutSwapBuffers();
}


int main (int argc, char **argv) {
    //Testing functions:
    vector<GLfloat> test= {2,2,2,  2,2,2  , 2,2,2};
    vector<GLfloat> test2= {1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 1};
    vector<GLfloat> test4= {1, 2, 3, 0};
    vector<GLfloat> test3= {2,2,2};
    vector<GLfloat> result = to_cartesian_coord(test4);
    vector<GLfloat>::iterator it;
    cout << "myvector contains:";
    for (it = result.begin(); it<result.end(); it++)
        cout << ' ' << *it;
    cout << '\n';
    
    
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    // Create a window with rendering context and everything else we need
    glutCreateWindow("Assignment 2");
    
    setup();
    init_camera();
    
    // Set up our display function
    glutDisplayFunc(display_func);
    // Render our world
    glutMainLoop();
    
    // Remember to call "delete" on your dynmically allocated arrays
    // such that you don't suffer from memory leaks. e.g.
    // delete arr;
    
    return 0;
}

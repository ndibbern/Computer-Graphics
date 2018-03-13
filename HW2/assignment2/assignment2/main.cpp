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

// Transforms from degrees to radians
static double d2r(double d) {
    return (d / 180.0) * ((double) M_PI);
}

// Prints a vector

static void print(vector<GLfloat> result) {
        vector<GLfloat>::iterator it;
            cout << "myvector contains:";
            for (it = result.begin(); it<result.end(); it++)
                cout << ' ' << *it;
            cout << '\n';
}

// Initializes a square plane of unit lengths
vector<GLfloat> init_plane() {
    vector<GLfloat> vertices = {
//        +0.5,   +0.5,   +0.0,
//        -0.5,   +0.5,   +0.0,
//        -0.5,   -0.5,   +0.0,
//        +0.5,   -0.5,   +0.0,
//
        +1,   +1,   +0.0,
        -1,   +1,   +0.0,
        -1,   -1,   +0.0,
        +1,   -1,   +0.0,
    };
    return vertices;
}

// Initializes the 4x4 identity matrix
vector<GLfloat> identity() {
    vector<GLfloat> vertices = {1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1};
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
    // if it is a matrix that contains 4 points:
    if (cartesian_coords.size() == 12) {
        for (int i = 3; i <=12; i += 4){
            result.insert(result.begin()+i, 1, 1.00f);
        }
        result.push_back(1.00);
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

    // if it is a 4x4 matrix
    for (int i = 3; i <=3*3; i += 3){
        result.erase(result.begin()+i);
    }
    result.pop_back();
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
    vector<GLfloat> result;
    int r1, c1, r2, c2 = 0;
    int counterA = 0;
    int counterB = 0;

    if(A.size() == 16){ r1 = 4;c1 = 4;}
    if(B.size() == 16){r2 = 4;c2 = 4;}
    if(A.size() == 4){r1 = 4;c1 = 1;}
    if(B.size() == 4){r2 = 4;c2 = 1;}

    GLfloat a[r1][c1], b[r2][c2], C[r1][c2];

    if (c1 != r2){
        cout << "Matrices cannot be multiplied!";
        exit(0);
    }
    // Copying A to matrix format
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++){
            a[i][j] = A[counterA];
            counterA++;
        }
    // Copying B to matrix format

    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++){
            b[i][j] = B[counterB];
            counterB++;
        }

    // Perform Multiplication
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < r2; k++)
            {
                C[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // Transform back to vector
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result.push_back(C[i][j]);
        }
    }
    return result;
}

//// Performs matrix multiplication with given matrix and outputs a long concatenated vector with each point
vector<GLfloat> mult_many_points(vector<GLfloat> transformation_matrix, vector<GLfloat> points) {
    vector<GLfloat> result, homogeneous_point, mult_result;
    int nb_points = int(points.size());
    
    for (int i = 0; i <nb_points; i += 3){
        vector<GLfloat> point(points.begin()+i, points.begin()+i+3);
        homogeneous_point = to_homogenous_coord(point);
        mult_result = mat_mult(transformation_matrix, homogeneous_point);
        result.insert(end(result), begin(mult_result), end(mult_result));
    }
    return result;
}

// Builds a unit cube centered at the origin
vector<GLfloat> build_cube() {

    vector<GLfloat> initial_plane = init_plane();
    // Creates a unit cube by transforming a set of planes. We do transformations in homogeneous but then transform back to cartesian
    vector<GLfloat> front  = to_cartesian_coord(mult_many_points(translation_matrix(0,0,1), initial_plane));
    vector<GLfloat> back   = to_cartesian_coord(mult_many_points(translation_matrix(0,0,-1), to_cartesian_coord(mult_many_points(rotation_matrix_y(d2r(180)), initial_plane))));
    vector<GLfloat> right   = to_cartesian_coord(mult_many_points(translation_matrix(1,0,0), to_cartesian_coord(mult_many_points(rotation_matrix_y(d2r( 90)), initial_plane))));
    vector<GLfloat> left   = to_cartesian_coord(mult_many_points(translation_matrix(-1,0,0), to_cartesian_coord(mult_many_points(rotation_matrix_y(d2r(-90)), initial_plane))));
    vector<GLfloat> bottom   = to_cartesian_coord(mult_many_points(translation_matrix(0,-1,0), to_cartesian_coord(mult_many_points(rotation_matrix_x(d2r( 90)), initial_plane))));
    vector<GLfloat> top   = to_cartesian_coord(mult_many_points(translation_matrix(0,1,0), to_cartesian_coord(mult_many_points(rotation_matrix_x(d2r(-90)), initial_plane))));

    // concatenate into one long vector
    vector<GLfloat> result;
    result = front;
    result.insert(end(result), begin(back), end(back));
    result.insert(end(result), begin(right), end(right));
    result.insert(end(result), begin(left), end(left));
    result.insert(end(result), begin(top), end(top));
    result.insert(end(result), begin(bottom), end(bottom));

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

float theta = 0.0;

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

// Init camara
void init_camera() {
    // Camera parameters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a 50 degree field of view, 1:1 aspect ratio, near and far planes at 3 and 7
    gluPerspective(50.0, 1.0, 2.0, 10.0);
    // Position camera at (2, 3, 5), attention at (0, 0, 0), up at (0, 1, 0)
    gluLookAt(2.0, 6.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


//// Construct the scene using objects built from cubes/prisms
//GLfloat* init_scene() {
//    return nullptr;
//}
//
//// Construct the color mapping of the scene
//GLfloat* init_color() {
//    return nullptr;
//}


void display_func() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // World model parameters
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    GLfloat* vertices= vector2array(build_cube());
    
    GLfloat colors[] = {
        // Front plane
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        1.0,    0.0,    0.0,
        // Back plane
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        0.0,    1.0,    0.0,
        // Right
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        0.0,    0.0,    1.0,
        // Left
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        1.0,    1.0,    0.0,
        // Top
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        1.0,    0.0,    1.0,
        // Bottom
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
        0.0,    1.0,    1.0,
    };
    
    glVertexPointer(3,          // 3 components (x, y, z)
                    GL_FLOAT,   // Vertex type is GL_FLOAT
                    0,          // Start position in referenced memory
                    vertices);  // Pointer to memory location to read from
    
    //pass the color pointer
    glColorPointer(3,           // 3 components (r, g, b)
                   GL_FLOAT,    // Vertex type is GL_FLOAT
                   0,           // Start position in referenced memory
                   colors);     // Pointer to memory location to read from
    
    // Draw quad point planes: each 4 vertices
    glDrawArrays(GL_QUADS, 0, 4*6);
    
    glFlush();            //Finish rendering
    glutSwapBuffers();
}

//void display_func() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // Perform display functions
//
//    glFlush();            //Finish rendering
//    glutSwapBuffers();
//}


int main (int argc, char **argv) {
    print(build_cube());
    
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

















//void display_func() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // World model parameters
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    glRotatef(theta, 0.0, 1.0, 0.0);
//    glRotatef(theta, 1.0, 0.0, 0.0);
//
//    GLfloat vertices[] = {
//        // Front plane
//        +1.0,   +1.0,   +1.0,
//        -1.0,   +1.0,   +1.0,
//        -1.0,   -1.0,   +1.0,
//        +1.0,   -1.0,   +1.0,
//        // Back plane
//        +1.0,   +1.0,   -1.0,
//        -1.0,   +1.0,   -1.0,
//        -1.0,   -1.0,   -1.0,
//        +1.0,   -1.0,   -1.0,
//        // Right
//        +1.0,   +1.0,   -1.0,
//        +1.0,   +1.0,   +1.0,
//        +1.0,   -1.0,   +1.0,
//        +1.0,   -1.0,   -1.0,
//        // Left
//        -1.0,   +1.0,   -1.0,
//        -1.0,   +1.0,   +1.0,
//        -1.0,   -1.0,   +1.0,
//        -1.0,   -1.0,   -1.0,
//        // Top
//        +1.0,   +1.0,   +1.0,
//        -1.0,   +1.0,   +1.0,
//        -1.0,   +1.0,   -1.0,
//        +1.0,   +1.0,   -1.0,
//        // Bottom
//        +1.0,   -1.0,   +1.0,
//        -1.0,   -1.0,   +1.0,
//        -1.0,   -1.0,   -1.0,
//        +1.0,   -1.0,   -1.0,
//    };
//
//    GLfloat colors[] = {
//        // Front plane
//        1.0,    0.0,    0.0,
//        1.0,    0.0,    0.0,
//        1.0,    0.0,    0.0,
//        1.0,    0.0,    0.0,
//        // Back plane
//        0.0,    1.0,    0.0,
//        0.0,    1.0,    0.0,
//        0.0,    1.0,    0.0,
//        0.0,    1.0,    0.0,
//        // Right
//        0.0,    0.0,    1.0,
//        0.0,    0.0,    1.0,
//        0.0,    0.0,    1.0,
//        0.0,    0.0,    1.0,
//        // Left
//        1.0,    1.0,    0.0,
//        1.0,    1.0,    0.0,
//        1.0,    1.0,    0.0,
//        1.0,    1.0,    0.0,
//        // Top
//        1.0,    0.0,    1.0,
//        1.0,    0.0,    1.0,
//        1.0,    0.0,    1.0,
//        1.0,    0.0,    1.0,
//        // Bottom
//        0.0,    1.0,    1.0,
//        0.0,    1.0,    1.0,
//        0.0,    1.0,    1.0,
//        0.0,    1.0,    1.0,
//    };
//
//    glVertexPointer(3,          // 3 components (x, y, z)
//                    GL_FLOAT,   // Vertex type is GL_FLOAT
//                    0,          // Start position in referenced memory
//                    vertices);  // Pointer to memory location to read from
//
//    //pass the color pointer
//    glColorPointer(3,           // 3 components (r, g, b)
//                   GL_FLOAT,    // Vertex type is GL_FLOAT
//                   0,           // Start position in referenced memory
//                   colors);     // Pointer to memory location to read from
//
//    // Draw quad point planes: each 4 vertices
//    glDrawArrays(GL_QUADS, 0, 4*6);
//
//    glFlush();            //Finish rendering
//    glutSwapBuffers();
//}


//1, 1, 1,
//-1, 1, 1,
//-1, -1, 1,
//1, -1, 1,
//
//-1, 1, -1,
//1, 1, -1,
//1, -1, -1,
//-1, -1, -1,
//
//1, 1, -1,
//1, 1, 1,
//1, -1, 1,
//1, -1, -1,
//
//-1, 1, 1,
//-1, 1, -1,
//-1, -1, -1,
//-1, -1, 1,
//
//1, 1, -1,
//-1, 1, -1,
//-1, 1, 1,
//1, 1, 1,
//
//1, -1, 1,
//-1, -1, 1,
//-1, -1, -1,
//1, -1, -1


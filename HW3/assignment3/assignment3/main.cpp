/***
 Assignment-3: Shading via Lighting and Colors
 
 Name: Dibbern, Natalia
 Collaborators: Me myself and I (as usual)
 
 Project Summary: This project was a continuation of project II. This time
we create the colors for each object and implement a shading
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
#include <random>
#include <iostream>
using namespace std;

/**************************************************
 *              Object Model Class                *
 *                                                *
 *  Stores the points of the object as a vector   *
 *  along with the colors and normals for each    *
 *  point. Normals are computed from the points.  *
 *                                                *
 *************************************************/
class ObjectModel {
    vector<GLfloat> _points;
    vector<GLfloat> _normals;
    vector<GLfloat> _base_colors;
    vector<GLfloat> _colors;
public:
    ObjectModel();
    vector<GLfloat> get_points() { return _points; };
    vector<GLfloat> get_normals() { return _normals; };
    vector<GLfloat> get_base_colors() { return _base_colors; };
    vector<GLfloat> get_colors() { return _colors; };
    void set_points(vector<GLfloat> points) { _points = points; };
    void set_normals(vector<GLfloat> normals) { _normals = normals; };
    void set_base_colors(vector<GLfloat> base_colors) { _base_colors = base_colors; };
    void set_colors(vector<GLfloat> colors) { _colors = colors; };
};

/**************************************************
 *  Rectangular Prisms via Hierarchical Modeling  *
 *                                                *
 *  using planes as building blocks, build a unit *
 *  cube with transformations that will serve as  *
 *  a primitive for modeling objects in the scene *
 *                                                *
 *************************************************/

float theta = 0.0;

// Transforms from degrees to radians
static double d2r(double d) {
    return (d / 180.0) * ((double) M_PI);
    
    ObjectModel o = ObjectModel();
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
        +0.5,   +0.5,   +0.0,
        -0.5,   +0.5,   +0.0,
        -0.5,   -0.5,   +0.0,
        +0.5,   -0.5,   +0.0,
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
    // The way I coded this, I will only send a vector every time
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

// Performs matrix multiplication with given matrix and outputs a long concatenated vector with each point
vector<GLfloat> mult_many_points(vector<GLfloat> transformation_matrix, vector<GLfloat> points) {
    vector<GLfloat> result, homogeneous_point, mult_result;
    double nb_points = points.size();
    
    for (double i = 0; i <int(nb_points/3); i ++){
        vector<GLfloat> point(points.begin()+i*3, points.begin()+i*3+3);
        homogeneous_point = to_homogenous_coord(point);
        mult_result = to_cartesian_coord(mat_mult(transformation_matrix, homogeneous_point));
        result.insert(end(result), begin(mult_result), end(mult_result));
    }
    return result;
}

// Builds a unit cube centered at the origin
vector<GLfloat> build_cube() {
    
    vector<GLfloat> initial_plane = init_plane();
    // Creates a unit cube by transforming a set of planes. We do transformations in homogeneous but then transform back to cartesian
    vector<GLfloat> front = (mult_many_points(translation_matrix(0,0,0.5), initial_plane));
    vector<GLfloat> back = (mult_many_points(translation_matrix(0,0,-0.5), (mult_many_points(rotation_matrix_y(d2r(180)), initial_plane))));
    vector<GLfloat> right = (mult_many_points(translation_matrix(0.5,0,0), (mult_many_points(rotation_matrix_y(d2r( 90)), initial_plane))));
    vector<GLfloat> left = (mult_many_points(translation_matrix(-0.5,0,0), (mult_many_points(rotation_matrix_y(d2r(-90)), initial_plane))));
    vector<GLfloat> bottom = (mult_many_points(translation_matrix(0,-0.5,0), (mult_many_points(rotation_matrix_x(d2r( 90)), initial_plane))));
    vector<GLfloat> top = (mult_many_points(translation_matrix(0,0.5,0), (mult_many_points(rotation_matrix_x(d2r(-90)), initial_plane))));
    
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
 *           Generating Surface Normals           *
 *                                                *
 *  Generate the surface normals of the objects   *
 *  using the cross product between two vectors   *
 *  that lie on the surface (plane) of interest.  *
 *  Recall that the direction of the normal to a  *
 *  surface follows the Right Hand Rule.          *
 *                                                *
 *************************************************/

// Performs the cross product between two vectors
vector<GLfloat> cross_product(vector<GLfloat> A, vector<GLfloat> B) {
    vector<GLfloat> C;
    C.push_back(A[1]*B[2]-A[2]*B[1]);
    C.push_back(A[0]*B[2]-A[2]*B[0]);
    C.push_back(A[0]*B[1]-A[1]*B[0]);
    return C;
}

// Substracts two vectors
vector<GLfloat> substract(vector<GLfloat> A, vector<GLfloat> B){
    vector<GLfloat> result;
    transform(A.begin(), A.end(), B.begin(), back_inserter(result), [&](GLfloat l, GLfloat r){
        return l - r;
    });
    return result;
}

// Generates the normals to each surface (plane)
vector<GLfloat> generate_normals(vector<GLfloat> points) {
    vector<GLfloat> normals;
    
    // Note: each plane (quad) contains 4 points, choose the points
    // to generate your vectors such that the normals (given by the
    // cross product, point to the correct direction
    
    for(int i=0; i <= points.size() - 12; i = i+12) {
        vector<GLfloat> cross_prod, q0, q1, q2, q3, sub1, sub2;
        // pick up points
        q0.insert(end(q0), begin(points)+i, begin(points)+i+3);
        q1.insert(end(q1), begin(points)+i+3, begin(points)+i+6);
        q2.insert(end(q2), begin(points)+i+6, begin(points)+i+9);
        q3.insert(end(q3), begin(points)+i+9, begin(points)+i+12);
        // generate substractions
        sub1 = substract(q1, q0);
        sub2 = substract(q3, q0);
        cross_prod = cross_product(sub1, sub2);
        
        for(int i=0; i < 4; i++){
            normals.insert(end(normals), begin(cross_prod), end(cross_prod));
        }
    }
    return normals;
}


/**************************************************
 *         Shading via Lighting and Color         *
 *                                                *
 *  Generate the set of colors for each face of   *
 *  the planes that compose the objects in the    *
 *  scene. Based on the light source and surface  *
 *  normals, render the colors of the objects by  *
 *  applying the shading equation.                *
 *                                                *
 *************************************************/

// Initializes the base color of a plane to a single color
vector<GLfloat> init_base_color(GLfloat r, GLfloat g, GLfloat b) {
    vector<GLfloat> base_color = {
        r,   g,   b,
        r,   g,   b,
        r,   g,   b,
        r,   g,   b
    };
    return base_color;
}

// Initializes the base color of a plane by specifying the color of each point
vector<GLfloat> init_base_color(GLfloat r0, GLfloat g0, GLfloat b0, GLfloat r1, GLfloat g1, GLfloat b1,
                                GLfloat r2, GLfloat g2, GLfloat b2, GLfloat r3, GLfloat g3, GLfloat b3) {
    // This enables OpenGL to use interpolation for (Gouraud) shading the plane
    vector<GLfloat> base_color = {
        r0,   g0,   b0,
        r1,   g1,   b1,
        r2,   g2,   b2,
        r3,   g3,   b3
    };
    return base_color;
}

// Performs the dot product between two vectors
GLfloat dot_product(vector<GLfloat> A, vector<GLfloat> B) {
    GLfloat result = 0.0;
    
    for (int i=0; i < A.size(); i++) {
        result = result + A[i]*B[i];
    }
    return result;
}

// Adds two vectors
vector<GLfloat> add(vector<GLfloat> A, vector<GLfloat> B){
    vector<GLfloat> result;
    transform(A.begin(), A.end(), B.begin(), back_inserter(result), [&](GLfloat l, GLfloat r){
        return l + r;
    });
    return result;
}

// Modulo of a vector
GLfloat modulo(vector<GLfloat> v) {
    GLfloat result = 0.0;
    for (int i = 0; i < v.size(); i++){
        result = result + v[i]*v[i];
    }
    return sqrt(result);
}


//Generate h
vector<GLfloat> get_h(vector<GLfloat> l, vector<GLfloat> v) {
    vector<GLfloat> result;
    vector<GLfloat> added = add(l, v);
    GLfloat m = modulo(added);
    
    for(int i = 0; i < added.size(); i++) {
        result.push_back(added[i]/m);
    }
    return result;
}

// Generates the colors of a set of surfaces based on the light source,
// surface normals, and base color of the surface
vector<GLfloat> apply_shading(vector<GLfloat> normals, vector<GLfloat> points, vector<GLfloat> base_colors, vector<GLfloat> light_source, vector<GLfloat> camera) {
    vector<GLfloat> colors;
    GLfloat Ir, Ib, Ig;
    GLfloat amb_c = 0.45;
    GLfloat diff_c = 0.15;
    GLfloat spec_c = 0.2;
    vector<GLfloat> h = get_h(light_source, camera);
    
    for(int i=0; i <= points.size() - 3; i = i+3) {
        vector<GLfloat> normal;
        normal.insert(end(normal), begin(normals)+i, begin(normals)+i+3);
        Ir = base_colors[i] * (amb_c + diff_c * dot_product(normal, light_source)+ spec_c * base_colors[i]* dot_product(normal, h));
        Ig = base_colors[i+1] * (amb_c + diff_c * dot_product(normal, light_source)+ spec_c * base_colors[i+1]* dot_product(normal, h));
        Ib = base_colors[i+2] * (amb_c + diff_c * dot_product(normal, light_source)+ spec_c * base_colors[i+2]* dot_product(normal, h));
        colors.push_back(Ir);
        colors.push_back(Ig);
        colors.push_back(Ib);
        
    }
    
    return colors;
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

float Theta = 0.0;

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
    //gluLookAt(-3.0, 5.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt(-3.0, 5.0, -6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt(0.0, 5.0, -6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt(4, 5.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(2.0, 6.0, 5, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0);
    
}


// Construct the scene using objects built from cubes/prisms
vector<GLfloat> init_scene_vector() {
    // declare scene and initialize cube
    vector<GLfloat> scene;
    vector<GLfloat> cube = build_cube();

    // Create table
    vector<GLfloat> table;
    vector<GLfloat> table_top = mult_many_points(translation_matrix(0,2,0), mult_many_points(scaling_matrix(2,0.1,1),   cube));
    vector<GLfloat> table_leg = mult_many_points(translation_matrix(0.9,0.9,0.4), mult_many_points(scaling_matrix(0.1,2.1,0.1), cube));
    vector<GLfloat> table_leg2 = mult_many_points(translation_matrix(-0.9,0.9,0.4), mult_many_points(scaling_matrix(0.1,2.1,0.1), cube));
    vector<GLfloat> table_leg3 = mult_many_points(translation_matrix(0.9,0.9,-0.4), mult_many_points(scaling_matrix(0.1,2.1,0.1), cube));
    vector<GLfloat> table_leg4 = mult_many_points(translation_matrix(-0.9,0.9,-0.4), mult_many_points(scaling_matrix(0.1,2.1,0.1), cube));
    table = table_top;
    table.insert(end(table), begin(table_leg), end(table_leg));
    table.insert(end(table), begin(table_leg2), end(table_leg2));
    table.insert(end(table), begin(table_leg3), end(table_leg3));
    table.insert(end(table), begin(table_leg4), end(table_leg4));
    table = mult_many_points(translation_matrix(0,-0.1,0),mult_many_points(scaling_matrix(1.5,0.9,1.5),table));
    
    // Create chair
    vector<GLfloat> chair;
    vector<GLfloat> chair_back = mult_many_points(translation_matrix(0,2.1,-0.4), mult_many_points(scaling_matrix(1,1,0.1),   cube));
    vector<GLfloat> chair_seat = mult_many_points(translation_matrix(0,1.6,0), mult_many_points(scaling_matrix(1,0.1,1),   cube));
    vector<GLfloat> chair_leg = mult_many_points(translation_matrix(0.45,1.1,-0.4), mult_many_points(scaling_matrix(0.1,1,0.1), cube));
    vector<GLfloat> chair_leg2 = mult_many_points(translation_matrix(-0.45,1.1,-0.4), mult_many_points(scaling_matrix(0.1,1,0.1), cube));
    vector<GLfloat> chair_leg3 = mult_many_points(translation_matrix(0.45,1.1,0.4), mult_many_points(scaling_matrix(0.1,1,0.1), cube));
    vector<GLfloat> chair_leg4 = mult_many_points(translation_matrix(-0.45,1.1,0.4), mult_many_points(scaling_matrix(0.1,1,0.1), cube));
    chair = chair_seat;
    chair.insert(end(chair), begin(chair_leg), end(chair_leg));
    chair.insert(end(chair), begin(chair_back), end(chair_back));
    chair.insert(end(chair), begin(chair_leg2), end(chair_leg2));
    chair.insert(end(chair), begin(chair_leg3), end(chair_leg3));
    chair.insert(end(chair), begin(chair_leg4), end(chair_leg4));
    chair = mult_many_points(translation_matrix(-0.3,-0.5,-1.5), chair);
    
    // create shelf
    vector<GLfloat> shelf;
    vector<GLfloat> shelf_top = mult_many_points(translation_matrix(-2,1,0.4), mult_many_points(scaling_matrix(0.9,0.1,1.2), cube));
    vector<GLfloat> shelf_middle = mult_many_points(translation_matrix(-2,1.75,0.4), mult_many_points(scaling_matrix(0.9,0.1,1.2), cube));
    vector<GLfloat> shelf_bottom = mult_many_points(translation_matrix(-2,0.25,0.4), mult_many_points(scaling_matrix(0.9,0.1,1.2), cube));
    vector<GLfloat> shelf_left_side = mult_many_points(translation_matrix(-2.5,1,0.4), mult_many_points(scaling_matrix(0.1,1.6,1.2), cube));
    vector<GLfloat> shelf_right_side = mult_many_points(translation_matrix(-1.5,1,0.4), mult_many_points(scaling_matrix(0.1,1.6,1.2), cube));
    shelf = shelf_top;
    shelf.insert(end(shelf), begin(shelf_middle), end(shelf_middle));
    shelf.insert(end(shelf), begin(shelf_bottom), end(shelf_bottom));
    shelf.insert(end(shelf), begin(shelf_left_side), end(shelf_left_side));
    shelf.insert(end(shelf), begin(shelf_right_side), end(shelf_right_side));
    shelf = mult_many_points(translation_matrix(-0.1,-0.2,0), shelf);
    
    // create notebook
    vector<GLfloat> notebook = mult_many_points(translation_matrix(-2.13,1.65,0.4), mult_many_points(rotation_matrix_y(45),mult_many_points(scaling_matrix(0.6*1,0.6*0.1,0.6*1.2), cube)));
    
    // create screen
    vector<GLfloat> monitor;
    vector<GLfloat> screen = mult_many_points(translation_matrix(-0.1,2.55,-0.2), mult_many_points(rotation_matrix_y(0),mult_many_points(scaling_matrix(1.4, 1,0.05), cube)));
    vector<GLfloat> base = mult_many_points(translation_matrix(-0.1,1.8,-0.2), mult_many_points(rotation_matrix_y(0),mult_many_points(scaling_matrix(0.6*1,0.6*0.1,0.6*1.2), cube)));
    vector<GLfloat> base_stick = mult_many_points(translation_matrix(-0.1,1.9,-0.2), mult_many_points(rotation_matrix_y(0),mult_many_points(scaling_matrix(0.6*0.1,0.6*0.5,0.6*0.1), cube)));
    monitor = screen;
    monitor.insert(end(monitor), begin(base), end(base));
    monitor.insert(end(monitor), begin(base_stick), end(base_stick));
    monitor = mult_many_points(translation_matrix(0,0,0.5), monitor);
    
    // create second shelf
    vector<GLfloat> shelf2 = mult_many_points(scaling_matrix(1,2,1), shelf);
    shelf2 = mult_many_points(translation_matrix(4.22,-0.1,0), shelf2);
    
    // create books
    vector<GLfloat> book1 = mult_many_points(translation_matrix(2.51,2.2,0.4), mult_many_points(scaling_matrix(0.1,1.2,1.2), cube));

    
    // concat all objects on scene
    scene.insert(end(scene), begin(table), end(table));
    scene.insert(end(scene), begin(chair), end(chair));
    scene.insert(end(scene), begin(shelf), end(shelf));
    scene.insert(end(scene), begin(notebook), end(notebook));
    scene.insert(end(scene), begin(monitor), end(monitor));
    scene.insert(end(scene), begin(shelf2), end(shelf2));
    scene.insert(end(scene), begin(book1), end(book1));
    return scene;
}

// Construct the scene using objects built from cubes/prisms
GLfloat* init_scene() {
    // declare scene and initialize cube
    vector<GLfloat> scene = init_scene_vector();
    return vector2array(scene);
}


// COLORS:
//  wheat: 0.847059 0.847059  0.74902  --> one shelf
// light wood: 0.65, 0.50, 0.39        --> table, chair
// sienna:  0.556863 green 0.419608 blue 0.137255
// dark slate gray 0.184314 green 0.309804 blue 0.309804   medio azulado
// gray oscuro: color red 0.329412 green 0.329412 blue 0.329412 --> monitor
// salmon :  0.435294 green 0.258824 blue 0.258824
// LightBlue = color red 0.74902 green 0.847059 blue 0.847059
// neon pink" color red 1.00 green 0.43 blue 0.78
// dark brown: color red 0.36 green 0.25 blue 0.20
// quarz : color red 0.85 green 0.85 blue 0.95

// table 5
// chair 6
// shelf 5
// notebook 1
// screen 3
// second shelf 5

vector<GLfloat> get_colors(){
    vector<GLfloat> final_vector;
    
    // table
    for(int i=0; i < 6*5*4; i++){
        final_vector.push_back(0.36);
        final_vector.push_back(0.25);
        final_vector.push_back(0.20);
    }
    
    // chair
    for(int i=0; i < 6*6*4; i++){
        final_vector.push_back(0.65);
        final_vector.push_back(0.50);
        final_vector.push_back(0.39);
    }
    
    // shelf
    for(int i=0; i < 6*5*4; i++){
        
        final_vector.push_back(0.85);
        final_vector.push_back(0.85);
        final_vector.push_back(0.95);
    }
    
    // notebook
    for(int i=0; i < 6*1*4; i++){
        final_vector.push_back(1.00);
        final_vector.push_back(0.43);
        final_vector.push_back(0.78);
    }
    
    // screen
    for(int i=0; i < 6*3*4; i++){
        final_vector.push_back(0.1);
        final_vector.push_back(0.1);
        final_vector.push_back(0.102);
    }
    
    // second shelf
    for(int i=0; i < 6*5*4; i++){
        final_vector.push_back(0.847059);
        final_vector.push_back(0.847059);
        final_vector.push_back(0.74902);
    }
    
    // book1
    for(int i=0; i < 6*1*4; i++){
        final_vector.push_back(0.74902);
        final_vector.push_back(0.847059);
        final_vector.push_back(0.847059);
    }

    return final_vector;
}
vector<GLfloat> color_vector = get_colors();


// Construct the color mapping of the scene
GLfloat* init_color() {
    vector<GLfloat> points = init_scene_vector();
    vector<GLfloat> normals = generate_normals(points);
   vector<GLfloat> colors = apply_shading(normals, points, color_vector, {-2.0f, -1.0f, -5.0f}, {-2.0f, -3.0f, -5.0f});
    return vector2array(colors);
}

void display_func() {
    int sides_nb = 6*26; // 20 is the number of "cubes" I transformed, I do this to make sure I create the correct color size vector
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // World model parameters
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //glRotatef(theta, 0.0, 1.0, 0.0);
    glRotatef(theta, 0.0, 1, 0.0);
    
    GLfloat* vertices = init_scene();
    GLfloat* colors = init_color();
    
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
    glDrawArrays(GL_QUADS, 0, 4*sides_nb);
    
    glFlush();            //Finish rendering
    glutSwapBuffers();
    
    delete vertices;
    delete colors;
}

void idle_func() {
    theta = theta+0.5;
    display_func();
}


int main (int argc, char **argv) {
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
    glutIdleFunc(idle_func);
    // Render our world
    glutMainLoop();
    
    // Remember to call "delete" on your dynmically allocated arrays
    // such that you don't suffer from memory leaks. e.g.
    // delete arr;
    
    return 0;
}















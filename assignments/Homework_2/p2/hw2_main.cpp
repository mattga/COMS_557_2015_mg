//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>

// include local files
#include "controls.h"
#include "HCI557Common.h"

using namespace std;

static const string vs_string = "#version 410 core                                                 \n"
                                "                                                                   \n"
                                "uniform mat4 projectionMatrix;                                    \n"
                                "uniform mat4 viewMatrix;                                           \n"
                                "uniform mat4 modelMatrix;                                          \n"
                                "in vec3 in_Position;                                               \n"
                                "                                                                   \n"
                                "in vec3 in_Color;                                                  \n"
                                "out vec3 pass_Color;                                               \n"
                                "                                                                  \n"
                                "void main(void)                                                   \n"
                                "{                                                                 \n"
                                "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
                                "    pass_Color = in_Color;                                         \n"
                                "}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the
// inside of our triangle specified by our vertex shader.
static const string fs_string = "#version 410 core                                                 \n"
                                "                                                                  \n"
                                "in vec3 pass_Color;                                                 \n"
                                "out vec4 color;                                                    \n"
                                "void main(void)                                                   \n"
                                "{                                                                 \n"
                                "    color = vec4(pass_Color, 1.0);                               \n"
                                "}                                                                 \n";

/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix;       // Store the view matrix
glm::mat4 modelMatrix;      // Store the model matrix

// The handle to the window object
GLFWwindow *window;

// Define some of the global variables we're using for this sample
GLuint program;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];
unsigned int vboID1[2], vboID2[2];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 
 MATTHEW GARDNER
 */
static float *blue = new float[3]{.0706, .404, .98};

void setColor(float* colors, int i, float* color) {
	colors[i] = color[0];
	colors[i+1] = color[1];
	colors[i+2] = color[2];
}

unsigned int createTriangleStripModel(void)
{
	const int numVert = 126;
    float *vertices = new float[numVert];
	float *colors   = new float[numVert];
	float *blue2 = new float[3];
	float d;

	// f1
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[0] = -2.; vertices[1] = 0.; vertices[2] = -1.; setColor(colors, 0, blue2);// 1
	vertices[3] = -2.; vertices[4] = 0.; vertices[5] = 0.; setColor(colors, 3, blue2);// 2
	vertices[6] = -2.; vertices[7] = -1.; vertices[8] = -1.; setColor(colors, 6, blue2);// 3
	vertices[9] = -2.; vertices[10] = -1.; vertices[11] = 0.; setColor(colors, 9, blue2);// 4

	// f2
	d = .9;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[12] = 0.; vertices[13] = -1.; vertices[14] = -1.; setColor(colors, 12, blue2);// 5
	vertices[15] = 0.; vertices[16] = -1.; vertices[17] = 0.; setColor(colors, 15, blue2);// 6
	
	// f3
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[18] = 0.; vertices[19] = 1.; vertices[20] = -1.; setColor(colors, 18, blue2);// 7
	vertices[21] = 0.; vertices[22] = 1.; vertices[23] = 0.; setColor(colors, 21, blue2);// 8
	
	// f4
	d = .93;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[24] = 1.; vertices[25] = 1.; vertices[26] = -1.; setColor(colors, 24, blue2);// 9
	vertices[27] = 1.; vertices[28] = 1.; vertices[29] = 0.; setColor(colors, 27, blue2);// 10
	
	// f4
	d = .93;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[30] = 1.; vertices[31] = 1.; vertices[32] = -1.; setColor(colors, 30, blue2);// 11
	vertices[33] = 1.; vertices[34] = 1.; vertices[35] = 0.; setColor(colors, 33, blue2);// 12
	
	// f5
	d = .93;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[36] = 1.; vertices[37] = -1.; vertices[38] = -1.; setColor(colors, 36, blue2);// 13
	vertices[39] = 1.; vertices[40] = -1.; vertices[41] = 0.; setColor(colors, 39, blue2);// 14
	vertices[42] = 1.; vertices[43] = 1.; vertices[44] = 0.; setColor(colors, 42, blue2);// 15
	
	// f6
	d = .93;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[45] = 1.; vertices[46] = -1.; vertices[47] = 2.; setColor(colors, 45, blue2);// 16
	vertices[48] = 1.; vertices[49] = 0.; vertices[50] = 2.; setColor(colors, 48, blue2);// 17
	
	// f7
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[51] = 0.; vertices[52] = -1.; vertices[53] = 2.; setColor(colors, 51, blue2);// 18
	vertices[54] = 0.; vertices[55] = 0.; vertices[56] = 2.; setColor(colors, 54, blue2);// 19
	
	// f8
	d = .95;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[57] = 0.; vertices[58] = 1.; vertices[59] = 0.; setColor(colors, 57, blue2);// 20
	vertices[60] = 1.; vertices[61] = 0.; vertices[62] = 2.; setColor(colors, 60, blue2);// 21
	vertices[63] = 1.; vertices[64] = 1.; vertices[65] = 0.; setColor(colors, 63, blue2);// 22
	vertices[66] = 0.; vertices[67] = 1.; vertices[68] = 0.; setColor(colors, 66, blue2);// 23
	vertices[69] = 0.; vertices[70] = 0.; vertices[71] = 2.; setColor(colors, 69, blue2);// 24
	
	// f9
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[72] = 0.; vertices[73] = -1.; vertices[74] = 0.; setColor(colors, 72, blue2);// 25
	vertices[75] = 0.; vertices[76] = -1.; vertices[77] = 2.; setColor(colors, 75, blue2);// 26
	
	// f10
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[78] = 1.; vertices[79] = -1.; vertices[80] = 0.; setColor(colors, 78, blue2);// 27
	vertices[81] = 1.; vertices[82] = -1.; vertices[83] = 2.; setColor(colors, 81, blue2);// 28
	
	// f11
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[84] = 0.; vertices[85] = -1.; vertices[86] = 2.; setColor(colors, 84, blue2);// 29
	vertices[87] = 1.; vertices[88] = -1.; vertices[89] = -1.; setColor(colors, 87, blue2);// 30
	vertices[90] = 0.; vertices[91] = -1.; vertices[92] = -1.; setColor(colors, 90, blue2);// 31
	
	// f12
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[93] = 1.; vertices[94] = -1.; vertices[95] = -1.; setColor(colors, 93, blue2);// 32
	vertices[96] = 0.; vertices[97] = 1.; vertices[98] = -1.; setColor(colors, 96, blue2);// 33
	vertices[99] = 0.; vertices[100] = -1.; vertices[101] = -1.; setColor(colors, 99, blue2);// 34
	vertices[102] = 0.; vertices[103] = 0.; vertices[104] = -1.; setColor(colors, 102, blue2);// 35
	
	// f13
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[105] = -2.; vertices[106] = -1.; vertices[107] = -1.; setColor(colors, 105, blue2);// 36
	vertices[108] = -2.; vertices[109] = 0.; vertices[110] = -1.; setColor(colors, 108, blue2);// 37
	vertices[111] = 0.; vertices[112] = 0.; vertices[113] = -1.; setColor(colors, 111, blue2);// 38
	
	// f14
	d = .9;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[114] = -2.; vertices[115] = 0.; vertices[116] = 0.; setColor(colors, 114, blue2);// 39
	vertices[117] = 0.; vertices[118] = 0.; vertices[119] = 0.; setColor(colors, 117, blue2);// 40
	
	// f15
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[120] = -2.; vertices[121] = -1.; vertices[122] = 0.; setColor(colors, 120, blue2);// 41
	vertices[123] = 0.; vertices[124] = -1.; vertices[125] = 0.; setColor(colors, 123, blue2);// 42
	
    glGenVertexArrays(2, &vaoID[0]);
	glBindVertexArray(vaoID[0]);
	glGenBuffers(2, vboID1);
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID1[0]);
	glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, vboID1[1]);
	glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(GL_FLOAT), colors, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
	delete [] vertices;
	delete [] colors;
	delete [] blue2;
	
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 
 MATTHEW GARDNER
 */
unsigned int createMyModel(void)
{
	const int numVert = 252;
	float *vertices = new float[numVert];
	float *colors   = new float[numVert];
	float *blue2 = new float[3];
	float d;
	
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[0] = -2.; vertices[1] = 0.; vertices[2] = -1.; setColor(colors, 0, blue2);
	vertices[3] = -2.; vertices[4] = -1.; vertices[5] = 0.; setColor(colors, 3, blue2);
	vertices[6] = -2.; vertices[7] = -1.; vertices[8] = -1.; setColor(colors, 6, blue2);
	vertices[9] = -2.; vertices[10] = 0.; vertices[11] = -1.; setColor(colors, 9, blue2);
	vertices[12] = -2.; vertices[13] = -1.; vertices[14] = 0.; setColor(colors, 12, blue2);
	vertices[15] = -2.; vertices[16] = 0.; vertices[17] = 0.; setColor(colors, 15, blue2);
	
	d = .90;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[18] = 0.; vertices[19] = -1.; vertices[20] = 0.; setColor(colors, 18, blue2);
	vertices[21] = -2.; vertices[22] = -1.; vertices[23] = 0.; setColor(colors, 21, blue2);
	vertices[24] = 0.; vertices[25] = -1.; vertices[26] = -1.; setColor(colors, 24, blue2);
	vertices[27] = -2.; vertices[28] = -1.; vertices[29] = 0.; setColor(colors, 27, blue2);
	vertices[30] = 0.; vertices[31] = -1.; vertices[32] = -1.; setColor(colors, 39, blue2);
	vertices[33] = -2.; vertices[34] = -1.; vertices[35] = -1.; setColor(colors, 33, blue2);
	
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[36] = -2.; vertices[37] = 0.; vertices[38] = -1.; setColor(colors, 36, blue2);
	vertices[39] = -2.; vertices[40] = -1.; vertices[41] = -1.; setColor(colors, 39, blue2);
	vertices[42] = 0.; vertices[43] = 0.; vertices[44] = -1.; setColor(colors, 42, blue2);
	vertices[45] = -2.; vertices[46] = -1.; vertices[47] = -1.; setColor(colors, 45, blue2);
	vertices[48] = 0.; vertices[49] = 0.; vertices[50] = -1.; setColor(colors, 48, blue2);
	vertices[51] = 0.; vertices[52] = -1.; vertices[53] = -1.; setColor(colors, 51, blue2);
	
	d = .8;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[54] = 0.; vertices[55] = 1.; vertices[56] = -1.; setColor(colors, 54, blue2);
	vertices[57] = 0.; vertices[58] = -1.; vertices[59] = -1.; setColor(colors, 57, blue2);
	vertices[60] = 0.; vertices[61] = 1.; vertices[62] = 0.; setColor(colors, 60, blue2);
	vertices[63] = 0.; vertices[64] = -1.; vertices[65] = -1.; setColor(colors, 63, blue2);
	vertices[66] = 0.; vertices[67] = 1.; vertices[68] = 0.; setColor(colors, 66, blue2);
	vertices[69] = 0.; vertices[70] = -1.; vertices[71] = 0.; setColor(colors, 69, blue2);
	
	vertices[72] = 0.; vertices[73] = 1.; vertices[74] = 0.; setColor(colors, 72, blue2);
	vertices[75] = 0.; vertices[76] = -1.; vertices[77] = 0.; setColor(colors, 75, blue2);
	vertices[78] = 0.; vertices[79] = 0.; vertices[80] = 2.; setColor(colors, 78, blue2);
	vertices[81] = 0.; vertices[82] = -1.; vertices[83] = 0.; setColor(colors, 81, blue2);
	vertices[84] = 0.; vertices[85] = 0.; vertices[86] = 2.; setColor(colors, 84, blue2);
	vertices[87] = 0.; vertices[88] = -1.; vertices[89] = 2.; setColor(colors, 87, blue2);
	
	d = .90;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[90] = -2.; vertices[91] = 0.; vertices[92] = -1.; setColor(colors, 90, blue2);
	vertices[93] = -2.; vertices[94] = 0.; vertices[95] = 0.; setColor(colors, 93, blue2);
	vertices[96] = 0.; vertices[97] = 0.; vertices[98] = -1.; setColor(colors, 96, blue2);
	vertices[99] = -2.; vertices[100] = 0.; vertices[101] = 0.; setColor(colors, 99, blue2);
	vertices[102] = 0.; vertices[103] = 0.; vertices[104] = -1.; setColor(colors, 102, blue2);
	vertices[105] = 0.; vertices[106] = 0.; vertices[107] = 0.; setColor(colors, 105, blue2);
	
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[108] = -2.; vertices[109] = 0.; vertices[110] = 0.; setColor(colors, 108, blue2);
	vertices[111] = -2.; vertices[112] = -1.; vertices[113] = 0.; setColor(colors, 111, blue2);
	vertices[114] = 0.; vertices[115] = 0.; vertices[116] = 0.; setColor(colors, 114, blue2);
	vertices[117] = -2.; vertices[118] = -1.; vertices[119] = 0.; setColor(colors, 117, blue2);
	vertices[120] = 0.; vertices[121] = 0.; vertices[122] = 0.; setColor(colors, 120, blue2);
	vertices[123] = 0.; vertices[124] = -1.; vertices[125] = 0.; setColor(colors, 123, blue2);
	
	vertices[126] = 0.; vertices[127] = 1.; vertices[128] = -1.; setColor(colors, 126, blue2);
	vertices[129] = 0.; vertices[130] = -1.; vertices[131] = -1.; setColor(colors, 129, blue2);
	vertices[132] = 1.; vertices[133] = 1.; vertices[134] = -1.; setColor(colors, 132, blue2);
	vertices[135] = 0.; vertices[136] = -1.; vertices[137] = -1.; setColor(colors, 135, blue2);
	vertices[138] = 1.; vertices[139] = 1.; vertices[140] = -1.; setColor(colors, 138, blue2);
	vertices[141] = 1.; vertices[142] = -1.; vertices[143] = -1.; setColor(colors, 141, blue2);
	
	d = .9;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[144] = 0.; vertices[145] = 1.; vertices[146] = -1.; setColor(colors, 144, blue2);
	vertices[147] = 0.; vertices[148] = 1.; vertices[149] = 0.; setColor(colors, 147, blue2);
	vertices[150] = 1.; vertices[151] = 1.; vertices[152] = -1.; setColor(colors, 150, blue2);
	vertices[153] = 0.; vertices[154] = 1.; vertices[155] = 0.; setColor(colors, 153, blue2);
	vertices[156] = 1.; vertices[157] = 1.; vertices[158] = -1.; setColor(colors, 156, blue2);
	vertices[159] = 1.; vertices[160] = 1.; vertices[161] = 0.; setColor(colors, 159, blue2);
	
	d = .95;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[162] = 0.; vertices[163] = 1.; vertices[164] = 0.; setColor(colors, 162, blue2);
	vertices[165] = 1.; vertices[166] = 1.; vertices[167] = 0.; setColor(colors, 165, blue2);
	vertices[168] = 0.; vertices[169] = 0.; vertices[170] = 2.; setColor(colors, 168, blue2);
	vertices[171] = 1.; vertices[172] = 1.; vertices[173] = 0.; setColor(colors, 171, blue2);
	vertices[174] = 0.; vertices[175] = 0.; vertices[176] = 2.; setColor(colors, 174, blue2);
	vertices[177] = 1.; vertices[178] = 0.; vertices[179] = 2.; setColor(colors, 177, blue2);
	
	d = 1.;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[180] = 0.; vertices[181] = 0.; vertices[182] = 2.; setColor(colors, 180, blue2);
	vertices[183] = 0.; vertices[184] = -1.; vertices[185] = 2.; setColor(colors, 183, blue2);
	vertices[186] = 1.; vertices[187] = 0.; vertices[188] = 2.; setColor(colors, 186, blue2);
	vertices[189] = 0.; vertices[190] = -1.; vertices[191] = 2.; setColor(colors, 189, blue2);
	vertices[192] = 1.; vertices[193] = 0.; vertices[194] = 2.; setColor(colors, 192, blue2);
	vertices[195] = 1.; vertices[196] = -1.; vertices[197] = 2.; setColor(colors, 195, blue2);
	
	d = .90;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[198] = 1.; vertices[199] = -1.; vertices[200] = 2.; setColor(colors, 198, blue2);
	vertices[201] = 0.; vertices[202] = -1.; vertices[203] = 2.; setColor(colors, 201, blue2);
	vertices[204] = 1.; vertices[205] = -1.; vertices[206] = -1.; setColor(colors, 204, blue2);
	vertices[207] = 0.; vertices[208] = -1.; vertices[209] = 2.; setColor(colors, 207, blue2);
	vertices[210] = 1.; vertices[211] = -1.; vertices[212] = -1.; setColor(colors, 210, blue2);
	vertices[213] = 0.; vertices[214] = -1.; vertices[215] = -1.; setColor(colors, 213, blue2);
	
	d = .93;
	blue2[0] = d*blue[0]; blue2[1] = d*blue[1]; blue2[2] = d*blue[2];
	vertices[216] = 1.; vertices[217] = 1.; vertices[218] = -1.; setColor(colors, 216, blue2);
	vertices[219] = 1.; vertices[220] = -1.; vertices[221] = -1.; setColor(colors, 219, blue2);
	vertices[222] = 1.; vertices[223] = 1.; vertices[224] = 0.; setColor(colors, 222, blue2);
	vertices[225] = 1.; vertices[226] = -1.; vertices[227] = -1.; setColor(colors, 225, blue2);
	vertices[228] = 1.; vertices[229] = 1.; vertices[230] = 0.; setColor(colors, 228, blue2);
	vertices[231] = 1.; vertices[232] = -1.; vertices[233] = 0.; setColor(colors, 231, blue2);
	
	vertices[234] = 1.; vertices[235] = 1.; vertices[236] = 0.; setColor(colors, 234, blue2);
	vertices[237] = 1.; vertices[238] = -1.; vertices[239] = 0.; setColor(colors, 237, blue2);
	vertices[240] = 1.; vertices[241] = 0.; vertices[242] = 2.; setColor(colors, 240, blue2);
	vertices[243] = 1.; vertices[244] = -1.; vertices[245] = 0.; setColor(colors, 243, blue2);
	vertices[246] = 1.; vertices[247] = 0.; vertices[248] = 2.; setColor(colors, 246, blue2);
	vertices[249] = 1.; vertices[250] = -1.; vertices[251] = 2.; setColor(colors, 249, blue2);
	
	glBindVertexArray(vaoID[1]);
	glGenBuffers(2, vboID2);
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID2[0]);
	glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, vboID2[1]);
	glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(GL_FLOAT), colors, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
	
	delete [] vertices;
	delete [] colors;
	delete [] blue2;
	
    return 1;
}

/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void) {
	glBindVertexArray(vaoID[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 42);
	glBindVertexArray(0);
}

/*!
 ADD YOUR CODE TO RENDER YOUR MODEL TO THIS FUNCTION
 */
void renderMyModel(void) {
	glBindVertexArray(vaoID[1]);
	glDrawArrays(GL_TRIANGLES, 0, 84);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 This function creates the two models
 */
void setupScene(void)
{
    createTriangleStripModel();
    createMyModel();
}

/*!
 This function updates the virtual camera
 */
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix = getViewMatrix(); // get the current view matrix

    return true;
}

int main(int argc, const char *argv[])
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew

    // Init the GLFW Window
    window = initWindow();

    // Init the glew api
    initGlew();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here

    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char *vs_source    = vertex_code.c_str();

    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the
    // inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char *fs_source      = fragment_code.c_str();

    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();

    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);

    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera

    // Set up our green background color
    static const GLfloat clear_color[] = {0.6f, 0.7f, 1.0f, 1.0f};
    static const GLfloat clear_depth[] = {1.0f, 1.0f, 1.0f, 1.0f};

    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    int projectionMatrixLocation =
        glGetUniformLocation(program, "projectionMatrix");                  // Get the location of our projection matrix in the shader
    int viewMatrixLocation  = glGetUniformLocation(program, "viewMatrix");  // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);             // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);           // Send our model matrix to the shader

    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");

    //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // this creates the scene
    setupScene();

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);

    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while (!glfwWindowShouldClose(window)) {
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, clear_depth);

        // update the virtual camera
        // ignore this line since we did not introduced cameras.
        updateCamera();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);

        // this changes the camera location
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

        renderTriangleStripModel();

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

        renderMyModel();

        glUseProgram(0);
        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

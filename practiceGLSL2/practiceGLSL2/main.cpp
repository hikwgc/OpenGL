//
//  main.cpp
//  practiceGLSL2
//
//  Created by 川口大志 on 2014/07/22.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include <iostream>
#include "GL/glew.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using glm::mat4;
using glm::vec3;
#include "glm/gtc/matrix_transform.hpp"

//#include <GLUT/glut.h>
/*
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
*/
#include <fstream>
using std::ifstream;


int width, height;
GLuint vboHandles[2];
GLuint vaoHandle;

void getInfo() {
    /*
     glm::vec4 position = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
     glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
     glm::mat4 model = glm::mat4(1.0f);
     model = glm::rotate(model, 90.0f,  glm::vec3(0.0f, 1.0f, 0.0));
     
     glm::mat4 mv = view * model;
     
     glm::vec4 transformed = mv * position;
     */
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *vendor   = glGetString(GL_VENDOR);
    const GLubyte *version  = glGetString(GL_VERSION);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    
    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version(string) : %s\n", version);
    printf("GL Version(integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);
    
}

const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    /*
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
     */
    std::string filetext;
    
    while( shader_file.good() ) {
        std::string line;
        std::getline(shader_file, line);
        filetext.append(line + "\n");
    }
    
    return filetext.c_str();
}

void loadShader(GLuint &pHandle) {
    GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
    const GLchar *shaderCode = loadShaderAsString("/Users/kawaguchihiroshi/Developer/practice/OpenGL/practiceGLSL2/practiceGLSL2/basic_block.vert");
    const GLchar *codeArray[] = {shaderCode};
    glShaderSource( vertShader, 1, codeArray, NULL);
    
    glCompileShader(vertShader);
    
    GLint result;
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &result );
    if(GL_FALSE==result) {
        fprintf(stderr, "miss\n");
        
        GLint logLen;
        glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            char *log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(vertShader, logLen, &written, log);
            fprintf(stderr, "shader log: \n%s", log);
            free(log);
        }
    }
    
    GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
    const GLchar *shaderCode2 = loadShaderAsString("/Users/kawaguchihiroshi/Developer/practice/OpenGL/practiceGLSL2/practiceGLSL2/basic_block.frag");
    const GLchar *codeArray2[] = {shaderCode2};
    glShaderSource( fragShader, 1, codeArray2, NULL);
    
    glCompileShader(fragShader);
    
    GLint result2;
    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &result2 );
    if(GL_FALSE==result2) {
        fprintf(stderr, "miss2\n");
        
        GLint logLen;
        glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            char *log = (char *)malloc(logLen);
            GLsizei written;
            glGetShaderInfoLog(fragShader, logLen, &written, log);
            fprintf(stderr, "shader log: \n%s", log);
            free(log);
        }
    }
    
    GLuint programHandle = glCreateProgram();
    
    if(0==programHandle){
        fprintf(stderr, "object error\n");
    }
    
    //glBindAttribLocation(programHandle, 0, "VertexPosition");
    //glBindAttribLocation(programHandle, 1, "VertexColor");
    
    glAttachShader(programHandle, vertShader);
    glAttachShader(programHandle, fragShader);
    
    glLinkProgram(programHandle);
    GLint status;
    glGetProgramiv(programHandle,GL_LINK_STATUS, &status);
    if(GL_FALSE==status ) {
        fprintf(stderr, "error\n");
        
        GLint logLen;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0) {
            char *log = (char*)malloc(logLen);
            GLsizei written;
        
            
            glGetProgramInfoLog(programHandle, logLen, &written, log);
            fprintf(stderr, "program log: \n%s", log);
            free(log);
        }
        
    }
    else {
        std::cout << "liking is succeeded" << std::endl;
        glUseProgram(programHandle);
        
    }
    
    // -----------print
    GLint nUniforms, size, location, maxLen;
    GLchar * name;
    GLsizei written;
    GLenum type;
    
    glGetProgramiv( programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv( programHandle, GL_ACTIVE_UNIFORMS, &nUniforms);
    
    name = (GLchar *) malloc( maxLen );
    
    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nUniforms; ++i ) {
        glGetActiveUniform( programHandle, i, maxLen, &written, &size, &type, name );
        location = glGetUniformLocation(programHandle, name);
        printf(" %-8d | %s\n",location, name);
    }
    
    free(name);
    
    // -----------------block
    GLuint blockIndex = glGetUniformBlockIndex(programHandle, "BlobSettings");
    GLint blockSize;
    glGetActiveUniformBlockiv(programHandle,blockIndex,GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    GLubyte * blockBuffer = (GLubyte *) malloc(blockSize);
    
    const GLchar *names[] = {
        "InnerColor",
        "OuterColor",
        "RadiusInner",
        "RadiusOuter"
    };
    GLuint indices[4];
    glGetUniformIndices(programHandle, 4, names, indices);
    
    GLint offset[4];
    glGetActiveUniformsiv(programHandle, 4, indices, GL_UNIFORM_OFFSET, offset);
    
    GLfloat outerColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat innerColor[] = {1.0f, 1.0f, 0.75f, 1.0f};
    GLfloat innerRadius = 0.25f, outerRadius = 0.45f;
    
    memcpy(blockBuffer+offset[0], innerColor, 4*sizeof(GLfloat));
    memcpy(blockBuffer+offset[1], outerColor, 4*sizeof(GLfloat));
    memcpy(blockBuffer+offset[2], &innerRadius, sizeof(GLfloat));
    memcpy(blockBuffer+offset[3], &outerRadius, sizeof(GLfloat));
    
    GLuint uboHandle;
    glGenBuffers(1, &uboHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle);
    
    pHandle = programHandle;
}

void createData() {
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.8f,  0.8f, 0.0f,
        -0.8f, -0.8f, 0.0f,
        0.8f, 0.8f, 0.0f,
        -0.8f, 0.8f, 0.0f
    };
    float colorData[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    
    
    // Create and populate the buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), positionData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colorData, GL_STATIC_DRAW);
    
    // Create and set-up the vertex array object
    glGenVertexArrays(1 , &vaoHandle );
    glBindVertexArray(vaoHandle);
    
    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, const char * argv[])
{
    // Initialize the library
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "cant open Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW err: %s\n", glewGetErrorString(err));
    }

    GLuint pHandle;
    getInfo();
    loadShader(pHandle);
    createData();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        /*
        mat4 rotationMatrix = glm::rotate(mat4(1.0f), 90.0f, vec3(0.0f,0.0f,1.0f));
        
        GLuint location = glGetUniformLocation(pHandle, "RotationMatrix");
        if (location >= 0) {
            glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        }
        */
        
        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
    
}


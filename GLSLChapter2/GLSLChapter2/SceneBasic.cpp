//
//  SceneBasic.cpp
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include "SceneBasic.h"

void SceneBasic::initScene() {
    if(!prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/basic.vert", GLSLShader::VERTEX)) {
        printf("vertex cant compile\n%s", prog.log().c_str());
        exit(1);
    }
    if(!prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/basic.frag", GLSLShader::FRAGMENT)) {
        printf("fragment cant compile\n%s", prog.log().c_str());
        exit(1);
    }
    
    if (!prog.link()) {
        printf("link error\n%s", prog.log().c_str());
        exit(1);
    }
    
    prog.use();
    prog.printActiveUniforms();
    prog.printActiveAttribs();
    
    angle = 90.0f;
    prog.setUniform("RotationMatrix", glm::rotate(mat4(1.0f), angle, vec3(0.0f, 0.0f, 1.0f)));
    
    createData();
}

void SceneBasic::createData() {
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f,  0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    // Create and populate the buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);
    
    // Create and set-up the vertex array object
    glGenVertexArrays(1 , &vaoHandle );
    glBindVertexArray(vaoHandle);
    
    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
}

void SceneBasic::update(float t) {
    angle += 1.0f;
    prog.setUniform("RotationMatrix", glm::rotate(mat4(1.0f), angle, vec3(0.0f, 0.0f, 1.0f)));
}

void SceneBasic::render() {
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

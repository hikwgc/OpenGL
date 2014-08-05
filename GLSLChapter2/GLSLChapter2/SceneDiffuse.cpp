//
//  SceneDiffuse.cpp
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include "SceneDiffuse.h"
void SceneDiffuse::initScene() {
    compileAndLinkShader();
    
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    
    torus = new VBOTorus(0.7f, 0.3f, 30, 30);
    
    model = mat4(1.0f);
    model = glm::rotate(model,-35.0f, vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model,35.0f, vec3(0.0f,1.0f,0.0f));
    view = glm::lookAt(vec3(0.0f,0.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    //projection = mat4(1.0f);
    projection = glm::perspective(90.0f, 800.0f/600.0f, 0.1f, 100.0f);
    
    prog.setUniform("Kd", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("LightPosition", view * vec4(5.0f,5.0f,2.0f,1.0f) );
    //prog.setUniform("RotationMatrix", glm::rotate(mat4(1.0f), 0.0f, vec3(0.0f, 0.0f, 1.0f)));
}

void SceneDiffuse::update(float t) {

}

void SceneDiffuse::render() {
    setMatrices();
    torus->render();
    
}

void SceneDiffuse::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneDiffuse::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneDiffuse::compileAndLinkShader()
{
    if(!prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/diffuse.vert", GLSLShader::VERTEX)) {
        printf("vertex cant compile\n%s", prog.log().c_str());
        exit(1);
    }
    if(!prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/diffuse.frag", GLSLShader::FRAGMENT)) {
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


}

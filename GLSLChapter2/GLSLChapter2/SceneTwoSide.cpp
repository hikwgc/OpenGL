//
//  SceneTwoSide.cpp
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/08/01.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include "SceneTwoSide.h"

SceneTwoSide::SceneTwoSide() : angle(0.0f)
{
}

void SceneTwoSide::initScene()
{
    compileAndLinkShader();
    
    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    
    mat4 transform = glm::translate(mat4(1.0f),vec3(0.0f,1.5f,0.25f));
    teapot = new VBOTeapot(13, transform);
    
    view = glm::lookAt(vec3(2.0f,4.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    //projection = mat4(1.0f);
    projection = glm::perspective(70.0f, 800.0f/600.0f, 0.3f, 100.0f);
    
    prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Shininess", 100.0f);
}

void SceneTwoSide::update( float t )
{
    //angle += 1.0f;
    //if( angle > 360.0 ) angle -= 360.0;
}

void SceneTwoSide::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    vec4 worldLight = vec4(2.0f,4.0f,2.0f,1.0f);
    model = glm::rotate(model, angle, vec3(0.0f,1.0f,0.0f));
    prog.setUniform("Light.Position", view * model * worldLight );
    
    model = mat4(1.0f);
    model = glm::translate(model,vec3(0.0,-1.0,0.0));
    model = glm::rotate(model, -90.0f, vec3(1.0f,0.0f,0.0f));
    //model *= glm::rotate(140.0f, vec3(0.0f,1.0f,0.0f));
    
    setMatrices();
    teapot->render();
}

void SceneTwoSide::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);
}

void SceneTwoSide::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(70.0f, (float)w/h, 0.3f, 100.0f);
}

void SceneTwoSide::compileAndLinkShader()
{
    if( ! prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/twoside.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("/Users/kawaguchihiroshi/Developer/practice/OpenGL/GLSLChapter2/GLSLChapter2/twoside.frag",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    /*
    if( ! prog.validate() )
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }*/
    
    prog.use();
}
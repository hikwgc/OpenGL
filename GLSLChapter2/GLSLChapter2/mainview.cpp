//
//  mainview.cpp
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#include "mainview.h"
#include "SceneBasic.h"
#include "SceneDiffuse.h"
#include "SceneADS.h"
#include "SceneTwoSide.h"
#include "SceneSubroutine.h"
#include "SceneDiscard.h"

mainview::mainview() {
    if (!glfwInit()) exit(1);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //////////////// PLUG IN SCENE HERE /////////////////
    scene = new SceneDiscard();
    ////////////////////////////////////////////////////

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "cant open Window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW err: %s\n", glewGetErrorString(err));
    }
    
    scene->initScene();
}

void mainview::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //scene->update(0.0f);
        scene->render();
                
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void mainview::exitview() {
    glfwTerminate();
}

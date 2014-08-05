//
//  mainview.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__mainview__
#define __GLSLChapter2__mainview__

#include <iostream>
#include "GL/glew.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Scene.h"

class mainview {
private:
    Scene *scene;
public:
    mainview();
    void draw();
    void exitview();
    
    GLFWwindow* window;

};

#endif /* defined(__GLSLChapter2__mainview__) */

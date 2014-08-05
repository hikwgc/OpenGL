//
//  SceneDiffuse.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__SceneDiffuse__
#define __GLSLChapter2__SceneDiffuse__

#include <iostream>
#include "Scene.h"
#include "vbotorus.h"
#include <glm/glm.hpp>

class SceneDiffuse: public Scene {
    GLSLProgram prog;
    int width, height;
    VBOTorus *torus;
    
    mat4 model;
    mat4 view;
    mat4 projection;
    
    void setMatrices();
    void compileAndLinkShader();
    
public:
    SceneDiffuse(){};
    void initScene();
    void update(float t);
    void render();
    void resize(int w, int h);
    
    void createData();
    
    GLuint vaoHandle;
};

#endif /* defined(__GLSLChapter2__SceneDiffuse__) */

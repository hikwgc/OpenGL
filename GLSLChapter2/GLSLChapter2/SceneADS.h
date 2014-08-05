//
//  SceneADS.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/08/01.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__SceneADS__
#define __GLSLChapter2__SceneADS__

#include <iostream>
#include "scene.h"
#include "vbotorus.h"

class SceneADS : public Scene
{
private:
    GLSLProgram prog;
    
    int width, height;
    VBOTorus *torus;
    float angle;
    
    mat4 model;
    mat4 view;
    mat4 projection;
    
    void setMatrices();
    void compileAndLinkShader();
    
public:
    SceneADS();
    
    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};
#endif /* defined(__GLSLChapter2__SceneADS__) */

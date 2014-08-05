//
//  SceneBasic.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__SceneBasic__
#define __GLSLChapter2__SceneBasic__

#include <iostream>
#include "Scene.h"


class SceneBasic: public Scene {
    GLSLProgram prog;
public:
    SceneBasic(){};
    void initScene();
    void update(float t);
    void render();
    
    void createData();
    
    GLuint vaoHandle;
    float angle;
};


#endif /* defined(__GLSLChapter2__SceneBasic__) */

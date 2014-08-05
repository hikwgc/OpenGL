//
//  Scene.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__Scene__
#define __GLSLChapter2__Scene__

#include "GL/glew.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using glm::mat4;
using glm::vec3;
#include "glm/gtc/matrix_transform.hpp"
#include "GLSLProgram.h"

class Scene {
public:
    virtual void initScene() = 0;
    
    virtual void update( float t ) = 0;
    
    virtual void render() = 0;
    
};


#endif /* defined(__GLSLChapter2__Scene__) */

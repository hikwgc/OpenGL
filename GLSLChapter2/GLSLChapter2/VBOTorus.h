//
//  VBOTorus.h
//  GLSLChapter2
//
//  Created by 川口大志 on 2014/07/31.
//  Copyright (c) 2014年 川口大志. All rights reserved.
//

#ifndef __GLSLChapter2__VBOTorus__
#define __GLSLChapter2__VBOTorus__

class VBOTorus {
private:
    unsigned int vaoHandle;
    int faces, rings, sides;
    
    void generateVerts(float * , float * ,float *, unsigned int *,
                       float , float);
    
public:
    VBOTorus(float, float, int, int);
    
    void render() const;
};
#endif /* defined(__GLSLChapter2__VBOTorus__) */

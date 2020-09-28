/* 
 * File:   Agent.h
 * Author: Marcelo Zamith
 *
 * Created on June 18, 2010, 11:51 AM
 */

#ifndef _AGENT_H
#define	_AGENT_H
#include <GL/glew.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/glut.h>
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif
#include "ImageTGA.h"
#include <cstdlib>
#include <cstdio>
enum STATE { WEAK, STRONG };
class Agent {
public:
    const int MAXSPEED = 12;
    
    Agent();
    virtual ~Agent();

    virtual void reset(void);
    virtual void updated(float) = 0 ;
    virtual void render(void) = 0;
    virtual void back(void) = 0;
    virtual void resurrect (void);
    void print(void);
    void up(void){VY++; };
    void down(void){VY--;};
    void left(void){VX--;};
    void right(void){VX++;};
    
    float VX,
          VY,
          X,
          Y,
          mSpeed,
          mMinX,
          mMaxX,
          mMinY,
          mMaxY,
          mSize,
          mRaio,
          X1,
          Y1,
          Xi,
          Yi,
          mAngle,
          mRatio;
          
    int mLives,
        mMyState;

    bool mAnimated;

    TextureImage mTexture;
    
    bool mDebug;

};

#endif	/* _AGENT_H */


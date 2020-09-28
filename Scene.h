#ifndef _SCENE_H_
#define _SCENE_H_
#include <string>
#include <GL/glew.h>    
#include <Agent.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
  #include <OpenGL/gl.h>
#else
  
  #include <GL/glut.h>
  #include <GL/glu.h>
  #include <GL/gl.h>
#endif
#include <AStar.h>
class Scene{
public:
    Scene();
    ~Scene();
    void load(std::string);
    void render(void);
    bool testCollision(Agent *);
    int getPosition(int x, int y);
   
    void setCloseList(stNode *s){mCloseList = s;}
    int getWidth(void) {return width; }
    int getHeight(void) {return height; }
    void renderCloseList2(void);
    
private:
    void tile(bool = true);
    void renderCloseList(void);
    int  width,
         height, 
         *scene;

    stNode *mCloseList;
};

#endif

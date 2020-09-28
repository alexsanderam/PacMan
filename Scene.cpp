#include <Scene.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <climits>
using namespace std;
Scene:: Scene():
    width(0),
    height(0),
    scene(NULL),
    mCloseList(NULL){}

Scene::~Scene(){
    if (scene != NULL)
        delete[] scene;
    
    if (mCloseList != NULL)
        destroyList(&mCloseList);
}

void Scene::load(std::string fileName){
    
   fstream input;
   input.open(fileName.c_str(), fstream::in);
   assert(input.is_open());
   input >> width;
   input >> height;
   
   cout << "Scene: " << width << " x " << height << endl;
   scene = new int [width * height];
   int i = 0;
   while (!input.eof()){

     int y = i / width;
     int x = i % width;
     y = height - 1 - y;
     int k = y * width + x;
     input >> scene[k];

     i++;
   }
    
   input.close();
    
}
   
void Scene::render(void){
        float dX = 0.0f;
        float dY  = 0.0f;
        
        glDisable(GL_TEXTURE_2D);
        for (int j = 0; j < height; j++){

          for (int i = 0; i < width; i++){
             
            //dY += static_cast<float>(scene.height);
              int  p = j *width + i;
              if (scene[p] == 1){
                  glPushMatrix();
                  glTranslatef(dX, dY, 0.0f);
                    
                  tile(true);
                  glPopMatrix();
                 
              }//;end-if (scene.scene[i] == 1){
           
              dX += 1.0f;
          }//end-for (int j = 0; i < scene.height; i++){
              dX = 0.0f;
              dY += 1.0f;
        }//end-for (int i = 0; i <  scene.width; i++){

        renderCloseList();
};

bool Scene:: testCollision(Agent *a){
    int iX,
        iY,
        p;

    iX = static_cast <int> (a->mMaxX),
    iY = static_cast <int> (a->Y);
    p = iY * width + iX;
    p = scene[p];
    if (p > 0)
        return true;

    iX = static_cast <int> (a->mMinX),
    iY = static_cast <int> (a->Y);
    p = iY * width + iX;
    p = scene[p];
    if (p > 0)
        return true;



    iX = static_cast <int> (a->X),
    iY = static_cast <int> (a->mMaxY);
    p = iY * width + iX;
    p = scene[p];
    if (p > 0)
        return true;


    iX = static_cast <int> (a->X),
    iY = static_cast <int> (a->mMinY);
    p = iY * width + iX;
    p = scene[p];
    if (p > 0)
        return true;
   

    return false;
}

int  Scene::getPosition(int x, int y){
    int value  = 1;
    int p = y*width + x;

    if(  (x >= 0) && (y >= 0) && (x < width) && (y < height)){
        value = scene[p];
    }

    return value * 1000 * p;;
};

///////////////////////////////////////////////////////////////////////
//
// private methods
//
///////////////////////////////////////////////////////////////////////
void Scene::tile (bool s){
  if (s)
    glColor3f(0.0f, 0.0f, 0.5f);
  else
    glColor3f(1.0f, 1.0f, 0.0f);

  glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
  
  glEnd();
  
}


void Scene::renderCloseList(void){
    if (mCloseList == NULL)
        return;
    
    float dX = 0.0f;
    float dY  = 0.0f;
    stNode *ptr = mCloseList;
    
    glDisable(GL_TEXTURE_2D);

    while (ptr != NULL){
        glPushMatrix();
            dX = static_cast <float> (ptr->x);
            dY = static_cast <float> (ptr->y);
            glTranslatef(dX, dY, 0.0f);
            tile(false);
        glPopMatrix();
        ptr = ptr->ptrChild;
    }   
}

void Scene::renderCloseList2(void){
	this->renderCloseList();
}

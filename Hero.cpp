    #include <Hero.h>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
Hero::Hero()
{
    this->reset();
    X = 0.0f;
    Y = 0.0f;
   glEnable ( GL_TEXTURE_2D );
   assert(LoadTGA(&mTexture, "Ghost.tga") != false);

};


Hero::Hero(float x, float y):Agent()
{
    Xi = x; Yi = y;
    this->reset();
    glEnable ( GL_TEXTURE_2D );
    assert(LoadTGA(&mTexture, "pacman.tga") != false);

};

Hero::~Hero(void)
{};

void Hero::reset(void){
    Agent::reset();
    mSpeed = 16.0f;
    mMyState = WEAK;
    
}

void Hero::back(void)
{
    X = X1;
    Y = Y1;
/*
    mMaxX = X+mSize;;
    mMinX = X-mSize;
    mMaxY = Y+mSize;
    mMinY = Y-mSize;
   */ 
    VX = 0.0f;
    VY = 0.0f;

};

void Hero::updated(float elapsedTime)
{

    X1 = X;
    Y1 = Y;


    X += (VX * elapsedTime * mSpeed );
    Y += (VY * elapsedTime * mSpeed ) ;
    //X +=  VX * elapsedTime * mSpeed ;
    //Y +=  VY * elapsedTime * mSpeed;
    mMaxX = X+mRaio;;
    mMinX = X-mRaio;
    mMaxY = Y+mRaio;
    mMinY = Y-mRaio;
   /*
    VX *= mRatio;
     VY *= mRatio;
     */

    VX = VY = 0.0f;
     if (fabs(VX) < 0.001f)
         VX = 0.0f;
    if (fabs(VY) < 0.001f)
         VY  = 0.0f;
}



void Hero::render(void){
/*
    glPushMatrix();
	 	 glColor3f(1.0f, 1.0f, 0.0f);
	 	 glTranslatef(X+0.5f, 0.0f, Y+0.5f);

	 	 glutSolidCube(mSize);

    glPopMatrix();
    */
    //draw current pacman
    glPushMatrix();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    
    glTranslatef(X-mSize, Y-mSize, 0.0f);
     glEnable ( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, mTexture.texID);
   
    
    
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(0.0f, 1.0f);
  
  glEnd();
   //glTexCoord2f(1.0f, 0.0f);// glVertex3f( mSize, -mSize, -mSize); 
   //glTexCoord2f(1.0f, 1.0f);// glVertex3f( mSize,  mSize, -mSize); 
   //glTexCoord2f(0.0f, 1.0f);// glVertex3f( mSize,  mSize,  mSize); 
   //glTexCoord2f(0.0f, 0.0f);// glVertex3f( mSize, -mSize,  mSize);
   
//    glutSolidSphere(mSize, 100.0f,100.0f);
    glPopMatrix();
    /*
    //draw remaining pacman lives above the board
    for (int i = 0; i < mLives-1; i++)
    {
        glPushMatrix();
        glTranslatef((float)Board::BOARD_X/-2.0f + i*2, (float) Board::BOARD_Y/2.0f+3,1);
        glutSolidSphere(0.5,10,10);
        glPopMatrix();
    }
*/

}

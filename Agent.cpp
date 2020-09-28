/* 
 * File:   Agent.cpp
 * Author: Marcelo Zamith
 * 
 * Created on June 18, 2010, 11:51 AM
 */

#include "Agent.h"
#include <iostream>
using namespace std;


Agent::Agent(): mLives(3) {};

Agent::~Agent() {};


void Agent::print(void){
   cout << "\nCoordenate: "  << X << "," << Y << endl;
   cout.flush();
    
};

void Agent::resurrect(void){
    mLives--;
    X = Xi;
    Y = Yi; 
}

void Agent::reset(void)
{
   
    mAngle = 90;
    VX = 0.0f;
    VY = 0.0f;
    mAnimated = true;
    mSpeed = 4.0f;
    mRatio = 0.9;
    mSize = 0.5f;
    mRaio = 0.3f; //It is the ratio between centroid of sphere and its bounderies.
    mDebug  =  false;
    X = Xi;
    Y = Yi;
    mMaxX = X+mRaio;;
    mMinX = X-mRaio;
    mMaxY = Y+mRaio;
    mMinY = Y-mRaio;
    mMyState = STRONG;
}

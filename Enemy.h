#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <Agent.h>
#include <AStar.h>
#include <Scene.h>
#include <fstream>
#include <cstdio>
#include <App.h>

using namespace std;

#define SUCCESS true
#define FAIL false

class Enemy: public Agent{
public:
    const float STOPPED = 0.1f;
    Enemy();
    Enemy(const Agent& orig);
    Enemy(float, float, int, int = 0);
    ~Enemy();
    
    virtual void updated(float);
    virtual void render(void);
    virtual void back(void);

    void setAgent(Agent *agent);
    void setScene(Scene *scene);
    
    void rAStar(void);
    void cAStar(void);
    void debugCloseList(void);
    void reset(void);
    stNode *getCloseList(void){ return mTopClose; }
    void print(void);
    bool getCatch(void){ return mCatch; }
    int getID(void){return mID;}
    

protected:
    float mAngle,
          mRatio;

private:
    int fh(int x, int y);
    void check(int x, int y);
    bool testCollision(void);
	void createOpenLists(stNode* start);
	bool learningPath(stNode* start, stNode* goal);
	stNode** getNeighbors(stNode* father);
    //void delay(float d);


    Agent *mAgent;
    Scene *mScene;
    
    int mMin,
        mF,
        mH;
    
          
    bool mPath,
         mStopped,
         mCatch,
         mLearning;
    
    stNode  *mTopOpen,
            //*mNodeU,
            //*mNodeV,
            //*mNodeInOpen, 
            //*mNodeInClose, 
            *mTopClose;
    float mInter;

   int mID;
};


#endif

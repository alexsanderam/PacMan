#include <Enemy.h>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <climits>
#include <ctime>
using namespace std;
Enemy::Enemy()
{

    this->reset();
    glEnable ( GL_TEXTURE_2D );
    assert(LoadTGA(&mTexture, "Ghost.tga") != false);

};



Enemy::Enemy(float x, float y, int i, int id):
Agent(),
//mTopClose(NULL),
//mTopOpen(NULL),
//mPath(true),
//mInter(0.0f),
//mStopped(true),
//mCatch(false),
mID(id)
{

    //int  k = i + 65536;
    this->Xi = x;
    this->Yi = y;
    this->reset();

    glEnable ( GL_TEXTURE_2D );
    assert(LoadTGA(&mTexture, "ghost2.tga") != false);

	mTopClose = NULL;
	mTopOpen = NULL;
	mCatch = false;
	mInter = 0.0f;
};

Enemy::~Enemy(void)
{};


void Enemy::createOpenLists(stNode* start){
	
	mTopOpen = (stNode*) malloc (sizeof(stNode));
	
	mTopOpen->ptrFather = NULL;
	mTopOpen->ptrChild = NULL;
	
	mTopOpen->x = floor(start->x);
	mTopOpen->y = floor(start->y);

	mTopOpen->G = 0;
	mTopOpen->H = fh(mTopOpen->x, mTopOpen->y);
	mTopOpen->F = mTopOpen->G + mTopOpen->H;
}


bool Enemy::learningPath(stNode* start, stNode* goal)
{
	mTopClose = NULL;
	createOpenLists(start);

	bool inOpenSet = false;
	bool inClosedSet = false;
	int score = 0;

	int i, j;

	stNode* current = NULL;
	stNode** mNeighbors = NULL;
	stNode* came_from[mScene->getWidth()][mScene->getHeight()];


	for(i = 0; i < mScene->getWidth(); i++)
		for(j = 0; j < mScene->getHeight(); j++)
			came_from[i][j] = NULL;


	while(mTopOpen != NULL)
	{
	
		//get node in openset having the lowest f score
		current = createAndCopy(mTopOpen);
		
		if(isEqual(current, goal))
		{
			current->ptrFather = came_from[current->x][current->y];
			goal->ptrFather = current->ptrFather;

			return SUCCESS;
		}

		//remove current from openset
		removeList(&mTopOpen);

		/*came_from[current->x][current->y] is necessarilly in closed list and not in open list.*/
		current->ptrFather = came_from[current->x][current->y];

		insert(&mTopClose, current);

		//for each neighbor of current
		mNeighbors = getNeighbors(current);


		for(i = 0; i < 4; i++)
		{
			if(mNeighbors[i]->x < 0 || mNeighbors[i]->y < 0 || mNeighbors[i]->x >= (mScene->getWidth()) || mNeighbors[i]->y >= (mScene->getHeight()))
			{
				free(mNeighbors[i]);
				continue;
			}

			//if neighbor in closed set
			inClosedSet = inTheList(mTopClose, mNeighbors[i]->x, mNeighbors[i]->y) != NULL;
			if(inClosedSet)
				continue;

			score = current->G + mScene->getPosition(mNeighbors[i]->x, mNeighbors[i]->y) + 1;
		
			stNode* node = inTheList(mTopOpen, mNeighbors[i]->x, mNeighbors[i]->y);
			inOpenSet = node != NULL;

			if (!inOpenSet)
				node = mNeighbors[i];

	
			if((!inOpenSet) || (score < node->G))
			{
				came_from[node->x][node->y] = current;

				node->G = score;
				node->H = fh(node->x, node->y);
				node->F = node->G + node->H;

				if(!inOpenSet)
				{
					//add neighbor to open set
					insertSorted(&mTopOpen, node);
				}
			}
		}
	}

	return FAIL;
}


stNode** Enemy::getNeighbors(stNode* father)
{
	stNode** mNeighbors = (stNode**) malloc (sizeof(stNode*) * 4);
	
	short int i = 0;	
	
	for (i = 0; i < 2; i++)
	{
		mNeighbors[i] = (stNode*) malloc (sizeof(stNode));
		mNeighbors[i]->ptrChild = NULL;
		mNeighbors[i]->ptrFather = NULL;
		mNeighbors[i]->G = (father->G) + 1;

		mNeighbors[i]->x = (father->x) + (i - 1);
		mNeighbors[i]->y = (father->y) + i;

		mNeighbors[i+2] = (stNode*) malloc (sizeof(stNode));
		mNeighbors[i+2]->ptrChild = NULL;
		mNeighbors[i+2]->ptrFather = NULL;
		mNeighbors[i+2]->G = (father->G) + 1;

		mNeighbors[i+2]->x = (father->x) + i;
		mNeighbors[i+2]->y = (father->y) + (i - 1);
	}

	return mNeighbors;
}


void Enemy::rAStar(void){
	
}

void Enemy::cAStar(void){
	         
}


//Mahatan distance - Heurist function
int Enemy::fh(int x, int y){
    return   (int) fabs(mAgent->X - (float)x) + fabs(mAgent->Y - (float) y);
}


void Enemy::check(int x, int y)
{
	bool colision = sqrt(pow(mAgent->X - this->X, 2) + pow(mAgent->Y - this->Y, 2)) <= 1.5;
	
	if (colision)
		mCatch = true;
}

/*Update position of Enemy*/
void Enemy::updated(float elapsedTime)
{
	bool ll = false;
	//int x_var = 0;
	//int y_var = 0;

	if((mTopClose == NULL) && (!mLearning))
	{		
		stNode* start = (stNode*) malloc (sizeof(stNode));
		stNode* goal = (stNode*) malloc (sizeof(stNode));

		//define start
		start->x = floor(this->X);
		start->y = floor(this->Y);
		start->G = start->H = start->F = 0;
		start->ptrChild = NULL;
		start->ptrFather = NULL;

		//define goal
		goal->x = floor(mAgent->X);
		goal->y = floor(mAgent->Y);
		goal->G = goal->H = goal->F = 0;
		goal->ptrChild = NULL;
		goal->ptrFather = NULL;		

		if(mTopOpen != NULL)	
		{
			destroyList(&mTopOpen);
			mTopOpen = NULL;
		}

		ll = learningPath(start, goal);

		if(ll)
		{
			printf("\nLearning with success!");

			//remove bifurcations
			buildPath(goal->ptrFather);
			//mScene->setCloseList(mTopClose);
		}
		else
			printf("\n:(");	
	}

	//update postion of enemy
	stNode* nextNode = mTopClose;

	if(nextNode != NULL)
	{
		/*X1 = X;
		Y1 = Y;

		x_var = ceil(nextNode->x - X);
		y_var = ceil(nextNode->x - X);

		VX += x_var * 0.1; 
		VY += y_var * 0.1;

		X += (VX * elapsedTime * mSpeed );
		Y += (VY * elapsedTime * mSpeed ) ;

		Xi = X;
		Yi = Y;
		this->reset();

		if (abs(VX) >= 1.0f || abs(VY) >= 1.0f)
		{
			VX = 0.0f;
			VY = 0.0f;*/

			if(nextNode != NULL)
				removeList(&mTopClose);
		//}	

		check(X, Y);
	}
}


void Enemy::debugCloseList(void){
    
}



void Enemy::back(void)
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

bool Enemy::testCollision(void){
    
    
    if (mAgent->mMaxX < this->mMinX)
        return false;
    
    if (mAgent->mMinX > this->mMaxX)
        return false;
    
    if (mAgent->mMaxY < this->mMinY)
        return false;
    
    if (mAgent->mMinY > this->mMaxY)
        return false;
    
    return true;
        
}

void Enemy::reset(void){
    Agent::reset();
    mStopped = true;
    
}

void Enemy::render(void){
    //draw current pacman
    
    glPushMatrix();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    
    
    glTranslatef(X, Y, 0.0f);
    glEnable ( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, mTexture.texID);
   
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(0.0f, 1.0f);
  
    glEnd();

    glPopMatrix();
}


void  Enemy::setAgent(Agent *agent){
    mAgent = agent;      
}


void Enemy::setScene(Scene *scene){
    mScene = scene;
}

void Enemy::print(void){
    cout << "Enemy" << endl;
    cout.flush();
}

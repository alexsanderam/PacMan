#ifndef _ASTAR_H_
#define _ASTAR_H_

#define WALLCOST 10
#define MAZECOST 1;
struct stNode{
    int x;          //Posicao X do no
    int y;          //Posico Y do no
    int G;          //Custo G -> percorrigo
    int H;          //Custo H -> estimado
    int F;          //Custo F = G + H
    stNode *ptrFather;
    stNode *ptrChild;
};

void insertSorted(stNode **top, stNode *nNode);
bool isEqual(stNode* ptr1, stNode* ptr2);
void insert(stNode **top, stNode *nNode);
void removeList(stNode **ptrR);
stNode * inTheList(stNode *top, int x, int y);
stNode* createAndCopy(stNode* source);
void copyNode(stNode * destination, stNode* source);
void debugList(stNode *node);
void debugNode(stNode* node);
unsigned long destroyList(stNode **ptrR);
void buildPath(stNode *bottom);
#endif

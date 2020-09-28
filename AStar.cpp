#include "AStar.h"
#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

bool isEqual(stNode* ptr1, stNode* ptr2)
{
	if(ptr1->x == ptr2->x && ptr1->y == ptr2->y)
		return true;

	return false;
}

void removeList(stNode **ptrR){
    stNode *ptr = *(ptrR);

    if (ptr == NULL)
        return;

    if (ptr->ptrFather != NULL){
        ptr->ptrFather->ptrChild = ptr->ptrChild;
        *(ptrR) = ptr->ptrFather;
    }
    
    if (ptr->ptrChild != NULL){
        ptr->ptrChild->ptrFather  = ptr->ptrFather;
        *(ptrR) = ptr->ptrChild;
    }

	if (ptr->ptrFather == NULL && ptr->ptrChild == NULL)
	    *(ptrR) = NULL;
    
	ptr->ptrChild = ptr->ptrFather = NULL;

    free(ptr);
	//delete ptr;

    ptr = NULL;
}


void insertSorted(stNode **top, stNode *nNode){
   

		if (*(top) != NULL){
	        stNode *ptr = *top;
        
        if (nNode->F < ptr->F){
            nNode->ptrChild = *top;
            ptr->ptrFather = nNode;
            *(top) = nNode;
            return;
        }else{
            while ((ptr->F <= nNode->F) && (ptr->ptrChild != NULL))
                ptr = ptr->ptrChild;
            
            if (nNode->F < ptr->F){
                nNode->ptrChild = ptr;
                nNode->ptrFather = ptr->ptrFather;
                
                ptr->ptrFather = nNode;
                nNode->ptrFather->ptrChild = nNode;
                return;
            }//end-if (nNode->F < ptr->F){
            
            if (ptr->ptrChild == NULL){
                ptr->ptrChild = nNode;
                nNode->ptrFather = ptr;
                nNode->ptrChild = NULL;
                return;
            }//end-if (ptr->ptrChild == NULL){
            
            if (nNode->F == ptr->F)
                return;
            
            cerr << "\n\t***[ERROR] " << __LINE__ << endl;
            exit(-1);
        }//end-if (nNode->F < ptr->F){        
    }

    *(top) = nNode;
    
}

void insert(stNode **top, stNode *nNode){
    
    if (*(top) != NULL){
        stNode *ptr = *top;
        while (ptr->ptrChild != NULL)
            ptr = ptr->ptrChild;
        
        ptr->ptrChild = nNode;
        nNode->ptrFather = ptr;
        return;
    }
    
    *(top) = nNode;
}



stNode * inTheList(stNode *top, int x, int y){
    stNode *ptr = top;
    while (ptr != NULL){
        if ((ptr->x == x) && (ptr->y == y))
            return ptr;
        ptr = ptr->ptrChild;
    }
    return NULL;
};


stNode* createAndCopy(stNode* source)
{
	stNode* newNode = (stNode*) malloc (sizeof(stNode));
	copyNode(newNode, source);
	return newNode;
}

void copyNode(stNode * destination, stNode* source){
       
    assert(destination != NULL);
    destination->x = source->x;
    destination->y = source->y;
    destination->G = source->G;
    destination->H = source->H;
    destination->F = source->F;
    destination->ptrFather = destination->ptrChild = NULL;
    
};

void debugList(stNode *node){
    stNode *ptr = node;
    
   while (ptr != NULL){
        debugNode(ptr);
        ptr = ptr->ptrChild;
    }
   
}

void debugNode(stNode* node)
{
	cout << "F: " << node->F << " G: " << node->G << " H: " << node->H << "\t(" << node->x << ", " << node->y << ")" << endl;
}

unsigned long destroyList(stNode **ptrR){

    unsigned long memory = 0;
    stNode *ptr = *(ptrR), *aux;
    int  i =0;


    while (ptr != NULL){
        aux = ptr;
        ptr = ptr->ptrChild;
        memory += sizeof(stNode);

		if(aux != NULL)
        {
	        free(aux);
            aux = NULL;
        }
        i++;
    }
   
    *(ptrR) = NULL;
    return memory;
};

/*
 * This function gets rid of ambiguous paths
/ */
void buildPath(stNode *bottom){
    stNode *ptr = bottom;
    stNode *ptrFather = NULL;
    if (bottom == NULL)
        return;
    if (bottom->ptrFather == NULL)
        return;
    do{
        ptrFather = ptr->ptrFather;
        int d = abs(ptr->x - ptrFather->x) + abs(ptr->y - ptrFather->y);

        //cerr << d << "  (" << ptr->x << "," << ptr->y << ") - ";
        //cerr << "R[" << ptrFather->x << "," << ptrFather->y << "]" << endl;
        if (d > 1){
            removeList(&ptrFather);
        }
        else
            ptr = ptr->ptrFather;
        
    }while (ptr->ptrFather != NULL);
    

};

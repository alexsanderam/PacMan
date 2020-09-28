#ifndef _HERO_H_
#define _HERO_H_
#include <Agent.h>



class Hero: public Agent{
public:
    Hero();
    Hero(const Agent& orig);
    Hero(float, float);
    ~Hero();
    
    virtual void updated(float);
    virtual void render(void);
    virtual void back(void);
    virtual void reset(void);

  
};


#endif

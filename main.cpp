#include<GL/glew.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
  #include <OpenGL/glu.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/OpenGL.h>
  #include <OpenGL/CGLCurrent.h>
  #include <OpenGL/CGLRenderers.h>
  #include <OpenGL/CGLTypes.h>

#else
  #include <GL/glut.h>
  #include <GL/glu.h>
  #include <GL/gl.h>
#endif
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cassert>
#include <App.h>
#include <Scene.h>
#include <Hero.h>
#include <Enemy.h>

using namespace std;

double mAStarElaspedTime = 0.0f;
float fcount = 0.0f, facc = 0.0f, fAverageSteps = 0.0f;
Stopwatch stopwatch, appsw;
Scene *scene;
Hero *hero;
Enemy **enemy;

bool inited = false;
bool mGameOver = false;

unsigned long mMemoryUsed = 0;
fstream logFile;

//string fileName  = "board03.ftxt";
int width = 800,
     height = 600,
     nGhosts = 0;

int mFPS = 0;



//Tardiness variables
float mTProgramed = 1000.0f/60.0f,
      mTExecuted = mTProgramed,
      mTardiness = 0.0f,
      mAgentTardiness = 0.0f,
      mAverageT  = 0.0f,
      mMajorT    = 0.0f;
      
bool  mComputed = false;
int   mICount = 0,
      mITransient = 100,
      mRenderCount = 0;

void render(void){

    glClear(GL_COLOR_BUFFER_BIT);
    
    
    scene->render();
    hero->render();



    for (int i = 0; i < nGhosts; i++){

        enemy[i]->render();
    }

    mRenderCount++;
    if ((mRenderCount == 100) || (mGameOver)){
        if (mGameOver)
        	cout << "GO";

    			fAverageSteps = 0.0f;
    			facc = 0.0f;
    			fcount = 0.0f;
    			mAverageT = 0.0f;
    			mAStarElaspedTime = 0.0f;

    	mRenderCount = 0;
    }


    
    if (mGameOver){
        STOP_STOPWATCH(appsw);
        cerr << "\nGAMEOVER!!!"<< endl;
        exit(EXIT_SUCCESS);
    }
    glutSwapBuffers();
}





// Função de inicialização de parâmetros (OpenGL e outros)
void init (void){
    
    
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   cout << "Loading GLEW:" <<  glewGetErrorString(glewInit()) << std::endl;
    if(!glewIsSupported(
          "GL_VERSION_2_0 "
          "GL_ARB_pixel_buffer_object "
          "GL_EXT_framebuffer_object "
    )){
          cerr <<  "ERROR: Support for necessary OpenGL extensions missing " << std::endl;
          exit(EXIT_FAILURE);
    }
    
#ifdef __APPLE__
    CGLContextObj	ctx = CGLGetCurrentContext();
    int interval = 0;
    CGLError err = CGLSetParameter(ctx, kCGLCPSwapInterval, &interval);
#endif
   
     
  srand (time(NULL));

  scene = new Scene();
  scene->load("board.txt");

  printf("\n");
  hero = new Hero(scene->getWidth() - 2, scene->getHeight() - 2);
  
  enemy = new Enemy*[nGhosts];
  for (int i = 0; i < nGhosts; i++){
    enemy[i] = new Enemy( 1.0f , 3.47045f, i+1, i+1);
    enemy[i]->setAgent(hero);
    enemy[i]->setScene(scene);    
      
  }

}

// Função de evento do teclado
void keyboardEvent(unsigned char key, int x, int y)
{
     //    glutPostRedisplay();
    switch (key) {
        case 'w': hero->up(); break;
        case 's':  hero->down();break;
        case 'a':  hero->left();break;
        case 'd':  hero->right();break;
        case 'p':  hero->print(); 
                   //enemy->print(); 
                   //enemy->debugCloseList();     
            break;

        case 'r':  hero->print();
                   //enemy->rAStar();
                   //scene->setCloseList(NULL);                    
            break;
        case 'c':  
            //enemy->cAStar(); 
            //scene->setCloseList(enemy->getCloseList());
            break;
        case 'Q':
        case 27:
            exit (EXIT_SUCCESS);
            break;
            
       
        default:
            break;
   }
}


//Viewport
void viewPort(int w, int h){
    
    if(h == 0) h = 1;
    
    
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    float fw = scene->getWidth() + 0.1f;
    float fh = scene->getHeight() + 0.04f;
    
    glOrtho (-0.01f, fw, 1.00f, fh, -0.01f, 0.01f);
    glutPostRedisplay();
}


//Loop principal da visualização
void mainloop(void){

    if (!inited){
        inited = true;
        START_STOPWATCH(appsw);
        
    }
    glutPostRedisplay();
    STOP_STOPWATCH(stopwatch);
    
    for (int i = 0; i < nGhosts; i++){
        if(enemy[i]->getCatch())
            mGameOver = true;            
    }
    
    if (!mGameOver){
        hero->updated(stopwatch.mElapsedTime/1000.0f);
        for (int i = 0; i < nGhosts; i++){
        	enemy[i]->updated(stopwatch.mElapsedTime/1000.0f);
        }
    }
    

   if(scene->testCollision(hero))
       hero->back();
    
    fcount++;

    facc += 1000.0f /  stopwatch.mElapsedTime;
    

        
    
    if (fcount >= 100.0f){
        char msg[1024];
                    
        sprintf(msg, "Pacman - %.0f", facc / fcount);




        glutSetWindowTitle(msg);
        
    }
    
    START_STOPWATCH(stopwatch);
}



void Timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(120, Timer, 0); // next Timer call milliseconds later
}



int main(int argc, char**argv){
    
    if (argc > 1)
        nGhosts = atoi(argv[1]);
    else
        nGhosts = 4;
    cout << "\nNumber of ghosts: " << nGhosts << endl;
    cout.flush();
  
    
    START_STOPWATCH(stopwatch);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //NSOpenGLCPSwapInterval
    //glXSwapIntervalEXT(0);
    glutInitWindowSize(width, height);
    glutCreateWindow("PACMAN - 2D");
    //glutFullScreen();
    glutDisplayFunc(render);
    glutReshapeFunc(viewPort);
    glutKeyboardFunc(keyboardEvent);
    glutIdleFunc(mainloop);
    //glutTimerFunc(0, Timer, 0);     // frequencia fixa
    init();
    glutMainLoop();
    return EXIT_SUCCESS;
}

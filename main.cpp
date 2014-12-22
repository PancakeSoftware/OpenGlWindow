/* -- INCLUDE ------------------------------------------------ */
#include <stdlib.h>
#include <iostream>
using namespace std;

/* -- includes depinding on platform */
#ifdef          __gnu_linux__
    #include <SDL/SDL.h>
    #include <SDL/SDL_opengl.h>
        
#elif defined   __APPLE__     
#elif defined   __WINDOWS__        
#else  
#endif



/* -- PRE DEFINED FUNC ---------------------------------------- */
void renderLoop();


/* -- CREATE OPENGL WINDOW ------------------------------------ */
// -- Linux - Ubuntu 
bool createWindowUbuntu()
{
    int error = 0;
    cout << "[....] creating Window for Ubuntu" << endl;
    
    // init sdl -----------------------------
    error = SDL_Init(SDL_INIT_VIDEO);
    if (error != 0)
    {
        cout << "[ERR ] SDL_Init" << endl;
        return false;
    }
    else 
        cout << "[ OK ] SDL_Init" << endl;
    
    // set window titel
    SDL_WM_SetCaption("OpenGl Window", "");
    
    // activate doublebuffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // open window
    SDL_SetVideoMode(800, 800, 32, SDL_OPENGL);
}


// -- Linux - Pi
bool createWindowPi()
{
    cout << "[....] creating Window for Raspberry pi" << endl;
    
    /* @TODO
     * create openGl Surface for Pi
     */
}


// -- Mac
bool createWindowMac()
{
    cout << "[....] creating Window for Mac" << endl;
    
    /* @TODO
     * create openGl Surface for Mac OSx
     */
}


// -- Windows
bool createWindowWin()
{
    cout << "[....] creating Window for Windows" << endl;
    
    /* @TODO
     * create openGl Surface for Windows
     */
}




/* -- MAIN PROGRAM ------------------------------------------- */
int main()
{
    // output
    cout << "[ OK ] program start" << endl;
    
    // execute depending on platform
    #ifdef          __gnu_linux__
        createWindowUbuntu();
        
    #elif defined   __APPLE__
        createWindowMac();
        
    #elif defined   __WINDOWS__
        createWindowWin();
        
    #else 
        createWindowPi();   
        
    #endif

        
        
    // start render loop
    renderLoop();
}



/* -- RENDER LOOP ---------------------------------------------- */
void renderLoop()
{
    // sdl event
    SDL_Event event;
    
    
    // render loop
    while (true)
    {
        // get next SDL event
        SDL_PollEvent(&event);
        
        // check for SDL event
        switch (event.type)
        {
            case SDL_QUIT:
                cout << "[END ] close program" << endl;
                SDL_Quit();// close SDL
                exit(0);    // close program
        }
        
        
        
        // clear framebuffer
        
    }
}
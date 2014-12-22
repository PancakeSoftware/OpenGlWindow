/* -- INCLUDE ------------------------------------------------ */
#include <stdlib.h>
#include <iostream>
using namespace std;

/* -- includes depinding on platform */
#ifdef          __gnu_linux__
    
        
#elif defined   __APPLE__     
#elif defined   __WINDOWS__        
#else  
#endif




/* -- CREATE OPENGL WINDOW ------------------------------------ */
// -- Linux - Ubuntu 
bool createWindowUbuntu()
{
    cout << "[....] creating Window for Ubuntu" << endl;
    
    /* @TODO
     * create openGl Surface for Ubuntu
     */
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
}
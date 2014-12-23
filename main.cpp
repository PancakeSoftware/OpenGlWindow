/* -- INCLUDE ------------------------------------------------ */
#include <stdlib.h>
#include <iostream>
#include <sstream>

//#include <>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // gl Math matix transform
using namespace std;

/* -- includes depinding on platform */
#ifdef          __gnu_linux__
    #include <GL/glew.h>
    #include <GL/glu.h>
    #include <SDL/SDL.h>
    #include <ctime>
    #include <unistd.h>
    //#include <SDL/SDL_opengl.h>
    
        
#elif defined   __APPLE__     
#elif defined   __WINDOWS__        
#else  
#endif


// -- VAR
GLint HANDEL_SHADER,
      HANDEL_SHADER_ATTR_VERTEX,
      HANDEL_SHADER_UNI_TRANSFORM,
      HANDEL_SHADER_UNI_COLOR;

int windowWith  = 1500;
int windowHight = 400;
double fps      = 0;



/* -- PRE DEFINED FUNC ---------------------------------------- */
void renderLoop();
void createShader();
void checkShaderError(GLuint shader, bool isProgram, GLint flag, string message);


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
    SDL_SetVideoMode(windowWith, windowHight, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
    
    // init glew
    glewInit();
    
    // ouput ok
    cout << "[DONE] created Window for Ubuntu" << endl;
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
        //createWindowMac();
        createWindowUbuntu();
        
    #elif defined   __WINDOWS__
        createWindowWin();
        
    #else 
        createWindowPi();   
        
    #endif

    
    // output of openGl versions
    cout << "[INFO] openGl version: " << glGetString( GL_VERSION ) << endl; 
    cout << "[INFO] openGl SL version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << endl; 
        
        
    // start render loop
    renderLoop();
}


 double starttime = 0;
 double endtime   = 0;
/* -- RENDER LOOP ---------------------------------------------- */
void renderLoop()
{    
    float time = 0;
    int   frame = 0;    
    // vertices
    GLfloat vertices[12] = {
        -100, -100, 0,
        -100, 100, 0,
         100, -100, 0,
         100, 100, 0
    };
    
    // transform matrix
    glm::mat4 transformMatrix;
    // resize ortho
    transformMatrix = glm::ortho( -(float)windowWith/2  /* left */,
                                    (float)windowWith/2  /* right */,
                                   -(float)windowHight/2 /* bottom */,
                                    (float)windowHight/2 /* top */,
            
                                    1.0f                     /* zNear */,
                                   -1.0f                     /* zFar */);
    
    
    // sdl event
    SDL_Event event;
    
    // output 
    cout << "[....] start render loop" << endl;
    
    // create shader
    createShader();

    
    
   
    
    // render loop
    while (true)
    {
        
        // get next SDL event
        while (SDL_PollEvent(&event))
        {
            // check for SDL event
            switch (event.type)
            {
                case SDL_QUIT:
                    cout << "[END ] close program" << endl;
                    SDL_Quit();// close SDL
                    exit(0);    // close program
                    break;
                    
                case SDL_VIDEORESIZE:
                    int h = event.resize.h; 
                    int w = event.resize.w;
                    windowHight = h;
                    windowWith  = w;
                    
                    // out
                    // cout << "[INFO] window height: " << h << "  width: " << w << endl;
                    // reset screen
                    SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_RESIZABLE | SDL_DOUBLEBUF);
                    glViewport(0,0, w, h);
                    // resize ortho
                    transformMatrix = glm::ortho( -(float)w/2  /* left */,
                                                    (float)w/2  /* right */,
                                                   -(float)h/2 /* bottom */,
                                                    (float)h/2 /* top */,

                                                    1.0f                     /* zNear */,
                                                   -1.0f                     /* zFar */);
                    
                    
                    
                    break;
            }
        }
               
        
        
        /* clear framebuffer 
         * -> red               */
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear( GL_COLOR_BUFFER_BIT );
        
       
        
        // draw some stuff -------------------------------------------------
        // aktivate shader program
        glUseProgram(HANDEL_SHADER);
        
        // set attribute to recive vertex data
        glEnableVertexAttribArray(HANDEL_SHADER_ATTR_VERTEX);
        
        
        
        
        for (float i=-1; i<=1.0; i+=0.25)
        {
        // remove
        float value = (0.3*glm::sin(time)+i);
        float value2 = (0.3*glm::cos(time+i));
        
        glm::vec3 move = glm::vec3(value,value2, 0);
        glm::vec3 rot = glm::vec3(0,0,1);
        
        
        glm::mat4 moveMatrix  = glm::translate(glm::mat4(1.0f), move);
        glm::mat4 rotMatrix   = glm::rotate(glm::mat4(1.0f), value*100,rot);
        glm::mat4 matrixFinal = moveMatrix * transformMatrix *  rotMatrix;
        
        
        
        // set transform/projecttion matrix
        glUniformMatrix4fv(HANDEL_SHADER_UNI_TRANSFORM,
                       1                /* amount of matrix */,
                       GL_FALSE         /* convert format -> NO */,
                       &matrixFinal[0][0]);
        
        // set color
        glUniform4f(HANDEL_SHADER_UNI_COLOR,
                    1.0,
                    value,
                    value2,
                    1.0);
        
        // give gl the Vertices via array
        glVertexAttribPointer(
            HANDEL_SHADER_ATTR_VERTEX                       /* pass vertices to vertex Pos attribute of vertexShader */,
            3                                               /* 3 Aruments: x,y,z */,
            GL_FLOAT                                        /* Format: float     */,
            GL_FALSE                                        /* take values as-is */,   
            0                                               /* Entry lenght ?    */,
            vertices                       /* vertices Array    */ );
    
        // draw with the vertices form the given Array
        // make two connected triangle to create a rectangle
        glDrawArrays(
            GL_TRIANGLE_STRIP,
            0 /* Array start pos   */,
            4 /* how much vertices */);

         }
        
        
        
        // -- FPS -----------------------------------------------
         // vertices
        GLfloat verticesFps[12] = {
            -0, -10, 0,
            -0, 0, 0,
             (fps/4), -10, 0,
             (fps/4), 0, 0
        };
        
        // remove        
        glm::vec3 move = glm::vec3(-1, +1,0);
        glm::vec3 rot = glm::vec3(0,0,0);
        
        
        glm::mat4 moveMatrix  = glm::translate(glm::mat4(1.0f), move);
        glm::mat4 matrixFinal = moveMatrix * transformMatrix;
        
        
        
        // set transform/projecttion matrix
        glUniformMatrix4fv(HANDEL_SHADER_UNI_TRANSFORM,
                       1                /* amount of matrix */,
                       GL_FALSE         /* convert format -> NO */,
                       &matrixFinal[0][0]);
        
        // set color
        glUniform4f(HANDEL_SHADER_UNI_COLOR,
                    0.0,
                    1.0,
                    0.2,
                    1.0);
        
        // give gl the Vertices via array
        glVertexAttribPointer(
            HANDEL_SHADER_ATTR_VERTEX                       /* pass vertices to vertex Pos attribute of vertexShader */,
            3                                               /* 3 Aruments: x,y,z */,
            GL_FLOAT                                        /* Format: float     */,
            GL_FALSE                                        /* take values as-is */,   
            0                                               /* Entry lenght ?    */,
            verticesFps                       /* vertices Array    */ );
    
        // draw with the vertices form the given Array
        // make two connected triangle to create a rectangle
        glDrawArrays(
            GL_TRIANGLE_STRIP,
            0 /* Array start pos   */,
            4 /* how much vertices */);
        // -- End FPS -------------------------------------------
        
        
        
        
        

        // deactivate vertex Array mode
        // => end of operation
        glDisableVertexAttribArray(HANDEL_SHADER_ATTR_VERTEX);

        // unbind shader
        glUseProgram(0);
                
        // end draw --------------------------------------------------
        
        
        // swarp buffer
        SDL_GL_SwapBuffers();
        
        time+= 0.09;
        frame++;
        
        
        //sleep(3);
        
        // calc fps
        endtime = clock();
        double timeDiff = (endtime - starttime)/ (double) CLOCKS_PER_SEC;
        double fpsTemp = 1/timeDiff ;
        starttime = endtime;
        
        
        if (frame >= 5)
        {
            fps = (fpsTemp);       
            
            // set window titel
//            ostringstream stream;
//            stream << "OpenGl Window - Fps " << fps;
//            const char* streamO = stream.str().c_str();
//            SDL_WM_SetCaption(streamO, "");
            
            
            frame = 0;
        }
        

    }
}


/* -- CREATE SHADER ----------------------------- */
void createShader()
{
    // shader src
    const GLchar* vertexShader = 
                 "attribute vec3 vertexPos;                                \n"
                 "uniform   mat4 transformMatrix;                          \n" // uniform can be set by cpu
                 "                                                         \n"
                 "void main() {                                            \n"
                 "                                                         \n"
                 "    gl_Position = transformMatrix * vec4(vertexPos, 1.0);\n"
                 "}                                                        \n";
    
    const GLchar* fragmentShader = 
                 "uniform vec4 color;                      \n" // uniform can be set by cpu
                 "                                         \n"
                 "void main() {                            \n"
                 "                                         \n" 
                 "   gl_FragColor =  color;                \n"
                 "}                                        \n";
    
    
    
    GLint shaderVertex, shaderFragment;
    
    // create shader programm 
    HANDEL_SHADER = glCreateProgram();
    if (HANDEL_SHADER == 0)
        cout << "[ GL ] create shader program [ERR]" << endl;
    else 
        cout << "[ GL ] create shader program [OK]" << endl;
    
    
    // create shader container --------
    shaderVertex   = glCreateShader(GL_VERTEX_SHADER);   // for vertext-shader
    shaderFragment = glCreateShader(GL_FRAGMENT_SHADER); // for fragment-shader
    if (shaderVertex == 0  ||  shaderFragment == 0)
        cout << "[ GL ] create shader [ERR]" << endl;
    else 
        cout << "[ GL ] create shader [OK]" << endl;
    
    
    // load shaders into char vars
    // => not necessary
    
    
    // load shader into container
    glShaderSource(shaderVertex,   1, &vertexShader,   NULL);
    glShaderSource(shaderFragment, 1, &fragmentShader, NULL);
    
    
    // compile shader
    glCompileShader(shaderVertex);
    glCompileShader(shaderFragment);    
    
    
    // add shader to programm
    glAttachShader(HANDEL_SHADER, shaderVertex);
    glAttachShader(HANDEL_SHADER, shaderFragment);
    
    
    // bind shader programm to openGl
    glLinkProgram(HANDEL_SHADER);
    checkShaderError(HANDEL_SHADER, true, GL_LINK_STATUS, "link shader program");
    
    glValidateProgram(HANDEL_SHADER);
    checkShaderError(HANDEL_SHADER, true, GL_VALIDATE_STATUS, "validate shader program");
            
    
    // get attributes / uniformes
    HANDEL_SHADER_ATTR_VERTEX       = glGetAttribLocation( HANDEL_SHADER, "vertexPos");
    HANDEL_SHADER_UNI_TRANSFORM     = glGetUniformLocation(HANDEL_SHADER, "transformMatrix");  
    HANDEL_SHADER_UNI_COLOR         = glGetUniformLocation(HANDEL_SHADER, "color");
    
    if ( HANDEL_SHADER_ATTR_VERTEX      == -1 
      || HANDEL_SHADER_UNI_TRANSFORM    == -1
      || HANDEL_SHADER_UNI_COLOR        == -1 )
        cout << "[ GL ] get Attribute/Uniform [ERR]" << endl;
    else 
        cout << "[ GL ] get Attribute/Uniform [OK]"  << endl;
    
}


// -- CHECK SHADER ERROR ----------------------
void checkShaderError(GLuint shader, bool isProgram, GLint flag, string message) 
{
    // error var
    GLint  success         = GL_FALSE;
    GLchar errorText[1024] = { 0 };
    
    
    // is there an error
    if (isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    } else
    {
        glGetShaderiv(shader, flag, &success);
    }
    
    
    // if there is error
    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(errorText), NULL, errorText);
        else
            glGetShaderInfoLog(shader, sizeof(errorText), NULL, errorText);
    }
    
    // out
    if (success == GL_FALSE)
        cout << "[ GL ] " << message << " [ERR] '" << errorText << "'" << endl;
    else
        cout << "[ GL ] " << message << " [OK]" << endl;
}
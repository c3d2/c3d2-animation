//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe
// (email Richard Campbell at ulmont@bellsouth.net)
//
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header File For sleeping.

#include <stdio.h>

/* ASCII code for the escape key. */
#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

/* The number of our GLUT window */
int window;

float xrot = 0.0f;
float yrot = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

    glMatrixMode(GL_MODELVIEW);

}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
        Height=1;

    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View


    glTranslatef(0.0f,0.0f,-6.0f);		// Move Left 1.5 Units And Into The Screen 6.0

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    // draw a square (quadrilateral)
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)

    /* --- Top --- */
    glColor3f(  1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Front

    glColor3f(  1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Front

    glColor3f(  1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Back

    glColor3f(  1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Back


    /* --- Left Side --- */
    glColor3f(  0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Left Side Bottom Back

    glColor3f(  0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Left Side Bottom Front

    glColor3f(  1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Left Side Top Front

    glColor3f(  1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Left Side Top Back


    /* --- Right Side --- */
    glColor3f(  0.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Right Side Bottom Back

    glColor3f(  0.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Right Side Bottom Front

    glColor3f(  1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Right Side Top Front

    glColor3f(  1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Right Side Top Back


    /* --- Back Side --- */
    glColor3f(  0.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Back Right Side Bottom

    glColor3f(  0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Back Left Side Bottom

    glColor3f(  1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);		// Back Left Side Top

    glColor3f(  1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);		// Back Right Side Top


    /* --- Front --- */
    glColor3f(  0.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Front Right Side Bottom

    glColor3f(  0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Front Left Side Bottom

    glColor3f(  1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);		// Front Left Side Top

    glColor3f(  1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);		// Front Right Side Top


    /* --- Bottom --- */
    glColor3f(  0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Back

    glColor3f(  0.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Back

    glColor3f(  0.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Front

    glColor3f(  0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Front

    glEnd();					// done with the polygon

    // swap buffers to display, since we're double buffered.
    glutSwapBuffers();
}

void rota()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(5,1,0.5,0.8);
    DrawGLScene();
    glFlush();
    glutTimerFunc(10.0, &rota, 5);
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(100);

    switch (key)
    {
        case 'f': glutFullScreen();
                  break;
        case 'w': glutReshapeWindow(640,480);
                  break;
        case 27:  glutDestroyWindow(window);
                  exit(0);
        default:
                  break;
    }
}

void specialKeyPressed(int key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(100);

    switch (key)
    {
        case GLUT_KEY_UP:
                  xrot += 10;
                  break;
        case GLUT_KEY_DOWN:
                  xrot -= 10;
                  break;
        case GLUT_KEY_LEFT:
                  yrot += 10;
                  break;
        case GLUT_KEY_RIGHT:
                  yrot -= 10;
                  break;
        default:
                  break;
    }
}

int main(int argc, char **argv)
{
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
    glutInit(&argc, argv);

    /* Select type of Display mode:
       Double buffer
       RGBA color
       Alpha components supported
       Depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);

    /* Open a window */
    window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);

    /* Go fullscreen.  This is the soonest we could possibly go fullscreen. */
    /*glutFullScreen();*/

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&keyPressed);

    glutSpecialFunc(&specialKeyPressed);

    /* Initialize our window. */
    InitGL(640, 480);

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;
}

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
#include <math.h>     // Header File for math.

#include <stdio.h>
#include <stdlib.h>

#include "slash.h"
#include "openBracket.h"
#include "closeBracket.h"

#define PI 3.1415

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;

float xrot = 0.0f;
float yrot = 0.0f;
float zrot = 0.0f;

float xrot_scene = 0.0f;
float yrot_scene = 0.0f;
float zrot_scene = 0.0f;
float xrot_scene_d = 0.0f;
float yrot_scene_d = 0.0f;
float zrot_scene_d = 0.0f;

float i = 0.3;
int full = 0;
int oszi = 0;

GLuint texture[1];     // Stores one new Texture

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1)
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp1;                          // temporary color storage for bgr-rgb conversion.
    char temp2;
    char temp3;

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);

    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }

    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp1 = image->data[ i ]; // b  -- don't ask its what gimp gave me
        temp2 = image->data[i+1]; // r
        temp3 = image->data[i+2]; // g

        image->data[i] = temp2;
        image->data[i+1] = temp1;
        image->data[i+2] = temp3;
    }

    // we're done.
    return 1;
}

// Load Bitmaps And Convert To Textures
void LoadGLTextures() {
    // Load Texture
    Image *image1;

    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }

    if (!ImageLoad("texture.bmp", image1)) {
        exit(1);
    }

    // Create Texture
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
};

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
    LoadGLTextures();				// Load The Texture(s)
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);		// This Will Clear The Background Color To Black
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

void rotate(int what)
{
    usleep(10);
    switch(what)
    {
        case 0:
            xrot += i;
            break;
        case 1:
            yrot += i;
            break;
        case 2:
            zrot += i;
            break;
        default:
            xrot += i;
            yrot += i;
            zrot += i;
    }
    if (xrot >= 360) xrot = 0;
    if (yrot >= 360) yrot = 0;
    if (zrot >= 360) zrot = 0;
}

/* The main drawing function. */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View


    glTranslatef(0.0f,0.0f,-8.0f);		// Move Left 1.5 Units And Into The Screen 6.0

    xrot_scene += xrot_scene_d;
    yrot_scene += yrot_scene_d;
    zrot_scene += zrot_scene_d;
    glRotatef(xrot_scene, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot_scene, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot_scene, 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0f, sin((yrot*PI)/180), 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.

    glTranslatef(-3.0f, 0.0f, 0.0f);
    DrawOpenBracket( xrot, yrot, zrot, texture[0]);

    glTranslatef(1.2f, 0.0f, 0.0f);
    DrawOpenBracket( xrot, yrot, zrot, texture[0]);

    glTranslatef(1.2f, 0.0f, 0.0f);
    DrawOpenBracket( xrot, yrot, zrot, texture[0]);

    glTranslatef(1.2f, 0.0f, 0.0f);
    DrawSlash(xrot, yrot, zrot, texture[0]);

    glTranslatef(1.2f, 0.0f, 0.0f);
    DrawCloseBracket(xrot, yrot, zrot, texture[0]);

    glTranslatef(1.2f, 0.0f, 0.0f);
    DrawCloseBracket(xrot, yrot, zrot, texture[0]);

    // swap buffers to display, since we're double buffered.
    glutSwapBuffers();
    if (oszi) rotate(1);
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(100);

    switch (key)
    {
        case 'f': if (!full)
                  {
                      glutFullScreen();
                      full = 1;
                  } else {
                      glutReshapeWindow(640,480);
                      full = 0;
                  }
                  break;

        case 'm': if (!oszi)
                  {
                      oszi = 1;
                  } else {
                      oszi = 0;
                  }
                  break;

        case ' ':
                  zrot_scene += 5;
                  break;

        case '0': zrot_scene = xrot_scene = yrot_scene = 0;
                  break;

        case 27:  glutDestroyWindow(window);
                  exit(0);
        default:
                  break;
    }
}

void specialPressKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
                  xrot_scene_d = 5;
                  break;
        case GLUT_KEY_DOWN:
                  xrot_scene_d = -5;
                  break;
        case GLUT_KEY_LEFT:
                  yrot_scene_d = 5;
                  break;
        case GLUT_KEY_RIGHT:
                  yrot_scene_d = -5;
                  break;
        default:
                  break;
    }
}

void specialUpKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
                  xrot_scene_d = 0;
                  break;
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
                  yrot_scene_d = 0;
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
    glutInitWindowPosition(400, 210);

    /* Open a window */
    window = glutCreateWindow("c3d2 animation");

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

    glutSpecialFunc(&specialPressKey);
    glutSpecialUpFunc(&specialUpKey);

    /* Initialize our window. */
    InitGL(640, 480);

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;
}

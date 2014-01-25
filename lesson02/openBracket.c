#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library


void DrawOpenBracket(float xrot, float yrot, float zrot, GLuint texture)
{
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture);

    // draw a square (quadrilateral)
    glBegin(GL_QUADS);				// start drawing a polygon (4 sided)

    // Down
    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, -0.5f,  0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f,  0.0f,  0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f,  0.0f,  0.5f);	// Top Left Of The Texture and Quad

    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, -0.5f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f,  0.0f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f,  0.0f, -0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -0.5f, -0.5f);	// Bottom Left Of The Texture and Quad

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -0.5f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, -0.5f, -0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -0.5f,  0.5f);	// Bottom Right Of The Texture and Quad

    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, -0.5f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.2f,  0.0f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.2f,  0.0f,  0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.4f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, -0.5f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.2f,  0.0f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.2f,  0.0f,  0.5f);	// Top Left Of The Texture and Quad

    // Up
    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f,  0.0f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f,  0.0f,  0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f,  0.5f,  0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.5f,  0.5f);	// Top Left Of The Texture and Quad

    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f,  0.0f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.5f, -0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f,  0.0f, -0.5f);	// Bottom Left Of The Texture and Quad

    // Top Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.5f, -0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.4f,  0.5f,  0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.4f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad

    // Left Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.2f, -0.0f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.5f,  0.5f);	// Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.0f,  0.5f);	// Bottom Left Of The Texture and Quad

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.2f,  0.0f,  0.5f);	// Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.2f,  0.0f, -0.5f);	// Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.4f,  0.5f,  0.5f);	// Top Left Of The Texture and Quad

    glEnd();					// done with the polygon

    glRotatef(xrot,-1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f,-1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f,-1.0f);
}

/* vim: set et sw=4 ts=4: */


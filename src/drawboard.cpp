#include <GL/glut.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include "drawboard.h"

/* order of vertices:
   bottom-left
   top-left
   top-right
   bottom-right
   and front face first.
*/

float box_vertices[8][3] = {
        {-X, -Y, Z},
        {-X, Y, Z},
        {X, Y, Z},
        {X, -Y, Z},
        {-X, -Y, -Z},
        {-X, Y, -Z},
        {X, Y, -Z},
        {X, -Y, -Z},
};

float walls[NUMBER_OF_WALLS][8][3] = {
        {
                /* right wall */
                {X-T, -Y, Z+H},
                {X-T, Y, Z+H},
                {X, Y, Z+H},
                {X, -Y, Z+H},
                {X-T, -Y, Z},
                {X-T, Y, Z},
                {X, Y, Z},
                {X, -Y, Z},
        },
        {
                /* left wall */
                {-X, -Y, Z+H},
                {-X, Y, Z+H},
                {-X+T, Y, Z+H},
                {-X+T, -Y, Z+H},
                {-X+T, -Y, Z},
                {-X+T, Y, Z},
                {-X, Y, Z},
                {-X, -Y, Z},
        },
        {
                /* top wall */
                {-X+T, Y-T, Z+H},
                {-X+T, Y, Z+H},
                {X-T, Y, Z+H},
                {X-T, Y-T, Z+H},
                {-X+T, Y-T, Z},
                {-X+T, Y, Z},
                {X-T, Y, Z},
                {X-T, Y-T, Z},
        },
        {
                /* bottom wall */
                {-X+T, -Y, Z+H},
                {-X+T, -Y+T, Z+H},
                {X-T, -Y+T, Z+H},
                {X-T, -Y, Z+H},
                {-X+T, -Y, Z},
                {-X+T, -Y+T, Z},
                {X-T, -Y+T, Z},
                {X-T, -Y, Z},
        },
        {
                /* Vertical; X - 2, Y - 1,6 */
                {X_BLOCK(2) - T/2, Y_BLOCK(1), Z+H},
                {X_BLOCK(2) - T/2, Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(1), Z+H},
                {X_BLOCK(2) - T/2, Y_BLOCK(1), Z},
                {X_BLOCK(2) - T/2, Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(2) + T/2, Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(2) + T/2, Y_BLOCK(6), Z},
        },
        {
                /* Vertical; X - 4, Y - 0,2 */
                {X_BLOCK(4) - T/2, Y_BLOCK(0), Z+H},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(4) + T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(4) + T/2, Y_BLOCK(0), Z+H},
                {X_BLOCK(4) - T/2, Y_BLOCK(0), Z},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(4) + T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(4) + T/2, Y_BLOCK(0), Z},
        },
        {
                /* Vertical; X - 6, Y - 0,1 */
                {X_BLOCK(6) - T/2, Y_BLOCK(0) - T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(1), Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(1), Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(0) - T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(0) - T/2, Z},
                {X_BLOCK(6) - T/2, Y_BLOCK(1), Z},
                {X_BLOCK(6) + T/2, Y_BLOCK(1), Z},
                {X_BLOCK(6) + T/2, Y_BLOCK(0) - T/2, Z},
        },
        {
                /* Vertical; X - 6, Y - 2,8 */
                {X_BLOCK(6) - T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(8), Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(8), Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(2) - T/2, Z},
                {X_BLOCK(6) - T/2, Y_BLOCK(8), Z},
                {X_BLOCK(6) + T/2, Y_BLOCK(8), Z},
                {X_BLOCK(6) + T/2, Y_BLOCK(2) - T/2, Z},
        },
        {
                /* Vertical; X - 8, Y - 4,6 */
                {X_BLOCK(8) - T/2, Y_BLOCK(4), Z+H},
                {X_BLOCK(8) - T/2, Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(8) + T/2, Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(8) + T/2, Y_BLOCK(4), Z+H},
                {X_BLOCK(8) - T/2, Y_BLOCK(4), Z},
                {X_BLOCK(8) - T/2, Y_BLOCK(6) - T/2, Z},
                {X_BLOCK(8) + T/2, Y_BLOCK(6) - T/2, Z},
                {X_BLOCK(8) + T/2, Y_BLOCK(4), Z},
        },
        {
                /* Vertical; X - 10, Y - 2,4 */
                {X_BLOCK(10) - T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(10) + T/2, Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(10) + T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(2) - T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(10) + T/2, Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(10) + T/2, Y_BLOCK(2) - T/2, Z},
        },
        {
                /* Vertical; X - 10, Y - 6,7 */
                {X_BLOCK(10) - T/2, Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(7), Z+H},
                {X_BLOCK(10) + T/2, Y_BLOCK(7), Z+H},
                {X_BLOCK(10) + T/2, Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(7), Z},
                {X_BLOCK(10) + T/2, Y_BLOCK(7), Z},
                {X_BLOCK(10) + T/2, Y_BLOCK(6) + T/2, Z},
        },
        {
                /* Horizontall; X - 0,1 Y - 4 */
                {X_BLOCK(0), Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(0), Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(1), Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(1), Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(0), Y_BLOCK(4) - T/2, Z},
                {X_BLOCK(0), Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(1), Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(1), Y_BLOCK(4) - T/2, Z},
        },
        {
                /* Horizontall; X - 2,4 Y - 2 */
                {X_BLOCK(2) + T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(2) - T/2, Z},
                {X_BLOCK(2) + T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(4) - T/2, Y_BLOCK(2) - T/2, Z},
        },
        {
                /* Horizontall; X - 2,4, Y - 6 */
                {X_BLOCK(2) + T/2, Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(4), Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(4), Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(2) + T/2, Y_BLOCK(6) - T/2, Z},
                {X_BLOCK(2) + T/2, Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(4), Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(4), Y_BLOCK(6) - T/2, Z},
        },
        {
                /* Horizontall; X - 4,6 Y - 4 */
                {X_BLOCK(4), Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(4), Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(6) - T/2, Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(4), Y_BLOCK(4) - T/2, Z},
                {X_BLOCK(4), Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(6) - T/2, Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(6) - T/2, Y_BLOCK(4) - T/2, Z},
        },
        {
                /* Horizontall; X - 6,10 Y - 2 */
                {X_BLOCK(6) + T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(2) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(2) - T/2, Z+H},
                {X_BLOCK(6) + T/2, Y_BLOCK(2) - T/2, Z},
                {X_BLOCK(6) + T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(2) + T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(2) - T/2, Z},
        },
        {
                /* Horizontall; X - 9,10, Y - 4 */
                {X_BLOCK(9), Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(9), Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) + T/2, Z+H},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) - T/2, Z+H},
                {X_BLOCK(9), Y_BLOCK(4) - T/2, Z},
                {X_BLOCK(9), Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) + T/2, Z},
                {X_BLOCK(10) - T/2, Y_BLOCK(4) - T/2, Z},
        },
        {
                /* Horizontall; X - 7,12, Y - 6 */
                {X_BLOCK(7), Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(7), Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(12), Y_BLOCK(6) + T/2, Z+H},
                {X_BLOCK(12), Y_BLOCK(6) - T/2, Z+H},
                {X_BLOCK(7), Y_BLOCK(6) - T/2, Z},
                {X_BLOCK(7), Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(12), Y_BLOCK(6) + T/2, Z},
                {X_BLOCK(12), Y_BLOCK(6) - T/2, Z},
        },
};

void quad(int a,int b,int c,int d,float ver[8][3])
{
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3fv(ver[a]);
        glTexCoord2f(1,0);
        glVertex3fv(ver[b]);
        glTexCoord2f(1,1);
        glVertex3fv(ver[c]);
        glTexCoord2f(0,1);
        glVertex3fv(ver[d]);
        glEnd();
        glPopMatrix();
}

void callQuad(float ver[8][3])
{
        quad(0,3,2,1,ver);
        quad(2,3,7,6,ver);
        quad(0,4,7,3,ver);
        quad(1,2,6,5,ver);
        quad(4,5,6,7,ver);
        quad(0,1,5,4,ver);
}

void drawBoard(GLuint texture)
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texture);
        callQuad(box_vertices);
        /* draw walls */
        for(int i = 0; i < NUMBER_OF_WALLS; i++)
                callQuad(walls[i]);
        glDisable(GL_TEXTURE_2D);
}

void drawBall()
{
        extern b2Body *ballBody;
        b2Vec2 position = ballBody->GetPosition();

        glPushMatrix();
        glColor3f(0.74, 0.76, 0.78);
        glTranslatef(position.x, position.y, 0.5 + BALL_RADIUS);
        glutSolidSphere(BALL_RADIUS, 50, 50);
        glPopMatrix();
}

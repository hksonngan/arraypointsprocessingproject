#include "stdafx.h"

#include "graphics.h"

#include <stdio.h>

GLfloat angle = 0;

int InitGL(GLvoid) {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return TRUE;
}

void DrawGLScene(GLvoid) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    angle += 10;
    glTranslatef(0.0f, 0.0f, -3.0f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES); {
        glColor3f((GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)));
        glVertex3f(-1.0f, -0.4f, 0.0f);

        glColor3f((GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)));
        glVertex3f( 1.0f, -0.4f, 0.0f);

        glColor3f((GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)),
                  (GLfloat)(rand() / (rand()+1)));
        glVertex3f( 0.0f,  1.0f, 0.0f);
    }
    glEnd();
}
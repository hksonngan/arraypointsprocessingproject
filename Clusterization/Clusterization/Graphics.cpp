#include "stdafx.h"

#include "graphics.h"

//#define __ENABLE_LIGHTING

int InitGL(GLvoid) {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
#ifdef __ENABLE_LIGHTING
    GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient);

    GLfloat position[] = { 0.0f, 1.0f, -4.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
#endif

    return TRUE;
}
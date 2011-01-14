#include "stdafx.h"

#include "graphics.h"

#include <fstream>

using namespace std;

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);

    return TRUE;
}


char** LoadFile(const char *file) {
    char ** lines = new char*[1];

    lines[0] = NULL;

    ifstream fs(file, ios :: ate );

    size_t size = fs.tellg();

    fs.seekg(0, ios::beg);

    char* source = new char[size + 1];
    memset(source, 0, size + 1);
    fs.read(source, size);

    lines[0] = source;

    fs.close();

    return lines;
}

void printShaderInfoLog(GLuint shader) {
    int infologLen = 0;
    int charsWritten  = 0;
    GLchar *infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
    if (infologLen > 0)
    {
        infoLog = (GLchar*) malloc(infologLen);
        if (infoLog == NULL)
        {
            printf("ERROR: Could not allocate InfoLog buffer\n");
            exit(1);
        }
        glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
        printf("InfoLog:\n%s\n\n", infoLog);
        free(infoLog);
    }
}
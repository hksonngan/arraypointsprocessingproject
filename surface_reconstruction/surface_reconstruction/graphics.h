#pragma once

#include "stdafx.h"

#include <Windows.h>
#include "GLee.h"
#include <GL\GLU.h>

int InitGL();

char** LoadFile(const char *file);
void printShaderInfoLog(GLuint shader);
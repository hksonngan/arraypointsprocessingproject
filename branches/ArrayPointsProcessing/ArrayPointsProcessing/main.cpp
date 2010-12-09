#include <fstream>
#include "PointArrayStructure.h"

using namespace std;

int main(int argc, char *argv[])
{
    PointArray pointArray;
    LoadArray(pointArray, "brain_t2.bin");
    DestroyArray(pointArray);
}
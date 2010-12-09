#ifndef __PointArrayStructure_h__
#define __PointArrayStructure_h__

//все исходные данные
struct PointArray 
{
    short* data; //Плотность в точке
    int sizeX; //размер по х
    int sizeY;
    int sizeZ;
    int scaleX;
    int scaleY;
    int scaleZ;
};

//слой плотностей (x*y плоскость), размер слоя - sizeX * sizeY
struct Layer
{
    Layer(): data(NULL), sizeX(0), sizeY(0) {}
    Layer(short* density, int x, int y): data(density), sizeX(x), sizeY(y) {}
    short* data; //указатель на начало слоя
    int sizeX; //размер по х
    int sizeY; //размер по х
};

//загрузка данных из файла nameFile
void LoadArray(PointArray& pointArray, const char* nameFile)
{
    std::ifstream fs(nameFile,std::ios::in | std::ios::binary);

    fs.read((char*)&pointArray.sizeX,sizeof(int));
    fs.read((char*)&pointArray.sizeY,sizeof(int));
    fs.read((char*)&pointArray.sizeZ,sizeof(int));

    fs.read((char*)&pointArray.scaleX,sizeof(float));
    fs.read((char*)&pointArray.scaleY,sizeof(float));
    fs.read((char*)&pointArray.scaleZ,sizeof(float));

    pointArray.data = new short[pointArray.sizeX * pointArray.sizeY * pointArray.sizeZ];
    fs.read((char*)pointArray.data,2*pointArray.sizeX * pointArray.sizeY * pointArray.sizeX);


    fs.close();
}

//уничтожение исходных данных
void DestroyArray(PointArray& pointArray)
{
    delete [] pointArray.data;
}

//возвращает слой с координатой z(измняется от 0 до sizeZ)
Layer GetLayer(PointArray& pointArray, int z)
{
    return Layer(&pointArray.data[z * pointArray.sizeX * pointArray.sizeY], pointArray.sizeX, pointArray.sizeY);
}

//возвращает плотность в точке слоя с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY)
short GetDensity(Layer& layer, int x, int y)
{
    return layer.data[x + y * layer.sizeY];
}

//возвращает плотность в точке пространства с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY), z(измняется от 0 до sizeZ)
short GetDensity(PointArray& pointArray, int x, int y, int z)
{
    return pointArray.data[x + y * pointArray.sizeY + z * pointArray.sizeX * pointArray.sizeY];
}

#endif
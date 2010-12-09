#ifndef __PointArrayStructure_h__
#define __PointArrayStructure_h__

//��� �������� ������
struct PointArray 
{
    short* data; //��������� � �����
    int sizeX; //������ �� �
    int sizeY;
    int sizeZ;
    int scaleX;
    int scaleY;
    int scaleZ;
};

//���� ���������� (x*y ���������), ������ ���� - sizeX * sizeY
struct Layer
{
    Layer(): data(NULL), sizeX(0), sizeY(0) {}
    Layer(short* density, int x, int y): data(density), sizeX(x), sizeY(y) {}
    short* data; //��������� �� ������ ����
    int sizeX; //������ �� �
    int sizeY; //������ �� �
};

//�������� ������ �� ����� nameFile
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

//����������� �������� ������
void DestroyArray(PointArray& pointArray)
{
    delete [] pointArray.data;
}

//���������� ���� � ����������� z(��������� �� 0 �� sizeZ)
Layer GetLayer(PointArray& pointArray, int z)
{
    return Layer(&pointArray.data[z * pointArray.sizeX * pointArray.sizeY], pointArray.sizeX, pointArray.sizeY);
}

//���������� ��������� � ����� ���� � ������������  x(��������� �� 0 �� sizeX), y(��������� �� 0 �� sizeY)
short GetDensity(Layer& layer, int x, int y)
{
    return layer.data[x + y * layer.sizeY];
}

//���������� ��������� � ����� ������������ � ������������  x(��������� �� 0 �� sizeX), y(��������� �� 0 �� sizeY), z(��������� �� 0 �� sizeZ)
short GetDensity(PointArray& pointArray, int x, int y, int z)
{
    return pointArray.data[x + y * pointArray.sizeY + z * pointArray.sizeX * pointArray.sizeY];
}

#endif
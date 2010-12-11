#ifndef __PointArrayStructure_h__
#define __PointArrayStructure_h__

#include <fstream>

namespace ArrayPointsProcessing
{

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
	void LoadArray(PointArray& pointArray, const char* nameFile);

	//����������� �������� ������
	void DestroyArray(PointArray& pointArray);

	//���������� ���� � ����������� z(��������� �� 0 �� sizeZ)
	Layer GetLayer(PointArray& pointArray, int z);

	//���������� ��������� � ����� ���� � ������������  x(��������� �� 0 �� sizeX), y(��������� �� 0 �� sizeY)
	short GetDensity(Layer& layer, int x, int y);

	//���������� ��������� � ����� ������������ � ������������  x(��������� �� 0 �� sizeX), y(��������� �� 0 �� sizeY), z(��������� �� 0 �� sizeZ)
	short GetDensity(PointArray& pointArray, int x, int y, int z);
}
#endif
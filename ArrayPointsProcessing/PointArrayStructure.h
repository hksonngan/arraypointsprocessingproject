#ifndef __PointArrayStructure_h__
#define __PointArrayStructure_h__

#include <fstream>

namespace ArrayPointsProcessing
{

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
	void LoadArray(PointArray& pointArray, const char* nameFile);

	//уничтожение исходных данных
	void DestroyArray(PointArray& pointArray);

	//возвращает слой с координатой z(измняется от 0 до sizeZ)
	Layer GetLayer(PointArray& pointArray, int z);

	//возвращает плотность в точке слоя с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY)
	short GetDensity(Layer& layer, int x, int y);

	//возвращает плотность в точке пространства с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY), z(измняется от 0 до sizeZ)
	short GetDensity(PointArray& pointArray, int x, int y, int z);
}
#endif
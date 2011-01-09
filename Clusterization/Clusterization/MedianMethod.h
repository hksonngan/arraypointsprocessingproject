#include <vector>
#include "ScanData.h"

/* struct TVoxel
{
	size_t index;				// индекс воксела в наборе исходных данных
	short density;				// значение плотности в вокселе

	TVoxel(): index(0), density(0) {};
	TVoxel(size_t v_index, short v_density): index(v_index), density(v_density) {};
}; */

// Кластер из вокселов
struct TCluster
{
 std::vector <size_t> Objects;				// вектор приведённых индексов вокселов, образующих кластер
 
 // Конструкторы
 TCluster() { Objects.clear(); };
 TCluster(size_t size) 
 { 
  Objects.resize(size); 
  Objects.clear(); 
 };

  void Clear() { Objects.clear(); };
  void Print() 
 {
  std::vector <size_t>::iterator iter = Objects.begin();
  std::vector <size_t>::iterator iter_end = Objects.end();
  for (; iter!=iter_end; ++iter)
  {
	printf("%d \n", *iter);
  }
 }; 
};

// Класс, реализующий метод медиан для кластеризации вокселов
class MedianMethod   
{
 private:

	double Distance(size_t i, size_t j);				// расстояние между вокселами
	double Distance(TCluster cluster, size_t index);	// расстояние от воксела до кластера, которому он принадлежит
	size_t CalcMedian(TCluster cluster);				// вычисление медианы для кластера

	bool* IsMedianModified;								// признак "перевычисления" медианы для каждого кластера
	bool IsAnyMedianModified();							// проверка изменения медианы хотя бы одного кластера 

 public:

	size_t DataSize;									// объём кластеризуемых данных

	size_t NClusters;									// количество рассматриваемых кластеров

	ScanData* InputData;								// данные для кластеризации

	TCluster* Cluster;									// объекты, разбитые на кластеры

	// Конструкторы и деструктор

	MedianMethod();
	MedianMethod(ScanData *data);
	MedianMethod(Layer layer);
	~MedianMethod();

	void ReleaseResources();

	void SetClustersNumber(size_t value);					// задание количества кластеров

	std::vector<TCluster> GetClusters();					// вычисление меток кластеров для каждого воксела
};

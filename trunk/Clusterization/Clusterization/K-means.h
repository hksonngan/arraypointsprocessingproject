#include <vector>
#include "ScanData.h"

using namespace System::ComponentModel;

class KmeansMethod
{
 private:
	     size_t NClusters;						// количество кластеров
		 double* means;							// центры тяжести кластеров
		 size_t CountIterations;				// количество итераций метода
		 size_t DataSize;						// размер данных для кластеризации
		 ScanData* InputData;					// данные для кластеризации
		 std::vector <size_t>* Clusters;		// кластеры между которыми распределяются данные 
		 double GetMean(size_t i);				// вычисление медианы для i-ого кластера
		 void ReleaseResources();				// освобождение занимаемых ресурсов
		
 public:
		

	    // Конструкторы и деструктор
		KmeansMethod(ScanData* DataValue);
		KmeansMethod(Layer layer);
		KmeansMethod();
		~KmeansMethod();
		void SetClustersNumber(size_t value);	// установить число кластеров
		void SetCountIterations(size_t value);	// установить число итераций
		std::vector <std::vector <size_t> > GetClusters( BackgroundWorker^ worker);		// кластеризация методом медиан
};
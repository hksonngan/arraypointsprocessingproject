#include <vector>
#include "../ScanData.h"

using namespace System::ComponentModel;

class KmeansMethod
{
 protected:
			size_t NClusters;						// количество кластеров
			float* means;							// центры тяжести кластеров
			size_t CountIterations;					// количество итераций метода
			size_t DataSize;						// размер данных для кластеризации
			ScanData* InputData;					// данные для кластеризации
			std::vector <size_t>* Clusters;			// кластеры, между которыми распределяются данные 
			float GetMean(size_t i);				// вычисление медианы для i-ого кластера
			void ReleaseResources();				// освобождение занимаемых ресурсов

 public:
	    // Конструкторы и деструктор
	    KmeansMethod(ScanData* DataValue);
		KmeansMethod(Layer layer);
		~KmeansMethod();
		
		void SetClustersNumber(size_t value);											// установить число кластеров
		void SetCountIterations(size_t value);											// установить число итераций
		std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);		// кластеризация методом k-средних
};

class KmeansOpenCLMethod : public KmeansMethod
{
 private: size_t* Labels;										// метки кластеров 

 public:
	 // Конструкторы 
	 KmeansOpenCLMethod(ScanData* DataValue) : KmeansMethod(DataValue) {};
	 KmeansOpenCLMethod(Layer layer) : KmeansMethod(layer) {};
	
	 std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);	//кластеризация методом k-средних с использованием OpenCL
};

class KmeansConditionalMethod: public KmeansMethod			// кластеризация методом k-средних в заданном диапазоне
{
 private:
	short MinDensityRange, MaxDensityRange;					// границы диапазона
	size_t VoxelsNumberInRange();							// подсчёт числа вокселов в заданном диапазоне
	float GetMean(size_t i);								// вычисление значения плотности 

 public:
	 // Конструкторы
	 KmeansConditionalMethod(ScanData* DataValue): KmeansMethod(DataValue) {};
	 KmeansConditionalMethod(Layer layer): KmeansMethod(layer) {};

	void SetRangesOfDensity(short left, short right);							// установить диапазон значений плотности
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);	// условная кластеризация методом k-средних 
}; 
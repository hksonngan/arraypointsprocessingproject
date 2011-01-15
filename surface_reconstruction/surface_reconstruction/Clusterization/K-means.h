#include <vector>
#include "../ScanData.h"

using namespace System::ComponentModel;

class KmeansMethod
{
 protected:
			size_t NClusters;						// ���������� ���������
			float* means;							// ������ ������� ���������
			size_t CountIterations;					// ���������� �������� ������
			size_t DataSize;						// ������ ������ ��� �������������
			ScanData* InputData;					// ������ ��� �������������
			std::vector <size_t>* Clusters;			// ��������, ����� �������� �������������� ������ 
			float GetMean(size_t i);				// ���������� ������� ��� i-��� ��������
			void ReleaseResources();				// ������������ ���������� ��������

 public:
	    // ������������ � ����������
	    KmeansMethod(ScanData* DataValue);
		KmeansMethod(Layer layer);
		~KmeansMethod();
		
		void SetClustersNumber(size_t value);											// ���������� ����� ���������
		void SetCountIterations(size_t value);											// ���������� ����� ��������
		std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);		// ������������� ������� k-�������
};

class KmeansOpenCLMethod : public KmeansMethod
{
 private: size_t* Labels;										// ����� ��������� 

 public:
	 // ������������ 
	 KmeansOpenCLMethod(ScanData* DataValue) : KmeansMethod(DataValue) {};
	 KmeansOpenCLMethod(Layer layer) : KmeansMethod(layer) {};
	
	 std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);	//������������� ������� k-������� � �������������� OpenCL
};

class KmeansConditionalMethod: public KmeansMethod			// ������������� ������� k-������� � �������� ���������
{
 private:
	short MinDensityRange, MaxDensityRange;					// ������� ���������
	size_t VoxelsNumberInRange();							// ������� ����� �������� � �������� ���������
	float GetMean(size_t i);								// ���������� �������� ��������� 

 public:
	 // ������������
	 KmeansConditionalMethod(ScanData* DataValue): KmeansMethod(DataValue) {};
	 KmeansConditionalMethod(Layer layer): KmeansMethod(layer) {};

	void SetRangesOfDensity(short left, short right);							// ���������� �������� �������� ���������
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);	// �������� ������������� ������� k-������� 
}; 
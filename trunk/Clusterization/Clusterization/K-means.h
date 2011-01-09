#include <vector>
#include "ScanData.h"

using namespace System::ComponentModel;

class KmeansMethod
{
 private:
	     size_t NClusters;						// ���������� ���������
		 double* means;							// ������ ������� ���������
		 size_t CountIterations;				// ���������� �������� ������
		 size_t DataSize;						// ������ ������ ��� �������������
		 ScanData* InputData;					// ������ ��� �������������
		 std::vector <size_t>* Clusters;		// �������� ����� �������� �������������� ������ 
		 double GetMean(size_t i);				// ���������� ������� ��� i-��� ��������
		 void ReleaseResources();				// ������������ ���������� ��������
		
 public:
		

	    // ������������ � ����������
		KmeansMethod(ScanData* DataValue);
		KmeansMethod(Layer layer);
		KmeansMethod();
		~KmeansMethod();
		void SetClustersNumber(size_t value);	// ���������� ����� ���������
		void SetCountIterations(size_t value);	// ���������� ����� ��������
		std::vector <std::vector <size_t> > GetClusters( BackgroundWorker^ worker);		// ������������� ������� ������
};
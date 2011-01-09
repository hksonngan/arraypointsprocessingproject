#include <vector>
#include "ScanData.h"

/* struct TVoxel
{
	size_t index;				// ������ ������� � ������ �������� ������
	short density;				// �������� ��������� � �������

	TVoxel(): index(0), density(0) {};
	TVoxel(size_t v_index, short v_density): index(v_index), density(v_density) {};
}; */

// ������� �� ��������
struct TCluster
{
 std::vector <size_t> Objects;				// ������ ���������� �������� ��������, ���������� �������
 
 // ������������
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

// �����, ����������� ����� ������ ��� ������������� ��������
class MedianMethod   
{
 private:

	double Distance(size_t i, size_t j);				// ���������� ����� ���������
	double Distance(TCluster cluster, size_t index);	// ���������� �� ������� �� ��������, �������� �� �����������
	size_t CalcMedian(TCluster cluster);				// ���������� ������� ��� ��������

	bool* IsMedianModified;								// ������� "��������������" ������� ��� ������� ��������
	bool IsAnyMedianModified();							// �������� ��������� ������� ���� �� ������ �������� 

 public:

	size_t DataSize;									// ����� �������������� ������

	size_t NClusters;									// ���������� ��������������� ���������

	ScanData* InputData;								// ������ ��� �������������

	TCluster* Cluster;									// �������, �������� �� ��������

	// ������������ � ����������

	MedianMethod();
	MedianMethod(ScanData *data);
	MedianMethod(Layer layer);
	~MedianMethod();

	void ReleaseResources();

	void SetClustersNumber(size_t value);					// ������� ���������� ���������

	std::vector<TCluster> GetClusters();					// ���������� ����� ��������� ��� ������� �������
};

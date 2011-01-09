#include "stdafx.h"
#include "MedianMethod.h"

using namespace std;

MedianMethod::MedianMethod()
{
 DataSize = 0;
 NClusters = 0;
 InputData = NULL;
 Cluster = NULL;
}

MedianMethod::MedianMethod(ScanData *data)
{
 ReleaseResources();
 InputData = data;
 DataSize = data->sizeX*data->sizeY*data->sizeZ;
}

MedianMethod::MedianMethod(Layer layer)
{
 ReleaseResources();
 InputData = new ScanData(layer);
 DataSize = layer.sizeX*layer.sizeY;
}

void MedianMethod::SetClustersNumber(size_t value) {NClusters = value;}

void MedianMethod::ReleaseResources()
{
 //delete [] InputData;
 InputData = NULL;
 Cluster = NULL;
 NClusters = 0;
 DataSize = 0;
}

MedianMethod::~MedianMethod()
{
 delete [] InputData;
 delete [] Cluster;
 InputData = NULL;
 Cluster = NULL;
 NClusters = 0;
 DataSize = 0;
}

// ���������� ����� ��������� (�� ���������)
double MedianMethod::Distance(size_t i, size_t j)
{
 size_t x1 = i%InputData->sizeX;
 size_t y1 = (i-x1)%(InputData->sizeX*InputData->sizeY);
 size_t z1 = (i-x1-InputData->sizeX*y1)/(InputData->sizeX*InputData->sizeY); 

 size_t x2 = j%InputData->sizeX;
 size_t y2 = (j-x2)%(InputData->sizeX*InputData->sizeY);
 size_t z2 = (j-x2-InputData->sizeX*y2)/(InputData->sizeX*InputData->sizeY);

 return InputData->GetDistination(x1, y1, z1, x2, y2, z2); 
}

// ���������� ����� �������� � ���������, �������� �� �����������
double MedianMethod::Distance(TCluster cluster, size_t index)
{
 double Sum = 0;
 size_t cluster_size = cluster.Objects.size();

 vector<size_t>::iterator iter = cluster.Objects.begin();
 vector<size_t>::iterator iter_end = cluster.Objects.end();

 for (; iter!=iter_end; ++iter)
	 if (*iter!=index) Sum += Distance(*iter, index);
 
 return Sum;
}

// ���������� ������� ��� ����������� ��������
size_t MedianMethod::CalcMedian(TCluster cluster)
{
 size_t result;

 double min_dist = System::Double::MaxValue;

 size_t cluster_size = cluster.Objects.size();

 for (size_t i = 0; i < cluster_size; ++i) 
 {
  double new_dist = Distance(cluster, cluster.Objects.at(i));

  if (new_dist < min_dist)
  {
   result = (int)cluster.Objects.at(i);
   min_dist = new_dist;
  }
 }

 return result;
}

// �������� ����������� ���� �� ����� �� ������
bool MedianMethod::IsAnyMedianModified()
{
 bool result = false;

 for (size_t i = 0; i < NClusters; ++i)
 if (IsMedianModified[i]) { result = true; break; }
 
 return result;
}

// ������������� ������� ������
vector <TCluster> MedianMethod::GetClusters()
{
 Cluster = new TCluster[NClusters];

 size_t CountIterations;

 size_t part = DataSize/NClusters;

 int* median = new int [NClusters];

 // ������������� ��������� 
 for (size_t i = 0; i < NClusters; ++i)
 {
  for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
  /*if (InputData->data[j]==0) Cluster[0].Objects.push_back(j); 
  else if (i==0) Cluster[1].Objects.push_back(j); 
  else */ Cluster[i].Objects.push_back(j);
 }
 
 IsMedianModified = new bool [NClusters];

 IsMedianModified[0] = false;

 for (size_t i = 0; i < NClusters; ++i) IsMedianModified[i] = true;
 
 for (CountIterations = 0; CountIterations < 1; CountIterations++) 
 {
  // ������������� ������� ��� ���������
  for (size_t i = 0; i < NClusters; ++i) 
  if (Cluster[i].Objects.size()>0)
  { 
   int new_median = (int)CalcMedian(Cluster[i]); 
   IsMedianModified[i] = new_median==median[i] ? false : true;
   median[i] = new_median; 
   
   Cluster[i].Clear();
  }  else median[i] = -1;

  // ���������������� ������� ����� ����������
  for (size_t j = 0; j < DataSize; ++j) 
  //if (InputData->data[j]!=0)	  
  {
   size_t optimal_cluster_id;  // ����� ��������, ��������� ������� ����������� ��� �������
   
   double min_dist = System::Double::MaxValue;
   
   for (size_t k = 0; k < NClusters; ++k) 
   {
  	if (median[k]>=0)
	{
     double new_dist = Distance(j, median[k]);
     if (new_dist < min_dist)
     {
      optimal_cluster_id = k;
      min_dist = new_dist;
     }
	}
   } 
   
   Cluster[optimal_cluster_id].Objects.push_back(j);
  }
  
 }
  
 TCluster tmp_cluster;
 vector <TCluster> Clusters;
 Clusters.clear();

 for (size_t i = 0; i < NClusters; ++i) 
 if (Cluster[i].Objects.size()>0)
 Clusters.push_back(Cluster[i]);
 
 return Clusters;
}
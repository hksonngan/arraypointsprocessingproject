#include "stdafx.h"
#include "K-means.h"
#include <math.h>
//#include <cl.h>

using namespace std;



void KmeansMethod::ReleaseResources()
{
 InputData = NULL;
 Clusters = NULL;
 means = NULL;
 NClusters = 0;
 DataSize = 0;
}

KmeansMethod::KmeansMethod(ScanData *DataValue)
{
 ReleaseResources();	
 InputData = DataValue;
 DataSize = InputData->sizeX*InputData->sizeY*InputData->sizeZ;
}

KmeansMethod::KmeansMethod(Layer layer)
{
 ReleaseResources();
 InputData = new ScanData(layer);
 DataSize = layer.sizeX*layer.sizeY;
}

KmeansMethod::KmeansMethod() { ReleaseResources(); }

KmeansMethod::~KmeansMethod() { ReleaseResources(); }

void KmeansMethod::SetClustersNumber(size_t value) { NClusters = value; }

void KmeansMethod::SetCountIterations(size_t value) { CountIterations = value; }

// ¬ычисление центра т€жести дл€ i-ого кластера
double KmeansMethod::GetMean(size_t i)
{
 double Sum = 0;
 vector <size_t>::iterator iter = Clusters[i].begin();
 vector <size_t>::iterator _end = Clusters[i].end();
 for (; iter!=_end; ++iter) Sum += InputData->data[*iter];
 return Sum/Clusters[i].size();
}

vector <vector <size_t> > KmeansMethod::GetClusters(BackgroundWorker^ worker)
{
 size_t part = DataSize/NClusters;

 Clusters = new vector <size_t> [NClusters];

 for (size_t i = 0; i < NClusters; ++i)
 {
  for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
  Clusters[i].push_back(j);
 }

 means = new double [NClusters];

 for (size_t iter = 1; iter <= CountIterations; ++iter)
 {
  for (size_t i = 0; i < NClusters; ++i) 
  if (Clusters[i].size()>0) 
  {
   means[i] = GetMean(i); 
   Clusters[i].clear();
  }
  else means[i] = -1;
	
  for (size_t j = 0; j < DataSize; ++j)
  {
   size_t optimal_cluster_id = 0;

   double min_dist = (double)INT_MAX;

   for (size_t k = 0; k < NClusters; ++k) if (means[k]>=0)
   {
    double new_dist = fabs((double)InputData->data[j]-means[k]);
    if (new_dist < min_dist)
    {
     optimal_cluster_id = k;
     min_dist = new_dist;
    }
   }

   Clusters[optimal_cluster_id].push_back(j);
  }

  worker->ReportProgress(100*iter/CountIterations);
 }

 vector <vector <size_t> > result;
 result.clear();
 for (size_t i = 0; i < NClusters; ++i)
 if (Clusters[i].size()>0) result.push_back(Clusters[i]);

 return result;
}
#pragma once

class GraphVoxel
{
public:

    GraphVoxel();
    GraphVoxel(int maxCountSegments);

protected:
    int maxCountSegments;
    int currentCountSegments;
    int* segments;
};
//������� ��������
const byte relativeIndexMatrix[26][3] = {//i,j,k
    {0,0,0},//0
    {0,0,1},//1
    {0,0,-1},//2
    {0,1,0},//3
    {0,1,1},//4
    {0,1,-1},//5
    {0,-1,0},//6
    {0,-1,1},//7
    {0,-1,-1},//8
    {1,0,0},//9
    {1,0,1},//10
    {1,0,-1},//11
    {1,1,0},//12
    {1,1,1},//13
    {1,1,-1},//14
    {1,-1,0},//15
    {1,-1,1},//16
    {1,-1,-1},//17
    {-1,0,0},//18
    {-1,0,1},//19
    {-1,0,-1},//20
    {-1,1,0},//21
    {-1,1,1},//22
    {-1,1,-1},//23
    {-1,-1,0},//24
    {-1,-1,1},//25
    {-1,-1,-1},//26
}

//��������� ������� � ���������������� ������
class Segment
{
public:
    int countVoxel;//���������� ����� ���������
    int* voxel;//������� � ����� �������
    int weightSegment;//��� ��������(������������ ������� ����� �������)
    int valueSegment;//�������� � ��������
    Segment* next;
};

class LayerSegmentsTree
{
    int maxCapacity;//������������ ���������� ����� � ���������
    int countSegment;//���������� ���������
    Segment* segment;//������ �� ��������
    LayerSegmentsTree* up;//����� ������
    LayerSegmentsTree* down;//���� ������
    int maxValueSegment;//������������ �������� ���������
    Segment* oldSegment;//������ �� ��������� �������
};

//��������� ��������� ������ ��������
class SegmentsTree
{
public:
    int countLayer;//���������� �������
    LayerSegmentsTree* root;//������
};
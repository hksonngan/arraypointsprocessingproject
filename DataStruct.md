#Структура данных 3d массивов

# Что хранится в бинарных исходных файлах MRI #

1) размер массива по X (int) количество точек в трехмерной матрице<br>
2) размер массива по Y (int) ...<br>
3) размер массива по Z (int) ...<br>

4) размер воксела по X (float) ??? <br>
5) размер воксела по Y (float)<br>
6) размер воксела по Z (float)<br>

7) 3д массив, т.е. size.x <b>size.y</b> size.z чисел (short) - Это плотность в точке.<br>
Таким образом нам дана обычная трехмерная матрица засунута в бинарный файл по строчно, координаты изменяются от 0 до sizeX(пункт 1) для координаты x и т.д.<br>
Т.е. мы имеем обычную функцию от трех переменных, при отображение это значение цвета(оттенок серого) в точке. Координаты это int изменяющиеся от 0 до sizeX.<br>
<br>
<h1>Структура данных в программе</h1>

//все исходные данные<br>
struct PointArray<br>
{<br>
<blockquote>short<b>data; //Плотность в точке</b><br>
int sizeX; //размер по х<br>
int sizeY;<br>
int sizeZ;<br>
int scaleX;<br>
int scaleY;<br>
int scaleZ;<br>
};</blockquote>

//слой плотностей (x*y плоскость), размер слоя - sizeX <b>sizeY<br>
struct Layer<br>
{<br>
<blockquote>Layer(): data(NULL), sizeX(0), sizeY(0) {}</b><br>
Layer(short<b>density, int x, int y): data(density), sizeX(x), sizeY(y) {}</b><br>
short<b>data; //указатель на начало слоя</b><br>
int sizeX; //размер по х<br>
int sizeY; //размер по y<br>
};</blockquote>

<h1>методы работы с данными</h1>
//загрузка данных из файла nameFile<br>
void LoadArray(PointArray& pointArray, const char<b>nameFile)</b><br>

//уничтожение исходных данных<br>
void DestroyArray(PointArray& pointArray)<br>


//возвращает слой с координатой z(измняется от 0 до sizeZ)<br>
Layer GetLayer(PointArray& pointArray, int z)<br>

//возвращает плотность в точке слоя с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY)<br>
short GetDensity(Layer& layer, int x, int y)<br>

//возвращает плотность в точке пространства с координатами  x(измняется от 0 до sizeX), y(измняется от 0 до sizeY), z(измняется от 0 до sizeZ)<br>
short GetDensity(PointArray& pointArray, int x, int y, int z)<br>
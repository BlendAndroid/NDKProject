#include "./include/ArrayList.h"
#include "iostream"
using namespace std;

// 构造函数
ArrayList::ArrayList(int capacity)
{
    this->actulSize = 0;
    this->size = capacity;
    this->arr = new int[this->size]; // new  delete  / malloc  free
}

ArrayList::~ArrayList()
{
    if (this->arr != NULL)
    {
        delete[] this->arr;
        this->arr = NULL;
    }
}

ArrayList::ArrayList()
{
    this->size = 16;
    this->actulSize = 0;
    this->arr = new int[this->size];
}

// 拷贝构造函数
ArrayList::ArrayList(const ArrayList &arr)
{
    this->actulSize = arr.actulSize;
    this->size = arr.size;
    // 数组名是一个常量指针，指向数组的首元素，因此数组名是不可修改的。也就是说，你不能修改数组名指向的地址，但是可以修改数组元素的值
    this->arr = new int[arr.size];
    for (int i = 0; i < size; ++i)
    {
        this->arr[i] = arr.arr[i];
    }
}

void ArrayList::add(int val)
{
    //    actulSize 最后一个位置  0
    add(val, actulSize);
}

void ArrayList::add(int val, int index)
{
    if (index < 0 || index > size)
    {
        return;
    }
    //    扩容 ---》   0.75
    if (this->actulSize >= size)
    {
        resize();
    }
    //    下标法    地址法
    //   (*( this->arr+index)) = val;
    this->arr[index] = val;
    actulSize++;
}

void ArrayList::resize()
{
    cout << "----------------resize-------" << endl;
    int neLength = size * 2;
    int *p = new int[neLength];
    for (int i = 0; i < size; ++i)
    {
        *(p + i) = arr[i];
    }
    // 要移除掉
    delete[] this->arr;

    this->arr = p;
    this->size = neLength;
}

int ArrayList::get(int index)
{
    if (index < 0 || index > size)
    {
        return -1;
    }
    return this->arr[index];
}

void ArrayList::remove(int index)
{
    if (index < 0 || index > size)
    {
        return;
    }
    // 获取要移除的目标元素
    int targetElement = arr[index];
    for (int i = index; i < size - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }
    actulSize--;
}

int ArrayList::getLength()
{
    return actulSize;
}

bool ArrayList::isEmpty()
{
    return actulSize == 0;
}

void ArrayList::toString()
{
    cout << "[ ";
    for (int i = 0; i < actulSize; i++)
    {
        cout << arr[i] << " , ";
    }
    cout << "]" << endl; // flush
}

#ifndef LS10_ARRAYLIST_H
#define LS10_ARRAYLIST_H

class ArrayList
{
public:
    ArrayList();

    // explicit用于修饰类构造函数，表示该构造函数不能用于隐式类型转换。这意味着在使用该构造函数时，必须显式地进行类型转换
    explicit ArrayList(int capacity);

    // 拷贝构造函数
    ArrayList(const ArrayList &arrayList);

    // 析构函数
    ~ArrayList();

    void add(int val);

    void add(int val, int size);

    int get(int pos);

    void remove(int index);

    int getLength();

    bool isEmpty();
    //    数组不够了 扩容机制
    void resize();

    void toString();

    void test();

private:
    //    数组.length（）
    int size;
    int actulSize;
    // 这里定义的数组为指针，因为要扩容，得重新赋值，而数组是一个常量指针，不能重新赋值
    int *arr; // 常量
};

#endif // LS10_ARRAYLIST_H

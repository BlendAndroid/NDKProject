#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    string s1();              // si = ""
    string s2("Hello");       // s2 = "Hello"
    string s3(4, 'K');        // s3 = "KKKK"
    string s4("12345", 1, 3); // s4 = "234"，即 "12345" 的从下标 1 开始，长度为 3 的子串
    string s5 = "Hello";
    // string s6 = 'K';
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
    cout << "s5: " << s5 << endl;

    // 最好不要这样写，c最后指向的内容是垃圾，因为s对象被析构，其内容被处理
    const char *cc = s2.c_str();

    char c[20];
    strcpy(c, s2.c_str());

    cout << "cc: " << cc << endl;
    cout << "c: " << c << endl;

    return 0;
}
//############################## CPP开篇 #######################################
#if 0
//==============================================================================
// C++支持的编程范式：
// 面向过程：顺序+选择+循环
// 数据抽象 = ADT（抽象数据类型）：数据 + 操作 -> 封装
// 基于对象：封装
// 面向对象：封装+继承+多态：程序 = 对象 + 对象 + 消息传递
// 泛型编程：              ：程序 = 对象 + 对象 + 抽象行为 ： 抽象行为施加在不同类型之上
// 模板元编程：给出代码产生规则，让编译器产生功能代码实现预期功能，某些运行时工作提前到
//             编译器来完成，增加了编译时间，但提高了运行效率。可以实现神奇的类型推导。
// 函数式：更多的使用递归而不是循环（lambda表达式和闭包）
//==============================================================================
// C++11值得学习的新特性：
// 智能指针；
// 右值引用；
// function库 + bind库；
// lambda表达式 + 闭包；
//==============================================================================
// 推荐书籍：
// 《C++编程规范》   |  编程规范
// 《Fffective C++》 |  编程规范
// 《敏捷软件开发》
// 《代码大全》
//==============================================================================

#include <iostream>

int main()
{
    std::cout << "Hello" << std::endl;

    return 0;
}
#endif

//############################### const ########################################
#if 0
//==============================================================================
// const定义的只读变量的作用于变量本身。
// 高层次编程中尽量用const、enum替换#define; 用inline替换带参数的#define。
// 底层（如框架）编程中#defie是很灵活的(如#与##的用法)，替换就预示着灵活，如泛型编程
//===============================================================================

#include <iostream>
using std::cout;
using std::endl;

int f(int a)
{
    return a;
}

#define STR(a) #a
#define CAT(a,b) a##b
// 宏的副作用
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

// 结构体内存对齐
#pragma pack(2) // 能设置的最大数与操作系统位数有关，x64 -> 8; x86 -> 4
struct Test
{
    char ch;
    double dval;
    char ch2;
};
#pragma pack()

int main()
{
    int xy = 100;
    cout << STR(ABCD) << endl; // #ABCD <=> "ABCD"
    cout << CAT(x, y) << endl; // x##y  <=> xy

    int a = 5;
    int b = 0;
    CALL_WITH_MAX(++a, b);    // a被累加了2次
    CALL_WITH_MAX(++a, b+10); // a被累加了1次  =>调用f之前a的递增次数竟然取决于与和谁比较！

    cout << sizeof(Test) << endl;

    return 0;
}
#endif

//################################ new #########################################
#if 0
//==============================================================================
// ::域运算符，用于访问与局部变量同名的全局变量
//==============================================================================
// new：创建堆空间：成功返回首地址，*失败不会返回空指针，直接抛出异常*
// new的三种用法：
// new operator  <=> 内存分配(operator new) + 调用构造函数
// operator new  <=> 内存分配
// placement new <=> 不分配内存，只是调用拷贝构造函数
//==============================================================================
// delete <=> 调用析构函数 + 释放内存
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

int val = 100;

int main(void)
{
    int val = 50;
    cout << val << endl;   // 访问的是局部的那个val
    cout << ::val << endl; // 域运算符，此时访问的是全局的那个val

    int *p_val = new int(10);
    int array[10] = {0};
    int *p_array = array; // 数组名代表首元素地址，*array<=>array[0]
    cout << sizeof(p_val) << endl;   //  8 bytes
    cout << sizeof(p_array) << endl; //  8 bytes 因为这就是个指针
    cout << sizeof(array) << "  " << *array << endl;   // 40 bytes 数组不是指针
    delete p_val;

    int *p_array2 = new int[10];
    delete [] p_array2;

    return 0;
}
#endif

//############################## 函数重载 #######################################
#if 0
//==============================================================================
// 函数重载是指的参数不同的同名函数，如果仅仅是返回值不同，参数完全相同，则无法进行
// 重载。
//==============================================================================
// name managling(名字改写机制)。
// extern "C"表示不进行名称改写；不使用名称改写，就不能使用函数重载功能。
// C++与C混合编程 => C++代码要想用到C中必须用extern "C",因为C中没有函数重载。
//==============================================================================
// 函数参数默认值，从右到左原则。
// 如果没有声明，则在函数定义时指定默认值，有声明，则只能在函数声明时指定默认
// 参数，函数定义的时候不能再次给定默认值。
// **注意默认参数引起的二义性。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

void func(int a, int b)
{
    cout << a*b << " int func a+b" << endl;
}

void func(int a, int b, int c = 5)
{
    cout << a*b << " int func a+b+c" << endl;
}

void func(float a, float b)
{
    cout << a*b << " float func" << endl;
}

#ifdef __cplusplus
extern "C"
{
#endif
void func(double a)
{
    cout << a << " xxxx" << endl;
}

void func2(double a)
{
    cout << a << " xxxx" << endl;
}
#ifdef __cplusplus
}
#endif


int main(void)
{
    func(3);

    // 当给两个实参时，func(int a, int b)与func(int a, int b, int c = 5)都能匹配
    // 上，出现二义。这时要想继续使用，可以把三个参数的默认值去掉。
    // func(3, 5);

    func(1.0f, 2.0f);
    func(3.0);

    return 0;
}
#endif

//################################ 引用 ########################################
#if 0
//==============================================================================
// 变量 = 名称 + 内存空间。
// 引用不是变量，只是变量的别名，它没有自己的内存空间，它与所引用变量共享内存空间。
// 引用必须初始化，引用一经初始化，不能再指向其它变量。
//==============================================================================
// const引用:不能被修改。
// 非const引用不能指向const对象。
// const引用可以指向非const对象，只是不能使用这个引用修改所引用的对象的值。
// **const引用可以使用类型转换特性，非const引用不支持使用类型转换，只能指向同类型的对象。
// 非const引用不能绑定临时对象

#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
    int val = 10;
    int& ref_val = val;
    ref_val = 20; // 实际上改变的是val代表的内存，因为引用本身没有内存空间。
    cout << val << endl;

    int val2 = 100;
    ref_val = val2; // 这里不是将ref_val引用至val2，而是用val2的值来改变val。
    cout << val << endl;

    const int a = 10;
    const int& ref_a = a;
    // ref_a = 1; // ERROR:const
    cout << ref_a << endl;
    //int& ref_a2 = a; // binding "const int" to reference of type "int&"是不允许的

    int b = 10;
    const int& ref_b = b;
    // ref_b = 2; // ERROR:const
    cout << ref_b << endl;

    double c = 100.2;
    const int& ref_c = c; // ** 可以编译通过：<=> int temp = c; const int& ref_c = temp;
    cout << "c = " << c << endl;
    cout << "ref_c = " << ref_c << endl;

    // int& ref_c2 = c; // ** 编译不通过

    return 0;
}
#endif

//############################ 引用做函数参数 ###################################
#if 0
//==============================================================================
// 引用作为参数传递，使得形参与实参在内存中共享存储单元，从而实现形参改变实参。
// 引用作为函数返回值：使得函数可以作为左值（可以放在赋值运算符左边）。
// 函数返回引用时，这个引用是在函数返回的时候被初始化的。
//==============================================================================
// 函数不能返回局部变量/auto变量的引用。
//==============================================================================
// 引用没有自己的内存空间，而指针有自己的内存空间。
// 引用一经初始化不能再引用其它变量，而非const指针可以。
// C++推荐尽可能使用引用，迫不得已时使用指针。
//==============================================================================
// 引用与指针的区别：
// 值传递  ：实参初始化形参要分配内存空间，将实参内容拷贝到形参。
// 引用传递：实参初始化形参不分配内存空间。
// 指针传递：本质是值传递，要分配内存空间。
//           要修改指针的地址，单纯用指针传递是不行的，要用指针的指针或者指针引用。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

int a[] = {0, 1, 2, 3, 4};

int& index(int i)
{
    return a[i];
}

int& add(int a, int b) // 返回局部变量的引用
{
    int sum;
    sum = a + b;

    return sum;
}

int main(void)
{
    index(3) = 100; // => a[3] = 100
    cout << a[3] << endl;

    int sum1 = add(3, 4);  // sum1是变量，有独立的内存空间，功能正常。
    int& sum2 = add(5, 6); // sum2是引用，没有自己独立的内存空间，sum2的值依赖域它
                           // 所引用的变量，如果sum2所引用的变量的生命周期结束了，
                           // sum2就变成了一个无效的引用，sum2的值将是不确定的。
    cout << "sum1 = " << sum1 << endl;
    cout << "sum2 = " << sum2 << endl;


    return 0;
}
#endif

//########################## 内联函数、CPP类型转换 ##############################
#if 0
//==============================================================================
// 内联函数：内联函数是由编译器进行展开。
// 什么时候用：代码体短小精悍，经常调用的函数适合声明为内联函数，函数前面加inline。
//==============================================================================
// 内联函数与带参数的宏区别：
// 内联函数调用时会进行实参和形参的类型检查，宏函数只是简单的把形参替换为实参。
// 内联函数是在编译的时候将代码展开，而宏函数是在预处理的时候将代码展开。
//==============================================================================
// C++类型转换：（实际上是对原先C的类型转换进行了细分）
// 旧式：(T)expr
//       T(expr)
// 新式：const_cast<T>(expr)：移除对象的常量属性，主要用于指针或者引用。
//                            去除指针或引用的const限定的目的不是用来修改它的内容，
//                      （**）通常是为了函数能够接受这个实际参数。
//       static_cast<T>(expr)：隐式类型转换=>显示类型转换
//       reinterpret_cast<T>(expr)：将数据以二进制存在形式重新解释，如指针类型
//                                  变量与整形变量相互转换。
//       dynamic_cast<T>(expr)：一般用于派生类与基类之间的转型操作，支持运行时识别
//                              指针或它所指向的对象，实现“安全向下”转型。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include <cstring>

void func(int &val)
{
    cout << "func " << val << endl;
}

int main(void)
{
    const int val = 100;
    // 返回的是值，需要用新的变量来接收，原变量啥变化也没有，这个转型没任何意义，编译不通过。
    // int n = const_cast<int>(val); // 不用于变量。
    int n = val; // 不涉及转型，可以编译通过。

    // 即使使用了旧的(c)类型转换也无法改变const变量的值，而C语言里可以通过这种方式改变。
    int* p2 = (int*)(&val);
    *p2 = 200;
    cout << val << endl;

    // int* p = &val; // Error：无法从const int*转换为int*
    int* p = const_cast<int*>(&val);
    *p = 200;
    cout << val << "\t" << *p << endl; // 并没有发生改变,val=100,*p=200
    cout << "&val = " << &val << endl; // 并没有发生改变
    cout << "   p = " << p << endl;    // 但p确实是指向了val ?

    int& ref_val = const_cast<int&>(val);
    cout << ref_val << endl;           // 200
    cout << val << "\t" << *p << endl; // 100  200

    func(const_cast<int&>(val)); // 函数形参是非const的，需要使用const的，那就要去const

    char *p3 = "This is a char*";
    // 指针转换为整形（转换后i里存的是指针变量里的内容，不是指针变量本身的地址）
    long i = reinterpret_cast<long>(p3); // i和p3在内存中占的byte数一定要一样
    printf("%p,  %p\n", p3, i);

    long ip = 100;
    char *pc = reinterpret_cast<char*>(ip); // pc和ip的byte数一定要一样
    printf("%p,  %p\n", ip, pc);
    // 整形转换为指针,但pc指向的并不真的是字符串，不能当字符串来用，如strlen(pc)
    // 造成运行时错误，编译时不会出错。
    cout << strlen(pc) << endl;



    return 0;
}
#endif

//################################# 对象 #######################################
#if 0
//==============================================================================
// 指令 = 操作码 + 操作数
// 结构化程序设计：考虑问题以算法为中心，而不是以数据为中心。
// 程序 = 算法 + 数据结构。
// 数据与数据处理分离 => 导致面向过程程序设计存在缺点
//==============================================================================
// 面向对象：
// 程序 = 对象 + 对象 + ... + 对象 ＋ 发送消息
// 对象 ＝ 算法 ＋ 数据
//==============================================================================
// 对象、继承、
// 多态性（同一接口，不同方法）：使得我们可以以一致的观点来看待不同的对象；同一
// 消息发送到不同的对象，就会呈现出不同的行为。
// 继承 + 多态
//==============================================================================
// 内联：有switch for等不会内联

#include "clock.h"
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
    Clock c;
    c.Init(22, 56, 58);
    c.Display();
    c.Update();
    c.Display();
    c.Update();
    c.Display();

    c.SetHour(10);
    c.Display();

    return 0;
}
#endif

//############################# 类的作用域 #####################################
#if 0
//==============================================================================
// 类作用域：类作用域中说明的标识符只在类中可见。
// 块作用域：花括号之内
// 文件作用域：从定义的地方到文件件结束
// 函数原型作用域：
// 函数作用域：只是针对goto语句
//==============================================================================
// 前向声明：两个类相互引用形成环形引用时，不能两个都在.h中用#include包含对方，
// 这时可以时其中至少一个用前向声明class ...,但前向声明的类不能实例化对象，只能用指针。
//==============================================================================
// 嵌套类与外围类：只是语法上的嵌套，其它照着作用域和类权限规则来，此时的外围类
// 相当于给嵌入类加了个名字空间（共有时外部照样访问，私有时外部无法访问）。
// 嵌套类的成员函数可以在类体外定义。
//==============================================================================
// 局部类：类可以定义在函数内。局部类只在定义它的局部域可见。局部类的成员函数必须
// 定义在类体中，局部类中不可以有静态成员。
//==============================================================================

#include <iostream>

class Outer // 外围类
{
    class Inner // 嵌套类，此处为私有
    {
    public:
        void Func();
    };
public:
    Inner obj_;
    void Func()
    {
        std::cout << "Outer" << std::endl;
        obj_.Func(); // 外围类调用嵌套类的成员函数
    }
};

void Outer::Inner::Func() // 在外部定义嵌套类的成员函数时，需要加对应的外围的名字作为限定
{
    std::cout << "inner" << std::endl;
}

class Test
{
public:
    int num_; // 类作用域
};

// num = 20;   // Error:num的作用域在类内部
int num = 20; // num的作用域是文件作用域，与类中的num是不同的作用域

int Add(int a, int b); // a, b两个标识符的作用域为 函数原型作用域

int Func()
{
    class LocalClass // 只能在该函数内使用
    {
    public:
        int num_;
        void Init(int num)
        {
            num_ = num;
        }
        void Display()
        {
            std::cout << "num_: " << num_ << std::endl;
        }

        // static int i_; // Error:不允许
    };

    LocalClass lc;
    lc.Init(10);
    lc.Display();
}


int main() {
    int num = 30;
    {
        int num = 20; // 块作用域
    }
    std::cout << num << std::endl;  // 30

    Outer outer;
    outer.Func();

    Func();
    // LocalClass lc; // Error:局部类只能在定义它的函数体内使用。

    return 0;
}

int Add(int a, int b)
{
    return a + b;
}

int Test()
{
    LABEL1: // LABEL1、LABEL2、LABEL3是函数作用域
    std::cout << "label1" << std::endl;
    goto LABEL3;
    LABEL2:
    std::cout<< "label2" << std::endl;
    LABEL3:
    std::cout << "label3" << std::endl;
}
#endif

//########################### 构造函数、析构函数 ################################
#if 0
//==============================================================================
// * 构造函数：特殊的成员函数，为了保证每个成员都被正确初始化
// * 构造函数一般声明为公有，否则不能被外部调用。构造函数是自动调用的。
// * 不带参数的构造函数成为默认构造函数。一个类可以有多个构造函数（重载）。
// * 一个构造函数也不写编译器会默认给一个空的构造函数，类不可能没有构造函数。
//   只要编写者定义了一个构造函数，编译器就不会再给提供默认构造函数。
// * 构造函数声明为私有有特殊用途，后面讲解。
// * 构造函数和new运算符 : new operator分配内存并调用构造函数。
//==============================================================================
// * 析构函数不能被重载。
// * 不提供析构函数编译器会默认提供一个空的。
// * 析构函数与delete运算符：delete operator调用析构函数并释放内存。
// * 析构函数与数组：数组创建时会顺次调用每一个元素的构造函数，delete时一样也是
//   顺次调用析构函数。
// * 析构函数可以显式调用：但要注意，如果手动调用了一次析构函数，那对象生命周期
//   结束的时候会再次调用析构函数，就会导致析构了两次，一般不用。
//==============================================================================
// 全局对象的构造先于main函数，全局对象的析构后于main函数。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "Test.h"

// Test global_test(60);

int main(void)
{
#if 0
    cout << "Entering main ..." << endl;
    Test test; // 实例化类的时候调用构造函数，自动调用
    Test test1(10);
    Test *test3 = new Test(20);
    delete test3;
    cout << "Exiting main ..." << endl;
#endif

    Test test_array[2] = {100, 200};
    Test *test_ptr = new Test[2];
    delete [] test_ptr;

    return 0;
}
#endif

//########################### 构造函数初始化列表 ################################
#if 0
//==============================================================================
// 构造函数初始化列表：
// * 推荐最构造函数初始化列表中进行成员变量的初始化。
// * 构造函数的执行分为两个阶段：
//   1、初始化段（初始化列表中）：这里面的是真正的初始化
//   2、普通计算段（构造函数体内）：在构造函数体内的不是初始化，只是普通赋值。
//==============================================================================
// 对象成员（成员变量是一个类对象）及其初始化：
// * 初始化的时候先构造对象成员
//  （按声明的顺序，从上到下依次构造，即使在自身构造函数的初始化列表中重新给了
//   顺序也没用，即它与初始化列表中的初始化顺序无关），再构造自身。析构的时候先
//   析构自身再析构对象成员。
// * 当对象成员有默认构造函数时，在自身的构造函数中如果不显式初始化对象成员，编译器
//   会自动调用对象成员的默认构造函数，此时如果对象成员没有默认构造函数，就会出错。
//   [---注意：如果提供了带参数构造函数，没提供默认构造函数，但是形参都有默认值，
//       那就相当于提供了默认构造函数，因为可以什么参数也不用输入。]
//   也就是说对象成员即使你不显式去初始化它，编译器也会调它的默认构造函数去初始化它，
//   这与普通的auto成员变量不同，auto成员变量当你不显式去初始化它的时候，编译器也
//   不会管它，那它的值就是随机的。
//==============================================================================
// const成员、引用成员初始化：
// * const成员的初始化只能在构造函数的初始化列表中进行。
// * 引用成员的初始化也只能在构造函数的初始化列表中进行。
// * 如果对象成员对应的类没有默认构造函数，那它也只能在构造函数初始化列表中进行。
//==============================================================================
// 枚举成员：
// * 对所有类的对象，枚举值都是相同的->常量 ->常量可以用类名引用Object::TYPE_A
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "clock.h"

class Object
{
public:
    enum E_TYPE // 对于该类所有对象，TYPE_A和TYPE_B都是常量
    {
        TYPE_A = 100,
        TYPE_B = 200
    };
public:
    explicit Object(int num = 0) : num_(num), const_num_(num), ref_num_(num)
    {
        cout << "Object ... " <<  num_ << endl;
    }
    ~Object()
    {
        cout << "～Object ..." <<  num_ << endl;
    }
private:
    int num_;
    const int const_num_; // 只作用于对象内部，类的不同对象之间可以不同。
    int& ref_num_;
};

class Container
{
public:
    Container(int obj1 = 0, int obj2 = 0) : obj2_(obj2), obj1_(obj1)
    {
        cout << "Container" << endl;
    }
    ~Container()
    {
        cout << "~Container" << endl;
    }
private:
    Object obj1_;
    Object obj2_;
};

int main(void)
{
    Clock clock(1, 2, 3);
    clock.Display();
    clock.Update();
    clock.Display();

    cout << "===========================" << endl;

    Container container(10, 20);

    cout << "===========================" << endl;

    Object obj1(10);
    Object obj2(20);
    cout << obj1.TYPE_A << " | " << obj2.TYPE_A << endl;
    cout << Object::TYPE_A << endl; // 常量可以这样用

    return 0;
}
#endif

//############################## 转换构造函数 ##################################
#if 0
//==============================================================================
// * 转换构造函数：单个参数的构造函数称为转换构造函数->将其它类型转换为类类型；
//   只要提供了带一个参数的构造函数，就可以进行隐式转换了。
// * 它同时具有初始化成员变量的传统功能。
//==============================================================================
// * 赋值与初始化区别：初始化时的'='不是运算符，只是被编译器解释为初始化工作，与在
//   class obj()括号中给初始值一样。但赋值时就不同了，'='是运算符。
//==============================================================================
// * explicit：只提供给类的构造函数使用的关键字。
// * 编译器不会把声明为explicit的构造函数用于隐式转换，它只能在程序中显式创建对象。
//   Test t = 10 || t = 20 这两种形式的就都不允许了。注意第一种形式虽然不是赋值，
//   但也不允许,因为用了'='而且两边类型不一致，就意味着要转换了，就不是传统的带一个
//   参数的构造函数了。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "Test.h"

int main(void)
{
    //Test t(10); //  带一个参数的构造函数，充当的是普通构造函数的功能
    // 注意这是赋值，初始化的时候跟这个过程不同
    //t = 20; // 将20这个整数赋值给类对象(隐式转换)：
            // 1、调用构造函数将20这个整数转换成类类型（生成一个临时对象）
            // 2、将临时对象赋值给t对象（调用的是默认的'='运算符|逐成员赋值）,[是赋值，不是拷贝构造函数]
            // 3、释放临时对象

    cout << "===========================" << endl;
    Test t1 = 20; // <=> Test t1(20); *不是运算符*不会调用我们重载的运算符函数
    cout << "===========================" << endl;

    t1 = 30; // 赋值操作(需要转换); 能够转换的前提时要提供带一个参数的构造函数。

    Test t2;
    t1 = t2; // 同类型不需要转换，直接赋值。赋值操作


    return 0;
}
#endif

//############################## 拷贝构造函数 ##################################
#if 0
//==============================================================================
// 拷贝构造函数：
// * 使用一个已经存在的对象来初始化新的对象。
// * 声明：只有一个参数，且参数为该类对象的引用(必须为引用,不能用值传递，值传递会引
//   起循环调用拷贝构造函数)。
// * 拷贝构造函数中，可以访问传入的对象的私有数据成员。
// * 如果没有提供拷贝构造函数，编译器会自动生成一个缺省的拷贝构造函数，作为公有成员。
// ### 默认构造函数、拷贝构造函数编译器可以默认提供。
//==============================================================================
// 拷贝构造函数调用的几种情况：
// * 函数形参是类对象（传值），要调用拷贝构造函数，生成新的对象。
// * 函数返回局部对象,会调用拷贝构造函数生成临时对象，并返回这个临时对象，如果这个临时对象有
//   const引用接收会被立即销毁，如果被接收了就不会被销毁，临时对象只能用const引用接收。临时对象
//   与局部对象行为不太一样。

#include <iostream>
using std::cout;
using std::endl;
#include "Test.h"

void TestFunc(const Test t) // 传值，该形参是函数的局部变量，实参初始化形参，调用构造函数
{
}

void TestFunc2(const Test& t)
{
}

Test TestFunc3(const Test& t)
{
    Test tt(t);
    cout << "TestFunc3" << endl;
    return tt; // 返回的是t的一个拷贝
}

const Test &TestFunc4(const Test& t) {
    Test *tt = new Test(t);
    cout << "TestFunc4" << endl;
    //return const_cast<Test&>(t);
    return *tt;
}

int main(void)
{
    Test t(10); // 带一个参数的构造函数
    cout << "=========================" << endl;
    Test t2(t); // 调用拷贝构造函数
    cout << "=========================" << endl;
    Test t3 = t; // 调用拷贝构造函数 // <=> Test t3(t)  不是赋值运算符
    cout << "=========================" << endl;
    Test tt;
    tt = 30; // 1、转换构造函数，生成临时对象 2、赋值[不是拷贝构造函数] 3、析构临时对象
    cout << "=========================" << endl;
    //TestFunc(20); // 调用转换构造函数
    TestFunc(t);    // 调用拷贝构造函数
    cout << "===========================" << endl;
    TestFunc2(20); // 调用转换构造函数, 会生成一个临时对象，这样调用会生成临时对象，
                   // 但下面的直接用就不行。
    // Test& ttt = 20; // 不可以直接这样调用
    cout << "=========================" << endl;
    TestFunc2(t); // 引用，不会生成新对象，无拷贝函数调用
    cout << "=========================" << endl;
    // ->传参数时不调用拷贝构造函数，但返回的时候要创建无名临时对象，调用拷贝构造函数
    // ->如果返回的时标量值过程类似，只是不调用拷贝构造函数。
    TestFunc3(t); // 如果返回值没人接收则会立即销毁，调用析构函数。
    cout << "=========================" << endl;
    // ->这里返回值有人接收，返回的临时对象对T进行赋值，调用赋值操作符，赋值完没有
    // ->存在的意义，被立即销毁。
    t = TestFunc3(t); // 如果返回的是函数内部[定义]的局部对象，返回该对象时不会
                      // 调用构造函数生成临时对象，而是直接把这个局部对象当做临
                      // 时对象。如果没有接收的就会随机销毁，如果用来赋值，就会
                      // 在赋值完成后被销毁，如果是初始化，就不销毁了。
    cout << "===========||==============" << endl;
    // ->如果返回值用来初始化新的对象，则不会再进行新的构造，而是等价于将那个临时对
    // ->象改了个名字，变成了有名对象，名字为y,有名对象不会被立即销毁。这里就只有一次
    // ->拷贝构造函数的调用，用来生成那个'临时对象'。
    // ->所以说初始化和赋值差距还是很大的。
    Test y = TestFunc3(t);
    cout << "=========================" << endl;
    //Test& z = TestFunc3(t); //Error:非const引用不能绑定临时对象。
    const Test& z = TestFunc3(t); // const引用绑定临时对象,这时临时对象不会被立即销毁
    cout << "=========================" << endl;
    Test zz = TestFunc4(t); // 调用拷贝构造函数，函数外部调用
    cout << "===========================" << endl;
    const Test &zzz = TestFunc4(t); // 不会调用拷贝构造函数
    cout << "=========================" << endl;

    return 0;
}
#endif

//####################### 类的深浅拷贝、空类默认产生的内容 ######################
#if 0
//==============================================================================
// 深拷贝与浅拷贝：
// * 当类中有指针成员时，编译器默认产生的拷贝构造函数实施的是浅拷贝，需要自己提供
//   拷贝构造函数，实施深拷贝。
//==============================================================================
// 赋值操作：'='运算符的重载
// * 编译器提供的默认等号运算符，也是浅拷贝,逐成员赋值。
//==============================================================================
// 禁止拷贝：有些对象是独一无二的，不允许拷贝给另一个对象。
// * 将拷贝构造函数和赋值操作符声明为私有(不能不写，如果不写编译器会默认产生，为共有函数)，
//   并且不提供它的实现，如果再使用拷贝，则编译时会出错。
//==============================================================================
// 空类默认产生的成员： class Empty {}
// 1、默认构造函数      Empty();
// 2、默认拷贝构造函数  Empty(const Empty&);
// 3、默认析构函数      ~Empty();
// 4、默认赋值运算符    Empty& operator=(const Empty&);
// 5、取址运算符        Empty* operator&();
// 6、取址运算符const   const Empty* operator&() const;
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "String.h"

class Empty
{
public:
    Empty* operator&()
    {
        cout << "AAAAAAAA" << endl;
        return this;
    }

    const Empty* operator&() const
    {
        cout << "BBBBBBBB" << endl;
        return this;
    }
};

int main(void)
{
    String str1("AAA"); // 调用转换构造函数
    str1.Display();
    cout << "===================" << endl;
    String str2 = str1;  // 调用默认拷贝构造函数 -> 浅拷贝
    str2.Display();
    cout << "===================" << endl;
    String str3;
    str3.Display();
    str3 = str2; // 调用编译器提供的默认等号运算符，是浅拷贝
                 // <=> str3.operatoe=(str2)
    cout << "===========||===========" << endl;
    Empty empty;
    cout << sizeof(empty) << endl;
    Empty *p = &empty;     // 调用的是非const取地址符
    //cout << &Empty << endl;
    cout << "===================" << endl;
    const Empty e2;
    const Empty *pp = &e2; // 调用的是const取地址符
    cout << "===================" << endl;

    return 0;
}
#endif

//######################## static成员函数、static成员 ###########################
#if 0
//==============================================================================
// 类static成员：
// * 与类关联，不与类对象关联，被所有类的对象共享。
// * 类的静态成员在类体中声明，在类体外的文件域中进行定义与初始化。必须是在文件域，
//   不能在函数中定义与初始化。
// * 默认值为 0。
// 类static成员优点：
// * 处于类作用域中，可以避免与其它类成员或全局对象出现名字冲突。
// * 静态成员可以私有，封装性好。配合静态成员函数，可以方便获取它的值。
// 特殊情况：
// * static const整型成员：可以在类体内定义并初始化，不需要在类体外再次定义、初始化。
// * 注意：只有整型（char、short、long等都是整型）
// * 可以通过类::调用，也可以通过对象调用，但不推荐。
//==============================================================================
// static成员函数：在类体内或类体外定义都可以，但数据成员没这么自由。
// * static成员函数中没有this指针,所以static成员函数不能访问非static成员，因为非static成员
//   是对象域的，只有通过隐含的this指针才能访问。
// * 但非static函数可以访问static成员。
// * 可以通过类::来调用，也可以通过对象调用，但不推荐。
//==============================================================================
// 类大小计算：
// * 遵循结构体对齐原则。
// * 只与数据成员有关，与成员函数无关，与static成员无关。因为成员函数存于代码段，
//   static成员存于数据区.data,它们都不存在与堆区或栈区。
// * 虚函数对类的大小有影响：每一个虚函数会占用四个字节(x86)/八个字节(x64)的空间，
//   它是指向虚表的指针。
// * 虚继承也会影响类的大小。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "CountedObject.h"

 class Test
 {
 public:
     Test() : y_(0), ch('a')
     {

     }
     explicit Test(int y) : y_(y), ch('a')
     {
        x_++;
     }
     ~Test()
     {
        x_--;
     }

     void TestFunc()
     {
         cout << "x_: " << x_ << "  y_: " << y_ << endl;
     }

     static void TestStaticFunc()
     {
         //cout << "y_: " << y_ << endl;
         cout << "x_: " << x_ << endl;
     }

     static int x_ = 0; // 位于数据区.data，不占类大小
     int y_;  // 4 bytes
     char ch; // 1 bytes
//   char pad[3]; // 3 bytes
 };

//int Test::x_ = 0; // 类体外的文件域中进行定义、初始化。

int main(void)
{
    cout << CountedObject::GetObjectCount() << endl;
    CountedObject obj;
    cout << CountedObject::GetObjectCount() << endl;
    CountedObject *p_obj2 = new CountedObject;
    cout << CountedObject::GetObjectCount() << endl;
    delete p_obj2;
    cout << CountedObject::GetObjectCount() << endl;

    cout << "======================" << endl;

    Test t(10);
    t.TestFunc();
    Test::TestStaticFunc();
    cout << Test::x_ << endl;
    t.TestStaticFunc();
    cout << t.x_ << endl;

    cout << "======================" << endl;

    cout << sizeof(Test) << endl;

    return 0;
}
#endif

//########################### static与单例模式 ##################################
#if 0
//==============================================================================
// static与单例模式：
// * 单例模式是一个设计模式　－>　保证类只有一个实例，并提供一个全局访问点。
// * 将默认构造函数声明为私有成员，就可以防止在类外部定义对象。
// * 定义一个类型为本身的静态变量，然后定义一个共有的静态函数，用于获取实例。
// 问题:
// 1、如何保证析构函数在合适的时候被调用。
//    -> 利用对象的确定性析构，定义一个嵌套类，在该类的析构函数中释放单例类的指针成员，
// 　　　然后定义一个该类的静态成员，当生命周期结束会自动调用嵌套类的析构函数，释放
// 　　　单例类的资源。
//    -> 或者不用指针成员，而是定义一个局部静态变量。
// 2、应该不允许拷贝。
//   －> 编译器会默认生成的那些构造函数（默认构造函数、默认拷贝构造函数，
//       默认赋值运算符），如果我们不希望要，就要禁止编译器自动产生,提供一个私有的,可以
//       只声明不提供实现。
// * 本章的实现简单，但不是线程安全的。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::unique_ptr;

class Singleton
{
public:
    static Singleton& GetInstance()
    {
        static Singleton instance;
        return instance;
    }

//    class Garbo
//    {
//    public:
//        ~Garbo()
//        {
//            if (Singleton::instance_ != nullptr) {
//                delete instance_;
//            }
//        }
//    };
    ~Singleton()
    {
        cout << "~Singleton" <<endl;
    }
private:
    Singleton()
    {
        cout << "Singleton" << endl;
    }
    Singleton(const Singleton& other);
    Singleton&operator=(const Singleton& other);

//    ~Singleton()
//    {
//        cout << "~Singleton" <<endl;
//    }

//    static Singleton *instance_;
//    static Garbo garbo_;
};

//Singleton::Garbo Singleton::garbo_;
//Singleton *Singleton::instance_;

int main(void)
{
    Singleton &s1 = Singleton::GetInstance();
    Singleton &s2 = Singleton::GetInstance();
    //Singleton s3(*s1); // 调用默认的拷贝构造函数
    //s3 = *s2;
    //Singleton::Free();
    return 0;
}
#endif

//########################### 作用域与生命周期 ##################################
#if 0
//==============================================================================
// 四种对象的作用域与生存期：
// * 1、栈对象：构造函数隐含调用，自动释放。
// * 2、堆对象：构造函数隐含调用，显示释放。
// * 3、全局对象、静态全局对象：构造现于main函数。
//     -> 已初始化的存于.data段，未初始化的
//        --> .data段特点：在可执行程序中占用空间。
//     -> 全局变量存于.bss段，会被自动初始化为0。
//        --> .bss段特点：在可执行程序中不占用空间，只需要一个符号，程序加载后才会分配这个段。
// * 4、静态局部对象：
//     -> 如果是c++内部变量，则与全局静态变量一致。都是编译器初始化的。
//     -> 如果是静态局部类对象，存储位置与全局的一样，只是它不会先于main构造，执行
//        到这才会构建，它是运行期初始化的。
// 作用域与生存期不等同。
//==============================================================================
// static用法总结：
// 一、C中的用法：
//     1、函数内部修饰变量，生命期长于函数，相当于记忆元件，使得函数具有状态。
//        它会导致函数不可重入，也不是线程安全的。
//     2、用在文件级别（函数体之外），修饰变量或函数，表示该函数或该变量只在本文件
//        可见，其它文件看不到也访问不到该变量。（internal linkage）
//      * 相对的是external linkage（全局变量）：全局变量必须定义在.c文件中，不允许
//        定义在.h文件中，因为如果有两个文件同时包含这个.h文件，
//      * 例：[x.h(int n = 100) a.c b.c],那相当于a.c b.c中都有定义int n = 100这条
//        语句，而它们前面又没有static限制，就会引起重复定义错误。
// 二、CPP保持对C中static的用法，同时又进行了扩展：
//     3、修饰类的数据成员，即静态成员。它的生存期大于类对象。静态数据成员每个类有一份，
//        普通数据成员每个类实例（对象）有一份。
//     4、修饰类的成员函数，即静态成员函数。这种成员函数只能访问静态成员和其它静态成
//        员函数，不能访问非静态数据成员和非静态成员函数。它没有this指针。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

#define STR(x,y) x##y

class Test
{
public:
    Test() : i_(0)
    {
        cout << "Test default ......" << endl;
    }
    explicit Test(int i) : i_(i)
    {
        cout << "Test " << i_ << " ..." << endl;
    }
    ~Test()
    {
        cout << "~Test " << i_ << " ..." << endl;
    }

    int i_;
};

int n;        // .bss
int n2 = 100; // .data
Test t_global(1000);
static Test t_global_const(2000);

int main(void)
{
    cout << "Entering main ..." << endl;
    Test t(10); // 栈
    {
        Test t(20);
    }

    Test* t2 = new Test(30);
    delete t2;

    { // 这三个的作用域只局限于这个块作用域，但生存期是整个程序运行期
        static int n3;       // .bss  编译期初始化
        static int n4 = 100; // .data 编译期初始化
        static Test t4(333); // .data 运行期初始化,程序第一次运行到这的时候初始化。
    }


    cout << "Existing main ..." << endl;
    return 0;
}
#endif

//############################# 类中的const ####################################
#if 0
//==============================================================================
// const成员函数：
// * const成员函数不会修改对象的状态。const函数只能访问数据成员的值，不能修改它。
// * const成员函数和非const成员函数可以构成重载（即使参数列表完全一样）。
//==============================================================================
// const对象：
// * const对象不能调用非const成员函数。
// * 非const成员函数可以调用const成员函数和const成员函数，如果类提供了成员函数的
//   const和非const两个版本，则非const对象调用非const的那个。
//==============================================================================
// mutable：
// * mutable修饰的数据成员在const对象或者const成员函数中都可以被修改。
//==============================================================================
// const总结：
// 1、const修饰变量。
// 2、const修饰引用，非const引用不能绑定const对象。
// 3、const修饰指针。
// 4、const修饰类数据成员：只能在初始化列表进行初始化。
// 5、const修饰类成员函数：只能访问数据成员，不能修改数据成员。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

class Test
{
public:
    explicit Test(int x) : x_(x), output_times_(0)
    {

    }

    int GetX() const
    {
        //x_ =100; // Error：不能修改数据成员的值
        cout << "GetX() const ..." << endl;
        return x_;
    }

    int GetX()
    {
        cout << "GetX() ..." << endl;
        return x_;
    }

    void Output() const
    {
        cout << "x_ = " << x_ << endl;
        output_times_++;
    }

    int GetOutputTimes() const
    {
        return output_times_;
    }
private:
    int x_;

    mutable int output_times_;
};

int main(void)
{
    const Test t(100);
    t.GetX();

    Test t2(200);
    t2.GetX();

    cout << "======================" << endl;

    const Test t3(300);
    t3.Output();
    t3.Output();
    cout << "Output times: " << t3.GetOutputTimes() << endl;

    return 0;
}
#endif

//####################### 通过栈的实现看数据抽象与封装 ##########################
#if 0
#include <iostream>
using std::cout;
using std::endl;
#include <cassert>

/*
struct Link // 链表节点
{
    int data;
    struct Link* next;
};

struct Stack
{
    struct Link* head;
    int size;
};

void StackInit(struct Stack* stack)
{
    stack->head = NULL;
    stack->size = 0;
}

void StackPush(struct Stack* stack, int data)
{
    //生成新的节点
    struct Link* node = (struct Link*)malloc(sizeof(struct Link));
    assert(node != NULL);
    node->data = data;
    node->next = stack->head;

    // 链表尾部插入节点
    stack->head = node;
    stack->size++;
}

int StackEmpty(struct Stack* stack)
{
    return (stack->size == 0);
}

int StackPop(struct Stack* stack, int* data)
{
    if (StackEmpty(stack)) {
        return 0;
    }

    struct Link* tmp = stack->head;
    *data = stack->head->data;
    stack->head = stack->head->next;
    free(tmp);

    stack->size--;

    return 1;
}

void StackCleanup(struct Stack* stack)
{
    struct Link* tmp = NULL;
    while (stack->head) {
        tmp = stack->head;
        stack->head = stack->head->next;
        free(tmp);
    }

    stack->size = 0;
}

int main(void)
{
    struct Stack stack;
    StackInit(&stack);
    int i;
    for (i = 0; i < 5; i++) {
        StackPush(&stack, i);
    }

    while (!StackEmpty(&stack)) {
        StackPop(&stack, &i);
        printf("%d  ", i);
    }

    return 0;
}
 */

class Stack
{
    struct Link
    {
        int data_;
        Link* next_;
        Link(int data, Link* next)
        {
            data_ = data;
            next_ = next;
        }
    };
public:
    Stack() : head_(NULL), size_(0)
    {
    }

    void Push(int data)
    {
        //生成新的节点
        Link* node = new Link(data, head_);
        assert(node != NULL);

        // 链表尾部插入节点
        head_ = node;
        size_++;
    }

    bool IsEmpty()
    {
        return (size_ == 0);
    }

    bool Pop(int& data)
    {
        if (IsEmpty()) {
            return false;
        }

        Link* tmp = head_;
        data = head_->data_;
        head_ = head_->next_;
        delete tmp;

        size_--;

        return true;
    }

    ~Stack()
    {
        Link* tmp = NULL;
        while (head_) {
            tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }

        size_ = 0;
    }

private:
    Link* head_;
    int size_;
};

int main(void)
{
    Stack stack;
    int i;
    for (i = 0; i < 5; i++) {
        stack.Push(i);
    }

    while (!stack.IsEmpty()) {
        stack.Pop(i);
        cout << i << "  ";
    }
    cout << endl;
}
#endif

//################################# 友元 #######################################
#if 0
//==============================================================================
// 使用[引用]和[指针]可以使用前向声明。
//==============================================================================
// 友元：
// * 允许非类成员函数访问类的非公有成员的一种机制。
// * 友元的形式可以是 函数 或者 类。
// 友元函数：
// * 某个类的友元函数需要在该类的[类体外定义、类体内声明]/[类体内直接定义]，用friend标示。
//   但无论哪种形式，友元都不属于给类。它放在类的哪个位置没任何影响。
// * 提高效率，不需要类提供额外的私有成员访问接口。
// * 破坏封装，不是必须，不要用。
// 友元类：
// * 一个类的友元类的所有成员函数是该类的友元函数。
// * 友元关系是单向的：
//   -> A是B的友元类，并不代表B是A的友元。
// * 友元不能被传递：
//   -> A是B的友元类，B又是C的友元，并不代表A是C的友元。
// * 友元关系不能被继承：
//   -> A是B的友元类，C继承自A，并不代表C是B的友元。
//   -> A是B的友元类，C继承自B，并不代表A是C的友元。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include <cmath>

class Point
{
    friend double Distance(const Point& p1, const Point& p2); // 不是Point的成员
public:
    Point(int x, int y);
private:
    int x_;
    int y_;
};

Point::Point(int x, int y) : x_(x), y_(y)
{
}

double Distance(const Point& p1, const Point& p2)
{
    double dx = p1.x_ - p2.x_;
    double dy = p1.y_ - p2.y_;
    return sqrt(dx * dx + dy * dy);
}

#include "TeleController.h"
#include "Television.h"

int main(void)
{
    Point p1(0, 0);
    Point* p2 = new Point(3, 4);
    double dist = Distance(p1, *p2);
    cout << dist << endl;

    cout << "=====================" << endl;

    Television tv(1, 1);
    TeleController controller;
    controller.VolumeUp(tv);
    controller.ChannelDown(tv);

    return 0;
}
#endif

//############################## 运算符重载 ####################################
#if 0
//==============================================================================
// 运算符重载：
// * 只是语法上的方便，本质就是函数调用，所以不要滥用，以方便搞笑为原则。
// * 可以以成员函数形式重载，也可以以友元函数形式重载，两者不可以共存。[因为成员函数
//   有默认的this参数，而友元函数不属于类，所以没有隐含的this指针参数，要比成员函数
//   形式的多一个参数]。
// 重载规则1：
// * 不允许创建新的运算符
// * 不允许改变运算符操作数个数
// * 重载后不改变优先级和结合性
// * ::  ?:  .  .*  sizeof等运算符不允许重载。
// 重载规则2：
// * 单目运算符最好重载为成员函数，双目运算符最好重载为友元函数。
// * 只能以类成员形式重载的运算符： =，()，[]，->，类型转换运算符。
// * 只能以友元函数形式重载的运算符： 流运算符
// 总结：
// * 如果运算符第一个参数是对象本身，则适合用成员函数形式，否则友元。当然还要看具体需求，
//   如 +运算符 就是友元实现。
//==============================================================================
// ++运算符重载：
// 1、前置++：
// 2、后置++：后置通过一个多出来的int参数来区分，只是用来区分，没有实际用处。
//      -> 但并不只是区分就完事了，代码实现有很大区别，为了实现‘后’这个特点，不能返回
//         引用，而要返回临时对象，临时对象内的数据成员是自加前的，类本身是自加后的。
//==============================================================================
// 赋值运算符、!运算符重载、[]运算符重载
//==============================================================================
// 流运算符重载：
//==============================================================================
// 类型转换运算符重载：提供了后就可以隐式由类对象转换为其它，其它转换为类对象是转换
// 构造函数的事情。
// * 必须是成员函数
// * 没有参数（类对象本身）
// * 不能指定返回类型(要转换的类型)
//==============================================================================
// 指针运算符'->'重载：
// * 形式和含义比较特殊。可以实现外层类调用成员对象（相当于是一个包装）。
//==============================================================================
// new的三种用法：
// * new operator = operator new（分配内存） + 构造函数 ： 不可以被重载
//
// * operator new： 可以被重载，如果operator new被重载了，那delete也要相应的重载。
//      -> 可以类内部重载也可以全局重载。
//      -> 形式：
//          void* operator new(size_t size)
//          void operator delete(void* p)
//          void operator delete(void* p, size_t size)
//          void* operator new[](size_t size)
//          void operator delete[](void* p)
//          void operator delete[](void* p, size_t size)
//       -> 附加参数：
//          void* operator new(size_t size, const char* file, long line)
//          void operator delete(void* p, , const char* file, long line)
//
// * placement new ： 使用已有的内存空间，不重新进行内存分配。
//      -> 形式：
//         void* operator new(size_t size, void* p)   <- 直接返回p就行
//         void operator delete(void*, void*)         <- 对应的析构函数什么也不用做，
//                                                       placement new应该通过显式
//                                                       析构函数来结束对象，而不是delete
//==============================================================================
// 注意：
// * 为了防止代码重复，可以重用的代码尽量重用。
// * 可以通过让非const版本的函数调用const版本的函数来实现。一般是用非const调用const。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include "Complex.h"
#include "Integer.h"
#include "String.h"

int add(int a, int b)
{
    return a + b;
}

class DBHelper
{
public:
    DBHelper()
    {
        cout << "DBHelper ..." << endl;
    }

    ~DBHelper()
    {
        cout << "~DBHelper ..." << endl;
    }

    void open()
    {
        cout << "Open ..." << endl;
    }

    void Close()
    {
        cout << "Close ..." << endl;
    }

    void Query()
    {
        cout << "Query ..." << endl;
    }
};

class DB // 相当于一个智能指针，包装了一个DBHelper指针。
{
public:
    DB()
    {
        db_ = new DBHelper;
    }

    ~DB()
    {
        delete db_;
    }

    DBHelper* operator->() //  指针运算符重载
    {
        return db_;
    }

private:
    DBHelper* db_;
};

class Test
{
public:
    Test(int n) : n_(n)
    {
        cout << "Test(int n)" << endl;
    }
    Test(const Test& other) :n_(other.n_)
    {
        cout << "Test(const Test& other)" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }

    friend ostream& operator<<(ostream& os, const Test& obj);

    void* operator new(size_t size) // 类内部的operator new 重载
    {
        cout << "operator new" << endl;
        void* p = malloc(size);
        return p;
    }

    void operator delete(void* p) // 优先级高一点
    {
        cout << "operator delete" << endl;
        free(p);
    }

    void operator delete(void* p, size_t size)
    {
        cout << "operator delete with size_t" << endl;
        free(p);
    }

    void* operator new(size_t size, const char* file, long line)
    {
        cout << "new -> " << file << ":" << line << endl;
        void* p = malloc(size);
        return p;
    }

    void operator delete(void* p, const char* file, long line) // 优先级高一点
    {
        cout << "delete -> " << file << ":" << line << endl;
        free(p);
    }

    void* operator new(size_t size, void* p) // placement new
    {
        return p;
    }

    void operator delete(void*, void*) // 不需要执行任何操作
    {

    }

private:
    int n_;
};

ostream& operator<<(ostream& os, const Test& obj)
{
    os << obj.n_;
    return os;
}

void* operator new(size_t size) // 类内部的operator new 重载
{
    cout << "global operator new" << endl;
    void* p = malloc(size);
    return p;
}

void* operator new[](size_t size) // 类内部的operator new 重载
{
    cout << "global operator new[]" << endl;
    void* p = malloc(size);
    return p;
}

void operator delete(void* p) // 优先级高一点
{
    cout << "global operator delete" << endl;
    free(p);
}

void operator delete(void* p, size_t size)
{
    cout << "global operator delete with size_t" << endl;
    free(p);
}

void operator delete[](void* p)
{
    cout << "global operator delete[]" << endl;
    free(p);
}

int main(void)
{
    Complex c1(3, 5);
    Complex c2(4, 6);
    c1.Add(c2);
    c1.Display();

    cout << "=======================" << endl;

    Complex c3 = c1 + c2; // 希望c1和c2保持不变
    // Complex c3 = c1.operator+(c2); // 使用成员函数重载时与上面等价，友元形式不能这样用
    c3.Display();
    c1.Display();
    c2.Display();

    cout << "===========++============" << endl;

    Integer n(100);
    n.Display();

    cout << "=======================" << endl;

    Integer n2 = ++n;
    n.Display();
    n2.Display();

    cout << "=======================" << endl;

    Integer n3;
    n3 = n++;
    cout << "++++++++" << endl;
    n.Display();
    n3.Display();

    cout << "===========++============" << endl;

    String s3;
    s3 = "xxxx"; // 转换构造函数生成临时对象－>赋值操作->删除临时对象
    s3.Display();

    cout << "==========||=============" << endl;

    String s4 = "zzz";
    cout << !s4 << endl;

    cout << "=======================" << endl;

    s4[2] = 'x';
    s4.Display();

//    const String s5("xyzabc");
//    //s5[2] = '1';
//    s5.Display();

    cout << "=======================" << endl;

    // 实际操作时"|aaa"会被首先转型为String类型(因为提供了转换构造函数)，然后传入
    // operator+，是隐式类型转换，也可以显示进行，只要提供了转换构造函数。
    String s6 = s4 + static_cast<String>("|aaa") + "|111";
    s6.Display();

    cout << "=======================" << endl;

    String s7;
    s7 += "xyz";
    cout << s7 << endl;

    cout << "=======================" << endl;

    String s8;
    //std::cin >> s8;
    cout << s8 << endl;

    cout << "=======================" << endl;

    Integer i(100);
    i = 200; // 转换构造函数生成临时对象，然后赋值操作符然后删除临时对象
    Integer i2(200);
    (i+i2).Display();
    //i.Display();

    cout << "=======================" << endl;

    cout << add(static_cast<int>(i), 20) << endl; // 类型转换运算符

    cout << "===========||============" << endl;

    DB db;
    db->open(); // 这些函数不是DB类的函数，而是他所包装的DBHelper类的函数
    db->Query();
    db->Close();

    cout << "=======================" << endl;

    Test *p1 = new Test(100); // 这里的new是new operator
                              // new operator = operator new(分配空间) + 赋值
    delete p1; // delete operator = 析构函数 + operator delete

    cout << "=======================" << endl;

    char chunk[10];
    Test* p2 = new (chunk) Test(300); // placement new，使用已有的内存，无内存分配，只是调用构造函数
    p2->~Test(); // 显示调用析构函数，不应该用delete，因为不是在堆上申请的，而是在已有的内存中。

    Test* p3 = reinterpret_cast<Test*>(chunk); // 没调用构造函数，成员的值是随机的
    cout << *p3 << endl;

    cout << "=======================" << endl;

    char *pp = new char[10];
    delete[] pp;

    cout << "==========||=============" << endl;

    Test* pp4 = new(__FILE__, __LINE__) Test(1000);
    delete pp4;

    cout << "=======================" << endl;

    return 0;
}
#endif

//################################# string #####################################
#if 0
//==============================================================================
// string  字符串     char*
// vector  动态数组   静态数组
// map     key/value  内部是以树的形式存储的[O(log2N)]/哈希表[O(1)]
//==============================================================================
// string : typedef basic_string<char> string : 是模板类
//          typedef basic_string<wchar_t> wstring
// 一般string函数会兼容string, substring, c-string, buffer, fill等形式
// 常用函数：size length empty substr find rfind replace compare insert copy erase
//           find_first_of find_first_no_of find_last_of find_last_no_of等
//==============================================================================

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::wstring;

int main(void)
{
    cout << "================== 构造函数 =====================" << endl;
    string s1; // 默认构造函数
    cout << "s1: " << s1 << endl;

    string s2("ABCDEFGHIJK"); // 转换构造函数 char* -> string
    cout << "s2: " << s2 << endl;

    string s3("ABCDEF", 4); // 转换构造函数 char* -> string
    cout << "s3: " << s3 << endl;

    std::basic_string<char> s4("BBBB"); // 转换构造函数 char* -> string
    cout << "s4: " << s4 << endl;

    string s5(s2); // 拷贝构造函数
    cout << "s5: " << s5 << endl;

    string s6(s2, 3, 3); // 带附加参数
    cout << "s6: " << s6 << endl;

    string::iterator head = s2.begin() + 3; // 暂时把它看成char*
    string::iterator tail = s2.begin() + 6;
    string s7(head, tail); // [head, tail) // 传两个迭代器
    cout << "s7: " << s7 << endl;

    cout << "================== 常用成员函数 =====================" << endl;
    cout << "string: " << s2 << endl;
    cout << "size: " << s2.size() << endl;
    cout << "length: " << s2.length() << endl;
    cout << "empty: " << s2.empty() << endl;
    cout << "substr: " << s2.substr(3, 3) << endl; // 默认值是整个字符串

    size_t pos0 = s2.find(s3, 0); // 正向查找，默认起始位置为０
    if (pos0 == string::npos) {
        cout << "find: " << "not found" << endl;
    } else {
        cout << "find: " << pos0 << endl;
    }
    size_t pos = s2.find('A', 0); // 正向查找，默认起始位置为０
    if (pos == string::npos) {
        cout << "find: " << "not found" << endl;
    } else {
        cout << "find: " << pos << endl;
    }
    size_t pos2 = s2.rfind("EFG", 3); // 反向查找，默认起始位置为npos，最后一个
    if (pos2 == string::npos) {
        cout << "rfind: " << "not found" << endl;
    } else {
        cout << "rfind: " << pos2 << endl;
    }

    // no const function -> can use iterator
    s2.replace(0, 3, s3);                 // string    <- can use iterator
    cout << "replace: " << s2 << endl;
    s2.replace(0, 3, s3, 0, 2);           // substring <- no iterator
    cout << "replace: " << s2 << endl;
    s2.replace(0, 3, 3, '0');            // fill      <- can use iterator
    cout << "replace: " << s2 << endl;
    s2.replace(0, 3, "just char* ");    // c-string  <- can use iterator
    cout << "replace: " << s2 << endl;
    s2.replace(0, 5, "just char* ", 5); // buffer    <- can use iterator
    cout << "replace: " << s2 << endl;

    // const function -> no iterator
    s2 = string("ABCDEFGHIJKLMN");
    int compare_res = s2.compare(s3);            // string - string
    compare_res = s2.compare(0, 3, s3);          // substring - string
    compare_res = s2.compare(0, 3, s3, 0, 3);    // substring - substring
    compare_res = s2.compare("just");           // string - c-string
    compare_res = s2.compare(0, 4, "just");     // substring - c-string
    compare_res = s2.compare(0, 4, "just", 3);  // substring - buffer
    cout << "compare: " << compare_res << endl;

    s2 = string("ABCDEFGHIJKLMN");
    s2.insert(0, string("0"));            // string
    s2.insert(0, string("01234"), 0, 1);  // substring
    s2.insert(0, "1");                    // c-string
    s2.insert(0, "123", 1);               // buffer
    s2.insert(0, 2, '-');                 // fill
    cout << "insert: " << s2 << endl;

    s2 = string("ABCDEFGHIJKLMN");
    s2.append(string("0"));            // string
    s2.append(string("01234"), 0, 1);  // substring
    s2.append("1");                    // c-string
    s2.append("123", 1);               // buffer
    s2.append(2, '-');                 // fill

    s2 = string("ABCDEFGHIJKLMN");
    string ss("1234");
    s2.swap(ss);
    cout << "swap: " << s2 << endl;

    s2 = string("ABCDEFGHafgb67eIJKLMN");
    char *ch = new char[4];
    ch[3] = '\0';
    s2.copy(ch, 3, 0);
    cout << "copy: " << ch << endl;

    s2 = string("ABCDEFGHIJKLMN");
    string sss("---Hello world......----");
    size_t poss = s2.find_first_of(sss);
    cout << "find_first_of: " << poss << endl; // s2中第一个出现的字符C,C是sss中的任意一个字符。
    // find_first_no_of
    // find_last_of
    // find_last_no_of

    // 去除字符串前后空格
    s2 = "  int main(void)  ";
    size_t space_head = s2.find_first_of(" ");
    size_t space_tail = s2.find_first_not_of(" ") - 1;
    s2.erase(space_head, space_tail-space_head+1);
    space_head = s2.find_last_not_of(" ") + 1;
    space_tail = s2.find_last_of(" ");
    s2.erase(space_head, space_tail-space_head+1);
    cout << "delete space: [" << s2 << "]" << endl;

    return 0;
}
#endif

//################################# vector #####################################
#if 0
//==============================================================================
// vector: 动态数组
// * 存储空间是连续的、可以自动扩展。
// *
//==============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;

void ShowVec(const vector<int>& vec)
{
//    for (size_t i = 0; i < vec.size(); i++) {
//        cout << vec.at(i) << endl;
//    }

    //vector<int>::const_reverse_iterator it; // 反序迭代器
    vector<int>::const_iterator it;
    // 使用后置++比前置++效率低，如果内容是类。因为后置++要生成临时对象，而前置++不需要。
    for (it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << *it << endl;
    }
}

int main(void)
{
    vector<int> v1;
    //vector<int> v2(v1); // 赋值构造函数
    //vector<int> v3(5);
    //vector<int> v4(5,0); // 5个元素，权初始化为0
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    ShowVec(v1);

    cout << "===========================" << endl;

    vector<int>::iterator it = v1.begin();
    // v1.erase(v1.cbegin()); // 删除单个元素
    v1.erase(v1.cbegin(), v1.cbegin() + 2);
    ShowVec(v1);
    v1.push_back(4);
    v1.push_back(5);

    cout << "=============||==============" << endl;

    cout << v1.front() << " | " << v1.back() << endl;

    const int *p_vec = v1.data(); // 获取底层指针数组
    size_t p_len = v1.size();
    for (size_t i = 0; i < p_len; ++i) {
        cout << *(p_vec+i) << endl;
    }

    cout << "===========||================" << endl;

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    ShowVec(v2);
    //v2.erase(std::remove(v2.begin(), v2.end(), 3), v2.end());
    vector<int>::const_iterator v2_it;
    for (v2_it = v2.cbegin(); v2_it != v2.cend(); /*++v2_it*/) {
        if (*v2_it == 3) {
            v2_it = v2.erase(v2_it); // 当前删除元素的下一个元素
        } else {
            ++v2_it;
        }

//        if (*v2_it == 3) {
//            v2.erase(v2_it); // 再++会出错，因为已经删除了。
//        }
    }
    ShowVec(v2);

    cout << "===========================" << endl;

}
#endif

//################################## map #######################################
#if 0
//==============================================================================
// map:
// * 插入到map容器内部的元素默认按照key从小到大排序。所以，key的类型一定要重载<运算符。
//   可以改变key的排序方式。
// * map的key是unique的，如果插入的与已有的重复，通过inset方式无法插入，通过[]插入
//   等价于用新值更新已有的值，不会增加新的pair。
// * 利用find函数进行查找，返回map.end()代表没找到。
// * 删除元素：输入iterator返回iterator，输入key输出size_t
//==============================================================================

#include <iostream>
#include <map>
using namespace std;

int main(void)
{
    map<char, int> map_test;
    map_test['a'] = 97;  // 两个步骤：
                         // 1、插入key=‘a’的一个元素，初始值是对应类型的默认值，
                         //    如果是类就用类的默认构造函数构造一个对象。
                         // 2、将等号后面的对象赋值给默认生成的那个对象。
    map_test['A'] = 65;
    map_test['0'] = 48;

    cout << "============||============" << endl;

    map<char,int> map_test2;
    map_test2.insert(pair<char,int>('a',97));
    map_test2.insert(pair<char,int>('b',98));
    // map的key是unique的，如果插入的与已有的重复，通过inset方式无法插入，通过[]可以更新已有的值
    pair<map<char,int>::iterator,bool> ret = map_test2.insert(pair<char,int>('b',100));
    if (ret.second == false) {
        cout << "Element 'b' already exist with a value " << ret.first->second << endl;
    } else {
        cout << "Pair ['b',98] inserted" << endl;
    }
    map_test2['c'] = 99;

    // 遍历
    map<char,int>::const_iterator map_it;
    for (map_it = map_test2.begin(); map_it != map_test2.end(); ++map_it) {
        cout << "[" << map_it->first << "," << map_it->second << "]" << endl;
    }

    // 访问元素，配合异常也可以达到查找目的
    int value = map_test2.at('a'); // c++11 at()里必须是存在的，不然会抛出异常。
    // 访问元素
    int value2 = map_test2['a'];   // 可以月结，返回0
    cout << value << "  " << value2 << endl;

    // 查找某个key是否存在
    map_it = map_test2.find('b');
    if (map_it != map_test2.end()) {
        cout << "Found " << map_it->first << " => " << map_it->second << endl;
    } else {
        cout << "Not found!" << endl;
    }

    cout << "===============================" << endl;
    // 删除某元素
    map_it = map_it = map_test2.find('b');
    if (map_it != map_test2.end()) {
        map_test2.erase(map_it);
    }

    for (map_it = map_test2.begin(); map_it != map_test2.end(); ++map_it) {
        cout << "[" << map_it->first << "," << map_it->second << "]" << endl;
    }

    return 0;
}
#endif

//####################### 继承1-继承方式与重定义 ################################
#if 0
//==============================================================================
// 继承方式：struct默认公有继承，class默认私有继承。公有成员成为接口。
// 1、public继承：    对于派生类，基类成员特性不变，基类的private成员不可直接访问。
//    -> 基类的public成员函数在派生类中仍然是公有 => 基类的接口变成了派生类的接口 => 接口继承
// 2、protected继承： 对于派生类，基类成员全变为protected，基类的private成员不可直接访问。
//    -> 基类的public成员函数在派生类中不在公有 => 派生类不再支持基类的接口，只是为
//       了重用基类实现 => 实现继承
// 3、private继承：   对于派生类，基类成员全变为private，基类的private成员不可直接访问。
//    -> 基类的public成员函数在派生类中不在公有 => 派生类不再支持基类的接口，只是为
//       了重用基类实现 => 实现继承
//===============================================================================
// 派生类对基类的重定义：
// 一、对基类数据成员的重定义（同名数据成员）：隐藏基类同名数据成员，可以通过基类名
//     称做限定[Derived.Base::func()]来访问。
// 二、对基类成员函数的重定义有两种：
//    1、overwrite（不是重载[overload],重载的前提是相同的作用域）：
//       1）与基类完全相同：隐藏基类的同名实现，这种情况下可以通过基类名称做限定
//          [Derived.Base::func()]来访问基类的同名函数。
//       2）与基类成员函数名相同，参数不同：会隐藏基类的同名函数，如果派生类中没有
//          与基类完全相同的重定义，即使使用基类名称做限定[Derived.Base::func()]也
//          无法访问基类的同名函数。
//    2、override（覆盖）：
//       * 必须是虚函数才行。
//==============================================================================
// 1、无论继承还是组合，本质上都是把基类/子对象放到新类型中，两者都是是有新类型的初始化
//    列表去构造这些子对象的。
// 2、组合[has-a] 继承[is-a]
// 3、[×] 继承的目的是处理接口继承（公有继承）,也就是希望派生类与基类有相同的接口。
//         如果只是利用已有类的功能（实现继承）,可以直接用组合的方式实现。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    Base() : x_(0)
    {

    }
    int GetBaseX() const
    {
        return x_;
    }

    /*virtual*/ void Show()
    {
        cout << "Base show ..." << endl;
    }
    int x_;
};

class Derived : public Base
{
public:
    Derived() : Base(), x_(0)
    {

    }
    int GetDerivedX() const
    {
        return x_;
    }

    void Show()
    {
        cout << "Derived show ..." << endl;
    }

    void Show(int n) // 与基类同名但参数不同，也会隐藏基类的同名函数
    {
        cout << "Derived show ..." << endl;
    }

    int x_; // 重定义基类的数据成员，会对外隐藏基类的这个数据成员。
};



int main(void)
{
    //PublicInherit public_obj;
    //public_obj.x_ = 10;       // public -> public 派生类内部和派生类对象都可直接访问
    // public_obj.y_ = 20;    // protected -> protected 派生类内部可直接访问，外部不可访问
    // public_obj.z_ = 30;    // 派生类内部和外部都不可访问

    //PrivateInherit protected_obj;
    // private_obj.x_ = 10;   // public -> protected 派生类内部可直接访问，外部不可访问
    // private_obj.y_ = 20;   // protected -> protected 派生类内部可直接访问，外部不可访问
    // private_obj.z_ = 30;   // 派生类内部和外部都不可访问

    //PrivateInherit private_obj;
    // private_obj.x_ = 10;   // public -> private 派生类内部可直接访问，外部不可访问
    // private_obj.y_ = 20;   // protected -> private 派生类内部可直接访问，外部不可访问
    // private_obj.z_ = 30;   // 派生类内部和外部都不可访问

    Derived d;
    d.x_ = 10;
    d.Base::x_ = 20;

    cout << d.GetBaseX() << endl;
    cout << d.GetDerivedX() << endl;

    d.Show();
    d.Base::Show();
    //dynamic_cast<Base*>(&d)->Show();

    cout << "sizeof(Base): " << sizeof(Base) << endl;
    cout << "sizeof(Derived): " << sizeof(Derived) << endl;

    return 0;
}
#endif

//####################### 继承2-派生类的构造与析构 ##############################
#if 0
//==============================================================================
// 不能自动继承的成员函数（编译器能默认能生成的都不会被自动继承）：
// 1、构造函数：
//  * 派生类构造函数只需要初始化新增的成员，基类成员通过调用基类构造函数进行初始化。
//  * 如果不在派生类初始化类表中显示调用基类构造函数，则编译器会默认调用基类的默认
//    构造函数，如果基类没有默认构造函数，又没在派生类中显示调用基类构造函数，就会出错。
// 2、析构函数：
//  * 派生类析构函数只需要处理新增的成员，基类成员调用基类的析构函数进行处理。
//  * 如果不在派生类析构函数中调用基类析构函数，则编译器会默认调用基类的默认析构函数。
// 3、=运算符
//==============================================================================
// 只能在初始化列表中初始化的成员：
// 1、const成员
// 2、引用成员
// 3、对基类成员的初始化，通过在初始化列表中调用基类构造函数（如果基类没有默认构造函数）。
// 4、数据成员对应的类没有默认构造函数时，需要在初始化类表中显式调用该数据成员对应类的构造函数。
//==============================================================================
// 派生类构造函数的执行过程：
//   * 基类构造函数 -> 数据成员(类对象)的构造函数(按照声明的顺序) -> 自己的构造函数
//   * 如果基类也有它的基类或者类对象数据成员，则这个过程是个递归的过程。
// 派生类析构函数的执行过程：
//   * 自己的析构函数 -> 数据成员(类对象)的析构函数(按照声明的反顺序) -> 基类的析构函数
//==============================================================================
// 派生类的拷贝构造函数执过程与构造函数逻辑一样，只是全都换为拷贝构造函数。
//==============================================================================
// * 友元关系不能被继承：
//    A是B的友元类，C是A的派生类，C不是B的友元类。
// * 友元关系是单向的。
// * 友元关系不能被传递。
//==============================================================================
// 静态成员无所谓继承。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

class ObjectD
{
public:
    ObjectD(int n) : d_(n)
    {
        cout << "ObjectD ..." << endl;
    }

    ObjectD(const ObjectD& other) : d_(other.d_)
    {
        cout << "ObjectD copy ..." << endl;
    }

    ~ObjectD()
    {
        cout << "~ObjectD ..." << endl;
    }

    int d_;
};

class Base
{
public:
    Base(int n) : objb_(n), b_(2*n)
    {
        cout << "Base ..." << endl;
    }

    Base(const Base& other) : objb_(other.objb_), b_(other.b_)
    {
        cout << "Base copy ..." << endl;
    }

    ~Base()
    {
        cout << "~Base ..." << endl;
    }

    int b_;
    ObjectD objb_;
};

class Derived : public Base
{
public:
    Derived(int n) : Base(n), objd_(2*n), d_(3*n)
    {
        cout << "Derived ..." << endl;
    }

    Derived(const Derived& other) : Base(other), objd_(other.objd_), d_(other.d_)
    {
        cout << "Derived copy ..." << endl;
    }

    ~Derived()
    {
        cout << "~Derived ..." << endl;
    }

    int d_;
    ObjectD objd_;
};

class StaticBase
{
public:
    static int b_;
};

int StaticBase::b_ = 100;

class StaticDerived : public StaticBase
{

};

int main(void)
{
    Derived d(100);
    //cout << d.b_ << " " << d.d_ << " " << d.objd_.d_ << endl;

    cout << "===================" << endl;

    Derived d1(d);
    cout << d1.b_ << endl;

    cout << "==========||=========" << endl;

    cout << "StaticBase::b_: " << StaticBase::b_ << endl;
    cout << "StaticDerived::b_: " << StaticDerived::b_ << endl;

    cout << "===================" << endl;

    return 0;
}
#endif

//####################### 继承3-基类与派生类转换 ################################
#if 0
//==============================================================================
// 派生类对象upcasting成基类对象：
// * 向上转型是安全的转型。
// 一、当派生类是public继承的时候，编译器可自动执行转换：
//    1、派生类对象指针自动转换为基类对象指针。
//    2、派生类对象引用自动转换为基类对象引用。
//    3、派生类对象自动转换为基类对象。真正的对象转换，会发生对象切割object slicing
// 二、私有或者保护继承的时候：
//    1、派生类对象指针不能自动转换为基类对象指针。但可以使用reinterpret_cast<...>(...)
//       或者C风格强制转换进行强制转换，其它强制转换不行。
//    2、对于私有继承的派生类对象引用，和指针一样只能通过强制类型转换进行向上转型。
//    3、对于派生类对象，即使使用强制转换也不行。
//==============================================================================
// 基类对象向下转型成派生类对象：[不受继承类型的约束]
// * 向下转型不安全，没有自动转换机制。
// * 基类对象指针可以通过强制类型转换转化为派生类指针，而基类对象无法完成这种转换。
//   无论那种强制转换都不行。
//==============================================================================
// 基类对象转换为派生类对象的两种方式：(语法上是可行的，但不推荐用)
// * 在派生类实现转换构造函数 或者 在基类重载类型转换运算符。
//==============================================================================
// 转换构造函数： 将其它类型转换为类类型。
// 类型转换运算符重载：将类类型转换为其它类型。
//==============================================================================
// CPP类型转换：
// 1、static_cast 用于编译器认可的静态转换，不如char->int,double->int；或者具有转换
//    构造函数；或者重载了类型转换运算符。
// 2、reinterpret_cast用于编译器不认可的静态转换，比如从int*->int，转型的时候不做任何对齐操作。
// 3、const_cast用于去除常量特性，静态转换。
// * 静态转换不需要运行时支持。
// 4、dynamic_cast用于动态转换，安全的向下、向上转型。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <string>
using std::string;

class Employee
{
public:
    Employee(const string& name, const int age,  const int depthno) :
            name_(name), age_(age), depthno_(depthno)
    {

    }

    friend ostream& operator<< (ostream& osm, const Employee& obj);
private:
    string name_;
    int age_;
    int depthno_;
};

ostream& operator<< (ostream& osm, const Employee& obj)
{
    osm << "name: " << obj.name_ << "  age: " << obj.age_ << "  depthno: " << obj.depthno_;
    return osm;
}



class Manager : public Employee
{
public:
    Manager(const string& name, const int age,  const int depthno, const int level) :
            Employee(name, age, depthno), level_(level)
    {

    }

    friend ostream& operator<< (ostream& osm, const Manager& obj);
private:
    int level_;
};

ostream& operator<< (ostream& osm, const Manager& obj)
{
    osm << dynamic_cast<const Employee&>(obj); // 派生类引用转换为基类引用
    osm << "  level: " << obj.level_;
    return osm;
}

class Manager2 : private Employee
{
public:
    Manager2(const string& name, const int age,  const int depthno, const int level) :
            Employee(name, age, depthno), level_(level)
    {

    }
private:
    int level_;
};


int main(void)
{
    cout << "==========公有继承==========" << endl;
    Employee e1("wang", 30, 01);
    Manager  m1("lixinyan", 25, 01, 9);

    Employee* pe = &e1;
    cout << *pe << endl;

    Manager* pm = &m1;
    cout << *pm << endl;

    pe = &m1;            // upcasting 类对象指针向上转型
    cout << *pe << endl;

    e1 = m1;            // upcasting 类对象向上转型，产生对象切割object slicing
    cout << e1 << endl;
    cout << m1 << endl;

    cout << "===========私有继承=============" << endl;

    Manager2 m2("zhang", 40, 15, 01);
    pe = reinterpret_cast<Employee*>(&m2);    // 私有继承，指针强制转换
    //cout << *pe << endl;
    Employee& ec = reinterpret_cast<Employee&>(m2);// 私有继承，引用强制转换
    cout << ec << endl;

    cout << "===========向下转型===============" << endl;
    Manager* mc = reinterpret_cast<Manager*>(pe);// 私有继承，引用强制转换
    cout << *mc << endl;
    Manager* mc2 = static_cast<Manager*>(pe);// 私有继承，引用强制转换
    cout << *mc2 << endl;

    return 0;
}
#endif

//####################### 继承4-多重继承与虚基类 ################################
#if 0
//==============================================================================
// 单继承：一个派生类只能有一个基类。
// 多重继承：一个派生类可以有多个基类：class Derived : public Base1, public Base2,...
// 多重继承中解决二义性：
//   1、用类名作限定，明确指明要访问哪个基类中的成员。
//   2、但是当多个基类又派生自同一个基类时，则访问此共同基类的成员，类名也无法限定，
//      此时需要采用虚基类来解决。
//==============================================================================
// 虚基类：用于有共同基类的场合。
// 1、声明：用virtual修饰基类 calss Derived : virtual public Base, ...
// 2、作用：为[最远]的基类提供唯一的基类成员，而不重复产生多次拷贝。
// 虚基类及其派生类的构造函数：
// 1、虚基类的成员是由最远派生类的构造函数通过调用虚基类的构造函数来初始化的。
// 2、在整个继承结构中，直接或间接继承虚基类的所有派生类，都必须在构造函数的初始化列表中
//    给出对虚基类的构造函数的调用，如果未列出表示调用虚基类的默认构造函数。
// 3、在建立对象时，只有最远派生类的构造函数调用虚基类的构造函数，该派生类的其它基类
//    对虚基类构造函数的调用将被忽略。而且无论初始化列表中顺序如何，最远派生类都是先
//    初始化最远的那个虚基类，然后是各个基类。
//==============================================================================
//             BB
// B1虚继承BB      B2虚继承BB       典型的钻石型继承
//         DD继承B1 B2
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class Furniture
{
public:
    Furniture(int weight) : weight_(weight)
    {
        cout << "Furniture one param ..." << weight << "..." << endl;
    }

    ~Furniture()
    {
        cout << "~Furniture ..." << endl;
    }

    int GetWeight() const
    {
        return weight_;
    }
    void SetWeight(int weight)
    {
        weight_ = weight;
    }
private:
    int weight_;
};

class Bed : virtual public Furniture
{
public:
    Bed(int weight) : Furniture(weight)
    {
        cout << "Bed one param " << weight << "..." << endl;
    }
    ~Bed()
    {
        cout << "~Bed ..." << endl;
    }
    void Sleep() const
    {
        cout << "Sleep ..." << endl;
    }
};

class Sofa : virtual public Furniture
{
public:
    Sofa(int weight) : Furniture(weight)
    {
        cout << "Sofa one param " << weight << "..." << endl;
    }
    ~Sofa()
    {
        cout << "~Sofa ..." << endl;
    }
    void WatchTv() const
    {
        cout << "WatchTv ..." << endl;
    }
};

class SofaBed : public Bed, public Sofa
{
public:
    SofaBed(int weight) : Bed(weight), Sofa(weight), Furniture(weight)
    {
        cout << "SofaBed one param " << weight << "..." << endl;
    }
    ~SofaBed()
    {
        cout << "~SofaBed ..." << endl;
    }
    void FoldOut() const
    {
        cout << "FoldOut ..." << endl;
    }
    void FoldIn() const
    {
        cout << "FoldIn ..." << endl;
    }
};

int main(void)
{
    Bed bed(100);
    cout << bed.GetWeight() << endl;

    cout << "==================" << endl;

    Sofa sofa(100);
    cout << sofa.GetWeight() << endl;

    cout << "==================" << endl;

    SofaBed sb(90);
    //sb.SetWeight(30);
    cout << sb.Furniture::GetWeight() << endl;
    cout << sb.Bed::GetWeight() << endl;
    cout << sb.Sofa::GetWeight() << endl;

    cout << "==================" << endl;

    sb.Sleep();
    sb.WatchTv();
    sb.FoldOut();
    sb.FoldIn();

    cout << "==================" << endl;

    cout << "sizeof(Furniture): " << sizeof(Furniture) << endl;
    cout << "sizeof(Bed): " << sizeof(Bed) << endl;
    cout << "sizeof(Sofa): " << sizeof(Sofa) << endl;
    cout << "sizeof(SofaBed): " << sizeof(SofaBed) << endl;

    cout << "==================" << endl;

    return 0;
}
#endif

//################### 继承5-虚继承对C++内存模型的影响 ########################
#if 0
//==============================================================================
// 类大小计算遵循结构体对齐原则；
// 类大小与数据成员有关，与成员函数无关；
// 类大小与静态数据成员无关；
// 虚继承对类大小的影响：每一个虚基类都会为派生类新增一个指针成员。
// 虚函数对类大小的影响：
//==============================================================================
// 虚基类表指针(virtual base table pointer)vbptr:
// 虚基类表(virtual base table)中保存的内容：
//  * 本类地址与虚基类表指针地址的差   [本类地址 - 虚基类表指针地址]
//    -> 注意：本类地址是指vbptr的直接拥有者，如DD类对象中分别有B1和B2，B1和B2
//              又都有一个vbptr，则B1的vbptr中本类地址指的是B1对象的地址，而不是DD的。
//  * 虚基类地址与虚基类表指针地址的差 [虚基类地址 - 虚基类表指针地址]
//==============================================================================
// virtual含义: 不是虚拟的意思：
// 1、存在 [实质上的，事实上的]
// 2、共享：虚基类一般会被放在整个类对象内存模型的最后面。实际上放哪不所谓。
// 3、间接：派生类对象对虚基类对象的访问是间接，先找到派生类的vbptr,然后用
//           xx = vbptr[1] - vbptr[0]可以算出虚基类地址相对于本类地址的偏移量
//           xx，然后本类地址 + xx就是虚基类地址。
//==============================================================================
// * 使用指向派生类对象的基类指针访问基类成员时，并不是简单的地址赋值，而是
//   要在运行时根据虚基类表指针进行调整，使基类指针其指向正确的地方。
// * 但使用派生类对象而不是基类指针访问基类成员，是直接访问，编译时就能确定，
//==============================================================================
//***[无论是栈上的对象还是堆上的对象，它们的内存模型在编译期就可以确定]
//***[栈空间是由编译器管理的，栈上对象的地址是由编译器分配的，所以编译器可以
//    明确知道栈上每一个对象的具体地址，根据对象的内存模型，可以直接得到对象
//    中每个成员的具体地址，所以凡是栈上的内存使用与访问，都可以在编译期确定，
//    而且访问时是直接访问。]
//***[而堆空间是由系统进行管理的，它不归编译器管理，具体使用的是哪块地址，只
//    有到运行时x向系统具体申请了堆内存，才知道使用的是哪块地址区域，所以编译
//    器无法在编译时就确切知道这些地址，也就是堆上对象的地址在编译期是未知的，
//    所以不能在编译期直接访问这些堆上的地址，而要通过间接手段。一般是通过相
//    对于对象首地址的偏移来访问]
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class BB
{
public:
    int bb_;
};

class B1 : virtual public BB
{
public:
    int b1_;
};

class B2 : virtual public BB
{
public:
    int b2_;
};

class DD : public B1, public B2
{
public:
    int dd_;
};

int main(void)
{
	cout << "================== size ================" << endl;

	cout << "sizeof(BB): " << sizeof(BB) << endl;
    cout << "sizeof(B1): " << sizeof(B1) << endl;
    cout << "sizeof(B2): " << sizeof(B2) << endl;
    cout << "sizeof(DD): " << sizeof(DD) << endl;

    cout << "================== B1 struct ==============" << endl;
	long** p;

    B1 b1;
	p = (long**)&b1;
	cout << "&b1:    : 0x" << &b1 << endl;
	cout << "vbptr   : " << p[0][0]  << " | " << p[0][1]<< endl;
	cout << "&b1.b1_ : 0x" << &b1.b1_ << endl;
	cout << "&b1.bb_ : 0x" << &b1.bb_ << endl;

    cout << "================== DD struct ==============" << endl;

	DD dd;
	dd.bb_ = 100;
	p = (long**)&dd;
	cout << "&dd         : 0x" << &dd << endl;
	cout << "vbptr       : " << p[0][0]  << " | " << p[0][1]<< endl;
	cout << "&dd.B1::b1_ : 0x" << &dd.B1::b1_ << endl;
	p = (long**)((int*)&dd+2);
	cout << "vbptr       : " << p[0][0]  << " | " << p[0][1]<< endl;
	cout << "&dd.B2::b1_ : 0x" << &dd.B2::b2_ << endl;
	cout << "&dd.dd_     : 0x" << &dd.dd_ << endl;
	cout << "&dd.bb_     : 0x" << &dd.bb_ << endl;

	cout << "================== virtual ==============" << endl;

	BB* pp;
	pp = &dd; // pp并不是简单的指向dd的首地址，不然pp->b_访问的应该是pp开始的
	          // 前四个字节而不是真正的bb_，它是在运行时通过vbptr间接得到dd中
	          // 包含的BB类对象地址，然后用这个地址进行偏移去访问bb_;
	cout << pp << endl;
	cout << pp->bb_ << endl;


	getchar();
    return 0;
}
#endif

//########################## 虚函数与多态1 ####################################
#if 0
//==============================================================================
// 多态：发出同样的消息被不同类型的对象接收时，有可能导致完全不同的行为。
// 1、调用同名的函数导致不同的行为
// 2、以一致的观点对待同一类派生下来的对象，减轻了分别设计的负担。
// 多态的实现：
// 1、函数重载、运算符重载：静态多态/静态绑定
// 2、模板：静态多态/静态绑定
// 3、虚函数：动态多态/动态绑定
//==============================================================================
// 静态绑定与动态绑定：
// 1、静态绑定：发生于编译阶段，在编译期就确定要调用的函数。
// 2、动态绑定：发生于程序运行时执行，运行时才确定要调用的函数。
//==============================================================================
// 虚函数：
// 1、概念：在基类中用virtual修饰
// 2、如果函数在基类中被生命为虚函数，则它在所有派生类中都是虚函数。
// 3、只有通过基类指针或者引用调用时才能引发动态绑定。
// 4、虚函数不能生命为静态函数。
//==============================================================================
// 基类指针指向派生类对象：
// 1、如果是虚函数，则调用的是派生类中的同名虚函数，
// 2、如果是非虚函数，则根据指针实际类型来调用相应类型的成员函数。
//==============================================================================
// 虚析构函数：
// 1、如果析构函数不是虚的，则会根据指针类型来调用析构函数，基类指针就调用基类
//    析构函数，不会去管实际指向对象的类型，如果通过基类指针向派生类对象，存在
//    内存泄漏的风险。
// 2、如果析构函数是虚的，则会根据指针指向对象的真实类型来调用析构函数，基类指
//    针就会调用某个具体派生类的析构函数。
// * 如果一个类要作为多态基类，就应当使用虚析构函数。
// * 如果一个类永远不会被派生类继承，就不要定义成虚函数，无端增加数据复杂性。
//==============================================================================
// 虚表指针：
// 1、虚函数的动态绑定是通过虚表来实现的。含有虚函数的类，类对象内存空间的前
//    4/8个存储单元用来保存虚表指针，它指向一个虚表。
//==============================================================================
// object slicing与虚函数：
// * MyDoc对象强制转换为CDocument对象,向上转型，虚表也会发生变化转换后就是
//   完完全全的CDocument了，包括虚表。期间需要调用拷贝构造函数。
//==============================================================================
// overload overwrite override:
// 1、overload重载，特征：
//    * 相同的作用域[同一类中]
//    * 函数名称相同
//    * 参数不同
//    * virtual关键字可有可无
// 2、overwrite覆盖是指派生类函数覆盖基类函数,特征：
//    * 不同的作用域[派生类与基类]
//    * 函数名字与参数都相同
//    * 基类函数必须有virtual关键字
// 3、override重定义（派生类与基类），特征：
//    * 不同的作用域[派生类与基类]
//    * 函数名与参数都相同，无virtual关键字
//    * 函数名相同，参数不同，virtual可有可无。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	virtual void func1()
	{
		cout << "Base::Func1 ... " << endl;
	}

	virtual void Func2()
	{
		cout << "Base::Func2 ... " << endl;
	}

	/*void Func3()
	{
		cout << "Base::Func3 ... " << endl;
	}*/

	Base()
	{
		cout << "Base ..." << endl;
	}

	//virtual ~Base()
	//{
	//	cout << "~Base ..." << endl;
	//}

	int data_base_;
};

class Derived : public Base
{
public:
	///*virtual*/ void func1()
	//{
	//	cout << "Derived::Func1 ... " << endl;
	//}

	/*virtual*/ void Func2()
	{
		cout << "Derived::Func2 ... " << endl;
	}

	virtual void Func3()
	{
		cout << "Derived::Func3 ... " << endl;
	}

	Derived()
	{
		cout << "Derived ..." << endl;
	}

	/*virtual ~Derived()
	{
		cout << "~Derived ..." << endl;
	}*/

	int data_derived_;
};

class CObject
{
public:
	virtual void Serialize()
	{
		cout << "CObject::Serialize ..." << endl;
	}
};

class CDocument : public CObject
{
public:
	int data1_;
	void Func()
	{
		cout << "CDocument::Func ..." << endl;
		Serialize();
	}

	virtual void Serialize()
	{
		cout << "CDocument::Serialize ..." << endl;
	}

	CDocument()
	{
		cout <<"CDocument default constructor ..." << endl;
	}

	CDocument(const CDocument& other)
	{
		cout <<"CDocument copy constructor ..." << endl;
	}

	~CDocument()
	{
		cout <<"~CDocument deconstructor ..." << endl;
	}
};

class CMyDoc : public CDocument
{
public:
	int data2_;

	virtual void Serialize()
	{
		cout << "CMyDoc::Serialize ..." << endl;
	}
};


typedef void(*FUNC)();

int main(void)
{
	/*
	Base* p;
	p = new Derived;
	p->func1();
	p->Func2();
	p->Func3();
	delete p;
	*/

	//Base b;
	//cout << sizeof(Base) << endl;
	//cout << sizeof(Derived) << endl;

	//long** p = (long**)(&b);

	//FUNC func1 = (FUNC)p[0][0];
	//func1();
	//FUNC func2 = (FUNC)p[0][1];
	//func2();

	//cout << "======================" << endl;

	//Derived	d;
	//p = (long**)&d;
	//cout << &d.data_base_ << endl;
	//cout << &d.data_derived_ << endl;
	//FUNC func_d0 = (FUNC)(p[0][0]);
	//FUNC func_d1 = (FUNC)(p[0][1]);
	//FUNC func_d2 = (FUNC)(p[0][2]);
	//func_d0();
	//func_d1();
	//func_d2();

	//cout << "======================" << endl;

	//Base* pp = &d;
	//pp->Func2(); // 动态绑定
	//d.Func2();   // 没有动态绑定，是静态绑定。

	CMyDoc mydoc;
	CMyDoc* pmydoc = new CMyDoc;

	cout << "#1 testing" << endl;
	mydoc.Func();

	cout << "#2 testing" << endl;
	((CDocument*)(&mydoc))->Func();

	cout << "#3 testing" << endl;
	pmydoc->Func();

	cout << "#4 testing" << endl;
	((CDocument)mydoc).Func(); // MyDoc对象强制转换为CDocument对象,向上转型，虚表也会发生变化
	                           // 转换后就是完完全全的CDocument了，包括虚表。期间需要调用拷贝
	                           // 构造函数。对象切割


	getchar();
	return 0;
}
#endif

//########################## 虚函数与多态2 ####################################
#if 0
//==============================================================================
// 虚函数：基类指针指向派生类对象，调用的是派生类虚函数，而不是基类的。使得
//          可以以一致的观点看待派生类。
// * 在基类中定义共同的接口，并声明为虚函数。
// * 问题：如果基类的接口没办法实现怎么办，如形状Shape
// * 解决方法：将这些接口定义为纯虚函数。
//==============================================================================
// 纯虚函数：
// * 拥有纯虚函数的类为抽象类，即使只有一个。
// * 纯虚函数不需要实现。
// * 抽象类不能实例化。抽象类只能作为基类使用。
// * virtual ReturnType FuncNname(para list) = 0
// 注意：
// 1、构造函数不能是虚函数。因为在构造函数调用完成前，对象还没有构造出来，
//    也就不存在虚表，也就没法调用。
// 2、析构函数可以是虚函数。实际上，如果作为基类，并且有派生类，就用该声明
//    为虚的，不然存在内存泄漏风险。
//==============================================================================
// 多态：
// 1、多态有助于更好地对程序进行抽象：
//    * 控制模块功能专注于一般性问题的处理，具体操作交给具体的对象去做。
// 2、多态有助于提高程序的可扩展性：
//    * 可以把控制模块和被操作的对象分开。
//    * 可以添加已定义类的新对象，并能管理该对象
//    * 可以添加新类(派生类)的新对象，并能管理该对象
//==============================================================================
// 虚析构函数：
// 1、析构函数可以声明为虚函数：
//    * delete基类指针时，程序会根据基类指针指向的对象的类型确定要调用的析
//      构函数。
//    * 基类的析构函数为虚函数，则所有派生类的析构函数都是虚函数。
// 2、析构函数可以是纯虚函数:
//    ** 一般用在：这个类没有任何一个接口的前提下，但希望这个类是抽象类的时候，
//      可以声明一个纯虚析构函数，使得类成为抽象类。如果有接口，则一般不需要
//      纯虚析构函数.
//    * 纯虚析构函数不同于一般纯虚函数[基类中不需要实现]，它需要在基类中实现，
//      给出一个空的实现即可。
//==============================================================================
// 将分散的类创建统一管理：工厂模式。
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

class Shape                  // 抽象类
{
public:
	virtual void Draw() = 0; // 纯虚函数
	virtual ~Shape() = 0     // 纯虚析构函数
	{
		cout << "~Shape ..." << endl;
	}
};

class Circle : public Shape
{
public:
	void Draw()
	{
		cout << "Circle::Draw() ..." << endl;
	}
	~Circle()
	{
		cout << "~Circle ..." << endl;
	}
};

class Square : public Shape
{
public:
	void Draw()
	{
		cout << "Square::Draw() ..." << endl;
	}
	~Square()
	{
		cout << "~Square ..." << endl;
	}
};

class Rectangle : public Shape
{
public:
	void Draw()
	{
		cout << "Rectangle::Draw() ..." << endl;
	}
	~Rectangle()
	{
		cout << "~Rectangle ..." << endl;
	}
};

// 控制代码
void DrawAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it = v.begin(); it != v.end(); ++it) {
		(*it)->Draw();
	}
}

void DeleteAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it = v.begin(); it != v.end(); ++it) {
		delete (*it);
	}
}

// 工场类
class ShapeFactory
{
public:
	static Shape* CreateShape(const string& name)
	{
		Shape* ps = NULL;

		// 多态的目的就是消除这种无聊的判断，此处仍然有判断，
		// 可以借助"动态创建"消除。
		if (name == "Circle") {
			ps = new Circle;
		} else if (name == "Square") {
			ps = new Square;
		} else if (name == "Rectangle") {
 			ps = new Rectangle;
		}

		return ps;
	}
};

int main(void)
{
	vector<Shape*> v;
	Shape* ps;
	/*ps = new Circle;
	v.push_back(ps);
	ps = new Square;
	v.push_back(ps);
	ps = new Rectangle;
	v.push_back(ps);*/
	ps = ShapeFactory::CreateShape("Circle");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Square");
	v.push_back(ps);
	ps = ShapeFactory::CreateShape("Rectangle");
	v.push_back(ps);

	DrawAllShape(v);
	DeleteAllShape(v);

	getchar();
	return 0;
}
#endif

//########################## 对象动态创建 #####################################
#if 0
//==============================================================================
// * 对象动态创建：给定一个字符串可以创建出一个对应的类。
// * 类似于java的反射技术：动态获取类型信息[方法和属性]：
//   -> 动态创建对象 、 动态调用对象 、 动态操作对象
//   -> 方式：给每个类添加元数据
//==============================================================================
// 本节：不改变原有对象，通过宏实现对象的动态创建。
//==============================================================================
// 基于组件的编程。
// 组件A, 主程序能创建A。后面增加了一个组件B，我们希望main能创建B又不需要去
// 改动主程序，只需要更新配置文件[main中根据配置文件创建组件]。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "Shape.h"
#include "DynBase.h"

// 控制代码
void DrawAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it = v.begin(); it != v.end(); ++it) {
		(*it)->Draw();
	}
}

void DeleteAllShape(const vector<Shape*>& v)
{
	vector<Shape*>::const_iterator it;
	for(it = v.begin(); it != v.end(); ++it) {
		delete (*it);
	}
}
//
//// 工场类
//class ShapeFactory
//{
//public:
//	static Shape* CreateShape(const string& name)
//	{
//		Shape* ps = NULL;
//
//		// 多态的目的就是消除这种无聊的判断，此处仍然有判断，
//		// 可以借助"动态创建"消除。
//		if (name == "Circle") {
//			ps = new Circle;
//		} else if (name == "Square") {
//			ps = new Square;
//		} else if (name == "Rectangle") {
//			ps = new Rectangle;
//		}
//
//		return ps;
//	}
//};

int main(void)
{
	// 可以把这些东西放到配置文件中去，新增了类这里的代码也不需要改动。
	vector<Shape*> v;
	Shape* ps;
	ps = static_cast<Shape*>(DynObjectFactory::CreateObject("Circle"));
	v.push_back(ps);
	ps = static_cast<Shape*>(DynObjectFactory::CreateObject("Square"));
	v.push_back(ps);
	ps = static_cast<Shape*>(DynObjectFactory::CreateObject("Rectangle"));
	v.push_back(ps);

	DrawAllShape(v);
	DeleteAllShape(v);

	getchar();
	return 0;
}
#endif

//############################## RTTI ##########################################
#if 0
//==============================================================================
// RTTI:运行时类型信息
//==============================================================================
// static_cast 编译器认可的转型
// reinterpret_cast 编译器不认可的转型，不做任何对对齐操作[内存不会有任何变化]，
//                  而C风格的类型转换会做对齐操作
// const_cast 去除常量限定
// dynamic_cast 安全的向下转型
//==============================================================================

#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

class Shape {
public:
    virtual void Draw() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void Draw() {
        cout << "Circle ..." << endl;
    }
};

class Square : public Shape {
public:
    void Draw() {
        cout << "Square ..." << endl;
    }
};

int main(void)
{
    Shape *p;
    Circle c;

    p = &c;
    p->Draw();

    cout << "================= dynamic_cast ========================" << endl;
    // 类型安全的向下转型，只有基类指针确实指向该类时，向该类转型才会成功。
    // 这种运行时类型识别，比用虚函数的开销大。基类需要有虚函数才能利用dynamic_cast
    // C++的多态机制中，保存了RTTI信息，位于虚表之前，C++的dynamic_cast通过查询该
    // 内存段的信息，可以获知运行时信息。
    if (dynamic_cast<Circle*>(p)) {
        cout << "p is Circle object" << endl;
    } else if (dynamic_cast<Square*>(p)) {
        cout << "p is Square object" << endl;
    } else {
        cout << "p is Other object" << endl;
    }

    cout << "================= typeid ========================" << endl;
    // 返回一个type_info类对象
    // 效率也没直接虚函数效率高
    cout << typeid(*p).name() << endl;
    cout << typeid(Circle).name() << endl;
    if (typeid(*p).name() == typeid(Circle).name()) {
        cout << "p is point to a Circle object" << endl;
        ((Circle*)p)->Draw();
    } else if (typeid(*p).name() == typeid(Square).name()) {
        cout << "p is point to a Square object" << endl;
        ((Square *) p)->Draw();
    }

	getchar();
	return 0;
}
#endif

#if 0
//############################ 类与类之间的关系 ##################################
//==============================================================================
// RUP Rational Unified Process 一开始就要有好的设计，才能保证软件开发质量
// XP eXtreme Programming 极限编程  敏捷软件开发，不需要一开始就有好的设计，但最终目标也是好的设计
// 极限编程提倡：
//    > 用户素材
//    > 短周期交付
//    > 结对编程：一个工程师编码，另一个工程师看着，一个遇到困难，另一个再上，交换思想
//    > 测试驱动开发：要完成某个任务，先编写测试用例，直接测试会导致失败，迫使我们编写实
//                   际代码，指导所有测试用例都成功
//    > 重构：不改变软件行为的前提，重构代码，从而改善既有的设计。
//==============================================================================
// 用于静态建模[软件结构]：
// 类图
// 对象图
// 用例图
// 组件图
// 部署图
// 用于动态建模[软件行为]：
// 组合结构图
// 序列图
// 协作图
// 状态图
// 活动图
//==============================================================================
// 类图：
// 1、继承关系
// 2、关联关系（固定关系。如订单是消费者的成员，则二者是关联关系，包含单向和双向）
// 3、聚合关系（固定关系。整体与部分的关系，但这个部分的生命周期不由整体来管理，整体结束生命周期，局部
//             并不一定结束生命周期，如公司与员工的关系）
// 4、组合关系（固定关系。整体与部分的关系，但这个部分的生命周期由整体来管理，整体结束生命周期，局部
//             也会结束生命周期，如公司与部门的关系）
// 5、依赖关系（偶然的、临时的关系。最弱的关联关系，A依赖B，从语义上就是A使用B，如：B作为
//             A的成员函数参数、B作为A的成员函数的局部变量、A的成员函数调用B的静态方法）
// 总结：
//    > 继承体现的是类与类之间的纵向关系，其它四种体现的是类与类之间的横向关系。
//    > 强弱：依赖<关联<聚合<组合
//    > 继承（A is B）
//    > 关联、聚合、组合（A has B）
//    > 依赖（A use B）
//==============================================================================

#endif

//################################# 异常1 ######################################
#if 0
//==============================================================================
// C语言错误处理方法：
// 1、返回值（if...else语句判断错误）；
// 2、errno：linux系统调用与C库函数调用时，如果出错返回-1，并置errno为相应的错误代码；
// 3、goto语句
// 4、setjmp、longjmp（这种跳转不会调用析构函数，因此堆上的对象不能被正常清理），
//    错误代码和错误处理代码可以分处理，两者可以相隔很远。它是C++异常处理的雏形。
//============================== C异常处理 =====================================
#if 0
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

float Divide(float a, float b) {
	if (b == 0) { // => throw 抛出异常
		longjmp(buf, 1); // 恢复先前保存的栈环境,跳转到setjmp处
	} else {
		return a / b;
	}
}

int main(void)
{
	int ret = setjmp(buf); // 保存栈环境
	if (ret == 0) { // => try 执行代码
		printf("Start dividing ...\n");
		float res = Divide(5.0f, 0.0f);
		printf("Result = %f\n", res);
	} else if (ret == 1) { // => catch,捕获异常
		printf("Divisor is zeros!\n");
	}

	getchar();
	return 0;
}
#endif
//==============================================================================
// C++中的异常不能被忽略，如果没有catch语句，出现错误会传递给系统，结束程序
//============================== C++异常处理 ===================================
#if 0
#include <iostream>
using std::cout;
using std::endl;

float Divide(float a, float b) {
	if (b == 0) { // => throw 抛出异常
		throw(1); // 恢复先前保存的栈环境,跳转到setjmp处
	} else {
		return a / b;
	}
}

int main(void)
{
	try { // => try 执行代码
		cout << "Start dividing ..." << endl;
		float res = Divide(5.0f, 1.0f);
		cout << "Result = " << res << endl;
		res = Divide(5.0f, 0.0f);
		cout << "Result = " << res << endl;
	} catch(int) { // => catch,捕获异常
		cout << "Divisor is zeros!" << endl;
	}

	getchar();
	return 0;
}
#endif
#endif

//################################# 异常2 #######################################
#if 0
//==============================================================================
// 错误类型：
// 1、 编译错误。即语法错误。
// 2、 运行时错误：
//     * 不可预料的逻辑错误（程序正常运行，但结果不对）
//     * 可以预料的运行异常（程序运行异常），例如：
//         > 动态分配内存失败
//         > 打开文件失败
//         > 除法运算时分母可能为0
//         > 整数相除可能溢出
//         > 数组越界等...
//==============================================================================
// C++异常语法：
// 1、格式：
// try {
//							// throw(值)
// } catch(类型 参数) {
//
// } catch (类型 参数) {
//
// }
// 注：catch(...)三个点代表捕获所有异常
//
// 2、C++不仅可以抛出内置类型的异常，还能抛出自定义类型的异常。
// 3、异常发生之前创建的所有局部对象会被销毁，这一过程称为栈展开。
// 4、一个异常处理器一般只捕捉一种类型的异常；异常处理器的参数类型和抛出异常的类型相同；...表示
//    可以捕获任何异常。
// 5、异常处理器进行异常类型匹配时不会进行任何类型转换（派生类到基类除外），不如int异常不能与
//    double异常匹配，虽然int可以转换为double，类似的float异常也不能与double异常匹配。
// 6、try语句可以嵌套，程序按顺序寻找匹配的异常处理器，直达找到第一个类型匹配的异常处理器,便停止传播；
//    如果内层try块后面没有找到合适的异常处理器，该异常向外传播，到外层try块后面的catch块中寻找；
//    直到最外层try块后面都没有被捕获的异常，将传给系统，系统调用terminate函数，该函数默认调用
//    abort函数终止程序，可以通过set_terminate函数指定terminate调用的函数。
//==============================================================================
// 栈展开：
// * 沿着嵌套调用链接向上查找，直至为异常找到一个catch语句，这个过程成为栈展开。
// * 栈展开时要调用局部对象析构函数。
// * 析构函数应该从不抛出异常，栈展开过程中，如果调用的析构函数抛出异常，会调用terminate
// * 构造函数中可以抛出异常，此时该对象可能是部分构造，已被构造的部分如果是栈上的会自动被销毁，但是
//   如果成员是指针，就不能被自动销毁，这时会导致内存泄露。-----
//==============================================================================
#include <iostream>
#include <exception>
using std::cout;
using std::endl;
using std::string;

class MyException
{
public:
	MyException(const string& message) : message_(message) {
		cout << "MyException ..." << endl;
	}
	MyException(const MyException& other) : message_(other.message_) {
		cout << "Copy MyException ..." << endl;
	}
	~MyException() {
		cout << "~MyException ..." << endl;
	}
	const string& What() const {
		return message_;
	}
private:
	string message_;
};

float Divide(float a, float b) {
	if (b == 0) { // => throw 抛出异常
		cout << "b == 0 start" << endl;
		//throw(MyException("Divisor is zeros!")); // 恢复先前保存的栈环境,跳转到setjmp处
		throw(1.0f);
	} else {
		return a / b;
	}
}

void ProcTerminate()
{
    cout << "-- Terminate! --" << endl;
    abort();
}

int main(void)
{
    std::set_terminate(&ProcTerminate);

	try { // => try 执行代码
		cout << "Start dividing ..." << endl;
		float res = Divide(5.0f, 1.0f);
		cout << "Result = " << res << endl;
        try {
            res = Divide(5.0f, 0.0f);
            cout << "Result = " << res << endl;
        } catch (int i) {
            cout << "inner int exception" << endl;
            throw i; // 要想异常继续传播，则需要在捕获后重新抛出
        } catch(const MyException& e) { // => catch,捕获异常
            cout << "inner " << e.What() << endl;
            throw e;
        }
	} catch(const MyException& e) { // => catch,捕获异常
		cout << "outer " << e.What() << endl;
	} catch (int i) {
        cout << "outer int exception" << endl;
    } catch (double f) {
        cout << "outer double exception" << endl;
    }
//    catch (...) {
//        cout << "outer other exception" << endl;
//    }

	getchar();
	return 0;
}
#endif

//################################ 异常3 ########################################
#if 0
//==============================================================================
// 1、异常与继承
//   * 如果异常为C++类，并且该类有基类，则应该将派生类的错误处理程序放在前面，基类的错误处理程
//     序放在后面。
//==============================================================================
// 2、异常与指针
//   * 可以抛出指针，但不推荐。抛出指针要求在对应处理代码存在的任意地方都存在指针所指向的对象，
//     throw只会复制指针本身，而不会复制指针指向的内容。
//   * 抛出的任何类型的指针异常，都能被无类型指针(void*)异常处理器捕获。
//==============================================================================
// 3、异常规格说明
//   * 异常规格说明的目的是让函数使用者知道该函数可能抛出的异常有哪些。
//   * 可以在函数声明中列出该函数可能抛出的所有异常类型。void func() throw(A,B,C,D);
//   * 若无异常接口声明，则此函数可以抛出任何类型的异常。
//   * 不抛掷任何类型异常的函数声明如下： void func() throe()
//==============================================================================
// 4、C++标准库异常层次
//   * exception
//        |-- bad_Cast
//        |--bad_alloc
//        |-- runtime_error
//              |-- overflow_error
//              |-- underflow_error
//              |-- range_error
//        |-- logic_error
//              |-- domain_error
//              |-- invalid_argument
//              |-- out_of_range
//              |-- length_error
//==============================================================================
// 异常发生之前所做的操作，需要处理的，一定要保证发生异常时仍然能正确处理。因为并不一定全是释放
// 局部对象这种可以自动完成的事情，不如数据库插入，发生异常时需要取消这个操作等。
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
using std::string;

class MyException
{
public:
    MyException(const string& message) noexcept : message_(message) {
        cout << "MyException ..." << endl;
    }
    MyException(const MyException& other) noexcept : message_(other.message_) {
        cout << "Copy MyException ..." << endl;
    }
    virtual ~MyException() noexcept{
        cout << "~MyException ..." << endl;
    }
    const string& What() const noexcept{
        return message_;
    }
protected:
    string message_;
};

class MyExceptionD : public MyException
{
public:
    MyExceptionD(const string& message) noexcept : MyException(message) {
        cout << "MyExceptionD ..." << endl;
    }
    MyExceptionD(const MyExceptionD& other) noexcept : MyException(other) {
        cout << "Copy MyExceptionD ..." << endl;
    }
    ~MyExceptionD() noexcept {
        cout << "~MyExceptionD ..." << endl;
    }
    const string& What() const noexcept {
        return message_;
    }
};

void func() throw(int, MyException, MyExceptionD)
{
    throw MyExceptionD("func exception");
}

int main(void)
{
//    try {
//        throw MyExceptionD("test exception");
//    } catch (const MyExceptionD& e) {
//        cout << "catch MyExceptionD" << endl;
//        cout << e.What() << endl;
//    } catch (const MyException& e) {
//        cout << "catch MyException" << endl;
//        cout << e.What() << endl;
//    }

    try {
        MyExceptionD *e = new MyExceptionD("test exception");
        throw e;
    } catch (const MyExceptionD* e) {
        cout << "catch MyExceptionD" << endl;
        cout << e->What() << endl;
    } catch (const MyException* e) {
        cout << "catch MyException" << endl;
        cout << e->What() << endl;
    } catch (const void* e) {
        cout << "catch void*" << endl;
    }

    return 0;
}
#endif

//############################### 单例模式 ######################################
#if 0
//==============================================================================
// 析构函数不会被调用，怎么释放静态指针成员 -> 智能指针
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::unique_ptr;

class Singleton
{
public:
    static Singleton* GetInstance()
    {
//        if (instance_ == nullptr) {
//            instance_ = new Singleton;
//        }
//        return instance_;
        if (instance_.get() == nullptr) {
            instance_ = unique_ptr<Singleton>(new Singleton);
        }

        return instance_.get();
    }

    ~Singleton()
    {
        cout << "~Singleton" <<endl;
    }
private:
    // 禁止外部构建对象
    Singleton()
    {
        cout << "Singleton" << endl;
    }
    // 禁止拷贝
    Singleton(const Singleton& other);
    Singleton&operator=(const Singleton& other);

    static unique_ptr<Singleton> instance_;
};

unique_ptr<Singleton> Singleton::instance_;


int main(void)
{
    //Singleton* s0 = new Singleton(); // 外部无法创建对象

    Singleton* s1 = Singleton::GetInstance();
    Singleton* s2 = Singleton::GetInstance();

    return 0;
}
#endif

//############################## 实现sizeof #####################################
#if 0
#include <iostream>
using std::cout;
using std::endl;

// 两个指针相减，得到相隔几个元素
#define sizeof_v(x) (char*)(&x+1) - (char*)(&x)
#define sizeof_t(t) (char*)((t*)0+1) - (char*)(0)

// 对齐(给定一个值，对齐到某个基数[2^n]，如给定31，对齐到16->32）
#define ALIGN(v, b) ((v+b-1) & ~(b-1))

// 内存池要用到对齐

class Empty
{

};

int main(void)
{
    Empty e;
    cout << sizeof_v(e) << endl;
    cout << sizeof_t(Empty) << endl;

    cout << ALIGN(3,16) << endl;
    cout << ALIGN(31,16) << endl;
    cout << ALIGN(0,16) << endl;
    cout << ALIGN(4196,16) << endl;

    return 0;
}

#endif

//############################ IO - iostream ###################################
#if 0
//==============================================================================
// 1、IO类型：
//  * 标准IO：标准输入设备、标准输出设备的输入输出。
//  * 文件IO：外存磁盘上文件的输入输出。
//  * 串IO：内存中指定字符串存储空间的输入输出。
//
// 2、ostream cout
//    istream cin
//    typedef basic_istream<char, char_traits<char>> istream
//    typedef basic_ostream<char, char_traits<char>> ostream
//    basic_istream : basic_ios<_Elem, _Traits>
//    basic_ostream : basic_ios<_Elem, _Traits>
//    typedef basic_ios<char, char_traits<char>> ios
//
// 3、cin cout cerr clog
//==============================================================================
// 4、ostream流操作：
//    * operator << 插入运算符
//      - 可以连续使用，因为插入运算符返回的是流对象的引用
//    * put()函数
//      - 向输出流写入一个字符
//    * write()函数
//      - 向输出流写入字符串（字符缓冲区）
//==============================================================================
// 5、istream流操作：
//    * operator >> 提取运算符, [遇到空格停止]
//    * get()函数：获取单个字符，返回int,是字符的ASCII码
//    * getline()函数，按行获取，遇到空格不停止,并且对空白字符[空格]照读不误；遇到换行停止。
//    * read()函数，一直读取，空白字符、换行字符都照读不误，只有缓冲区读满了，再遇到换行符才会停止。
//    * putback()函数，将一个字符放回流中，读入abcdefg回车后，流的第一个字符是a，提取流是从
//      前向后，类似链表
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(void)
{
//    int n1 = 100;
//    int n2 = 200;
//    cout << n1 << " " << n2 << endl;
//
//    cout.put('H');
//    cout.put('e');
//    cout.put('\n');
//
//    char buf[] = "test!!!";
//    cout << sizeof(buf) << endl;
//    cout.write(buf, 5);


//    int ch = cin.get();
//    cout << ch << endl;

//    char ch1, ch2;
//    cin.get(ch1).get(ch2);
//    cout.put(ch1).put(ch2);

//    char buf[10]{0};
//    cin >> buf; // 遇空白字符停止
//    cout.write(buf,10);

//    char buf[10]{0};
//    cin.getline(buf,10); // 只接收10个char，其中包含一个\0,输入超过9个，只取前9个
//    // 输入不足9个，buf后面用\0填充。
//    cout.write(buf,10);

//    char buf[10]{0};
//    cin.read(buf,10);
//    cout.write(buf,10);
    char c[10], c1, c2;
    cin.get(c1);
    cin.get(c2);
    cin.putback(c1);
    cin.getline(c,10);
    cout.write(c,10);

    return 0;
}
#endif

//############################ IO - fstream 1 ##################################
#if 0
//==============================================================================
// 文件流：fstream ofstream ifstream
//     * open(file_name, openmode)函数
//        - app   写之前找到文件尾，如果多个流链接到文件，当别的流向文件写入数据后，该流再
//                  写入数据，不会覆盖其他流的数据，因为每次写的时候，都会重新定位到文件尾。
//        - ate   打开文件后立即定位到文件尾,打开之后，这个位置就不会变化了，如果多个流链接
//                  到文件，当别的流向文件写入数据后，该位置也不会发生改变，该流再写数据，会
//                  覆盖之前那个流写的数据。
//        - bin   以二进制形式打开一个文件
//        - in    读取
//        - out   写入
//        - trunc 废弃当前文件内容
//     * ofstream::open(),默认是out|trunc，会清空文件内容; 只使用out模式，也会清空；
//       out|app不会清空; in|out不会清空文件, fstream默认就是in|out,所以不会清空。
//     * out|app不清空， out|ate清空
//     * ofstream::open()，如果文件不存在会创建文件；ifstream文件不存在不会创建文件，会报错。
//==============================================================================
// 一个文件可以在一个进程中被打开多次，可以在不同线程中打开同一个文件多次。
//==============================================================================
// 流状态：
//    * ios::goodbit <->  bool good() 该位置位，表示一切正常，没有发生错误
//    * ios::eofbit  <->  bool eof()  该位置位，表示输入结束
//    * ios::failbit <->  bool fail() 该位置位，表示IO操作失败，主要原因是非法数据，例如
//                                    试图读数字遇到字母时，流可以继续使用，输入结束后也将置位。
//    * ios::badbit  <->  bool bad()  该位置位，表示发生了致命性错误，流不可以继续使用。
//==============================================================================
#include <iostream>
#include <fstream>
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;
#include <cassert>

int main(void)
{
    ofstream fout;
    fout.open("/home/xinyan/test.txt", ofstream::in|ofstream::out|ofstream::ate);
    // 判断是否打开成功
    // 方法一：
//    if (fout.is_open()) {
//        cout << "open success" << endl;
//    } else {
//        cout << "open failed" << endl;
//    }
    // 方法二：
//    if (fout.good()) {
//        cout << "open success" << endl;
//    } else {
//        cout << "open failed" << endl;
//    }
    // 方法三：
//    if (fout) {
//        cout << "open success" << endl;
//    } else {
//        cout << "open failed" << endl;
//    }

//    // 方法四：
//    if (!fout) {
//        cout << "open failed" << endl;
//    } else {
//        cout << "open success" << endl;
//    }

    assert(fout);

    ofstream fout2;
    fout2.open("/home/xinyan/test.txt", ofstream::in|ofstream::out|ofstream::ate);
    assert(fout2);

    fout << "X";
    fout2 << "Y";

    fout.close();
    fout2.close();




    return 0;
}
#endif

//############################ IO - fstream 2 ##################################
#if 0
//==============================================================================
// 文本文件读写：
//   * >>提取运算符， <<插入运算符
//   * put()， get()
//==============================================================================
// 1、二进制文件读写：
//     * 文本模式下写入字符时，遇到\n会进行转化，而以二进制方式打开文件不会转化。
//       windows平台\n会被转化为\n\r;
//       linux平台\n会被转化位\n,保留不变;
//       mac平台\n会被转化位\r。
//
//     * 以文本方式打开文件，可以写入二进制数据；以二进制数据打开文件，也可以写入文本。
//       写入的数据是文本还是二进制，与打开的方式无关，与写入的函数有关，如果要写入二进制数据，
//       应该使用write()，读取要使用read()。
//
//     * 二进制打开与文本模式打开唯一区别就是是否会对\n进行转化。
//
// 2、注意：当写入包含指针的结构体或者类对象时，不能整体写入，因为整体写入时，指针指向的内容并未被
//      写入，这样读进来后，如果使用这个指针成员，那就会出错。这是就要分开写，确保指针指向的内
//      容也能写入
//==============================================================================
// 1、当前文件流活动指针：文件流指针用以跟踪发生I/O操作的位置
//    * 每当从流中读取或写入一个字符，当前活动指针就会向前移动；
//    * 当打开文件中不包含ios::ate或者ios::app选项是，则文件指针被自动文件流的开始位置，即
//      字节位置为0的位置。
// 2、随机读写（通过改变文件流指针）：
//    * seekp 设置输出文件流的文件流指针位置
//        - ostream& seekp(pos_type pos); // pos:新的文件流位置值
//        - ostream& seekp(off_type off, ios_base::seekdir dir) // off:需要偏移的值
//                                                              // dir:偏移的起始位置
//           dir: ios::beg 文件流起始位置；
//                ios::cur 文件流当前位置
//                ios::end 文件流结束位置
//        - tellp() // 获取文件流指针当前的位置，相对于文件开始位置。
//    * seekg 设置输入文件流的文件流指针位置
//        - ostream& seekg(pos_type pos);
//        - ostream& seekg(off_type off, ios_base::seekdir dir)
//        - tellg() // 获取文件流指针当前的位置，相对于文件开始位置。
//
// 3、对应关系：
//        c++       |   c     |        linux
//    seekp, seekg  |  fseek  |        lseek
//    tellp, tellg  |  ftell  |  lseek(fd, 0, SEEK_CUR)[返回当前文件指针位置]
//==============================================================================
#include <iostream>
#include <fstream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
#include <cassert>

struct Test
{
    int a;
    int b;
};

struct Test2
{
    int a;
    string b;
    string c;
};

int main()
{
    // <<  >>
//    ofstream fout("/home/xinyan/test.txt");
//    assert(fout);
//    fout << "abc" << " " << 200;
//    fout.close();
//
//    ifstream fin("/home/xinyan/test.txt");
//    assert(fin);
//    string s;
//    int n;
//    fin >> s >> n; // 提取运算符，遇到空格结束，string中无空格
//    cout << s << n << endl;

    // put()  get()
//    char ch;
//    ofstream fout("/home/xinyan/test.txt");
//    assert(fout);
//    for (int i = 0; i < 26; ++i) {
//        ch = 'A' + i;
//        fout.put(ch);
//    }
//    fout.close();
//
//    ifstream fin("/home/xinyan/test.txt");
//    assert(fin);
//    while(fin.get(ch)) {
//        cout << ch << " ";
//    }
//    cout << endl;

    // 文本模式打开，写二进制数据
//    Test test{100, 200};
//    ofstream fout("/home/xinyan/test", ofstream::out|ofstream::binary);
//    assert(fout);
//    fout.write(reinterpret_cast<char*>(&test), sizeof(test));
//    fout.close();
//
//    Test test2;
//    ifstream fin("/home/xinyan/test", ifstream::in|ifstream::binary);
//    assert(fin);
//    fin.read(reinterpret_cast<char*>(&test2), sizeof(Test));
//    fin.close();
//    cout << test2.a << " " << test2.b << endl;

    // 二进制打开，写文本
//    ofstream fout("/home/xinyan/test", ofstream::out|ofstream::binary);
//    assert(fout);
//    fout << "abc" << 200;
//    fout.close();

    // 当写入包含指针的结构体或者类对象时，不能整体写入，因为整体写入时，指针指向的内容并未被
    // 写入，这样读进来后，如果使用这个指针成员，那就会出错。
    // 这是就要分开写，确保指针指向的内容也能写入。
//    Test2 test2{100, "xxx", "yyy"};
//    ofstream fout("/home/xinyan/test", ofstream::out|ofstream::binary);
//    assert(fout);
//    fout.write(reinterpret_cast<char*>(&test2), sizeof(Test2));
//    fout.close();
//    cout << sizeof(Test2) << endl;
//
//    Test2 test2_in;
//    ifstream fin("/home/xinyan/test", ofstream::in|ofstream::binary);
//    assert(fin);
//    fin.read(reinterpret_cast<char*>(&test2_in), sizeof(Test2));
//    cout << test2_in.a << " " << test2_in.b << " " << test2_in.c << endl;

    // 正确读写包含指针成员的二进制文件[结构体]
//    Test2 test2{100, "xxx", "yyy"};
//    ofstream fout("/home/xinyan/test", ofstream::out|ofstream::binary);
//    assert(fout);
//    fout.write((char*)(&test2.a), sizeof(test2.a));
//
//    int len = test2.b.size();
//    fout.write((char*)(&len), sizeof(len));
//    fout.write(test2.b.data(), test2.b.size());
//
//    len = test2.c.size();
//    fout.write((char*)(&len), sizeof(len));
//    fout.write(test2.c.data(), test2.c.size());
//
//    fout.close();
//
//    Test2 test2_in;
//    ifstream fin("/home/xinyan/test", ofstream::in|ofstream::binary);
//    assert(fin);
//    int len_in;
//    fin.read((char*)(&test2_in.a), sizeof(test2_in.a));
//
//    fin.read((char*)(&len_in), sizeof(len_in));
//    test2_in.b.resize(len_in); // 读入指针内容，首先要给指针分配空间，string里有char*成员。
//    fin.read(&test2_in.b[0], len_in); // 然后读入指针指向的内容
//
//    fin.read((char*)(&len_in), sizeof(len_in));
//    test2_in.c.resize(len_in);
//    fin.read(&test2_in.c[0], len_in);
//
//    cout << test2_in.a << " " << test2_in.b << " " << test2_in.c << endl;

    char ch;

    ifstream fin("/home/xinyan/test2");
    assert(fin);

    fin.seekg(2);
    fin.get(ch);
    cout << ch << endl;

    // 向后偏移一个位置，是因为最后一个字节是文件结束符，跳过它。
    fin.seekg(-1, ifstream::end);
    fin.get(ch);
    cout << ch << endl;

    // 获取文件大小
    fin.seekg(0, ifstream::end);
    ifstream::pos_type pos = fin.tellg();
    cout << pos << "B" << endl;

    fin.close();


    return 0;
}
#endif

//########################### IO - stringstream ################################
#if 0
//==============================================================================
// 1、字符串流的类型：
//    istringstream ostringstream stringstream
// 2、str()函数
//==============================================================================
#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ostringstream;
using std::istringstream;
#include <cassert>

string Double2String(double val)
{
    ostringstream os;
    os << val;

    return os.str();
}

double String2Double(string& str)
{
    double val;
    istringstream is(str);
    is >> val;

    return val;
}

int main(void)
{
    // 标量与字符串相互转换
    string s = Double2String(10.0);
    cout << s << endl;

    double val = String2Double(s);
    cout << val << endl;

    // 将逗号替换位点
    string ip = "192,168,0,100";
    istringstream ss(ip);
    int v1, v2, v3, v4;
    char ch;
    ss >> v1 >> ch >> v2 >> ch >> v3 >> ch >> v4;
    ostringstream os;
    ch = '.';
    os << v1 << ch << v2 << ch << v3 << ch << v4;
    cout << os.str() << endl;

    // 分割单词
//    string line;
//    string word;
//
//    while(getline(cin, line)) {
//        istringstream is(line);
//        while(is >> word) {
//            cout << word << "#";
//        }
//        cout << endl;
//    }



    return 0;
}
#endif

//########################### IO - 格式化输出 ####################################
#if 0
//==============================================================================
// 1、输出流格式化方式：
//    * 通过操纵子的形式
//    * 通过成员函数的形式
// 2、输出流格式化内容：
//    * 宽度控制[setw(10)]：不会影响后面的输出；
//    * 对齐控制[setiosflags(ios::left)]：默认右对齐,会影响后面的输出,可以通过
//         resetiosflags(ios::left)或者setiosflags(ios::right)恢复；
//    * 填充控制[setfill('?')]：默认空白字符填充,会影响后面的输出,可以通过setfill(' ')恢复；
//    * 精度控制[setprecision(4)]：默认指有效位数，setiosflags(ios::fixed)后变为小数点
//         后个位数,会影响后面的输出。。
//    * 进制控制[直接dec,oct,hex]：会影响后面的输出
//
//    cout.setf(ios::showbase)/setiosflags(ios::showbase),显示进制标志
//==============================================================================
#include <iostream>
#include <iomanip>
using namespace std;

int main(void)
{
    int n = 64;
    double d = 123.45;
    double d2 = 0.0187;

    cout << "###################### 操纵子 ########################" << endl;
    cout << "======= 宽度控制 =======" << endl;
    cout << n << '#' << endl;
    cout << setw(10) << n << '#' << endl;
    cout.width(10);

    cout << "======= 对齐控制 =======" << endl;
    cout << setw(10) << setiosflags(ios::left) << n << '#' << endl;
    cout << resetiosflags(ios::left);

    cout << "======= 填充控制 =======" << endl;
    cout << setw(10) << setfill('?') << n << '#' << endl;
    cout << setfill(' ');

    cout << "======= 精度控制 =======" << endl;
    cout << setprecision(4) << d << '#' << endl; // 有效数字
    cout << setprecision(2) << d2 << '#' << endl;
    cout << setiosflags(ios::fixed);
    cout << setprecision(4) << d << '#' << endl; // 小数点的个数
    cout << setprecision(2) << d2 << '#' << endl;
    cout << resetiosflags(ios::fixed);

    cout << "======= 进制控制 =======" << endl;
    cout << n << endl;        // 默认10进制
    cout << oct << n << endl; // 8进制
    cout << hex << n << endl; // 16进制
    cout << dec << n << endl; // 10进制

    cout << "##################### 成员函数 #######################" << endl;
    cout << "======= 宽度控制 =======" << endl;
    cout << n << '#' << endl;
    cout.width(10);
    cout << n << '#' << endl;

    cout << "======= 对齐控制 =======" << endl;
    cout.width(10);
    cout.setf(ios::left);
    cout << n << '#' << endl;
    //cout.setf(ios::right);
    cout.unsetf(ios::left);

    cout << "======= 填充控制 =======" << endl;
    cout.width(10);
    cout.fill('?');
    cout << n << '#' << endl;
    cout.fill(' ');

    cout << "======= 精度控制 =======" << endl;
    cout.precision(4);
    cout << d << '#' << endl; // 有效数字
    cout.precision(2);
    cout << d2 << '#' << endl;
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << d << '#' << endl; // 小数点的个数
    cout.precision(2);
    cout << d2 << '#' << endl;
    cout.unsetf(ios::fixed);

    cout << "======= 进制控制 =======" << endl;
    cout << n << endl;        // 默认10进制
    cout.unsetf(ios::dec);
    cout.setf(ios::oct);
    cout.setf(ios::showbase);
    cout << n << endl; // 8进制
    cout.unsetf(ios::oct);
    cout.setf(ios::hex);
    cout << n << endl; // 16进制
    cout.unsetf(ios::hex); // 10进制

    return 0;
}
#endif

//############################ 模板-函数模板 #####################################
#if 0
//==============================================================================
// 为什么要模板：不同的数据类型，具有相同的处理方式：
//    * [宏替换]：不做类型检查
//    * [函数重载]：为每个类型提供一个重载版本，程序自己维护这些重载的版本
//    * [函数模板]：为相同逻辑提供一个模板，将类型当做参数来传递，让编译器实例化对应版本的函数
//                来处理（让编译器维护不同的重载函数，程序维护一份函数模板），结合了宏替换和
//                函数重载。是一种'类型参数化'的多态。函数版本编译器决定，属于静态多态。
// 1、模板：数据类型参数化
// 2、函数模板:
//    * 模板形参在模板中作为一种类型使用，可以用于函数形参、函数返回值和函数局部变量；
//    * 每个模板形参要在函数的'形参列表'中至少出现一次； @@@@@@@@
//    * 模板参数名的作用域局限于函数模板范围内。
// 3、函数模板的使用：
//    * 函数模板不是函数，不能被执行 -> 置换模板中的类型参数得到'模板函数'[实例化][编译过程
//      中完成] -> 实例化后的模板函数是真正的函数，可以被执行。
//    * 整个编译过程中，模板被编译了两次：
//        - 实例化之前，检查模板代码本身，查看语法是否正确；
//        - 实例化期间，检查模板代码，查看是否所有调用都有效。
//    * 普通函数只需要声明，即可顺利编译，而模板的编译需要查看模板的定义。C++是分离编译，头文
//      件和实现文件是单独编译的，如果把模板的声明和实现分开，在编译的时候就没法推导出模板函数，
//      即无法实例化，链接的时候就会出错。 @@因此模板的声明和实现必须在一起，不能像一般函数那
//      样分开@@
// 3、函数模板特化：针对某种数据类型进行特化，还是模板函数
// 4、重载函数模板:
//     * 函数模板可以重载
//     * 可以用非模板函数(普通函数)重载一个同名的函数模板@@@@@@
//       >>>> 重载的非模板函数是全局函数，优先调用全局函数。
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;
#include "max.hpp"

class Test
{

};

class Test2
{
public:
    friend bool operator> (const Test2& a, const Test2& b)
    {
        return true;
    }
};

int main(void)
{
    // ::表示全局函数，一般用于自己函数与库函数名相同，调用自己的函数。
    double res = ::Max(3.6, 5.4); // 这里没有在<>中实例化数据类型，实际上是编译器自己
                                  // 根据传的实参推导出了模板函数。
    char ch = Max('A', 'a');

    cout.setf(std::ios::fixed);
    cout.precision(4);
    cout << res << ch << endl;


//    Test t1, t2;
//    Test ret = Max(t1, t2); // 调用无效，Test不支持>运算符
    Test2 t1, t2;
    Test2 ret = Max(t1, t2); // 调用有效效，Test2支持>运算符

    const char* str1 = "zzz";
    const char* str2 = "aaa";
    cout << Max(str1, str2) << endl; // 此时比较的是指针变量，而不是字符串内容,与预期不符，
                                     // 可以通过模板特化来修正。

    cout << Max(1.0, 5.0, 3.0) << endl;

    cout << Max('a', 50) << endl; // 调用的是重载的非模板函数
    cout << Max<int>('a', 50) << endl; // 调用的是模板函数,数据类型是显示给定的，不是编
                                        // 译器自己推导的
//    cout << Max<>('a', 50) << endl; // 调用的是模板函数，只是要由编译器自己推导数据类型，
                                    // 如果推导不出来，就会编译出错。

    return 0;
}
#endif

//############################ 模板-类模板 #######################################
#if 0
//==============================================================================
// 1、类模板：将类定义中的数据类型参数化。
// 2、类模板使用：
//    * 类模板的实例化：用具体的数据类型替换模板的参数得到具体的类，模板类；
//    * 模板类可以实例化为类；
//    * 类名<数据类型实参表> 对象名称：两个实例化过程，类模板实例化为模板类，模板类有实例化为
//                                一个对象。
//    * 类模板只能显示实例化，不能像函数模板那样由编译器自动推导。@@@@@@@@@@@@@@@@@@@@@@@
// 3、非类型模板参数：对于函数模板与类模板，模板参数并不局限于类型，普通值也可以作为模板参数。
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;
#include "Stack.hpp"
#include "Stack2.hpp" // 使用非类型模板参数

int main(void)
{
//    Stack<int> stack(10);
//    stack.Push(1);
//    stack.Push(2);
//    stack.Push(3);
//
//    while(!stack.IsEmpty()) {
//        cout << stack.Top() << endl;
//        stack.Pop();
//    }

    Stack2<int,10> stack; // max_size以模板参数的形式传递给类模板
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    while(!stack.IsEmpty()) {
        cout << stack.Top() << endl;
        stack.Pop();
    }

    return 0;
}
#endif

//############################ 模板-其它 #######################################
#if 1
//==============================================================================
// 缺省模板参数
// 成员模板
// 关键字typename
// 派生类和模板
// 面向对象与泛型
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{

    return 0;
}
#endif

//############################ 模板-应用 #######################################
#if 0
//==============================================================================
// 模板实现单例模式
// 动态创建对象改为模板实现
//==============================================================================
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{

    return 0;
}
#endif

//############################ 表达式解析器 ######################################
#if 0
//==============================================================================
//
//==============================================================================

#include <iostream>
using std::cout;
using std::endl;

int main(void)
{


	getchar();
	return 0;
}
#endif
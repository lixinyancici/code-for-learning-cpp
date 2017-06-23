# code-for-learning-cpp

This is the source code typing by me when learning 
cpp language.

这是我自己学习c++语言基础时，边学边练所写的代码，main.cpp
中是一系列 [#if-#endif] 分割的独立代码块，每一个
[#if-#endif]代码块代表一个相对独立的知识点，之所以要把
所有独立代码块放在一个文件，是为了后面好温习，因为这样main.cpp
既是代码，又可以看做是学习笔记。

**注：**

 * cppbasic目录下的CMakeLists.txt中没有包含所有源码，我只包含
了当前main函数需要的文件，所以大家如果想运行看效果，如果提示
找不到文件，自己在CMakeLists.txt中的set(SOURCE_FILES ...)中加上相
应文件就行。
 * 编译器选项我打开了Wpadded[内存对齐警告]和
 fno-elide-constructors[关闭RVO返回值优化]选项，关闭**返回值优化**为的是获得与CPP教程
 一致的运行结果，如函数返回局部对象时临时对象的生成等。打开**内存对齐警告**是为了
 更加熟练的掌握结构体的内存对齐特性。大家不需要的话，可以自己注释掉。
 
**编译方法：***
``` shell
 1. cd ../code-for-learning-cpp      # 进入代码根目录
 2. mkdir build && cd build          # 分离编译，防止污染源码
 3. cmake ..                         # 生成makefile
 4. make                             # 编译，二进制文件会在build/cppbasic目录下生成
 5. cd cppbasic && ./cppbasic        # 运行编译得到的二进制文件
 ```

### 算法设计第一次作业
陈韫韬 201618014628014

#### 第11题 Karatsuba
##### 编译环境
Target: mingw32
Configured with: ../src/gcc-5.3.0/configure --build=x86_64-pc-linux-gnu --host=mingw32 --prefix=/mingw --disable-win32-registry --target=mingw32 --with-arch=i586 --enable-languages=c,c++,objc,obj-c++,fortran,ada --enable-static --enable-shared --enable-threads=posix --with-dwarf2 --disable-sjlj-exceptions --enable-version-specific-runtime-libs --enable-libstdcxx-debug --with-tune=generic --enable-libgomp --disable-libvtv --enable-nls
Thread model: posix
gcc version 5.3.0 (GCC)

#### 测试方法
```
cmake .
make
./a.out
```

##### 算法分析
测试方法：输入一个随机生成的长度为 n digits的高精度数，n=250, 500, 1000, 2000, 4000, 8000, 16000，分别利用 karatsuba 算法和 grade school 算法计算其平方，记录两个算法耗时。

测试结果：
|n  |karatsuba(ms)|ratio1|grade school(ms)|ratio2|
|---|---      |---         |---|---|
|250|104|-|3|-|
|500|333|3.2|10|3.3|
|1000|1020|3.1|35|3.5|
|2000|3342|3.3|134|3.8|
|4000|11438|3.4|533|4.0|
|8000|39928|3.5|2126|4.0|
|16000|142781|3.6|8555|4.0|

由测试结果可知 karatsuba 渐进复杂度小于 grade school 算法，但由于自行实现的Int高精度类的减法运算(karatsuba中需要减法，grade school不需要)没有经过优化，karatsuba 算法实际用时远远大于 grade school 算法。

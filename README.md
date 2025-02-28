MyTinySTL
=====
## 简介

   基于 [Alinshans/MyTinySTL: Achieve a tiny STL in C++11](https://github.com/Alinshans/MyTinySTL) 的 `tinySTL`

## 支持

* 操作系统
  * linux
  * windows
  * osx
* 编译器
  * g++ 5.4 或以上
  * clang++ 3.5 或以上
  * msvc 14.0 或以上

## 需要
  * 使用 cmake 2.8 来构建项目（**可选**）

## 运行

如果你想要运行测试，请先阅读 [这个](https://github.com/dengwangtao/dwt_stl/blob/master/Test/README.md) 。

  * gcc/clang on linux/osx
  1. 克隆仓库
```bash
$ git clone ...
$ cd MyTinySTL
```
  2. 构建并运行
```bash
$ mkdir build && cd build
$ cmake ..
$ make
$ cd ../bin && ./stltest
```

  * msvc on windows
  1. 克隆仓库
  2. 使用 `vs2015`（或 `vs2017`）打开 `MSVC/MyTinySTL_VS2015.sln`，配置成 `Release` 模式，（Ctrl + F5）开始执行。

## 文档
  见 [Wiki](https://github.com/Alinshans/MyTinySTL/wiki)。

## 测试

  见 [dwt_stl/Test at master · dengwangtao/dwt_stl](https://github.com/dengwangtao/dwt_stl/tree/master/Test)。


CMake-sample
======

 This repository is written for how to use cmake for cross compile.

 Target libraries are [cpprestsdk](https://github.com/Microsoft/cpprestsdk) and [gloox](https://camaya.net/gloox/).

 Target platform are windows, linux, andriod.

How to build for Visual Studio
------

    mkdir build_vs
    cd build_vs
    cmake -G "Visual Studio 10" ..

`sample.sln` will generate in `build_vs` folder.

How to build for linux
------

    mkdir build_linux
    cd build_linux
    cmake -G "Unix Makefiles" ..
    make
    
How to build for android
------

    mkdir build_android
    cd build_android
    ../configure.sh
    make

To do
------
 Build on ios

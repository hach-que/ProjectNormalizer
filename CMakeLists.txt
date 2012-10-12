cmake_minimum_required(VERSION 2.8.5)
project(tooltest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti")
add_executable(tooltest
    main.cpp
    test.cpp
)
include_directories(
    ~/tooling/llvm/include
    ~/tooling/llvm/tools/clang/include
    ~/tooling/llvm-build/tools/clang/include
)
target_link_libraries(tooltest
    /home/james/tooling/llvm-build/lib/libclangTooling.a
    /home/james/tooling/llvm-build/lib/libclangFrontend.a
    /home/james/tooling/llvm-build/lib/libclangDriver.a
    /home/james/tooling/llvm-build/lib/libclangSerialization.a
    /home/james/tooling/llvm-build/lib/libclangParse.a
    /home/james/tooling/llvm-build/lib/libclangSema.a
    /home/james/tooling/llvm-build/lib/libclangAnalysis.a
    /home/james/tooling/llvm-build/lib/libclangEdit.a
    /home/james/tooling/llvm-build/lib/libclangAST.a
    /home/james/tooling/llvm-build/lib/libclangLex.a
    /home/james/tooling/llvm-build/lib/libclangBasic.a
    /home/james/tooling/llvm-build/lib/libclangASTMatchers.a
    /home/james/tooling/llvm-build/lib/libclangRewriteCore.a
    /home/james/tooling/llvm-build/lib/libLLVMSupport.a
    /home/james/tooling/llvm-build/lib/libLLVMMCParser.a
    /home/james/tooling/llvm-build/lib/libLLVMMC.a
    pthread
    dl
)

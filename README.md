The paths in the CMakeLists.txt are currently hardcoded.  You will
need to clone LLVM and Clang and build new versions yourself before
using this tool.

When you have built LLVM, Clang and this tool, you then can test it
with something like this, inside the LLVM build `bin` directory:

```
cd path/to/llvm-build/bin
ln /home/james/tooling/build/tooltest ./
./tooltest -p /home/james/tooling/build /home/james/tooling/src/test.cpp
```

# library-management-system
Project based on blockchain to manage library's books.

## Install dependencies using vcpkg
```bash
vcpkg "@vcpkg_rf.txt"
```

## To run project

- using cmake
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE:STRING=[vcpkg root]/scripts/buildsystems/vcpkg.cmake -DCMAKE_CXX_COMPILER=g++ -S.. -B.
make
./lms
```


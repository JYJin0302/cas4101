# cas4101
컴퓨터 종합 설계

build 방법

Cmake download 필요

1. 폴더에 main.cpp, CMakeLists.txt, FindGUROBI.cmake 넣기
2. bash에 다음 명령어 입력
    cmake -B build
    cmake --build build --config Release
3. ./build/Release/myapp.exe 로 실행

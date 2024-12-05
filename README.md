# CHIP-8-Emulator
간단한 에뮬레이터 만들어보기


## 사용방법
git clone후에 Makefile 내부의 cflags의 sdl 디렉토리를 수정 후
```bash
make
./chip8 10 3 rom/tetris.ch8
```
과 같이 사용하거나,
sdl 디렉토리, 혹은 makefile 사용법을 모른다면
클론한 디렉토리 내부에서 
``` bash
c++ *.cpp *.hpp -I$(brew --prefix sdl2)/include/SDL2 -L$(brew --prefix sdl2)/lib -lSDL2 -lSDL2main --std=c++11
./a.out 10 3 rom/tetris.ch8
```
과 같이 사용가능


프로그램 이름 / 스케일 / 딜레이 / 롬파일 경로

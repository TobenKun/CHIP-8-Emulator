# CHIP-8-Emulator
간단한 에뮬레이터 만들어보기

## 요구사항
SDL2      - 그래픽 라이브러리

``` bash
brew install SDL2
```
말고 apt-get, pacman 등을 통해 설치 가능

## 빌드방법

맥을 사용중이고, brew를 통해 SDL2를 설치했다면
바로 make 명령어를 사용하여 빌드 가능
```bash
make
```
```sh
SDL2_PREFIX=/path/to/sdl2 make
```

다른 방법으로 sdl2를 설치한 경우에는 위와 같이 SDL2_PREFIX를 사용하여 경로를 지정해주어야 함

## 실행 방법
```sh
./chip8 10 3 rom/tetris.ch8
```

프로그램 이름 / 스케일 / 딜레이 / 롬파일 경로

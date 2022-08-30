# Dockerbuild #

## Building the dockerimage ##
docker build -t worksheet_crafter_oszimilian .

docker build --no-cache -t worksheet_crafter_oszimilian .

## Execute the dockerimage with a bind mount ##
docker run -v D:\14_Docker:/home/maximilian/Data worksheet_crafter_oszimilian


# Win Cross Compile Build #

## Base-Setup ##
* setup a virtual windows machine
* install MSYS2
* install Cygwin
* install VSCode
* install Git for Windows

## Init Git ##
```bash 
git clone https://github.com/Oszimilian/WCO.git
```

## Init GTK 3 with MSYS2 ##
Installing mingw
```bash
pacman -Syy
```
Installing packages for mingw
```bash
pacman -Syuu
```
Restart MSYS2 and repeat the previous two steps

Install GTK3
```bash
pacman -S mingw-w64-x86_64-gtk3
```
Install requirements for compiling gtk3
```bash
pacman -S mingw-w64-x86_64-toolchain base-devel
```

Set new environment variables to this path
```bash
C:\msys64\mingw64\bin
```









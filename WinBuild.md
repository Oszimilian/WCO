# Dockerbuild #

Building the docker image 
```build
docker build -t worksheet_crafter_oszimilian .
```
```build
docker build --no-cache -t worksheet_crafter_oszimilian .
```

Execute the dockerimage with a bind mount
```build
docker run -v D:\14_Docker:/home/maximilian/Data worksheet_crafter_oszimilian
```


# Win Cross Compile Build #

## Setup MSYS2

* Download and install MSYS2 from the official webside 

### Install all the following packages
```bash
pacman -Syy
pacman -Syuu
/* Restart MSYS2 and repeat the previous two steps */
pacman -S mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-toolchain base-devel
pacman -S mingw-w64-x86_64-imagemagick
pacman -S git
pacman -S autoconf-wrapper
pacman -S automake-wrapper
pacman -S make
pacman -S zlib-devel
pacman -S mingw-w64-x86_64-libpng
```

### Set a new environment variable to this path
```bash
C:\msys64\mingw64\bin
```

## Clone important repositories in a Git folder 

```bash
git clone https://github.com/libharu/libharu.git
git clone https://github.com/Oszimilian/WCO.git
```

## Build the LibHaru Library

#### Change the branch to a previous one (2_3) 
```bash
git checkout 2_3
```

#### Maybe you have to run because of missmatching lineendings
```bash
sed -i 's/\r//' ./buildconf.sh
```

#### Generate the configure spript with this command
```bash
./buildconf.sh --force
```

#### Generate the makefile with this command 
* Replacing the previous version with this one ```--with-png=/msys64/``` is very important because without this the script cant find the png headers.
```bash
./configure --prefix=/usr/local --with-zlib --with-png=/msys64/ --with-libdir=lib
```

#### Build the Library
```bash
make clean
make
make install
```

* The result should be that you can find a ```libhpdf.a``` file under ```/msys64/usr/local/lib/``` 

## Building the 

#### Adapt the makefile
* In line 6 there is a variable called OP which holds something like this ```OP = -DOP=1``` which is responsible for setting a variable in the sourcecode during the compileprocess. Change this part to this ```OP = -DOP=2```

#### Building the programm
* make sure that you use the mingw64 terminal to type ``` make```
* maybe you have to type ```make clean``` before this








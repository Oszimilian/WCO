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

### Base-Setup ###

* setup a virtual windows machine
* install MSYS2
* install Cygwin
* install VSCode
* install Git for Windows

### Init Git ###

```bash 
git clone https://github.com/Oszimilian/WCO.git
```

### Install GTK 3 with MSYS2 ###

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

### Install ImageMagick with MSYS2 ###

Install MSYS2
```bash
pacman -S mingw-w64-x86_64-imagemagick
```

### Install LibHaru with Cygwin ###

Install following packages with the setup programm
* autoconf
* automake
* make
* libtool
* zlib-devel
* libpng-devel

Clone the LibHaru GitHub Repository and navigate into the folder
```bash
git clone https://github.com/libharu/libharu.git
```

Change the branch to a previous one (2_3) 
```bash
git checkout 2_3
```

Maybe you have to run 
    ```bash
    sed -i 's/\r//' ./buildconf.sh
    ```
because of missmatching lineendings

Build the Configure-File
```bash
./buildconf.sh
```

Run the configure file with the prefix-paths
```bash
./configure --prefix=/usr/local --with-zlib --with-png --with-libdir=lib
```

Build the Library
```bash
make clean
make
make install
```

### Install MinGW for Windows ###

Go to this webside and download MinGW
```bash
https://sourceforge.net/projects/mingw/
```

Set the environment variables to this folder
```bash
C:\MinGW\bin
```

Open CMD. So now you can run mingw32-make on windows like make on linux










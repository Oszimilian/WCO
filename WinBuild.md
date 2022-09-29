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
https://github.com/Oszimilian/WCO.git
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











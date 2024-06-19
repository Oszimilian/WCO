# WCO
WCO stands for Worksheet Crafter Oszimilian

# Requirements
A linux based system is required. 
Can also be installed under Windows with Msys2. But this is very complecated. 

# Installation

## GTK3
```
sudo apt-get install libgtk-3-dev
```

## LIBHARU PDF-LIB
```
git clone https://github.com/libharu/libharu.git

mkdir build

cd build

cmake -S .. -B .

make

sudo make install
```

## Install ImageMagic
```
git clone https://github.com/ImageMagick/ImageMagick.git

cd ImageMagick

./configure

make

sudo make install

sudo ldconfig
```

## Install WCO
```
make
```

# Usage
```
cd bin

./wco
```

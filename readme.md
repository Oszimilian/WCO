# Dockerbuild

## Building the dockerimage
docker build -t worksheet_crafter_oszimilian .

docker build --no-cache -t worksheet_crafter_oszimilian .

## Execute the dockerimage with a bind mount
docker run -v D:\14_Docker:/home/maximilian/Data worksheet_crafter_oszimilian


# Win Cross Compile Build

## Base-Setup
Markup :    *setup a virtual windows machine
            *install MSYS2
            *install Cygwin
            *install VSCode
            *install Git for Windows

## Init Git
Markup:     *clone repo
                *git clone https://github.com/Oszimilian/WCO.git



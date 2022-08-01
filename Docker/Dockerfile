FROM ubuntu:latest

ARG IM_VERSION=7.1.0
ARG IM_NAME=ImageMagick-{IM_VERSION}


RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y libjpeg62-dev
RUN apt-get install -y libtiff-dev
RUN apt-get install -y libpng-dev
RUN apt-get install -y pkg-config
RUN apt-get install -y ghostscript
RUN apt-get install -y git

ENV DISPLAY=host.docker.internal:0.0



WORKDIR /home
RUN mkdir maximilian
WORKDIR /home/maximilian

RUN git clone https://github.com/ImageMagick/ImageMagick.git ImageMagick-7.1.0

WORKDIR /home/maximilian/ImageMagick-7.1.0
RUN ./configure --disable-shared
RUN make
RUN make install
RUN make check; exit 0

WORKDIR /home/maximilian
RUN git clone https://github.com/libharu/libharu.git

WORKDIR /home/maximilian/libharu
RUN apt-get install make
RUN apt-get install -y automake
RUN apt-get install autoconf
RUN apt-get install -y libtool
RUN apt-get -y install libpng-dev
RUN apt install zlib1g-dev

RUN ./buildconf.sh; return 0
RUN ./configure --prefix=/usr/local --with-zlib --with-png --with-libdir=lib
RUN make clean
RUN make
RUN make install

RUN apt-get install -y libgtk-3-dev

WORKDIR /home/maximilian
RUN git clone https://github.com/Oszimilian/WCO.git

RUN apt install -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt install -y gcc-9 g++-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9
RUN update-alternatives --config gcc

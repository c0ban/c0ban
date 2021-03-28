FROM ubuntu:18.04

# init
RUN apt update && \
    apt upgrade -y && \
    apt install -y \
    software-properties-common

# c0ban
RUN apt install -y build-essential libtool autotools-dev automake pkg-config bsdmainutils curl git

RUN apt install -y nsis g++-mingw-w64-x86-64
RUN update-alternatives --install /usr/bin/x86_64-w64-mingw32-g++ x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix 80

RUN apt install -y \
  libqt5gui5 \
  libqt5core5a \
  libqt5dbus5 \
  qttools5-dev \
  qttools5-dev-tools

COPY . /c0ban
WORKDIR /c0ban

RUN PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') \
    bash -c "echo 0 > /proc/sys/fs/binfmt_misc/status" \
    cd depends \
    make HOST=x86_64-w64-mingw32 -j4 \
    cd .. \
    ./autogen.sh \
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/ \
    make -j4 \
    make install

RUN makensis share/setup.nsi
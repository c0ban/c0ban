FROM ubuntu:14.04

# init
RUN apt-get update && apt-get install -y \
    software-properties-common

# c0ban
RUN add-apt-repository ppa:bitcoin/bitcoin
RUN apt-get update && apt-get install -y \
  libboost-all-dev \
  libdb4.8-dev \
  libdb4.8++-dev \
  libprotobuf-dev \
  protobuf-compiler \
  libzmq3-dev \
  libminiupnpc-dev \
  libqrencode-dev \
  git \
  build-essential \
  libtool \
  autotools-dev \
  automake \
  autoconf \
  pkg-config \
  libssl-dev \
  libevent-dev \
  bsdmainutils \
  curl \
  g++-mingw-w64-x86-64 \
  mingw-w64-x86-64-dev \
  nsis \
  npm

RUN npm config set strict-ssl false && \
  npm install -g makensis && \
  npm config set strict-ssl true

COPY . /c0ban
WORKDIR /c0ban

RUN PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') && \
  cd depends && \
  make HOST=x86_64-w64-mingw32 -j4 && \
  cd .. && \
  ./autogen.sh && \
  CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/ && \
  make -j4 && \
  make install

RUN makensis share/setup.nsi

CMD ["/sbin/init"]
# CMD ["/bin/c0band", "-conf=/c0ban/c0ban.conf", "-datadir=/c0ban-block/"]

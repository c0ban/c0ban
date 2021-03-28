FROM ubuntu:18.04

# init
RUN apt-get update && apt-get install -y \
    software-properties-common

# c0ban
RUN add-apt-repository ppa:bitcoin/bitcoin
RUN apt-get update && apt-get install -y \
  build-essential \
  libtool \
  autotools-dev \
  automake \
  pkg-config \
  bsdmainutils \
  python3 \
  libevent-dev \
  libboost-system-dev \
  libboost-filesystem-dev \
  libboost-test-dev \
  libboost-thread-dev \
  libdb4.8-dev \
  libdb4.8++-dev \
  libprotobuf-dev \
  protobuf-compiler \
  libzmq3-dev \
  libminiupnpc-dev \
  libqrencode-dev \
  git

# for qt
RUN apt-get install -y \
  libqt5gui5 \
  libqt5core5a \
  libqt5dbus5 \
  qttools5-dev \
  qttools5-dev-tools

COPY . /c0ban
WORKDIR /c0ban

RUN ./autogen.sh
RUN ./configure CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768"
RUN make -j4 install

# For test
# RUN pip3 install lyra2re2_hash
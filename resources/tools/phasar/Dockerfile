FROM sugarlyzer/base:latest

ARG PHASAR=/phasar
ARG PHASAR_INSTALL_DIR=/usr/local/phasar
ARG LLVM_INSTALL_DIR=/usr/local/llvm-12
ADD llvm-12.tar.gz ${LLVM_INSTALL_DIR}/..

RUN mkdir -p ${PHASAR}

ENV CC="/usr/local/llvm-12/bin/clang"
ENV CXX="/usr/local/llvm-12/bin/clang++"
ENV CFLAGS=""
ENV CXXFLAGS=""

RUN apt-get update && \
	DEBIAN_FRONTEND=noninteractive TZ="America/New_York" apt-get -y install tzdata && \
	apt-get install wget sudo -y && \
	apt-get install git make cmake -y && \
	apt-get install zlib1g-dev sqlite3 libsqlite3-dev bear python3 doxygen graphviz python3-pip libxml2 libxml2-dev libncurses5-dev libncursesw5-dev libtinfo5 swig build-essential g++ cmake libz3-dev libedit-dev python3-sphinx libomp-dev libcurl4-openssl-dev ninja-build -y && \
	apt-get install libboost-all-dev -y

RUN git clone https://github.com/secure-software-engineering/phasar.git ${PHASAR}
WORKDIR ${PHASAR}
RUN git checkout aed66c04e6dbb3f6ef1bed4ad69b29aa0017bd9a
RUN git submodule init && git submodule update

RUN mkdir -p ${PHASAR}/build
WORKDIR ${PHASAR}/build
ENV PATH="${LLVM_INSTALL_DIR}/bin/:$PATH"
RUN echo $PATH
RUN cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
RUN cmake --build .
RUN cmake -DCMAKE_INSTALL_PREFIX=${PHASAR_INSTALL_DIR} -P cmake_install.cmake
RUN ldconfig
RUN ${PHASAR}/utils/setEnvironmentVariables.sh ${LLVM_INSTALL_DIR} ${PHASAR_INSTALL_DIR}

RUN mkdir -p ${PHASAR}/external/json/build
WORKDIR ${PHASAR}/external/json/build
RUN cmake -DJSON_BuildTests=OFF .. && make -j20 && make install

RUN mkdir -p ${PHASAR}/external/json-schema-validator/build
WORKDIR ${PHASAR}/external/json-schema-validator/build
RUN cmake .. && make -j20 && make install
RUN ldconfig

RUN pip3 install wllvm

ENV LLVM_COMPILER=clang
ENV LLVM_COMPILER_PATH=${LLVM_INSTALL_DIR}/bin

ENV TOOL="phasar"

WORKDIR /

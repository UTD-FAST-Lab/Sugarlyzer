FROM ubuntu:20.04 AS base-setup
ARG JOBS
# SHELL ["/bin/bash", "-c"]
RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y software-properties-common gcc apt-transport-https
RUN add-apt-repository -y ppa:deadsnakes/ppa &&  \
    apt-get install -y z3 python3.10 python3-distutils python3-pip python3-apt python3.10-venv git \
    bison libjson-java sat4j openjdk-8-jdk default-jdk gcc g++ make libz3-java

RUN apt-get install -y gcc make zlib1g-dev git
# Install cmake From https://www.softwarepronto.com/2022/09/dockerubuntu-installing-latest-cmake-on.html
RUN apt-get update \
  && apt-get -y install build-essential \
    && apt-get install -y wget \
      && rm -rf /var/lib/apt/lists/* \
        && wget https://github.com/Kitware/CMake/releases/download/v3.24.1/cmake-3.24.1-Linux-x86_64.sh \
              -q -O /tmp/cmake-install.sh \
                    && chmod u+x /tmp/cmake-install.sh \
                          && mkdir /opt/cmake-3.24.1 \
                                && /tmp/cmake-install.sh --skip-license --prefix=/opt/cmake-3.24.1 \
                                      && rm /tmp/cmake-install.sh \
                                            && ln -s /opt/cmake-3.24.1/bin/* /usr/local/bin


RUN git clone https://github.com/llvm/llvm-project.git
RUN cd llvm-project && mkdir build && cd build && \
    cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm && \
    make -j ${JOBS}

FROM sugarlyzer/base:latest

COPY --from=base-setup /llvm-project /llvm-project
WORKDIR /llvm-project/build
RUN make install
WORKDIR /

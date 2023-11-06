FROM ubuntu:20.04 AS base-setup
ARG JOBS
# SHELL ["/bin/bash", "-c"]
RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y software-properties-common gcc apt-transport-https
RUN add-apt-repository -y ppa:deadsnakes/ppa &&  \
    apt-get install -y z3 python3.10 python3-distutils python3-pip python3-apt python3.10-venv git \
    bison libjson-java sat4j openjdk-8-jdk default-jdk gcc g++ make libz3-java

RUN apt-get install -y gcc make zlib1g-dev git
RUN pip install cmake
RUN git clone https://github.com/llvm/llvm-project.git
RUN cd llvm-project && mkdir build && cd build && \
    cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm && \
    make -j ${JOBS}

FROM sugarlyzer/base:latest

COPY --from=base-setup /llvm-project /llvm-project
WORKDIR /llvm-project/build
RUN make install
WORKDIR /

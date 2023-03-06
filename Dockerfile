FROM ubuntu:20.04 AS base-setup
RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y software-properties-common gcc apt-transport-https
RUN add-apt-repository -y ppa:deadsnakes/ppa &&  \
    apt-get install -y cmake z3 python3.10 python3-distutils python3-pip python3-apt python3.10-venv git \
    bison libjson-java sat4j openjdk-8-jdk default-jdk gcc g++ make libz3-java emacs curl

ARG JOBS
RUN git clone https://github.com/Z3Prover/z3.git
WORKDIR z3
RUN mkdir build && cd build && cmake -DZ3_BUILD_JAVA_BINDINGS=ON .. &&  \
    make -j ${JOBS} && make install
WORKDIR /
ADD "https://api.github.com/repos/appleseedlab/superc/commits?sha=mergingParseErrors&per_page=1" latest_commit
RUN git clone https://github.com/appleseedlab/superc.git && cd /superc && git checkout mergingParseErrors && cd -
ENV JAVA_DEV_ROOT=/superc
ENV CLASSPATH=:/superc/classes:/superc/bin/json-simple-1.1.1.jar:/superc/bin/junit.jar:/superc/bin/antlr.jar:/superc/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar:/usr/local/share/java/com.microsoft.z3.jar:/usr/share/java/json-lib.jar
ENV JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/
RUN cd superc && make configure && make

WORKDIR /
ADD "https://api.github.com/repos/pattersonz/sugarlyzerconfig/commits?per_page=1" latest_commit
RUN git clone https://github.com/pattersonz/SugarlyzerConfig

RUN python3.10 -m venv /venv
ENV PATH=/venv/bin:$PATH
ADD . /Sugarlyzer
WORKDIR /Sugarlyzer
RUN python -m pip install -r requirements.txt
RUN python -m pip install -e .
WORKDIR /

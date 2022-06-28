FROM ubuntu:20.04 AS base-setup
# SHELL ["/bin/bash", "-c"]
RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y software-properties-common gcc apt-transport-https
RUN add-apt-repository -y ppa:deadsnakes/ppa &&  \
    apt-get install -y cmake z3 python3.10 python3-distutils python3-pip python3-apt python3.10-venv git \
    bison libjson-java sat4j openjdk-8-jdk default-jdk gcc g++ make libz3-java

RUN git clone https://github.com/Z3Prover/z3.git
WORKDIR z3
RUN mkdir build && cd build && cmake -DZ3_BUILD_JAVA_BINDINGS=ON .. &&  \
    make && make install
WORKDIR /
RUN git clone https://github.com/appleseedlab/superc.git && \
    echo "JAVA_DEV_ROOT=/superc" >> /root/.bashrc && \
    echo "CLASSPATH=\$CLASSPATH:\$JAVA_DEV_ROOT/classes:\$JAVA_DEV_ROOT/bin/json-simple-1.1.1.jar:\$JAVA_DEV_ROOT/bin/junit.jar:\$JAVA_DEV_ROOT/bin/antlr.jar:\$JAVA_DEV_ROOT/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar:/usr/local/share/java/com.microsoft.z3.jar:/usr/share/java/json-lib.jar" >> /root/.bashrc && \
    echo "JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/" >> /root/.bashrc && \
    echo "export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME" >> /root/.bashrc

RUN . /root/.bashrc && cd superc && make configure && make

 RUN python3.10 -m venv /venv
 ENV PATH=/venv/bin:$PATH
 ADD . /Sugarlyzer
 WORKDIR /Sugarlyzer
 RUN python -m pip install -r requirements.txt
 RUN python -m pip install -e .
 WORKDIR /

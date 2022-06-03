FROM ubuntu:20.04 AS base-setup
SHELL ["/bin/bash", "-c"]
RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y software-properties-common gcc apt-transport-https && \
    add-apt-repository -y ppa:deadsnakes/ppa &&  \
    apt-get install -y cmake z3 python3.10 python3-distutils python3-pip python3-apt python3.10-venv git

FROM base-setup AS sugarlyzer-build

RUN python3.10 -m venv /venv
ENV PATH=/venv/bin:$PATH
ADD . /Sugarlyzer
WORKDIR /Sugarlyzer
RUN python -m pip install -r requirements.txt
RUN python -m pip install -e .
WORKDIR /
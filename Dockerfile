ARG SBT_VERSION=1.12.9
ARG Z3_TURNKEY_VERSION=4.14.1
ARG SUPERC_COMMIT=3a8c1f09c3b58c8953e524e5e4ac8bf401062140
ARG SMACK_COMMIT=ea0e275816f44fee867ad8b5228ef8a1ebe60493
ARG INFER_VERSION=1.2.0

### Building jars ###
FROM eclipse-temurin:17-jdk-jammy AS jars
ARG SBT_VERSION
ARG Z3_TURNKEY_VERSION
RUN apt-get update && apt-get install -y curl \
  && rm -rf /var/lib/apt/lists/* \
  && curl -fsSL https://github.com/sbt/sbt/releases/download/v${SBT_VERSION}/sbt-${SBT_VERSION}.tgz | tar -xz -C /opt
ENV PATH=/opt/sbt/bin:$PATH

WORKDIR /src
COPY sugarlyzer/ ./

RUN --mount=type=cache,target=/root/.cache/coursier \
  sbt tester/assembly \
  && mkdir /out && cp tester.jar /out/ \
  && cp "$(find /root/.cache/coursier -name "z3-turnkey-${Z3_TURNKEY_VERSION}.jar")" /out/com.microsoft.z3.jar

### BUILDING PROGRAM ###
FROM ubuntu:18.04 AS program
ARG SUPERC_COMMIT
ARG SMACK_COMMIT
ENV TZ=America/Chicago
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	software-properties-common wget curl git unzip \
	build-essential make gcc g++ \
	bear bison flex autoconf automake libtool \
	selinux-basics selinux-utils libselinux1-dev \
	libssl-dev zlib1g-dev libpam0g-dev libtirpc-dev \
	openjdk-17-jdk pkg-config libtinfo5 libboost-all-dev \
	libsqlite3-dev electric-fence python3 python3-pip \
	libsepol-dev libdmalloc-dev sat4j\
	&& rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/smack-team/smack.git /tmp/libsmack \
	&& cd /tmp/libsmack && git checkout "${SMACK_COMMIT}"\
	&& ./autogen.sh && ./configure --prefix=/usr --with-attr && make && make install \
	&& rm -rf /tmp/libsmack

ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64/

# Get sugarc
COPY --from=jars /out/com.microsoft.z3.jar /opt/z3/bin/
RUN git clone https://github.com/appleseedlab/superc.git /superc \
  && git -C /superc checkout "${SUPERC_COMMIT}"
ENV JAVA_DEV_ROOT=/superc
ENV CLASSPATH=:/superc/classes:/superc/bin/json-simple-1.1.1.jar:/superc/bin/junit.jar:/superc/bin/antlr.jar:/superc/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar:/opt/z3/bin/com.microsoft.z3.jar:/usr/share/java/json-lib.jar:/opt/z3/bin 
RUN cd /superc && make configure && make

COPY sugarlyzer/SugarlyzerConfig /SugarlyzerConfig
COPY --from=jars /out/tester.jar /tester.jar
WORKDIR /
ENTRYPOINT ["java", "-jar", "/tester.jar"]


### RUN ANALYSIS ###
FROM ubuntu:22.04 AS analysis
ARG SMACK_COMMIT
ENV TZ=America/Chicago
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	openjdk-17-jdk curl xz-utils zlib1g-dev tzdata \
	libselinux1-dev selinux-basics selinux-utils \
	libcurl4-openssl-dev libssl-dev libsqlite3-dev\
	git build-essential python3 \
	pkg-config make gcc autoconf automake libtool\
	libtirpc-dev unzip \
  && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/smack-team/smack.git /tmp/libsmack \
	&& cd /tmp/libsmack && git checkout "${SMACK_COMMIT}"\
	&& ./autogen.sh && ./configure --prefix=/usr --with-attr && make && make install \
	&& rm -rf /tmp/libsmack

ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64/
COPY sugarlyzer/SugarlyzerConfig /SugarlyzerConfig
COPY --from=jars /out/tester.jar /tester.jar
WORKDIR /
ENTRYPOINT ["java", "-jar", "/tester.jar"]

## CLANG RUNNER  ##
FROM analysis AS clang
RUN apt-get update && apt-get install -y clang-11

## INFER RUNNER  ##
FROM analysis AS infer 
ARG INFER_VERSION
RUN curl -fsSL "https://github.com/facebook/infer/releases/download/v${INFER_VERSION}/infer-linux-x86_64-v${INFER_VERSION}.tar.xz" | tar -C /opt -xJ && ln -s "/opt/infer-linux-x86_64-v${INFER_VERSION}/bin/infer" /usr/local/bin/infer

FROM analysis AS cppcheck
RUN apt-get update && apt-get install -y \
  cppcheck && rm -rf /var/lib/apt/lists/*

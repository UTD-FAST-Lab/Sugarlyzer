FROM sugarlyzer/base



RUN apt-get install -y curl
ENV VERSION=1.1.0
RUN curl -sSL "https://github.com/facebook/infer/releases/download/v$VERSION/infer-linux64-v$VERSION.tar.xz" \
	| tar -C /opt -xJ && ln -s "/opt/infer-linux64-v$VERSION/bin/infer" /usr/local/bin/infer

ENV TOOL="infer"

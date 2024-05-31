FROM node

RUN rm /bin/sh && ln -s /bin/bash /bin/sh
WORKDIR /home/

RUN apt -y update \
    && apt -y upgrade

RUN apt -y install cmake \
    && apt -y install build-essential  \
    && apt-get -y install manpages-dev

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd /home/emsdk/ \
    && git pull \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && source ./emsdk_env.sh

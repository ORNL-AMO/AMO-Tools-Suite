FROM node

RUN rm /bin/sh && ln -s /bin/bash /bin/sh
WORKDIR /home/

ADD .. /home/AMO-Tools-Suite/

RUN apt -y update \
    && apt -y upgrade

RUN apt -y install cmake \
    && apt -y install build-essential  \
    && apt-get -y install manpages-dev

RUN cd /home/AMO-Tools-Suite/ \
    && npm install

RUN mkdir -p /home/AMO-Tools-Suite/build-cpp  \
    && cd /home/AMO-Tools-Suite/build-cpp/ \
    && cmake .. \
    && cmake --build . -j 8

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd /home/emsdk/ \
    && git pull \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && source ./emsdk_env.sh \
    && mkdir -p /home/AMO-Tools-Suite/build-wasm \
    && cd /home/AMO-Tools-Suite/build-wasm/ \
    && emcmake cmake -D BUILD_WASM=ON .. \
    && emmake make -j 8

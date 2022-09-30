FROM ubuntu:latest AS base

FROM base AS dev_machine

RUN DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git \
    gcc \
    g++ \
    cmake \
    ninja-build \
    pkg-config \
    openssh-client \
    libjack-jackd2-dev \
    ladspa-sdk \
    libcurl4-openssl-dev  \
    libfreetype6-dev \
    libx11-dev  \
    libxcomposite-dev  \
    libxcursor-dev  \
    libxcursor-dev  \
    libxext-dev  \
    libxinerama-dev  \
    libxrandr-dev \
    libxrender-dev \
    libwebkit2gtk-4.0-dev \
    libglu1-mesa-dev  \
    mesa-common-dev

FROM dev_machine AS copy
COPY . /v
WORKDIR /v

FROM copy AS build

RUN cmake -B newBuild -G Ninja -DCMAKE_BUILD_TYPE=Release
RUN cmake --build newBuild --config Release --target Encryptor

FROM base AS run

WORKDIR /r
COPY --from=build v/newBuild/Apps/Encryptor/Encryptor_artefacts/Release/Encryptor /r

ENTRYPOINT ["./Encryptor"]
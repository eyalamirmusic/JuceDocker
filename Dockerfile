FROM ubuntu:latest AS base

FROM base AS juce_dev_machine

RUN DEBIAN_FRONTEND=noninteractive apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git \
    clang-11 \
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

ENV CC="/usr/bin/clang-11" \
    CXX="/usr/bin/clang++-11"

FROM juce_dev_machine AS build

COPY . /v
WORKDIR /v

RUN cmake -G Ninja -B build \
    -DCMAKE_BUILD_TYPE=Release  \
    -DCMAKE_C_COMPILER=clang-11 \
    -DCMAKE_CXX_COMPILER=clang++-11
RUN cmake --build build --config Release

FROM base AS runprogram

WORKDIR /r

COPY --from=build v/build/Apps/ConsoleAppTemplate/ConsoleAppTemplate_artefacts/Release/ConsoleAppTemplate /r
ENTRYPOINT ["./ConsoleAppTemplate"]
FROM docker.io/eyalamirmusic/juce_dev_machine:latest AS base

FROM base as build

COPY . /v
WORKDIR /v

RUN cmake -G Ninja -B build \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --config Release

FROM ubuntu:latest AS runprogram

WORKDIR /r

COPY --from=build v/build/Apps/ConsoleAppTemplate/ConsoleAppTemplate_artefacts/Release/ConsoleAppTemplate /r
ENTRYPOINT ["./ConsoleAppTemplate"]
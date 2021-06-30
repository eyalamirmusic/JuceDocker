FROM docker.io/eyalamirmusic/juce_dev_machine:latest AS build

COPY . /v
WORKDIR /v

RUN cmake -G Ninja -B build \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --config Release

FROM base AS runprogram

WORKDIR /r

COPY --from=build v/build/Apps/ConsoleAppTemplate/ConsoleAppTemplate_artefacts/Release/ConsoleAppTemplate /r
ENTRYPOINT ["./ConsoleAppTemplate"]
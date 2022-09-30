#!/bin/sh
# shellcheck disable=SC2164
cd "$(dirname "$0")"
cd ../..

docker buildx create --use --name=qemu
docker buildx inspect --bootstrap
docker buildx build --platform=linux/amd64 \
  --push -t eyalamirmusic/juce_encryptor:latest \
  -f ./Apps/Encryptor/Dockerfile .

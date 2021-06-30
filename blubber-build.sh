#!/usr/bin/env bash

# clean up previous builds
docker rm wikispeech-ahotts-test
docker rmi --force wikispeech-ahotts-test

docker rm wikispeech-ahotts
docker rmi --force wikispeech-ahotts

# build docker
blubber .pipeline/blubber.yaml test | docker build --tag wikispeech-ahotts-test --file - .
blubber .pipeline/blubber.yaml production | docker build --tag wikispeech-ahotts --file - .

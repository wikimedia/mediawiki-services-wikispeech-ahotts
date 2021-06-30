#!/usr/bin/env bash

#
# This script is executed from within the docker image during Blubber build.
#

mkdir ahotts
mv * ahotts

m_error() {
  echo $1
  exit 2
}

install_ahotts() {
  cd /srv/ahotts

  if ! ./script_compile_all_linux.sh; then
    m_error "Failed to build AHoTTS!"
  fi

  echo "Starting AHoTTS server. Will wait a minute for it to start up and download any dependencies, and then kill it."
  ./start_ahotts_wikispeech.sh &
  AHOTTS_PID=$!
  for i in $(seq 1 6); do
    sleep 10
    echo "${i}0/60 seconds slept before killing server..."
  done
  kill ${AHOTTS_PID}
}


install_ahotts

echo "Successfully prepared AHoTTS!"

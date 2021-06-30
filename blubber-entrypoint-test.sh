#!/usr/bin/env bash

echo "Starting AHoTTS..."

DIR=`pwd`

cd ${DIR}/ahotts
./start_ahotts_wikispeech.sh &
PID=$!
sleep 10
if ! kill -0 ${PID}; then
  echo "ERROR: Service process has prematurely ended!"
  exit 1
fi
wget -O /dev/null -o /dev/null "http://localhost:1200/"
EXIT_CODE=$?
kill ${PID}
if [ ${EXIT_CODE} -ne 0 ]; then
  echo "ERROR: Test failed!"
else
  echo "Test successful!"
fi
exit ${EXIT_CODE}


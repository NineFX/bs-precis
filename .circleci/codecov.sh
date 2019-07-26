#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"

pushd $SCRIPT_DIR/..
yarn jest
EXITCODE=$?

# Upload to CodeCov
./node_modules/.bin/codecov -f /home/circleci/bs-precis/coverage/coverage-final.json

exit $EXITCODE
popd

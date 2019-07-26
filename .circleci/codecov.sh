#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"
pushd $SCRIPT_DIR/..
yarn jest || true

# Upload to CodeCov
./node_modules/.bin/codecov -f ~/bs-precis/coverage/coverage-final.json

exit 0
popd

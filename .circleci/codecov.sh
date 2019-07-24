#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"

pushd $SCRIPT_DIR/..
yarn jest
EXITCODE=$?

# Upload to CodeCov
bash <(curl -s https://codecov.io/bash) -f ./coverage/coverage-final.json

exit $EXITCODE
popd

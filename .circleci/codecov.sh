#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"

pushd $SCRIPT_DIR/..
yarn jest
EXITCODE=$?

bash<(curl -s https://codecov.io/bash)
# Upload to CodeCov
bash <(curl -s https://codecov.io/bash) -f ./coverage/coverage.json

exit $EXITCODE
popd

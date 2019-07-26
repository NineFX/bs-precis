#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -P)"
EXITCODE=0
pushd $SCRIPT_DIR/..
(yarn jest || EXITCODE=1) || true

echo "Pass through"

# Upload to CodeCov
./node_modules/.bin/codecov -f ~/bs-precis/coverage/coverage-final.json

exit $EXITCODE
popd

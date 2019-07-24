#!/bin/bash
yarn jest
EXITCODE=$?

# Upload to CodeCov
bash <(curl -s https://codecov.io/bash) -f coverage/coverage.json

exit $EXITCODE

#!/bin/bash
yarn jest
EXITCODE=$#

# Upload to CodeCov
bash <(curl -s https://codecov.io/bash)

exit $EXITCODE

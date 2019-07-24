# bs-precis

[![CircleCI](https://circleci.com/gh/NineFX/bs-precis.svg?style=shield)](https://circleci.com/gh/NineFX/bs-precis)
[![codecov](https://codecov.io/gh/NineFX/bs-precis/branch/master/graph/badge.svg)](https://codecov.io/gh/NineFX/bs-precis)

A ReasonML library implementing PRECIS RFCs:

* [RFC8264](https://tools.ietf.org/html/rfc8264)
* [RFC8265](https://tools.ietf.org/html/rfc8265)
* [RFC8266](https://tools.ietf.org/html/rfc8265)

## Install

```
yarn install
```

## Tests

All tests use `jest`. 

```
yarn build && yarn jest --coverage;
```

`bs-precis` is tested against the `golden.json` test suites from [`precis_i18n`](https://github.com/byllyfish/precis_i18n).

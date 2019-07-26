// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Unorm = require("unorm");
var PrecisUtils$BsPrecis = require("./PrecisUtils.bs.js");

function nfcString(prim) {
  return Unorm.nfc(prim);
}

function nfc(codePointList) {
  return PrecisUtils$BsPrecis.toCodePointList(Unorm.nfc(PrecisUtils$BsPrecis.fromCodePointList(codePointList)));
}

function nfkcString(prim) {
  return Unorm.nfkc(prim);
}

function nfkc(codePointList) {
  return PrecisUtils$BsPrecis.toCodePointList(Unorm.nfkc(PrecisUtils$BsPrecis.fromCodePointList(codePointList)));
}

exports.nfcString = nfcString;
exports.nfc = nfc;
exports.nfkcString = nfkcString;
exports.nfkc = nfkc;
/* unorm Not a pure module */
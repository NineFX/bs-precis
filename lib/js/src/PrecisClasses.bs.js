// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var PrecisUtils$BsPrecis = require("./PrecisUtils.bs.js");
var PrecisContext$BsPrecis = require("./PrecisContext.bs.js");
var PrecisCodePoints$BsPrecis = require("./PrecisCodePoints.bs.js");

function identifierClass(codepoints, allowUnassigned) {
  var precisMap = List.map(PrecisCodePoints$BsPrecis.fromCodePoint, codepoints);
  var disallowed = List.mem(/* DISALLOWED */5, precisMap);
  var freepval = List.mem(/* FREEPVAL */4, precisMap);
  var unassigned = List.mem(/* UNASSIGNED */3, precisMap);
  var context = PrecisContext$BsPrecis.context(codepoints);
  var match = allowUnassigned || !unassigned;
  if (match) {
    var match$1 = disallowed || freepval;
    if (match$1) {
      throw [
            PrecisUtils$BsPrecis.PrecisError,
            /* Disallowed */0
          ];
    }
    if (context) {
      return codepoints;
    } else {
      throw [
            PrecisUtils$BsPrecis.PrecisError,
            /* Context */5
          ];
    }
  } else {
    throw [
          PrecisUtils$BsPrecis.PrecisError,
          /* Unassigned */1
        ];
  }
}

function identifierEnforce(codepoints) {
  return identifierClass(codepoints, false);
}

function freeformClass(codepoints, allowUnassigned) {
  var precisMap = List.map(PrecisCodePoints$BsPrecis.fromCodePoint, codepoints);
  var disallowed = List.mem(/* DISALLOWED */5, precisMap);
  var unassigned = List.mem(/* UNASSIGNED */3, precisMap);
  var context = PrecisContext$BsPrecis.context(codepoints);
  var match = allowUnassigned || !unassigned;
  if (match) {
    if (disallowed) {
      throw [
            PrecisUtils$BsPrecis.PrecisError,
            /* Disallowed */0
          ];
    }
    if (context) {
      return codepoints;
    } else {
      throw [
            PrecisUtils$BsPrecis.PrecisError,
            /* Context */5
          ];
    }
  } else {
    throw [
          PrecisUtils$BsPrecis.PrecisError,
          /* Unassigned */1
        ];
  }
}

function freeformEnforce(codepoints) {
  return freeformClass(codepoints, false);
}

exports.identifierClass = identifierClass;
exports.identifierEnforce = identifierEnforce;
exports.freeformClass = freeformClass;
exports.freeformEnforce = freeformEnforce;
/* No side effect */

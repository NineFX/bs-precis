/** Precis/Identifier.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** Based on Samuel Nichol's Original Implementation in Smeagol
 ** 16 May 2019
 */;

let identifierClass =
    (codepoints: list(PrecisUtils.codePoint), allowUnassigned: bool) => {
  let precisMap = List.map(PrecisCodePoints.fromCodePoint, codepoints);
  let disallowed = List.mem(PrecisCodePoints.DISALLOWED, precisMap);
  let freepval = List.mem(PrecisCodePoints.FREEPVAL, precisMap);
  let unassigned = List.mem(PrecisCodePoints.UNASSIGNED, precisMap);
  allowUnassigned || !unassigned
    ? switch (disallowed || freepval) {
      | false => codepoints
      | true => raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
      }
    : raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned));
};

let identifierEnforce = (codepoints: list(PrecisUtils.codePoint)) =>
  identifierClass(codepoints, false);

let freeformClass =
    (codepoints: list(PrecisUtils.codePoint), allowUnassigned: bool) => {
  let precisMap = List.map(PrecisCodePoints.fromCodePoint, codepoints);
  let disallowed = List.mem(PrecisCodePoints.DISALLOWED, precisMap);
  let unassigned = List.mem(PrecisCodePoints.UNASSIGNED, precisMap);
  allowUnassigned || !unassigned
    ? switch (disallowed) {
      | false => codepoints
      | true => raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
      }
    : raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned));
};

let freeformEnforce = (codepoints: list(PrecisUtils.codePoint)) =>
  freeformClass(codepoints, false);

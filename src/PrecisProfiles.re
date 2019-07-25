/** Precis/PrecisProfiles.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** Based on Samuel Nichol's Original Implementation in Smeagol
 ** 17 May 2019
 */

let bidi = (codePointList: list(PrecisUtils.codePoint)) => {
  let directionList =
    List.map(PrecisBidi.getDirectionProperty, codePointList);
  List.mem(PrecisBidi.R, directionList)
  || List.mem(PrecisBidi.AL, directionList)
  || List.mem(PrecisBidi.AN, directionList)
    ? PrecisBidi.validate(codePointList) : true;
};

let usernameCaseMapped = (codePointList: list(PrecisUtils.codePoint)) => {
  let widthMap = PrecisMapping.mapWidth(codePointList);
  let caseMapped = PrecisMapping.toLower(widthMap);
  let nfc = PrecisUnorm.nfc(caseMapped);
  bidi(nfc)
    ? switch (PrecisClasses.identifierEnforce(nfc)) {
      | exception (PrecisUtils.PrecisError(PrecisUtils.Disallowed)) =>
        raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
      | exception (PrecisUtils.PrecisError(PrecisUtils.Unassigned)) =>
        raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned))
      | x => x
      }
    : raise(PrecisUtils.PrecisError(PrecisUtils.BidiError));
};

let usernameCasePreserved = (codePointList: list(PrecisUtils.codePoint)) => {
  let widthMap = PrecisMapping.mapWidth(codePointList);
  let nfc = PrecisUnorm.nfc(widthMap);
  bidi(nfc)
    ? switch (PrecisClasses.identifierEnforce(nfc)) {
      | exception (PrecisUtils.PrecisError(PrecisUtils.Disallowed)) =>
        raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
      | exception (PrecisUtils.PrecisError(PrecisUtils.Unassigned)) =>
        raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned))
      | x => x
      }
    : raise(PrecisUtils.PrecisError(PrecisUtils.BidiError));
};

let opaqueString = (codePointList: list(PrecisUtils.codePoint)) => {
  let additionalMapping = PrecisMapping.additionalMapping(codePointList);
  let nfc = PrecisUnorm.nfc(additionalMapping);
  switch (PrecisClasses.freeformEnforce(nfc)) {
  | exception (PrecisUtils.PrecisError(PrecisUtils.Disallowed)) =>
    raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
  | exception (PrecisUtils.PrecisError(PrecisUtils.Unassigned)) =>
    raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned))
  | x => x
  };
};

let nickname = (codePointList: list(PrecisUtils.codePoint)) => {
  let lower = PrecisMapping.toLower(codePointList);
  let nfkc = PrecisUnorm.nfkc(lower);
  switch (PrecisClasses.freeformEnforce(nfkc)) {
  | exception (PrecisUtils.PrecisError(PrecisUtils.Disallowed)) =>
    raise(PrecisUtils.PrecisError(PrecisUtils.Disallowed))
  | exception (PrecisUtils.PrecisError(PrecisUtils.Unassigned)) =>
    raise(PrecisUtils.PrecisError(PrecisUtils.Unassigned))
  | x => x |> PrecisMapping.stripSpaces
  };
};

let usernameCaseMapped = (s: string) =>
  PrecisUtils.toCodePointList(s)
  |> usernameCaseMapped
  |> PrecisUtils.fromCodePointList;
let usernameCasePreserved = (s: string) =>
  PrecisUtils.toCodePointList(s)
  |> usernameCasePreserved
  |> PrecisUtils.fromCodePointList;
let opaqueString = (s: string) =>
  PrecisUtils.toCodePointList(s)
  |> opaqueString
  |> PrecisUtils.fromCodePointList;

let nickname = (s: string) =>
  PrecisUtils.toCodePointList(s) |> nickname |> PrecisUtils.fromCodePointList;

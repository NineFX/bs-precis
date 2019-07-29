/** PrecisUnitTests.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** 20 May 2019
 */
open Jest;

open Expect;

let codePointCheck = () => {
  let codePoints = [531454, 788451, 54483, 115221, 249866, 530580, 126, 32];
  let results = List.map(PrecisCodePoints.fromCodePoint, codePoints);
  let actual: list(PrecisCodePoints.precisTypes) = [
    PrecisCodePoints.UNASSIGNED,
    PrecisCodePoints.UNASSIGNED,
    PrecisCodePoints.PVALID,
    PrecisCodePoints.UNASSIGNED,
    PrecisCodePoints.UNASSIGNED,
    PrecisCodePoints.UNASSIGNED,
    PrecisCodePoints.PVALID,
    PrecisCodePoints.FREEPVAL,
  ];
  expect(results) |> toEqual(actual);
};

let identifierTest2 = () => {
  let given = {j|abc|j};
  let result = {j|abc|j};
  given
  |> PrecisUtils.toCodePointList
  |> PrecisClasses.identifierEnforce
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(result);
};

let identifierTest3 = () => {
  let given = {j|123|j};
  let result = {j|123|j};
  given
  |> PrecisUtils.toCodePointList
  |> PrecisClasses.identifierEnforce
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(result);
};

let identifierTest4 = () => {
  let given = {j|'्|j};
  let result = {j|'्|j};
  given
  |> PrecisUtils.toCodePointList
  |> PrecisClasses.identifierEnforce
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(result);
};

let identifierTest5 = () => {
  let given = {j|AbCdEfgh123|j};
  let result = {j|AbCdEfgh123|j};
  given
  |> PrecisUtils.toCodePointList
  |> PrecisClasses.identifierEnforce
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(result);
};

let identifierInvalidTest1 = () => {
  let given = [0x061c];
  expect(() =>
    given |> PrecisClasses.identifierEnforce
  ) |> toThrow;
};

let identifierInvalidTest2 = () => {
  let given = [0x200B];
  expect(() =>
    given |> PrecisClasses.identifierEnforce
  ) |> toThrow;
};

let identifierInvalidTest3 = () => {
  let given =
    "זזֶ ֶ זֶֶ  ֶ ֶ aֶ ֶ bcזזז" |> PrecisUtils.toCodePointList;
  expect(() =>
    given |> PrecisClasses.identifierEnforce
  ) |> toThrow;
};

let usernameInvalidTest1 = () => {
  let given = [0x061c] |> PrecisUtils.fromCodePointList;
  expect(() =>
    given |> PrecisProfiles.usernameCaseMapped
  ) |> toThrow;
};

let usernameInvalidTest2 = () => {
  let given = [0x200B] |> PrecisUtils.fromCodePointList;
  expect(() =>
    given |> PrecisProfiles.usernameCaseMapped
  ) |> toThrow;
};

let usernameInvalidTest3 = () => {
  let given = "זזֶ ֶ זֶֶ  ֶ ֶ aֶ ֶ bcזזז";
  expect(() =>
    given |> PrecisProfiles.usernameCaseMapped
  ) |> toThrow;
};

let bidiTestsValid = () => {
  let l = "A";
  let r = Js.String.fromCodePoint(0x05d1);
  let al = Js.String.fromCodePoint(0x0621);
  let en = "0";
  // let an = Js.String.fromCodePoint(0x10E60);
  let nsm = Js.String.fromCodePoint(0x0300);
  let p = "*";
  let tests = [
    l, // true
    l ++ p ++ l, // true
    r, // true
    r ++ r, // true
    al ++ r, // true
    al ++ en ++ r, // true
    al ++ r ++ en, // true
    r ++ p ++ r, // true
    r ++ p ++ r ++ nsm ++ nsm // true
    // r ++ an ++ nsm ++ an ++ r
  ];
  List.fold_left(
    (acc, string) =>
      string |> PrecisUtils.toCodePointList |> PrecisBidi.validate && acc,
    true,
    tests,
  )
  |> expect
  |> toEqual(true);
};

let bidiTestsInvalid = () => {
  let l = "A";
  let r = Js.String.fromCodePoint(0x05d1);
  // let al = Js.String.fromCodePoint(0x0621);
  let en = "0";
  let an = Js.String.fromCodePoint(0x10E60);
  // let nsm = Js.String.fromCodePoint(0x0300);
  let p = "*";
  let tests = [
    p ++ l,
    l ++ p,
    l ++ r ++ l,
    p ++ r,
    r ++ p,
    r ++ l ++ r,
    en ++ r,
    r ++ an ++ en,
    r ++ en ++ an ++ r,
  ];
  List.fold_left(
    (acc, string) =>
      !(string |> PrecisUtils.toCodePointList |> PrecisBidi.validate) && acc,
    true,
    tests,
  )
  |> expect
  |> toEqual(true);
};

let validUsername = () => {
  let username = "Justin";
  // username |> PrecisUtils.toCodePointList |> List.map((cp) => {Js.log(cp); 1;}) |> ignore;
  username
  |> PrecisProfiles.usernameCasePreserved
  |> expect
  |> toEqual("Justin");
};

let checkChangeUsername = () => {
  let username = "JustiN";
  username
  |> PrecisProfiles.usernameCasePreserved
  |> expect
  |> toEqual("JustiN");
};

let checkMapping = () => {
  let username = "justin";
  username
  |> PrecisUtils.toCodePointList
  |> PrecisMapping.mapWidth
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(username);
};

// let singleTest = () => {
//   let username = "0xi";
//   Js.log(username |> PrecisUtils.toCodePointList);
//   switch
//   (username
//   |> PrecisProfiles.usernameCaseMapped) {
//     | exception (PrecisUtils.PrecisError(PrecisUtils.BidiError)) =>
//       Js.log("Error: Bidi")
//     | exception (PrecisUtils.PrecisError(PrecisUtils.Disallowed)) =>
//       Js.log("Error: Disallowed")
//     | exception (PrecisUtils.PrecisError(PrecisUtils.Unassigned)) =>
//       Js.log("Error: Unassigned")
//     | exception (PrecisUtils.PrecisError(PrecisUtils.UnicodeError)) =>
//       Js.log("Error: Unicode Error")
//     | _str => Js.log("Worked")
//   }
//   expect(true) |> toBe(true);
// };

let checkLowerCase = () => {
  let username = "justin";
  username
  |> PrecisUtils.toCodePointList
  |> PrecisMapping.toLower
  |> PrecisUtils.fromCodePointList
  |> expect
  |> toEqual(username);
};

let () =
  describe("Precis Test", () => {
    test("Identifier Class Test 2", identifierTest2);
    test("Identifier Class Test 3", identifierTest3);
    test("Identifier Class Test 4", identifierTest4);
    test("Identifier Class Test 5", identifierTest5);
    test("Code Point Test", codePointCheck);
    test("Identifier Class Invalid Test 1", identifierInvalidTest1);
    test("Identifier Class Invalid Test 2", identifierInvalidTest2);
    test("Identifier Class Invalid Test 3", identifierInvalidTest3);
    test("Check Valid Nicknames", bidiTestsValid);
    test("Check Invalid Nicknames", bidiTestsInvalid);
    test("Check mapping stack overflow", checkMapping);
    test("Check lowerCase stack overflow", checkLowerCase);
    test("Check usernameCaseMapped `justin`", validUsername);
    test("Check checkChangeUsername `JustiN`", checkChangeUsername);
    // test("Check checkChangeUsername `JustiN`", singleTest);
  });

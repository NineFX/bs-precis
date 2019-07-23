open Jest;
open Expect;

let ucpJuliet = () => {
  let str = "Juliet";
  expect(str |> PrecisProfiles.usernameCasePreserved) |> toBe(str);
  };

let ucmJuliet = () => {
  let str = "Juliet";
  let expected = "juliet";
  expect(str |> PrecisProfiles.usernameCaseMapped) |> toBe(expected);
  };

let nickJuliet = () => {
  let str = " Juliet";
  let expected = "juliet";
  expect(str |> PrecisProfiles.nickname) |> toBe(expected);
  };

let ucpJ = () => {
  let str = "J*";
  expect(str |> PrecisProfiles.usernameCasePreserved) |> toBe(str);
};

let ucpSpace = () => {
  let str = " J";
  expect(() => str |> PrecisProfiles.usernameCasePreserved) |> toThrow;
  };

let ucpBidi = () => {
  let str = {j|א*|j};
  expect(() => str |> PrecisProfiles.usernameCasePreserved) |> toThrow;
};

let () =
  describe("Codec Test", () => {
    test("Username Case Preserved: Juliet", ucpJuliet);
    test("Username Case Mapped: Juliet -> juliet", ucmJuliet);
    test("Nickname: _Juliet -> juliet", nickJuliet);
    test("Username Case Preserved: J*", ucpJ);
    test("Username Case Preserved: _J", ucpSpace);
    test("Username Case Preserved: א*", ucpBidi);
  });
  

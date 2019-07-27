open Jest;
open Expect;

let codecTests = [
  ("Foo", "foo"), 
  ("foo", "foo"),
  ("Foo Bar", "foo bar"),
  ("foo bar", "foo bar"),
  ({j|ϔ|j}, {j|ϋ|j}),
  ({j|∞|j}, {j|∞|j}),
  ({j|Richard Ⅳ|j}, {j|richard iv|j}),
  ("       j      ", "j")
];

let testSingle = pair => {
  expect(input |> PrecisProfiles.nickname) |> toBe(output);
};

let testBuilder = pair => {
  let (input, output) = pair;
  test("Nickname Test: " ++ input, () => testSingle(input, output); 

let () =
  describe("Nickname Codec Tests", () => {
    Belt.List.forEach(codecTests, testSingle);
  };

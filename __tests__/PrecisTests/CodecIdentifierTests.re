open Jest;
open Expect;

let codecTest = [
  {j|juliet@example.com|j},
  "fussball",
  {j|fußball|j},
  {j|π|j},
  {j|σ|j},
  {j|ς|j},
];

let codecThrowTest = [
  "foo bar",
  "",
  {j|henryⅣ|j},
  {j|∞|j},
];

let testSingleCaseMapped = input =>
  expect(input |> PrecisProfiles.usernameCaseMapped) |> toBe(input);

let testSingleCasePreserved = input =>
  expect(input |> PrecisProfiles.usernameCasePreserved) |> toBe(input);

let throwSingleCaseMapped = input =>
  expect(() => input |> PrecisProfiles.usernameCaseMapped) |> toThrow;

let throwSingleCasePreserved = input =>
  expect(() => input |> PrecisProfiles.usernameCasePreserved) |> toThrow;


let testBuilder = input => {
  test("UsernameCaseMapped: " ++ input, () => testSingleCaseMapped(input));
  test("UsernameCasePreserved: " ++ input, () => testSingleCasePreserved(input));
};

let throwBuilder = input => {
  test("UsernameCaseMapped Throw: " ++ input, () => throwSingleCaseMapped(input));
  test("UsernaemCasePreserved Throw: " ++ input, () => throwSingleCasePreserved(input));
};

let () = describe("Identifiers Codec Tests", () => {
  Belt.List.forEach(codecTest, testBuilder);
  Belt.List.forEach(codecThrowTest, throwBuilder);
});

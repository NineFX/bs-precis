open Jest;
open Expect;

let opaquesTest = [
  {j|correct horse battery staple|j},
  {j|Correct Horse Battery Staple|j},
  {j|πßå|j},
  {j|Jack of ♦s|j},
];

let opaquesThrow = [
  {j||j},
];

let testSingleOpaque = input =>
  expect(input |> PrecisProfiles.opaqueString) |> toBe(input);

let throwSingleOpaque = input =>
  expect(() => input |> PrecisProfiles.opaqueString) |> toThrow;

let testBuilder = input =>
  test("Opaque String: " ++ input, () => testSingleOpaque(input));

let throwBuilder = input =>
  test("Opaque Throw: " ++ input, () => throwSingleOpaque(input));

let () =
  describe("Opaque String Codec Tests", () => {
    Belt.List.forEach(opaquesTest, testBuilder);
    Belt.List.forEach(opaquesThrow, throwBuilder);
  });

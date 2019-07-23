open Jest;
open Expect;

type test = {
  profile: string,
  input: string,
  output: option(string),
  error: option(string),
};

let decoder = json => Json.Decode.{
  profile: json |> field("profile", string),
  input: json |> field("input", string),
  output: json |> optional(field("output", string)),
  error: json |> optional(field("error", string)),
};

let testSingle = elem => {
  switch elem.output {
    | None =>
      switch elem.profile {
        | "UsernameCasePreserved" => expect(() => elem.input |> PrecisProfiles.usernameCasePreserved) |> toThrow
        | "UsernameCaseMapped" => expect(() => elem.input |> PrecisProfiles.usernameCaseMapped) |> toThrow
        | "NicknameCaseMapped" => expect(() => elem.input |> PrecisProfiles.nickname) |> toThrow
        | "OpaqueString" => expect(() => elem.input |> PrecisProfiles.opaqueString) |> toThrow
        | _ => expect(true) |> toBe(true)
      }
    | Some(output) =>
      switch elem.profile {
        | "UsernameCasePreserved" => expect(elem.input |> PrecisProfiles.usernameCasePreserved) |> toBe(output)
        | "UsernameCaseMapped" => expect(elem.input |> PrecisProfiles.usernameCaseMapped) |> toBe(output)
        | "NicknameCaseMapped" => expect(elem.input |> PrecisProfiles.nickname) |> toBe(output)
        | "OpaqueString" => expect(elem.input |> PrecisProfiles.opaqueString) |> toBe(output)
        | _ => expect(true) |> toBe(true)
      }
  }
};

let testBuilder = elem => {
  test(elem.profile ++" Test: "++elem.input, () => testSingle(elem));
};

let test1 = () => {
  expect(true) |> toBe(true);
};

let () =
  describe("Golden Tests", () => {
    test("Golden Test", test1);
    let data = TestUtils.readFileSync("__tests__/PrecisTests/golden.json") |> Json.parseOrRaise;
    let tests = Json.Decode.list(decoder, data);
    Belt.List.forEach(tests, testBuilder);
  });

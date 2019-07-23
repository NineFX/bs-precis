/** Precis/PrecisUtils.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** Based on Samuel Nichol's Original Implementation in Smeagol
 ** 16 May 2019
 */
type precisErrorTypes =
  | Disallowed
  | Unassigned
  | UnicodeError
  | BidiError;

type codePoint = int;
exception PrecisError(precisErrorTypes);

let toCodePointList = (s: string) => {
  let rec aux = (s: string, i: int, acc: list(int)) => {
    switch (Js.String.codePointAt(i, s)) {
    | Some(char) => aux(s, i + 1, acc @ [char])
    | None => acc
    };
  };
  aux(s, 0, []);
};

let fromCodePointList = (codePointList: list(codePoint)) => {
  Js.String.fromCodePointMany(ArrayLabels.of_list(codePointList));
};

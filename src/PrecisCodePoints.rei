type precisTypes =
    CONTEXTO
  | CONTEXTJ
  | PVALID
  | UNASSIGNED
  | FREEPVAL
  | DISALLOWED;
let fromCodePoint: BsPrecis.PrecisUtils.codePoint => precisTypes;

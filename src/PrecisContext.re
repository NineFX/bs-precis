/** Precis/Context.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** Based on Samuel Nichol's Original Implementation in Smeagol
 ** 14 August 2019
 */

let zeroWidthNonJoiner = 0x200c;
/*
Code point:
      U+200C

   Overview:
      This may occur in a formally cursive script (such as Arabic) in a
      context where it breaks a cursive connection as required for
      orthographic rules, as in the Persian language, for example.  It
      also may occur in Indic scripts in a consonant-conjunct context
      (immediately following a virama), to control required display of
      such conjuncts.

   Lookup:
      True

   Rule Set:

      False;

      If Canonical_Combining_Class(Before(cp)) .eq.  Virama Then True;

      If RegExpMatch((Joining_Type:{L,D})(Joining_Type:T)*\u200C

         (Joining_Type:T)*(Joining_Type:{R,D})) Then True;

*/
let zeroWidthJoiner = 0x200d;
/*
Appendix A.2.  ZERO WIDTH JOINER

   Code point:
      U+200D

   Overview:
      This may occur in Indic scripts in a consonant-conjunct context
      (immediately following a virama), to control required display of
      such conjuncts.

   Lookup:
      True

   Rule Set:

      False;

      If Canonical_Combining_Class(Before(cp)) .eq.  Virama Then True;
*/
let middleDot = 0x00b7;
let greekNumeralSign = 0x0375;
let hebrewPunctuationGeresh = 0x05f3;
let hebrewPunctuationGereshayim = 0x05f4;
let katakanaMiddleDot = 0x30fb;
let arabicIndicDigits = [0x0660, 0x0669];

let virama = _ => true;
let zwnjRegexp = true;

let rec optimizedContext = (codePointList, precisCodePoints, acc, precisAcc) => {
  open PrecisCodePoints;
  switch precisCodePoints {
    | [] => true
    // PreJoiners
    | [cp, CONTEXTO as contextCode | CONTEXTJ as contextCode, ...precisTail] =>
      switch codePointList {
        | [cp1, cp2, ...cpTail] when cp2 == zeroWidthNonJoiner => (virama(cp1) || zwnjRegexp) && optimizedContext(cpTail, precisTail, [cp2, cp1] @ acc, [contextCode, cp] @ precisAcc)
        // Zero Width Joiner
        | [cp1, cp2, ...cpTail] when cp2 == zeroWidthJoiner => virama(cp1) && optimizedContext(cpTail, precisTail, [cp2, cp1] @ acc, [contextCode, cp] @ precisAcc)
        | _ => false
      }
    // PostJoiners
    | [CONTEXTO as contextCode | CONTEXTJ as contextCode, cp, ...precisTail] =>
      switch codePointList {
        // PlaceHolder
        | [cp1, cp2, ...cpTail] when cp1 != 0 => optimizedContext(cpTail, precisTail, [cp2, cp1] @ acc, [cp, contextCode] @ precisAcc)
        | _ => false
        }
    | [cp, ...precisTail] => optimizedContext(List.tl(codePointList), precisTail, [List.hd(codePointList)] @ acc, [cp] @ precisAcc)
  }
};

let context = (codePointList) => optimizedContext(codePointList, codePointList |> List.map(PrecisCodePoints.fromCodePoint), [], []);

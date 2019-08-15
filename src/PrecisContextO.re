/** Precis/ContextO.re
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

let rec contextO = (codePointList, acc) => {
  switch codePointList {
    | [] => true
    // Zero Width Non Joiner
    | [cp1, cp2, ...tail] when cp2 == zeroWidthNonJoiner => (virama(cp1) || zwnjRegexp) && contextO(tail, [cp2, cp1] @ acc)
    // Zero Width Joiner
    | [cp1, cp2, ...tail] when cp2 == zeroWidthJoiner => virama(cp1) && contextO(tail, [cp2, cp1] @ acc)
    | [cp1, ...tail] => contextO(tail, [cp1] @ acc)
    }
};

let contextO = codePointList => contextO(codePointList, []);

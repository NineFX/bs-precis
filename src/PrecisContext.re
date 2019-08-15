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
/* 
   Code point:
      U+00B7

   Overview:
      Between 'l' (U+006C) characters only, used to permit the Catalan
      character ela geminada to be expressed.

   Lookup:
      False

   Rule Set:

      False;

      If Before(cp) .eq.  U+006C And

         After(cp) .eq.  U+006C Then True;
*/
let greekLowerNumericalSign = 0x0375;
let hebrewPunctuationGeresh = 0x05f3;
let hebrewPunctuationGereshayim = 0x05f4;
let katakanaMiddleDot = 0x30fb;
let arabicIndicDigitsStart = 0x0660; 
let arabicIndicDigitsEnd = 0x0669;

let virama = _ => false;
let zwnjRegexp = false;
let greek = _ => false;
let hebrew = _ => false;
let hiragana = _ => false;
let katakana = _ => false;
let han = _ => false;
// Check for arabic Indic Digits
let arabicIndicDigits = List.fold_left((v, cp) =>
  v && !(cp >= 0x06f0 && cp <= 0x06f9), true);

let rec optimizedContext = (codePointList, precisCodePoints, acc, precisAcc) => {
  open PrecisCodePoints;
  switch precisCodePoints {
    | [] => true
    // PreJoiners
    | [cc, CONTEXTO as contextCode | CONTEXTJ as contextCode, cc2, ...precisTail] =>
      switch codePointList {
        //Pre
        | [cp1, cp2, cp3, ...cpTail] when cp2 == middleDot => (cp1 == middleDot) && (cp1 == cp3) && optimizedContext(cpTail, precisTail, [cp3, cp2, cp1] @ acc, [cc2, contextCode, cc] @ precisAcc)
        | [cp1, cp2, ...cpTail] when cp2 == zeroWidthNonJoiner => (virama(cp1) || zwnjRegexp) && optimizedContext(cpTail, [cc2] @  precisTail, [cp2, cp1] @ acc, [contextCode, cc] @ precisAcc)
        // Zero Width Joiner
        | [cp1, cp2, ...cpTail] when cp2 == zeroWidthJoiner => virama(cp1) && optimizedContext(cpTail, [cc2] @ precisTail, [cp2, cp1] @ acc, [contextCode, cc] @ precisAcc)
        | [cp1, cp2, ...cpTail] when cp2 == hebrewPunctuationGeresh || cp2 == hebrewPunctuationGereshayim => hebrew(cp1) && optimizedContext(cpTail, [cc2] @ precisTail, [cp2, cp1] @ acc, [contextCode, cc] @ precisAcc)
        // Post
        | [cp1, cp2, cp3, ...cpTail] when cp2 == greekLowerNumericalSign => greek(cp3) && optimizedContext(cpTail, precisTail, [cp3, cp2, cp1] @ acc, [cc2, contextCode, cc] @ precisAcc)
        // Total
        | [cp1, cp2, ...cpTail] when cp2 == katakanaMiddleDot => (hiragana(acc @ codePointList) || katakana(acc @ codePointList) || han(acc @ codePointList)) && optimizedContext(cpTail, [cc2] @ precisTail, [cp2, cp1] @ acc, [contextCode, cc] @ precisAcc)
        | [cp1, cp2, ...cpTail] when cp2 >= arabicIndicDigitsStart && cp2 <= arabicIndicDigitsEnd => arabicIndicDigits(acc @ codePointList) && optimizedContext(cpTail, [cc2] @ precisTail, [cp2, cp1] @ acc, [contextCode, cc] @ precisAcc)
        | _ => false
      }
    | [cp, ...precisTail] => optimizedContext(List.tl(codePointList), precisTail, [List.hd(codePointList)] @ acc, [cp] @ precisAcc)
  }
};

let context = (codePointList) => optimizedContext(codePointList, codePointList |> List.map(PrecisCodePoints.fromCodePoint), [], []);

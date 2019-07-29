/** Precis/Bidi.re
 ** Copyright 2019 NineFX Inc.
 ** Justin Baum
 ** Based on Samuel Nichol's Original Implementation in Smeagol
 ** 16 May 2019
 */

/*
 https://github.com/byllyfish/precis_i18n/blob/master/precis_i18n/bidi.py
 The following rule, consisting of six conditions, applies to labels
 in Bidi domain names.  The requirements that this rule satisfies are
 described in Section 3.  All of the conditions must be satisfied for
 the rule to be satisfied.
 1. The first character must be a character with Bidi property L, R,
    or AL.  If it has the R or AL property, it is an RTL label; if it
    has the L property, it is an LTR label.
 2. In an RTL label, only characters with the Bidi properties R, AL,
    AN, EN, ES, CS, ET, ON, BN, or NSM are allowed.
 3. In an RTL label, the end of the label must be a character with
    Bidi property R, AL, EN, or AN, followed by zero or more
    characters with Bidi property NSM.
 4. In an RTL label, if an EN is present, no AN may be present, and
    vice versa.
 5. In an LTR label, only characters with the Bidi properties L, EN,
    ES, CS, ET, ON, BN, or NSM are allowed.
 6. In an LTR label, the end of the label must be a character with
    Bidi property L or EN, followed by zero or more characters with
    Bidi property NSM.
 */

type direction =
  | BN
  | AN
  | ES
  | ON
  | R
  | AL
  | NSM
  | WS
  | CS
  | EN
  | L
  | ET
  | B
  | Illegal;

let getDirectionProperty: PrecisUtils.codePoint => direction =
 point => {
   if (point < 8484) {
if (point < 3389) {
if (point < 1958) {
if (point < 768) {
if (point < 161) {
if (point < 43) {
if (point < 14) {
if (point < 10) {
if (point < 1) {
switch (point) {
 | point when (point == 0) => Illegal
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1 && point < 9) => BN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 12) {
switch (point) {
 | point when (point == 10) => B
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 12) => WS
 | point when (point == 13) => B
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 32) {
if (point < 28) {
switch (point) {
 | point when (point >= 14 && point < 28) => BN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 28 && point < 31) => B
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 35) {
switch (point) {
 | point when (point == 32) => WS
 | point when (point >= 33 && point < 35) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 35 && point < 38) => ET
 | point when (point >= 38 && point < 43) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 65) {
if (point < 46) {
if (point < 44) {
switch (point) {
 | point when (point == 43) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 44) => CS
 | point when (point == 45) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 58) {
switch (point) {
 | point when (point >= 46 && point < 48) => CS
 | point when (point >= 48 && point < 58) => EN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 58) => CS
 | point when (point >= 59 && point < 65) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 127) {
if (point < 97) {
switch (point) {
 | point when (point >= 65 && point < 91) => L
 | point when (point >= 91 && point < 97) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 97 && point < 123) => L
 | point when (point >= 123 && point < 127) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 134) {
switch (point) {
 | point when (point >= 127 && point < 133) => BN
 | point when (point == 133) => B
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 134 && point < 160) => BN
 | point when (point == 160) => CS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 187) {
if (point < 176) {
if (point < 170) {
if (point < 162) {
switch (point) {
 | point when (point == 161) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 162 && point < 166) => ET
 | point when (point >= 166 && point < 170) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 173) {
switch (point) {
 | point when (point == 170) => L
 | point when (point >= 171 && point < 173) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 173) => BN
 | point when (point >= 174 && point < 176) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 181) {
if (point < 178) {
switch (point) {
 | point when (point >= 176 && point < 178) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 178 && point < 180) => EN
 | point when (point == 180) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 185) {
switch (point) {
 | point when (point == 181) => L
 | point when (point >= 182 && point < 185) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 185) => EN
 | point when (point == 186) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 699) {
if (point < 216) {
if (point < 192) {
switch (point) {
 | point when (point >= 187 && point < 192) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 192 && point < 215) => L
 | point when (point == 215) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 248) {
switch (point) {
 | point when (point >= 216 && point < 247) => L
 | point when (point == 247) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 248 && point < 697) => L
 | point when (point >= 697 && point < 699) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 736) {
if (point < 720) {
switch (point) {
 | point when (point >= 699 && point < 706) => L
 | point when (point >= 706 && point < 720) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 720 && point < 722) => L
 | point when (point >= 722 && point < 736) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 750) {
switch (point) {
 | point when (point >= 736 && point < 741) => L
 | point when (point >= 741 && point < 750) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 750) => L
 | point when (point >= 751 && point < 768) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 1545) {
if (point < 1418) {
if (point < 902) {
if (point < 886) {
if (point < 880) {
switch (point) {
 | point when (point >= 768 && point < 880) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 880 && point < 884) => L
 | point when (point >= 884 && point < 886) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 895) {
switch (point) {
 | point when (point >= 886 && point < 894) => L
 | point when (point == 894) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 895 && point < 900) => L
 | point when (point >= 900 && point < 902) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 1014) {
if (point < 903) {
switch (point) {
 | point when (point == 902) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 903) => ON
 | point when (point >= 904 && point < 1014) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1155) {
switch (point) {
 | point when (point == 1014) => ON
 | point when (point >= 1015 && point < 1155) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1155 && point < 1162) => NSM
 | point when (point >= 1162 && point < 1418) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 1475) {
if (point < 1470) {
if (point < 1423) {
switch (point) {
 | point when (point >= 1418 && point < 1423) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1423 && point < 1425) => ET
 | point when (point >= 1425 && point < 1470) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1472) {
switch (point) {
 | point when (point == 1470) => R
 | point when (point == 1471) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 1472) => R
 | point when (point >= 1473 && point < 1475) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 1488) {
if (point < 1478) {
switch (point) {
 | point when (point == 1475) => R
 | point when (point >= 1476 && point < 1478) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 1478) => R
 | point when (point >= 1479 && point < 1488) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1542) {
switch (point) {
 | point when (point >= 1488 && point < 1536) => R
 | point when (point >= 1536 && point < 1542) => AN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1542 && point < 1544) => ON
 | point when (point == 1544) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 1750) {
if (point < 1611) {
if (point < 1549) {
if (point < 1547) {
switch (point) {
 | point when (point >= 1545 && point < 1547) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 1547) => AL
 | point when (point == 1548) => CS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1552) {
switch (point) {
 | point when (point == 1549) => AL
 | point when (point >= 1550 && point < 1552) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1552 && point < 1563) => NSM
 | point when (point >= 1563 && point < 1611) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 1643) {
if (point < 1632) {
switch (point) {
 | point when (point >= 1611 && point < 1632) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1632 && point < 1642) => AN
 | point when (point == 1642) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1648) {
switch (point) {
 | point when (point >= 1643 && point < 1645) => AN
 | point when (point >= 1645 && point < 1648) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 1648) => NSM
 | point when (point >= 1649 && point < 1750) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 1770) {
if (point < 1759) {
if (point < 1757) {
switch (point) {
 | point when (point >= 1750 && point < 1757) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 1757) => AN
 | point when (point == 1758) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1767) {
switch (point) {
 | point when (point >= 1759 && point < 1765) => NSM
 | point when (point >= 1765 && point < 1767) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1767 && point < 1769) => NSM
 | point when (point == 1769) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 1809) {
if (point < 1776) {
switch (point) {
 | point when (point >= 1770 && point < 1774) => NSM
 | point when (point >= 1774 && point < 1776) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1776 && point < 1786) => EN
 | point when (point >= 1786 && point < 1809) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 1840) {
switch (point) {
 | point when (point == 1809) => NSM
 | point when (point >= 1810 && point < 1840) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1840 && point < 1869) => NSM
 | point when (point >= 1869 && point < 1958) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
} else {
if (point < 2677) {
if (point < 2377) {
if (point < 2088) {
if (point < 2045) {
if (point < 2027) {
if (point < 1969) {
switch (point) {
 | point when (point >= 1958 && point < 1969) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 1969 && point < 1984) => AL
 | point when (point >= 1984 && point < 2027) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2038) {
switch (point) {
 | point when (point >= 2027 && point < 2036) => NSM
 | point when (point >= 2036 && point < 2038) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2038 && point < 2042) => ON
 | point when (point >= 2042 && point < 2045) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2074) {
if (point < 2046) {
switch (point) {
 | point when (point == 2045) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2046 && point < 2070) => R
 | point when (point >= 2070 && point < 2074) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2084) {
switch (point) {
 | point when (point == 2074) => R
 | point when (point >= 2075 && point < 2084) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 2084) => R
 | point when (point >= 2085 && point < 2088) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 2274) {
if (point < 2137) {
if (point < 2089) {
switch (point) {
 | point when (point == 2088) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2089 && point < 2096) => NSM
 | point when (point >= 2096 && point < 2137) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2144) {
switch (point) {
 | point when (point >= 2137 && point < 2142) => NSM
 | point when (point >= 2142 && point < 2144) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2144 && point < 2259) => AL
 | point when (point >= 2259 && point < 2274) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2363) {
if (point < 2307) {
switch (point) {
 | point when (point == 2274) => AN
 | point when (point >= 2275 && point < 2307) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2307 && point < 2362) => L
 | point when (point == 2362) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2365) {
switch (point) {
 | point when (point == 2363) => L
 | point when (point == 2364) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2365 && point < 2369) => L
 | point when (point >= 2369 && point < 2377) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 2510) {
if (point < 2433) {
if (point < 2385) {
if (point < 2381) {
switch (point) {
 | point when (point >= 2377 && point < 2381) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 2381) => NSM
 | point when (point >= 2382 && point < 2385) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2402) {
switch (point) {
 | point when (point >= 2385 && point < 2392) => NSM
 | point when (point >= 2392 && point < 2402) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2402 && point < 2404) => NSM
 | point when (point >= 2404 && point < 2433) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2493) {
if (point < 2434) {
switch (point) {
 | point when (point == 2433) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2434 && point < 2492) => L
 | point when (point == 2492) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2503) {
switch (point) {
 | point when (point >= 2493 && point < 2497) => L
 | point when (point >= 2497 && point < 2503) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2503 && point < 2509) => L
 | point when (point == 2509) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 2558) {
if (point < 2546) {
if (point < 2530) {
switch (point) {
 | point when (point >= 2510 && point < 2530) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2530 && point < 2534) => NSM
 | point when (point >= 2534 && point < 2546) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2555) {
switch (point) {
 | point when (point >= 2546 && point < 2548) => ET
 | point when (point >= 2548 && point < 2555) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 2555) => ET
 | point when (point >= 2556 && point < 2558) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2625) {
if (point < 2620) {
switch (point) {
 | point when (point >= 2558 && point < 2563) => NSM
 | point when (point >= 2563 && point < 2620) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2620 && point < 2622) => NSM
 | point when (point >= 2622 && point < 2625) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2672) {
switch (point) {
 | point when (point >= 2625 && point < 2649) => NSM
 | point when (point >= 2649 && point < 2672) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2672 && point < 2674) => NSM
 | point when (point >= 2674 && point < 2677) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 3009) {
if (point < 2810) {
if (point < 2761) {
if (point < 2691) {
if (point < 2678) {
switch (point) {
 | point when (point == 2677) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2678 && point < 2689) => L
 | point when (point >= 2689 && point < 2691) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2749) {
switch (point) {
 | point when (point >= 2691 && point < 2748) => L
 | point when (point == 2748) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2749 && point < 2753) => L
 | point when (point >= 2753 && point < 2761) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2786) {
if (point < 2765) {
switch (point) {
 | point when (point >= 2761 && point < 2765) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2765 && point < 2768) => NSM
 | point when (point >= 2768 && point < 2786) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2801) {
switch (point) {
 | point when (point >= 2786 && point < 2790) => NSM
 | point when (point >= 2790 && point < 2801) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2801 && point < 2809) => ET
 | point when (point == 2809) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 2887) {
if (point < 2877) {
if (point < 2818) {
switch (point) {
 | point when (point >= 2810 && point < 2818) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2818 && point < 2876) => L
 | point when (point == 2876) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2880) {
switch (point) {
 | point when (point >= 2877 && point < 2879) => L
 | point when (point == 2879) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 2880) => L
 | point when (point >= 2881 && point < 2887) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 2918) {
if (point < 2903) {
switch (point) {
 | point when (point >= 2887 && point < 2893) => L
 | point when (point >= 2893 && point < 2903) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2903 && point < 2914) => L
 | point when (point >= 2914 && point < 2918) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 2947) {
switch (point) {
 | point when (point >= 2918 && point < 2946) => L
 | point when (point == 2946) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 2947 && point < 3008) => L
 | point when (point == 3008) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 3170) {
if (point < 3073) {
if (point < 3059) {
if (point < 3021) {
switch (point) {
 | point when (point >= 3009 && point < 3021) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3021 && point < 3024) => NSM
 | point when (point >= 3024 && point < 3059) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3066) {
switch (point) {
 | point when (point >= 3059 && point < 3065) => ON
 | point when (point == 3065) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3066 && point < 3072) => ON
 | point when (point == 3072) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 3134) {
if (point < 3076) {
switch (point) {
 | point when (point >= 3073 && point < 3076) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 3076) => NSM
 | point when (point >= 3077 && point < 3134) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3142) {
switch (point) {
 | point when (point >= 3134 && point < 3137) => NSM
 | point when (point >= 3137 && point < 3142) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3142 && point < 3160) => NSM
 | point when (point >= 3160 && point < 3170) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 3261) {
if (point < 3199) {
if (point < 3174) {
switch (point) {
 | point when (point >= 3170 && point < 3174) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3174 && point < 3192) => L
 | point when (point >= 3192 && point < 3199) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3202) {
switch (point) {
 | point when (point >= 3199 && point < 3201) => L
 | point when (point == 3201) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3202 && point < 3260) => L
 | point when (point == 3260) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 3302) {
if (point < 3285) {
switch (point) {
 | point when (point >= 3261 && point < 3276) => L
 | point when (point >= 3276 && point < 3285) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3285 && point < 3298) => L
 | point when (point >= 3298 && point < 3302) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3330) {
switch (point) {
 | point when (point >= 3302 && point < 3328) => L
 | point when (point >= 3328 && point < 3330) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3330 && point < 3387) => L
 | point when (point >= 3387 && point < 3389) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
}
} else {
if (point < 6683) {
if (point < 4227) {
if (point < 3896) {
if (point < 3647) {
if (point < 3530) {
if (point < 3405) {
if (point < 3393) {
switch (point) {
 | point when (point >= 3389 && point < 3393) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3393 && point < 3398) => NSM
 | point when (point >= 3398 && point < 3405) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3426) {
switch (point) {
 | point when (point == 3405) => NSM
 | point when (point >= 3406 && point < 3426) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3426 && point < 3430) => NSM
 | point when (point >= 3430 && point < 3530) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 3544) {
if (point < 3535) {
switch (point) {
 | point when (point >= 3530 && point < 3535) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3535 && point < 3538) => L
 | point when (point >= 3538 && point < 3544) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3634) {
switch (point) {
 | point when (point >= 3544 && point < 3633) => L
 | point when (point == 3633) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3634 && point < 3636) => L
 | point when (point >= 3636 && point < 3647) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 3773) {
if (point < 3663) {
if (point < 3648) {
switch (point) {
 | point when (point == 3647) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3648 && point < 3655) => L
 | point when (point >= 3655 && point < 3663) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3762) {
switch (point) {
 | point when (point >= 3663 && point < 3761) => L
 | point when (point == 3761) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3762 && point < 3764) => L
 | point when (point >= 3764 && point < 3773) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 3866) {
if (point < 3792) {
switch (point) {
 | point when (point >= 3773 && point < 3784) => L
 | point when (point >= 3784 && point < 3792) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3792 && point < 3864) => L
 | point when (point >= 3864 && point < 3866) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3894) {
switch (point) {
 | point when (point >= 3866 && point < 3893) => L
 | point when (point == 3893) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 3894) => L
 | point when (point == 3895) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 4141) {
if (point < 3973) {
if (point < 3902) {
if (point < 3897) {
switch (point) {
 | point when (point == 3896) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 3897) => NSM
 | point when (point >= 3898 && point < 3902) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 3967) {
switch (point) {
 | point when (point >= 3902 && point < 3953) => L
 | point when (point >= 3953 && point < 3967) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 3967) => L
 | point when (point >= 3968 && point < 3973) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 3981) {
if (point < 3974) {
switch (point) {
 | point when (point == 3973) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 3974 && point < 3976) => NSM
 | point when (point >= 3976 && point < 3981) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 4038) {
switch (point) {
 | point when (point >= 3981 && point < 4030) => NSM
 | point when (point >= 4030 && point < 4038) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 4038) => NSM
 | point when (point >= 4039 && point < 4141) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 4159) {
if (point < 4152) {
if (point < 4145) {
switch (point) {
 | point when (point >= 4141 && point < 4145) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 4145) => L
 | point when (point >= 4146 && point < 4152) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 4155) {
switch (point) {
 | point when (point == 4152) => L
 | point when (point >= 4153 && point < 4155) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 4155 && point < 4157) => L
 | point when (point >= 4157 && point < 4159) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 4193) {
if (point < 4186) {
switch (point) {
 | point when (point >= 4159 && point < 4184) => L
 | point when (point >= 4184 && point < 4186) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 4186 && point < 4190) => L
 | point when (point >= 4190 && point < 4193) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 4213) {
switch (point) {
 | point when (point >= 4193 && point < 4209) => L
 | point when (point >= 4209 && point < 4213) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 4213 && point < 4226) => L
 | point when (point == 4226) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 6086) {
if (point < 5761) {
if (point < 4957) {
if (point < 4237) {
if (point < 4229) {
switch (point) {
 | point when (point >= 4227 && point < 4229) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 4229 && point < 4231) => NSM
 | point when (point >= 4231 && point < 4237) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 4253) {
switch (point) {
 | point when (point == 4237) => NSM
 | point when (point >= 4238 && point < 4253) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 4253) => NSM
 | point when (point >= 4254 && point < 4957) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 5024) {
if (point < 4960) {
switch (point) {
 | point when (point >= 4957 && point < 4960) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 4960 && point < 5008) => L
 | point when (point >= 5008 && point < 5024) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 5121) {
switch (point) {
 | point when (point >= 5024 && point < 5120) => L
 | point when (point == 5120) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 5121 && point < 5760) => L
 | point when (point == 5760) => WS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 5970) {
if (point < 5906) {
if (point < 5787) {
switch (point) {
 | point when (point >= 5761 && point < 5787) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 5787 && point < 5792) => ON
 | point when (point >= 5792 && point < 5906) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 5938) {
switch (point) {
 | point when (point >= 5906 && point < 5920) => NSM
 | point when (point >= 5920 && point < 5938) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 5938 && point < 5941) => NSM
 | point when (point >= 5941 && point < 5970) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 6068) {
if (point < 6002) {
switch (point) {
 | point when (point >= 5970 && point < 5984) => NSM
 | point when (point >= 5984 && point < 6002) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6002 && point < 6016) => NSM
 | point when (point >= 6016 && point < 6068) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6071) {
switch (point) {
 | point when (point >= 6068 && point < 6070) => NSM
 | point when (point == 6070) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6071 && point < 6078) => NSM
 | point when (point >= 6078 && point < 6086) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 6313) {
if (point < 6112) {
if (point < 6100) {
if (point < 6087) {
switch (point) {
 | point when (point == 6086) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6087 && point < 6089) => L
 | point when (point >= 6089 && point < 6100) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6108) {
switch (point) {
 | point when (point >= 6100 && point < 6107) => L
 | point when (point == 6107) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 6108) => L
 | point when (point >= 6109 && point < 6112) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 6158) {
if (point < 6128) {
switch (point) {
 | point when (point >= 6112 && point < 6128) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6128 && point < 6155) => ON
 | point when (point >= 6155 && point < 6158) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6277) {
switch (point) {
 | point when (point >= 6158 && point < 6160) => BN
 | point when (point >= 6160 && point < 6277) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6277 && point < 6279) => NSM
 | point when (point >= 6279 && point < 6313) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 6451) {
if (point < 6435) {
if (point < 6314) {
switch (point) {
 | point when (point == 6313) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6314 && point < 6432) => L
 | point when (point >= 6432 && point < 6435) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6441) {
switch (point) {
 | point when (point >= 6435 && point < 6439) => L
 | point when (point >= 6439 && point < 6441) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6441 && point < 6450) => L
 | point when (point == 6450) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 6622) {
if (point < 6464) {
switch (point) {
 | point when (point >= 6451 && point < 6457) => L
 | point when (point >= 6457 && point < 6464) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6464 && point < 6470) => ON
 | point when (point >= 6470 && point < 6622) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6679) {
switch (point) {
 | point when (point >= 6622 && point < 6656) => ON
 | point when (point >= 6656 && point < 6679) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6679 && point < 6681) => NSM
 | point when (point >= 6681 && point < 6683) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
} else {
if (point < 8125) {
if (point < 7082) {
if (point < 6964) {
if (point < 6755) {
if (point < 6743) {
if (point < 6686) {
switch (point) {
 | point when (point >= 6683 && point < 6686) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6686 && point < 6742) => L
 | point when (point == 6742) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6753) {
switch (point) {
 | point when (point == 6743) => L
 | point when (point >= 6744 && point < 6753) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 6753) => L
 | point when (point == 6754) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 6771) {
if (point < 6757) {
switch (point) {
 | point when (point >= 6755 && point < 6757) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6757 && point < 6765) => NSM
 | point when (point >= 6765 && point < 6771) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6832) {
switch (point) {
 | point when (point >= 6771 && point < 6784) => NSM
 | point when (point >= 6784 && point < 6832) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6832 && point < 6916) => NSM
 | point when (point >= 6916 && point < 6964) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 6979) {
if (point < 6971) {
if (point < 6965) {
switch (point) {
 | point when (point == 6964) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 6965) => L
 | point when (point >= 6966 && point < 6971) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 6973) {
switch (point) {
 | point when (point == 6971) => L
 | point when (point == 6972) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 6973 && point < 6978) => L
 | point when (point == 6978) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 7042) {
if (point < 7028) {
switch (point) {
 | point when (point >= 6979 && point < 7019) => L
 | point when (point >= 7019 && point < 7028) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7028 && point < 7040) => L
 | point when (point >= 7040 && point < 7042) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 7078) {
switch (point) {
 | point when (point >= 7042 && point < 7074) => L
 | point when (point >= 7074 && point < 7078) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7078 && point < 7080) => L
 | point when (point >= 7080 && point < 7082) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 7227) {
if (point < 7149) {
if (point < 7142) {
if (point < 7083) {
switch (point) {
 | point when (point == 7082) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7083 && point < 7086) => NSM
 | point when (point >= 7086 && point < 7142) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 7144) {
switch (point) {
 | point when (point == 7142) => NSM
 | point when (point == 7143) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7144 && point < 7146) => NSM
 | point when (point >= 7146 && point < 7149) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 7154) {
if (point < 7150) {
switch (point) {
 | point when (point == 7149) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 7150) => L
 | point when (point >= 7151 && point < 7154) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 7220) {
switch (point) {
 | point when (point >= 7154 && point < 7212) => L
 | point when (point >= 7212 && point < 7220) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7220 && point < 7222) => L
 | point when (point >= 7222 && point < 7227) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 7405) {
if (point < 7380) {
if (point < 7376) {
switch (point) {
 | point when (point >= 7227 && point < 7376) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7376 && point < 7379) => NSM
 | point when (point == 7379) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 7394) {
switch (point) {
 | point when (point >= 7380 && point < 7393) => NSM
 | point when (point == 7393) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7394 && point < 7401) => NSM
 | point when (point >= 7401 && point < 7405) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 7416) {
if (point < 7412) {
switch (point) {
 | point when (point == 7405) => NSM
 | point when (point >= 7406 && point < 7412) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 7412) => NSM
 | point when (point >= 7413 && point < 7416) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 7616) {
switch (point) {
 | point when (point >= 7416 && point < 7418) => NSM
 | point when (point >= 7418 && point < 7616) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 7616 && point < 7680) => NSM
 | point when (point >= 7680 && point < 8125) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 8288) {
if (point < 8207) {
if (point < 8160) {
if (point < 8130) {
if (point < 8126) {
switch (point) {
 | point when (point == 8125) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8126) => L
 | point when (point >= 8127 && point < 8130) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8144) {
switch (point) {
 | point when (point >= 8130 && point < 8141) => L
 | point when (point >= 8141 && point < 8144) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8144 && point < 8157) => L
 | point when (point >= 8157 && point < 8160) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 8189) {
if (point < 8173) {
switch (point) {
 | point when (point >= 8160 && point < 8173) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8173 && point < 8178) => ON
 | point when (point >= 8178 && point < 8189) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8203) {
switch (point) {
 | point when (point >= 8189 && point < 8192) => ON
 | point when (point >= 8192 && point < 8203) => WS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8203 && point < 8206) => BN
 | point when (point == 8206) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 8237) {
if (point < 8233) {
if (point < 8208) {
switch (point) {
 | point when (point == 8207) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8208 && point < 8232) => ON
 | point when (point == 8232) => WS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8235) {
switch (point) {
 | point when (point == 8233) => B
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 8245) {
if (point < 8239) {
switch (point) {
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8239) => CS
 | point when (point >= 8240 && point < 8245) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8261) {
switch (point) {
 | point when (point >= 8245 && point < 8260) => ON
 | point when (point == 8260) => CS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8261 && point < 8287) => ON
 | point when (point == 8287) => WS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 8332) {
if (point < 8305) {
if (point < 8296) {
if (point < 8294) {
switch (point) {
 | point when (point >= 8288 && point < 8294) => BN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8298) {
switch (point) {
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8298 && point < 8304) => BN
 | point when (point == 8304) => EN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 8316) {
if (point < 8308) {
switch (point) {
 | point when (point >= 8305 && point < 8308) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8308 && point < 8314) => EN
 | point when (point >= 8314 && point < 8316) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8320) {
switch (point) {
 | point when (point >= 8316 && point < 8319) => ON
 | point when (point == 8319) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8320 && point < 8330) => EN
 | point when (point >= 8330 && point < 8332) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 8455) {
if (point < 8400) {
if (point < 8336) {
switch (point) {
 | point when (point >= 8332 && point < 8336) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8336 && point < 8352) => L
 | point when (point >= 8352 && point < 8400) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8450) {
switch (point) {
 | point when (point >= 8400 && point < 8448) => NSM
 | point when (point >= 8448 && point < 8450) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8450) => L
 | point when (point >= 8451 && point < 8455) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 8469) {
if (point < 8458) {
switch (point) {
 | point when (point == 8455) => L
 | point when (point >= 8456 && point < 8458) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8458 && point < 8468) => L
 | point when (point == 8468) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8473) {
switch (point) {
 | point when (point == 8469) => L
 | point when (point >= 8470 && point < 8473) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8473 && point < 8478) => L
 | point when (point >= 8478 && point < 8484) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
}
}
} else {
if (point < 68160) {
if (point < 43232) {
if (point < 12445) {
if (point < 9901) {
if (point < 8526) {
if (point < 8494) {
if (point < 8487) {
if (point < 8485) {
switch (point) {
 | point when (point == 8484) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8485) => ON
 | point when (point == 8486) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8489) {
switch (point) {
 | point when (point == 8487) => ON
 | point when (point == 8488) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8489) => ON
 | point when (point >= 8490 && point < 8494) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 8508) {
if (point < 8495) {
switch (point) {
 | point when (point == 8494) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8495 && point < 8506) => L
 | point when (point >= 8506 && point < 8508) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8517) {
switch (point) {
 | point when (point >= 8508 && point < 8512) => L
 | point when (point >= 8512 && point < 8517) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8517 && point < 8522) => L
 | point when (point >= 8522 && point < 8526) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 9014) {
if (point < 8585) {
if (point < 8528) {
switch (point) {
 | point when (point >= 8526 && point < 8528) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 8528 && point < 8544) => ON
 | point when (point >= 8544 && point < 8585) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 8723) {
switch (point) {
 | point when (point >= 8585 && point < 8722) => ON
 | point when (point == 8722) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 8723) => ET
 | point when (point >= 8724 && point < 9014) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 9352) {
if (point < 9109) {
switch (point) {
 | point when (point >= 9014 && point < 9083) => L
 | point when (point >= 9083 && point < 9109) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 9109) => L
 | point when (point >= 9110 && point < 9352) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 9450) {
switch (point) {
 | point when (point >= 9352 && point < 9372) => EN
 | point when (point >= 9372 && point < 9450) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 9450 && point < 9900) => ON
 | point when (point == 9900) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 12288) {
if (point < 11506) {
if (point < 11264) {
if (point < 10240) {
switch (point) {
 | point when (point >= 9901 && point < 10240) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 10240 && point < 10496) => L
 | point when (point >= 10496 && point < 11264) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 11499) {
switch (point) {
 | point when (point >= 11264 && point < 11493) => L
 | point when (point >= 11493 && point < 11499) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 11499 && point < 11503) => L
 | point when (point >= 11503 && point < 11506) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 11647) {
if (point < 11513) {
switch (point) {
 | point when (point >= 11506 && point < 11513) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 11513 && point < 11520) => ON
 | point when (point >= 11520 && point < 11647) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 11744) {
switch (point) {
 | point when (point == 11647) => NSM
 | point when (point >= 11648 && point < 11744) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 11744 && point < 11776) => NSM
 | point when (point >= 11776 && point < 12288) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 12336) {
if (point < 12296) {
if (point < 12289) {
switch (point) {
 | point when (point == 12288) => WS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12289 && point < 12293) => ON
 | point when (point >= 12293 && point < 12296) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 12330) {
switch (point) {
 | point when (point >= 12296 && point < 12321) => ON
 | point when (point >= 12321 && point < 12330) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12330 && point < 12334) => NSM
 | point when (point >= 12334 && point < 12336) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 12349) {
if (point < 12342) {
switch (point) {
 | point when (point == 12336) => ON
 | point when (point >= 12337 && point < 12342) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12342 && point < 12344) => ON
 | point when (point >= 12344 && point < 12349) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 12441) {
switch (point) {
 | point when (point >= 12349 && point < 12353) => ON
 | point when (point >= 12353 && point < 12441) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12441 && point < 12443) => NSM
 | point when (point >= 12443 && point < 12445) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 42607) {
if (point < 12992) {
if (point < 12829) {
if (point < 12539) {
if (point < 12448) {
switch (point) {
 | point when (point >= 12445 && point < 12448) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 12448) => ON
 | point when (point >= 12449 && point < 12539) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 12736) {
switch (point) {
 | point when (point == 12539) => ON
 | point when (point >= 12540 && point < 12736) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12736 && point < 12784) => ON
 | point when (point >= 12784 && point < 12829) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 12896) {
if (point < 12832) {
switch (point) {
 | point when (point >= 12829 && point < 12832) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12832 && point < 12880) => L
 | point when (point >= 12880 && point < 12896) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 12927) {
switch (point) {
 | point when (point >= 12896 && point < 12924) => L
 | point when (point >= 12924 && point < 12927) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 12927 && point < 12977) => L
 | point when (point >= 12977 && point < 12992) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 13311) {
if (point < 13175) {
if (point < 13004) {
switch (point) {
 | point when (point >= 12992 && point < 13004) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 13004 && point < 13008) => ON
 | point when (point >= 13008 && point < 13175) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 13278) {
switch (point) {
 | point when (point >= 13175 && point < 13179) => ON
 | point when (point >= 13179 && point < 13278) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 13278 && point < 13280) => ON
 | point when (point >= 13280 && point < 13311) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 42128) {
if (point < 19904) {
switch (point) {
 | point when (point == 13311) => ON
 | point when (point >= 13312 && point < 19904) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 19904 && point < 19968) => ON
 | point when (point >= 19968 && point < 42128) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 42509) {
switch (point) {
 | point when (point >= 42128 && point < 42192) => ON
 | point when (point >= 42192 && point < 42509) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 42509 && point < 42512) => ON
 | point when (point >= 42512 && point < 42607) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 43011) {
if (point < 42736) {
if (point < 42622) {
if (point < 42611) {
switch (point) {
 | point when (point >= 42607 && point < 42611) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 42611) => ON
 | point when (point >= 42612 && point < 42622) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 42654) {
switch (point) {
 | point when (point >= 42622 && point < 42624) => ON
 | point when (point >= 42624 && point < 42654) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 42654 && point < 42656) => NSM
 | point when (point >= 42656 && point < 42736) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 42786) {
if (point < 42738) {
switch (point) {
 | point when (point >= 42736 && point < 42738) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 42738 && point < 42752) => L
 | point when (point >= 42752 && point < 42786) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 42889) {
switch (point) {
 | point when (point >= 42786 && point < 42888) => L
 | point when (point == 42888) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 42889 && point < 43010) => L
 | point when (point == 43010) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 43048) {
if (point < 43019) {
if (point < 43014) {
switch (point) {
 | point when (point >= 43011 && point < 43014) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 43014) => NSM
 | point when (point >= 43015 && point < 43019) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43045) {
switch (point) {
 | point when (point == 43019) => NSM
 | point when (point >= 43020 && point < 43045) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43045 && point < 43047) => NSM
 | point when (point == 43047) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 43124) {
if (point < 43064) {
switch (point) {
 | point when (point >= 43048 && point < 43056) => ON
 | point when (point >= 43056 && point < 43064) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43064 && point < 43072) => ET
 | point when (point >= 43072 && point < 43124) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43204) {
switch (point) {
 | point when (point >= 43124 && point < 43136) => ON
 | point when (point >= 43136 && point < 43204) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43204 && point < 43214) => NSM
 | point when (point >= 43214 && point < 43232) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
} else {
if (point < 65021) {
if (point < 43645) {
if (point < 43452) {
if (point < 43346) {
if (point < 43264) {
if (point < 43250) {
switch (point) {
 | point when (point >= 43232 && point < 43250) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43250 && point < 43263) => L
 | point when (point == 43263) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43310) {
switch (point) {
 | point when (point >= 43264 && point < 43302) => L
 | point when (point >= 43302 && point < 43310) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43310 && point < 43335) => L
 | point when (point >= 43335 && point < 43346) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 43443) {
if (point < 43392) {
switch (point) {
 | point when (point >= 43346 && point < 43392) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43392 && point < 43395) => NSM
 | point when (point >= 43395 && point < 43443) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43446) {
switch (point) {
 | point when (point == 43443) => NSM
 | point when (point >= 43444 && point < 43446) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43446 && point < 43450) => NSM
 | point when (point >= 43450 && point < 43452) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 43571) {
if (point < 43494) {
if (point < 43454) {
switch (point) {
 | point when (point >= 43452 && point < 43454) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43454 && point < 43493) => L
 | point when (point == 43493) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43567) {
switch (point) {
 | point when (point >= 43494 && point < 43561) => L
 | point when (point >= 43561 && point < 43567) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43567 && point < 43569) => L
 | point when (point >= 43569 && point < 43571) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 43588) {
if (point < 43584) {
switch (point) {
 | point when (point >= 43571 && point < 43573) => L
 | point when (point >= 43573 && point < 43584) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43584 && point < 43587) => L
 | point when (point == 43587) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43597) {
switch (point) {
 | point when (point >= 43588 && point < 43596) => L
 | point when (point == 43596) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43597 && point < 43644) => L
 | point when (point == 43644) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 43777) {
if (point < 43710) {
if (point < 43698) {
if (point < 43696) {
switch (point) {
 | point when (point >= 43645 && point < 43696) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 43696) => NSM
 | point when (point == 43697) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43703) {
switch (point) {
 | point when (point >= 43698 && point < 43701) => NSM
 | point when (point >= 43701 && point < 43703) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43703 && point < 43705) => NSM
 | point when (point >= 43705 && point < 43710) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 43714) {
if (point < 43712) {
switch (point) {
 | point when (point >= 43710 && point < 43712) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 43712) => L
 | point when (point == 43713) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 43758) {
switch (point) {
 | point when (point >= 43714 && point < 43756) => L
 | point when (point >= 43756 && point < 43758) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 43758 && point < 43766) => L
 | point when (point >= 43766 && point < 43777) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 64285) {
if (point < 44008) {
if (point < 44005) {
switch (point) {
 | point when (point >= 43777 && point < 44005) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 44005) => NSM
 | point when (point >= 44006 && point < 44008) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 44013) {
switch (point) {
 | point when (point == 44008) => NSM
 | point when (point >= 44009 && point < 44013) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 44013 && point < 44016) => NSM
 | point when (point >= 44016 && point < 64285) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 64298) {
if (point < 64287) {
switch (point) {
 | point when (point == 64285) => R
 | point when (point == 64286) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 64287 && point < 64297) => R
 | point when (point == 64297) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 64830) {
switch (point) {
 | point when (point >= 64298 && point < 64336) => R
 | point when (point >= 64336 && point < 64830) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 64830 && point < 64848) => ON
 | point when (point >= 64848 && point < 65021) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 65313) {
if (point < 65124) {
if (point < 65106) {
if (point < 65056) {
if (point < 65024) {
switch (point) {
 | point when (point >= 65021 && point < 65024) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65024 && point < 65040) => NSM
 | point when (point >= 65040 && point < 65056) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65104) {
switch (point) {
 | point when (point >= 65056 && point < 65072) => NSM
 | point when (point >= 65072 && point < 65104) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 65104) => CS
 | point when (point == 65105) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 65110) {
if (point < 65108) {
switch (point) {
 | point when (point >= 65106 && point < 65108) => CS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 65108) => ON
 | point when (point == 65109) => CS
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65120) {
switch (point) {
 | point when (point >= 65110 && point < 65119) => ON
 | point when (point == 65119) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65120 && point < 65122) => ON
 | point when (point >= 65122 && point < 65124) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 65286) {
if (point < 65136) {
if (point < 65129) {
switch (point) {
 | point when (point >= 65124 && point < 65129) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65129 && point < 65131) => ET
 | point when (point >= 65131 && point < 65136) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65281) {
switch (point) {
 | point when (point >= 65136 && point < 65279) => AL
 | point when (point >= 65279 && point < 65281) => BN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65281 && point < 65283) => ON
 | point when (point >= 65283 && point < 65286) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 65294) {
if (point < 65292) {
switch (point) {
 | point when (point >= 65286 && point < 65291) => ON
 | point when (point == 65291) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 65292) => CS
 | point when (point == 65293) => ES
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65306) {
switch (point) {
 | point when (point >= 65294 && point < 65296) => CS
 | point when (point >= 65296 && point < 65306) => EN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 65306) => CS
 | point when (point >= 65307 && point < 65313) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 65936) {
if (point < 65509) {
if (point < 65371) {
if (point < 65339) {
switch (point) {
 | point when (point >= 65313 && point < 65339) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65339 && point < 65345) => ON
 | point when (point >= 65345 && point < 65371) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65504) {
switch (point) {
 | point when (point >= 65371 && point < 65382) => ON
 | point when (point >= 65382 && point < 65504) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65504 && point < 65506) => ET
 | point when (point >= 65506 && point < 65509) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 65793) {
if (point < 65512) {
switch (point) {
 | point when (point >= 65509 && point < 65512) => ET
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65512 && point < 65536) => ON
 | point when (point >= 65536 && point < 65793) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 65856) {
switch (point) {
 | point when (point == 65793) => ON
 | point when (point >= 65794 && point < 65856) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 65856 && point < 65933) => ON
 | point when (point >= 65933 && point < 65936) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 66422) {
if (point < 66176) {
if (point < 66000) {
switch (point) {
 | point when (point >= 65936 && point < 66000) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 66000 && point < 66045) => L
 | point when (point >= 66045 && point < 66176) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 66273) {
switch (point) {
 | point when (point >= 66176 && point < 66272) => L
 | point when (point == 66272) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 66273 && point < 66304) => EN
 | point when (point >= 66304 && point < 66422) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 67872) {
if (point < 67584) {
switch (point) {
 | point when (point >= 66422 && point < 66432) => NSM
 | point when (point >= 66432 && point < 67584) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 67584 && point < 67871) => R
 | point when (point == 67871) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 68112) {
switch (point) {
 | point when (point >= 67872 && point < 68097) => R
 | point when (point >= 68097 && point < 68112) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 68112 && point < 68152) => R
 | point when (point >= 68152 && point < 68160) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
}
} else {
if (point < 72201) {
if (point < 70502) {
if (point < 69932) {
if (point < 69633) {
if (point < 68912) {
if (point < 68409) {
if (point < 68325) {
switch (point) {
 | point when (point >= 68160 && point < 68325) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 68325 && point < 68331) => NSM
 | point when (point >= 68331 && point < 68409) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 68864) {
switch (point) {
 | point when (point >= 68409 && point < 68416) => ON
 | point when (point >= 68416 && point < 68864) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 68864 && point < 68900) => AL
 | point when (point >= 68900 && point < 68912) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 69446) {
if (point < 69376) {
switch (point) {
 | point when (point >= 68912 && point < 69376) => AN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69376 && point < 69424) => R
 | point when (point >= 69424 && point < 69446) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 69600) {
switch (point) {
 | point when (point >= 69446 && point < 69457) => NSM
 | point when (point >= 69457 && point < 69600) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69600 && point < 69632) => R
 | point when (point == 69632) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 69762) {
if (point < 69703) {
if (point < 69634) {
switch (point) {
 | point when (point == 69633) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69634 && point < 69688) => L
 | point when (point >= 69688 && point < 69703) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 69734) {
switch (point) {
 | point when (point >= 69703 && point < 69714) => L
 | point when (point >= 69714 && point < 69734) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69734 && point < 69759) => L
 | point when (point >= 69759 && point < 69762) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 69819) {
if (point < 69815) {
switch (point) {
 | point when (point >= 69762 && point < 69811) => L
 | point when (point >= 69811 && point < 69815) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69815 && point < 69817) => L
 | point when (point >= 69817 && point < 69819) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 69891) {
switch (point) {
 | point when (point >= 69819 && point < 69888) => L
 | point when (point >= 69888 && point < 69891) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69891 && point < 69927) => L
 | point when (point >= 69927 && point < 69932) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 70197) {
if (point < 70070) {
if (point < 70003) {
if (point < 69933) {
switch (point) {
 | point when (point == 69932) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 69933 && point < 69942) => NSM
 | point when (point >= 69942 && point < 70003) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70016) {
switch (point) {
 | point when (point == 70003) => NSM
 | point when (point >= 70004 && point < 70016) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70016 && point < 70018) => NSM
 | point when (point >= 70018 && point < 70070) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 70093) {
if (point < 70079) {
switch (point) {
 | point when (point >= 70070 && point < 70079) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70079 && point < 70089) => L
 | point when (point >= 70089 && point < 70093) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70194) {
switch (point) {
 | point when (point >= 70093 && point < 70191) => L
 | point when (point >= 70191 && point < 70194) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70194 && point < 70196) => L
 | point when (point == 70196) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 70371) {
if (point < 70206) {
if (point < 70198) {
switch (point) {
 | point when (point == 70197) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70198 && point < 70200) => NSM
 | point when (point >= 70200 && point < 70206) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70367) {
switch (point) {
 | point when (point >= 70206 && point < 70272) => NSM
 | point when (point >= 70272 && point < 70367) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70367) => NSM
 | point when (point >= 70368 && point < 70371) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 70459) {
if (point < 70400) {
switch (point) {
 | point when (point >= 70371 && point < 70384) => NSM
 | point when (point >= 70384 && point < 70400) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70400 && point < 70402) => NSM
 | point when (point >= 70402 && point < 70459) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70464) {
switch (point) {
 | point when (point >= 70459 && point < 70461) => NSM
 | point when (point >= 70461 && point < 70464) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70464) => NSM
 | point when (point >= 70465 && point < 70502) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 71230) {
if (point < 70847) {
if (point < 70727) {
if (point < 70720) {
if (point < 70656) {
switch (point) {
 | point when (point >= 70502 && point < 70656) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 70656 && point < 70712) => L
 | point when (point >= 70712 && point < 70720) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70725) {
switch (point) {
 | point when (point >= 70720 && point < 70722) => L
 | point when (point >= 70722 && point < 70725) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70725) => L
 | point when (point == 70726) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 70835) {
if (point < 70750) {
switch (point) {
 | point when (point >= 70727 && point < 70750) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70750) => NSM
 | point when (point >= 70751 && point < 70835) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 70842) {
switch (point) {
 | point when (point >= 70835 && point < 70841) => NSM
 | point when (point == 70841) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70842) => NSM
 | point when (point >= 70843 && point < 70847) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 71102) {
if (point < 70852) {
if (point < 70849) {
switch (point) {
 | point when (point >= 70847 && point < 70849) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 70849) => L
 | point when (point >= 70850 && point < 70852) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 71096) {
switch (point) {
 | point when (point >= 70852 && point < 71090) => L
 | point when (point >= 71090 && point < 71096) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71096 && point < 71100) => L
 | point when (point >= 71100 && point < 71102) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 71168) {
if (point < 71105) {
switch (point) {
 | point when (point == 71102) => L
 | point when (point >= 71103 && point < 71105) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71105 && point < 71132) => L
 | point when (point >= 71132 && point < 71168) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 71227) {
switch (point) {
 | point when (point >= 71168 && point < 71219) => L
 | point when (point >= 71219 && point < 71227) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71227 && point < 71229) => L
 | point when (point == 71229) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 71456) {
if (point < 71341) {
if (point < 71264) {
if (point < 71231) {
switch (point) {
 | point when (point == 71230) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71231 && point < 71233) => NSM
 | point when (point >= 71233 && point < 71264) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 71339) {
switch (point) {
 | point when (point >= 71264 && point < 71296) => ON
 | point when (point >= 71296 && point < 71339) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 71339) => NSM
 | point when (point == 71340) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 71350) {
if (point < 71342) {
switch (point) {
 | point when (point == 71341) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71342 && point < 71344) => L
 | point when (point >= 71344 && point < 71350) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 71352) {
switch (point) {
 | point when (point == 71350) => L
 | point when (point == 71351) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71352 && point < 71453) => L
 | point when (point >= 71453 && point < 71456) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 71737) {
if (point < 71463) {
if (point < 71458) {
switch (point) {
 | point when (point >= 71456 && point < 71458) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71458 && point < 71462) => NSM
 | point when (point == 71462) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 71727) {
switch (point) {
 | point when (point >= 71463 && point < 71472) => NSM
 | point when (point >= 71472 && point < 71727) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 71727 && point < 71736) => NSM
 | point when (point == 71736) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 72160) {
if (point < 72148) {
switch (point) {
 | point when (point >= 71737 && point < 71739) => NSM
 | point when (point >= 71739 && point < 72148) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72148 && point < 72156) => NSM
 | point when (point >= 72156 && point < 72160) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 72193) {
switch (point) {
 | point when (point == 72160) => NSM
 | point when (point >= 72161 && point < 72193) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72193 && point < 72199) => NSM
 | point when (point >= 72199 && point < 72201) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
} else {
if (point < 119155) {
if (point < 73040) {
if (point < 72344) {
if (point < 72272) {
if (point < 72249) {
if (point < 72203) {
switch (point) {
 | point when (point >= 72201 && point < 72203) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72203 && point < 72243) => L
 | point when (point >= 72243 && point < 72249) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 72255) {
switch (point) {
 | point when (point >= 72249 && point < 72251) => L
 | point when (point >= 72251 && point < 72255) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72255 && point < 72263) => L
 | point when (point >= 72263 && point < 72272) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 72281) {
if (point < 72273) {
switch (point) {
 | point when (point == 72272) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72273 && point < 72279) => NSM
 | point when (point >= 72279 && point < 72281) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 72330) {
switch (point) {
 | point when (point >= 72281 && point < 72284) => NSM
 | point when (point >= 72284 && point < 72330) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72330 && point < 72343) => NSM
 | point when (point == 72343) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 72881) {
if (point < 72766) {
if (point < 72346) {
switch (point) {
 | point when (point >= 72344 && point < 72346) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 72346 && point < 72752) => L
 | point when (point >= 72752 && point < 72766) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 72873) {
switch (point) {
 | point when (point >= 72766 && point < 72850) => L
 | point when (point >= 72850 && point < 72873) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 72873) => L
 | point when (point >= 72874 && point < 72881) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 72960) {
if (point < 72884) {
switch (point) {
 | point when (point == 72881) => L
 | point when (point >= 72882 && point < 72884) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 72884) => L
 | point when (point >= 72885 && point < 72960) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 73030) {
switch (point) {
 | point when (point >= 72960 && point < 73009) => L
 | point when (point >= 73009 && point < 73030) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 73030) => L
 | point when (point >= 73031 && point < 73040) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 92917) {
if (point < 73459) {
if (point < 73109) {
if (point < 73104) {
switch (point) {
 | point when (point >= 73040 && point < 73104) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 73104 && point < 73107) => NSM
 | point when (point >= 73107 && point < 73109) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 73111) {
switch (point) {
 | point when (point == 73109) => NSM
 | point when (point == 73110) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 73111) => NSM
 | point when (point >= 73112 && point < 73459) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 73693) {
if (point < 73461) {
switch (point) {
 | point when (point >= 73459 && point < 73461) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 73461 && point < 73685) => L
 | point when (point >= 73685 && point < 73693) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 73727) {
switch (point) {
 | point when (point >= 73693 && point < 73697) => ET
 | point when (point >= 73697 && point < 73727) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 73727 && point < 92912) => L
 | point when (point >= 92912 && point < 92917) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 94178) {
if (point < 94031) {
if (point < 92976) {
switch (point) {
 | point when (point >= 92917 && point < 92976) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 92976 && point < 92983) => NSM
 | point when (point >= 92983 && point < 94031) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 94095) {
switch (point) {
 | point when (point == 94031) => NSM
 | point when (point >= 94032 && point < 94095) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 94095 && point < 94099) => NSM
 | point when (point >= 94099 && point < 94178) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 113824) {
if (point < 113821) {
switch (point) {
 | point when (point == 94178) => ON
 | point when (point >= 94179 && point < 113821) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 113821 && point < 113823) => NSM
 | point when (point == 113823) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 119143) {
switch (point) {
 | point when (point >= 113824 && point < 118784) => BN
 | point when (point >= 118784 && point < 119143) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 119143 && point < 119146) => NSM
 | point when (point >= 119146 && point < 119155) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
} else {
if (point < 121461) {
if (point < 120540) {
if (point < 119296) {
if (point < 119173) {
if (point < 119163) {
switch (point) {
 | point when (point >= 119155 && point < 119163) => BN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 119163 && point < 119171) => NSM
 | point when (point >= 119171 && point < 119173) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 119210) {
switch (point) {
 | point when (point >= 119173 && point < 119180) => NSM
 | point when (point >= 119180 && point < 119210) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 119210 && point < 119214) => NSM
 | point when (point >= 119214 && point < 119296) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 119520) {
if (point < 119362) {
switch (point) {
 | point when (point >= 119296 && point < 119362) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 119362 && point < 119365) => NSM
 | point when (point >= 119365 && point < 119520) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 119648) {
switch (point) {
 | point when (point >= 119520 && point < 119552) => L
 | point when (point >= 119552 && point < 119648) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 119648 && point < 120539) => L
 | point when (point == 120539) => ON
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 120771) {
if (point < 120655) {
if (point < 120597) {
switch (point) {
 | point when (point >= 120540 && point < 120597) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 120597) => ON
 | point when (point >= 120598 && point < 120655) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 120713) {
switch (point) {
 | point when (point == 120655) => ON
 | point when (point >= 120656 && point < 120713) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point == 120713) => ON
 | point when (point >= 120714 && point < 120771) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 121344) {
if (point < 120782) {
switch (point) {
 | point when (point == 120771) => ON
 | point when (point >= 120772 && point < 120782) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 120782 && point < 120832) => EN
 | point when (point >= 120832 && point < 121344) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 121403) {
switch (point) {
 | point when (point >= 121344 && point < 121399) => NSM
 | point when (point >= 121399 && point < 121403) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 121403 && point < 121453) => NSM
 | point when (point >= 121453 && point < 121461) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
} else {
if (point < 125252) {
if (point < 123191) {
if (point < 121477) {
if (point < 121462) {
switch (point) {
 | point when (point == 121461) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 121462 && point < 121476) => L
 | point when (point == 121476) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 123136) {
switch (point) {
 | point when (point >= 121477 && point < 121499) => L
 | point when (point >= 121499 && point < 123136) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 123136 && point < 123184) => L
 | point when (point >= 123184 && point < 123191) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 123647) {
if (point < 123628) {
switch (point) {
 | point when (point >= 123191 && point < 123628) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 123628 && point < 123632) => NSM
 | point when (point >= 123632 && point < 123647) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 125136) {
switch (point) {
 | point when (point >= 123647 && point < 124928) => ET
 | point when (point >= 124928 && point < 125136) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 125136 && point < 125184) => NSM
 | point when (point >= 125184 && point < 125252) => R
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
} else {
if (point < 127279) {
if (point < 126704) {
if (point < 125259) {
switch (point) {
 | point when (point >= 125252 && point < 125259) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 125259 && point < 126065) => R
 | point when (point >= 126065 && point < 126704) => AL
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 127243) {
switch (point) {
 | point when (point >= 126704 && point < 127232) => ON
 | point when (point >= 127232 && point < 127243) => EN
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 127243 && point < 127248) => ON
 | point when (point >= 127248 && point < 127279) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
} else {
if (point < 127584) {
if (point < 127338) {
switch (point) {
 | point when (point == 127279) => ON
 | point when (point >= 127280 && point < 127338) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 127338 && point < 127344) => ON
 | point when (point >= 127344 && point < 127584) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
} else {
if (point < 917505) {
switch (point) {
 | point when (point >= 127584 && point < 131072) => ON
 | point when (point >= 131072 && point < 917505) => L
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
} else {
switch (point) {
 | point when (point >= 917505 && point < 917760) => BN
 | point when (point >= 917760 && point < 983040) => NSM
| _point => raise(PrecisUtils.PrecisError(BidiError))
}
}
}
}
}
}
}
}
}
}

  };

let rtlAllowed = [R, AL, AN, EN, ES, CS, ET, ON, BN, NSM];
let ltrAllowed = [L, EN, ES, CS, ET, ON, BN, NSM];

let testRtlProps = directionList => {
  let allowList =
    List.map(
      index => {
        let propAllow = List.map(prop => index == prop, rtlAllowed);
        List.mem(true, propAllow);
      },
      directionList,
    );
  !List.mem(false, allowList);
};

let testEnAndAn = directionList => {
  let en = List.mem(EN, directionList);
  let an = List.mem(AN, directionList);
  !(en && an);
};

let rec testEndR = directionList =>
  switch (directionList) {
  | [NSM, ...tail] => testEndR(tail)
  | [R, ..._tail]
  | [AL, ..._tail]
  | [EN, ..._tail]
  | [AN, ..._tail] => true
  | [_head, ..._tail] => false
  | [] => true
  };

let testRtl = directionList => {
  let rtlAllow = testRtlProps(directionList);
  let noEnAndAn = testEnAndAn(directionList);
  let testEnd = testEndR(List.rev(directionList));
  rtlAllow && noEnAndAn && testEnd;
};

let rec testEndL = directionList =>
  switch (directionList) {
  | [NSM, ...tail] => testEndL(tail)
  | [L, ..._tail]
  | [AN, ..._tail]
  | [EN, ..._tail] => true
  | [_head, ..._tail] => false
  | [] => true
  };

let testLtrProps = directionList => {
  let allowList =
    List.map(
      index => {
        let propAllow = List.map(prop => index == prop, ltrAllowed);
        List.mem(true, propAllow);
      },
      directionList,
    );
  !List.mem(false, allowList);
};

let testLtr = directionList => {
  let ltrAllow = testLtrProps(directionList);
  let testEnd = testEndL(List.rev(directionList));
  ltrAllow && testEnd;
};

let validate: list(PrecisUtils.codePoint) => bool =
  codePointList => {
    let directionList = List.map(getDirectionProperty, codePointList);
    switch (List.hd(codePointList) |> getDirectionProperty) {
    | R
    | AL => testRtl(List.tl(directionList))
    | L => testLtr(List.tl(directionList))
    | _direction => false
    };
  };

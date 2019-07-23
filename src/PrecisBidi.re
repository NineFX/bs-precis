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
  x => {
    switch (x) {
    | cp when cp >= 0x1 && cp <= 0x8 => BN
    | cp when cp >= 0xe && cp <= 0x1b => BN
    | cp when cp >= 0x1c && cp <= 0x1e => B
    | cp when cp >= 0x21 && cp <= 0x22 => ON
    | cp when cp >= 0x23 && cp <= 0x25 => ET
    | cp when cp >= 0x26 && cp <= 0x2a => ON
    | cp when cp >= 0x2e && cp <= 0x2f => CS
    | cp when cp >= 0x30 && cp <= 0x39 => EN
    | cp when cp >= 0x3b && cp <= 0x40 => ON
    | cp when cp >= 0x41 && cp <= 0x5a => L
    | cp when cp >= 0x5b && cp <= 0x60 => ON
    | cp when cp >= 0x61 && cp <= 0x7a => L
    | cp when cp >= 0x7b && cp <= 0x7e => ON
    | cp when cp >= 0x7f && cp <= 0x84 => BN
    | cp when cp >= 0x86 && cp <= 0x9f => BN
    | cp when cp >= 0xa2 && cp <= 0xa5 => ET
    | cp when cp >= 0xa6 && cp <= 0xa9 => ON
    | cp when cp >= 0xab && cp <= 0xac => ON
    | cp when cp >= 0xae && cp <= 0xaf => ON
    | cp when cp >= 0xb0 && cp <= 0xb1 => ET
    | cp when cp >= 0xb2 && cp <= 0xb3 => EN
    | cp when cp >= 0xb6 && cp <= 0xb8 => ON
    | cp when cp >= 0xbb && cp <= 0xbf => ON
    | cp when cp >= 0xc0 && cp <= 0xd6 => L
    | cp when cp >= 0xd8 && cp <= 0xf6 => L
    | cp when cp >= 0xf8 && cp <= 0x2b8 => L
    | cp when cp >= 0x2b9 && cp <= 0x2ba => ON
    | cp when cp >= 0x2bb && cp <= 0x2c1 => L
    | cp when cp >= 0x2c2 && cp <= 0x2cf => ON
    | cp when cp >= 0x2d0 && cp <= 0x2d1 => L
    | cp when cp >= 0x2d2 && cp <= 0x2df => ON
    | cp when cp >= 0x2e0 && cp <= 0x2e4 => L
    | cp when cp >= 0x2e5 && cp <= 0x2ed => ON
    | cp when cp >= 0x2ef && cp <= 0x2ff => ON
    | cp when cp >= 0x300 && cp <= 0x36f => NSM
    | cp when cp >= 0x370 && cp <= 0x373 => L
    | cp when cp >= 0x374 && cp <= 0x375 => ON
    | cp when cp >= 0x376 && cp <= 0x37d => L
    | cp when cp >= 0x37f && cp <= 0x383 => L
    | cp when cp >= 0x384 && cp <= 0x385 => ON
    | cp when cp >= 0x388 && cp <= 0x3f5 => L
    | cp when cp >= 0x3f7 && cp <= 0x482 => L
    | cp when cp >= 0x483 && cp <= 0x489 => NSM
    | cp when cp >= 0x48a && cp <= 0x589 => L
    | cp when cp >= 0x58a && cp <= 0x58e => ON
    | cp when cp >= 0x58f && cp <= 0x590 => ET
    | cp when cp >= 0x591 && cp <= 0x5bd => NSM
    | cp when cp >= 0x5c1 && cp <= 0x5c2 => NSM
    | cp when cp >= 0x5c4 && cp <= 0x5c5 => NSM
    | cp when cp >= 0x5c7 && cp <= 0x5cf => NSM
    | cp when cp >= 0x5d0 && cp <= 0x5ff => R
    | cp when cp >= 0x600 && cp <= 0x605 => AN
    | cp when cp >= 0x606 && cp <= 0x607 => ON
    | cp when cp >= 0x609 && cp <= 0x60a => ET
    | cp when cp >= 0x60e && cp <= 0x60f => ON
    | cp when cp >= 0x610 && cp <= 0x61a => NSM
    | cp when cp >= 0x61b && cp <= 0x64a => AL
    | cp when cp >= 0x64b && cp <= 0x65f => NSM
    | cp when cp >= 0x660 && cp <= 0x669 => AN
    | cp when cp >= 0x66b && cp <= 0x66c => AN
    | cp when cp >= 0x66d && cp <= 0x66f => AL
    | cp when cp >= 0x671 && cp <= 0x6d5 => AL
    | cp when cp >= 0x6d6 && cp <= 0x6dc => NSM
    | cp when cp >= 0x6df && cp <= 0x6e4 => NSM
    | cp when cp >= 0x6e5 && cp <= 0x6e6 => AL
    | cp when cp >= 0x6e7 && cp <= 0x6e8 => NSM
    | cp when cp >= 0x6ea && cp <= 0x6ed => NSM
    | cp when cp >= 0x6ee && cp <= 0x6ef => AL
    | cp when cp >= 0x6f0 && cp <= 0x6f9 => EN
    | cp when cp >= 0x6fa && cp <= 0x710 => AL
    | cp when cp >= 0x712 && cp <= 0x72f => AL
    | cp when cp >= 0x730 && cp <= 0x74c => NSM
    | cp when cp >= 0x74d && cp <= 0x7a5 => AL
    | cp when cp >= 0x7a6 && cp <= 0x7b0 => NSM
    | cp when cp >= 0x7b1 && cp <= 0x7bf => AL
    | cp when cp >= 0x7c0 && cp <= 0x7ea => R
    | cp when cp >= 0x7eb && cp <= 0x7f3 => NSM
    | cp when cp >= 0x7f4 && cp <= 0x7f5 => R
    | cp when cp >= 0x7f6 && cp <= 0x7f9 => ON
    | cp when cp >= 0x7fa && cp <= 0x7fc => R
    | cp when cp >= 0x7fe && cp <= 0x815 => R
    | cp when cp >= 0x816 && cp <= 0x819 => NSM
    | cp when cp >= 0x81b && cp <= 0x823 => NSM
    | cp when cp >= 0x825 && cp <= 0x827 => NSM
    | cp when cp >= 0x829 && cp <= 0x82f => NSM
    | cp when cp >= 0x830 && cp <= 0x858 => R
    | cp when cp >= 0x859 && cp <= 0x85d => NSM
    | cp when cp >= 0x85e && cp <= 0x85f => R
    | cp when cp >= 0x860 && cp <= 0x8d2 => AL
    | cp when cp >= 0x8d3 && cp <= 0x8e1 => NSM
    | cp when cp >= 0x8e3 && cp <= 0x902 => NSM
    | cp when cp >= 0x903 && cp <= 0x939 => L
    | cp when cp >= 0x93d && cp <= 0x940 => L
    | cp when cp >= 0x941 && cp <= 0x948 => NSM
    | cp when cp >= 0x949 && cp <= 0x94c => L
    | cp when cp >= 0x94e && cp <= 0x950 => L
    | cp when cp >= 0x951 && cp <= 0x957 => NSM
    | cp when cp >= 0x958 && cp <= 0x961 => L
    | cp when cp >= 0x962 && cp <= 0x963 => NSM
    | cp when cp >= 0x964 && cp <= 0x980 => L
    | cp when cp >= 0x982 && cp <= 0x9bb => L
    | cp when cp >= 0x9bd && cp <= 0x9c0 => L
    | cp when cp >= 0x9c1 && cp <= 0x9c6 => NSM
    | cp when cp >= 0x9c7 && cp <= 0x9cc => L
    | cp when cp >= 0x9ce && cp <= 0x9e1 => L
    | cp when cp >= 0x9e2 && cp <= 0x9e5 => NSM
    | cp when cp >= 0x9e6 && cp <= 0x9f1 => L
    | cp when cp >= 0x9f2 && cp <= 0x9f3 => ET
    | cp when cp >= 0x9f4 && cp <= 0x9fa => L
    | cp when cp >= 0x9fc && cp <= 0x9fd => L
    | cp when cp >= 0x9fe && cp <= 0xa02 => NSM
    | cp when cp >= 0xa03 && cp <= 0xa3b => L
    | cp when cp >= 0xa3c && cp <= 0xa3d => NSM
    | cp when cp >= 0xa3e && cp <= 0xa40 => L
    | cp when cp >= 0xa41 && cp <= 0xa58 => NSM
    | cp when cp >= 0xa59 && cp <= 0xa6f => L
    | cp when cp >= 0xa70 && cp <= 0xa71 => NSM
    | cp when cp >= 0xa72 && cp <= 0xa74 => L
    | cp when cp >= 0xa76 && cp <= 0xa80 => L
    | cp when cp >= 0xa81 && cp <= 0xa82 => NSM
    | cp when cp >= 0xa83 && cp <= 0xabb => L
    | cp when cp >= 0xabd && cp <= 0xac0 => L
    | cp when cp >= 0xac1 && cp <= 0xac8 => NSM
    | cp when cp >= 0xac9 && cp <= 0xacc => L
    | cp when cp >= 0xacd && cp <= 0xacf => NSM
    | cp when cp >= 0xad0 && cp <= 0xae1 => L
    | cp when cp >= 0xae2 && cp <= 0xae5 => NSM
    | cp when cp >= 0xae6 && cp <= 0xaf0 => L
    | cp when cp >= 0xaf1 && cp <= 0xaf8 => ET
    | cp when cp >= 0xafa && cp <= 0xb01 => NSM
    | cp when cp >= 0xb02 && cp <= 0xb3b => L
    | cp when cp >= 0xb3d && cp <= 0xb3e => L
    | cp when cp >= 0xb41 && cp <= 0xb46 => NSM
    | cp when cp >= 0xb47 && cp <= 0xb4c => L
    | cp when cp >= 0xb4d && cp <= 0xb56 => NSM
    | cp when cp >= 0xb57 && cp <= 0xb61 => L
    | cp when cp >= 0xb62 && cp <= 0xb65 => NSM
    | cp when cp >= 0xb66 && cp <= 0xb81 => L
    | cp when cp >= 0xb83 && cp <= 0xbbf => L
    | cp when cp >= 0xbc1 && cp <= 0xbcc => L
    | cp when cp >= 0xbcd && cp <= 0xbcf => NSM
    | cp when cp >= 0xbd0 && cp <= 0xbf2 => L
    | cp when cp >= 0xbf3 && cp <= 0xbf8 => ON
    | cp when cp >= 0xbfa && cp <= 0xbff => ON
    | cp when cp >= 0xc01 && cp <= 0xc03 => L
    | cp when cp >= 0xc05 && cp <= 0xc3d => L
    | cp when cp >= 0xc3e && cp <= 0xc40 => NSM
    | cp when cp >= 0xc41 && cp <= 0xc45 => L
    | cp when cp >= 0xc46 && cp <= 0xc57 => NSM
    | cp when cp >= 0xc58 && cp <= 0xc61 => L
    | cp when cp >= 0xc62 && cp <= 0xc65 => NSM
    | cp when cp >= 0xc66 && cp <= 0xc77 => L
    | cp when cp >= 0xc78 && cp <= 0xc7e => ON
    | cp when cp >= 0xc7f && cp <= 0xc80 => L
    | cp when cp >= 0xc82 && cp <= 0xcbb => L
    | cp when cp >= 0xcbd && cp <= 0xccb => L
    | cp when cp >= 0xccc && cp <= 0xcd4 => NSM
    | cp when cp >= 0xcd5 && cp <= 0xce1 => L
    | cp when cp >= 0xce2 && cp <= 0xce5 => NSM
    | cp when cp >= 0xce6 && cp <= 0xcff => L
    | cp when cp >= 0xd00 && cp <= 0xd01 => NSM
    | cp when cp >= 0xd02 && cp <= 0xd3a => L
    | cp when cp >= 0xd3b && cp <= 0xd3c => NSM
    | cp when cp >= 0xd3d && cp <= 0xd40 => L
    | cp when cp >= 0xd41 && cp <= 0xd45 => NSM
    | cp when cp >= 0xd46 && cp <= 0xd4c => L
    | cp when cp >= 0xd4e && cp <= 0xd61 => L
    | cp when cp >= 0xd62 && cp <= 0xd65 => NSM
    | cp when cp >= 0xd66 && cp <= 0xdc9 => L
    | cp when cp >= 0xdca && cp <= 0xdce => NSM
    | cp when cp >= 0xdcf && cp <= 0xdd1 => L
    | cp when cp >= 0xdd2 && cp <= 0xdd7 => NSM
    | cp when cp >= 0xdd8 && cp <= 0xe30 => L
    | cp when cp >= 0xe32 && cp <= 0xe33 => L
    | cp when cp >= 0xe34 && cp <= 0xe3e => NSM
    | cp when cp >= 0xe40 && cp <= 0xe46 => L
    | cp when cp >= 0xe47 && cp <= 0xe4e => NSM
    | cp when cp >= 0xe4f && cp <= 0xeb0 => L
    | cp when cp >= 0xeb2 && cp <= 0xeb3 => L
    | cp when cp >= 0xeb4 && cp <= 0xebc => NSM
    | cp when cp >= 0xebd && cp <= 0xec7 => L
    | cp when cp >= 0xec8 && cp <= 0xecf => NSM
    | cp when cp >= 0xed0 && cp <= 0xf17 => L
    | cp when cp >= 0xf18 && cp <= 0xf19 => NSM
    | cp when cp >= 0xf1a && cp <= 0xf34 => L
    | cp when cp >= 0xf3a && cp <= 0xf3d => ON
    | cp when cp >= 0xf3e && cp <= 0xf70 => L
    | cp when cp >= 0xf71 && cp <= 0xf7e => NSM
    | cp when cp >= 0xf80 && cp <= 0xf84 => NSM
    | cp when cp >= 0xf86 && cp <= 0xf87 => NSM
    | cp when cp >= 0xf88 && cp <= 0xf8c => L
    | cp when cp >= 0xf8d && cp <= 0xfbd => NSM
    | cp when cp >= 0xfbe && cp <= 0xfc5 => L
    | cp when cp >= 0xfc7 && cp <= 0x102c => L
    | cp when cp >= 0x102d && cp <= 0x1030 => NSM
    | cp when cp >= 0x1032 && cp <= 0x1037 => NSM
    | cp when cp >= 0x1039 && cp <= 0x103a => NSM
    | cp when cp >= 0x103b && cp <= 0x103c => L
    | cp when cp >= 0x103d && cp <= 0x103e => NSM
    | cp when cp >= 0x103f && cp <= 0x1057 => L
    | cp when cp >= 0x1058 && cp <= 0x1059 => NSM
    | cp when cp >= 0x105a && cp <= 0x105d => L
    | cp when cp >= 0x105e && cp <= 0x1060 => NSM
    | cp when cp >= 0x1061 && cp <= 0x1070 => L
    | cp when cp >= 0x1071 && cp <= 0x1074 => NSM
    | cp when cp >= 0x1075 && cp <= 0x1081 => L
    | cp when cp >= 0x1083 && cp <= 0x1084 => L
    | cp when cp >= 0x1085 && cp <= 0x1086 => NSM
    | cp when cp >= 0x1087 && cp <= 0x108c => L
    | cp when cp >= 0x108e && cp <= 0x109c => L
    | cp when cp >= 0x109e && cp <= 0x135c => L
    | cp when cp >= 0x135d && cp <= 0x135f => NSM
    | cp when cp >= 0x1360 && cp <= 0x138f => L
    | cp when cp >= 0x1390 && cp <= 0x139f => ON
    | cp when cp >= 0x13a0 && cp <= 0x13ff => L
    | cp when cp >= 0x1401 && cp <= 0x167f => L
    | cp when cp >= 0x1681 && cp <= 0x169a => L
    | cp when cp >= 0x169b && cp <= 0x169f => ON
    | cp when cp >= 0x16a0 && cp <= 0x1711 => L
    | cp when cp >= 0x1712 && cp <= 0x171f => NSM
    | cp when cp >= 0x1720 && cp <= 0x1731 => L
    | cp when cp >= 0x1732 && cp <= 0x1734 => NSM
    | cp when cp >= 0x1735 && cp <= 0x1751 => L
    | cp when cp >= 0x1752 && cp <= 0x175f => NSM
    | cp when cp >= 0x1760 && cp <= 0x1771 => L
    | cp when cp >= 0x1772 && cp <= 0x177f => NSM
    | cp when cp >= 0x1780 && cp <= 0x17b3 => L
    | cp when cp >= 0x17b4 && cp <= 0x17b5 => NSM
    | cp when cp >= 0x17b7 && cp <= 0x17bd => NSM
    | cp when cp >= 0x17be && cp <= 0x17c5 => L
    | cp when cp >= 0x17c7 && cp <= 0x17c8 => L
    | cp when cp >= 0x17c9 && cp <= 0x17d3 => NSM
    | cp when cp >= 0x17d4 && cp <= 0x17da => L
    | cp when cp >= 0x17dd && cp <= 0x17df => NSM
    | cp when cp >= 0x17e0 && cp <= 0x17ef => L
    | cp when cp >= 0x17f0 && cp <= 0x180a => ON
    | cp when cp >= 0x180b && cp <= 0x180d => NSM
    | cp when cp >= 0x180e && cp <= 0x180f => BN
    | cp when cp >= 0x1810 && cp <= 0x1884 => L
    | cp when cp >= 0x1885 && cp <= 0x1886 => NSM
    | cp when cp >= 0x1887 && cp <= 0x18a8 => L
    | cp when cp >= 0x18aa && cp <= 0x191f => L
    | cp when cp >= 0x1920 && cp <= 0x1922 => NSM
    | cp when cp >= 0x1923 && cp <= 0x1926 => L
    | cp when cp >= 0x1927 && cp <= 0x1928 => NSM
    | cp when cp >= 0x1929 && cp <= 0x1931 => L
    | cp when cp >= 0x1933 && cp <= 0x1938 => L
    | cp when cp >= 0x1939 && cp <= 0x193f => NSM
    | cp when cp >= 0x1940 && cp <= 0x1945 => ON
    | cp when cp >= 0x1946 && cp <= 0x19dd => L
    | cp when cp >= 0x19de && cp <= 0x19ff => ON
    | cp when cp >= 0x1a00 && cp <= 0x1a16 => L
    | cp when cp >= 0x1a17 && cp <= 0x1a18 => NSM
    | cp when cp >= 0x1a19 && cp <= 0x1a1a => L
    | cp when cp >= 0x1a1b && cp <= 0x1a1d => NSM
    | cp when cp >= 0x1a1e && cp <= 0x1a55 => L
    | cp when cp >= 0x1a58 && cp <= 0x1a60 => NSM
    | cp when cp >= 0x1a63 && cp <= 0x1a64 => L
    | cp when cp >= 0x1a65 && cp <= 0x1a6c => NSM
    | cp when cp >= 0x1a6d && cp <= 0x1a72 => L
    | cp when cp >= 0x1a73 && cp <= 0x1a7f => NSM
    | cp when cp >= 0x1a80 && cp <= 0x1aaf => L
    | cp when cp >= 0x1ab0 && cp <= 0x1b03 => NSM
    | cp when cp >= 0x1b04 && cp <= 0x1b33 => L
    | cp when cp >= 0x1b36 && cp <= 0x1b3a => NSM
    | cp when cp >= 0x1b3d && cp <= 0x1b41 => L
    | cp when cp >= 0x1b43 && cp <= 0x1b6a => L
    | cp when cp >= 0x1b6b && cp <= 0x1b73 => NSM
    | cp when cp >= 0x1b74 && cp <= 0x1b7f => L
    | cp when cp >= 0x1b80 && cp <= 0x1b81 => NSM
    | cp when cp >= 0x1b82 && cp <= 0x1ba1 => L
    | cp when cp >= 0x1ba2 && cp <= 0x1ba5 => NSM
    | cp when cp >= 0x1ba6 && cp <= 0x1ba7 => L
    | cp when cp >= 0x1ba8 && cp <= 0x1ba9 => NSM
    | cp when cp >= 0x1bab && cp <= 0x1bad => NSM
    | cp when cp >= 0x1bae && cp <= 0x1be5 => L
    | cp when cp >= 0x1be8 && cp <= 0x1be9 => NSM
    | cp when cp >= 0x1bea && cp <= 0x1bec => L
    | cp when cp >= 0x1bef && cp <= 0x1bf1 => NSM
    | cp when cp >= 0x1bf2 && cp <= 0x1c2b => L
    | cp when cp >= 0x1c2c && cp <= 0x1c33 => NSM
    | cp when cp >= 0x1c34 && cp <= 0x1c35 => L
    | cp when cp >= 0x1c36 && cp <= 0x1c3a => NSM
    | cp when cp >= 0x1c3b && cp <= 0x1ccf => L
    | cp when cp >= 0x1cd0 && cp <= 0x1cd2 => NSM
    | cp when cp >= 0x1cd4 && cp <= 0x1ce0 => NSM
    | cp when cp >= 0x1ce2 && cp <= 0x1ce8 => NSM
    | cp when cp >= 0x1ce9 && cp <= 0x1cec => L
    | cp when cp >= 0x1cee && cp <= 0x1cf3 => L
    | cp when cp >= 0x1cf5 && cp <= 0x1cf7 => L
    | cp when cp >= 0x1cf8 && cp <= 0x1cf9 => NSM
    | cp when cp >= 0x1cfa && cp <= 0x1dbf => L
    | cp when cp >= 0x1dc0 && cp <= 0x1dff => NSM
    | cp when cp >= 0x1e00 && cp <= 0x1fbc => L
    | cp when cp >= 0x1fbf && cp <= 0x1fc1 => ON
    | cp when cp >= 0x1fc2 && cp <= 0x1fcc => L
    | cp when cp >= 0x1fcd && cp <= 0x1fcf => ON
    | cp when cp >= 0x1fd0 && cp <= 0x1fdc => L
    | cp when cp >= 0x1fdd && cp <= 0x1fdf => ON
    | cp when cp >= 0x1fe0 && cp <= 0x1fec => L
    | cp when cp >= 0x1fed && cp <= 0x1ff1 => ON
    | cp when cp >= 0x1ff2 && cp <= 0x1ffc => L
    | cp when cp >= 0x1ffd && cp <= 0x1fff => ON
    | cp when cp >= 0x2000 && cp <= 0x200a => WS
    | cp when cp >= 0x200b && cp <= 0x200d => BN
    | cp when cp >= 0x2010 && cp <= 0x2027 => ON
    | cp when cp >= 0x2030 && cp <= 0x2034 => ET
    | cp when cp >= 0x2035 && cp <= 0x2043 => ON
    | cp when cp >= 0x2045 && cp <= 0x205e => ON
    | cp when cp >= 0x2060 && cp <= 0x2065 => BN
    | cp when cp >= 0x206a && cp <= 0x206f => BN
    | cp when cp >= 0x2071 && cp <= 0x2073 => L
    | cp when cp >= 0x2074 && cp <= 0x2079 => EN
    | cp when cp >= 0x207a && cp <= 0x207b => ES
    | cp when cp >= 0x207c && cp <= 0x207e => ON
    | cp when cp >= 0x2080 && cp <= 0x2089 => EN
    | cp when cp >= 0x208a && cp <= 0x208b => ES
    | cp when cp >= 0x208c && cp <= 0x208f => ON
    | cp when cp >= 0x2090 && cp <= 0x209f => L
    | cp when cp >= 0x20a0 && cp <= 0x20cf => ET
    | cp when cp >= 0x20d0 && cp <= 0x20ff => NSM
    | cp when cp >= 0x2100 && cp <= 0x2101 => ON
    | cp when cp >= 0x2103 && cp <= 0x2106 => ON
    | cp when cp >= 0x2108 && cp <= 0x2109 => ON
    | cp when cp >= 0x210a && cp <= 0x2113 => L
    | cp when cp >= 0x2116 && cp <= 0x2118 => ON
    | cp when cp >= 0x2119 && cp <= 0x211d => L
    | cp when cp >= 0x211e && cp <= 0x2123 => ON
    | cp when cp >= 0x212a && cp <= 0x212d => L
    | cp when cp >= 0x212f && cp <= 0x2139 => L
    | cp when cp >= 0x213a && cp <= 0x213b => ON
    | cp when cp >= 0x213c && cp <= 0x213f => L
    | cp when cp >= 0x2140 && cp <= 0x2144 => ON
    | cp when cp >= 0x2145 && cp <= 0x2149 => L
    | cp when cp >= 0x214a && cp <= 0x214d => ON
    | cp when cp >= 0x214e && cp <= 0x214f => L
    | cp when cp >= 0x2150 && cp <= 0x215f => ON
    | cp when cp >= 0x2160 && cp <= 0x2188 => L
    | cp when cp >= 0x2189 && cp <= 0x2211 => ON
    | cp when cp >= 0x2214 && cp <= 0x2335 => ON
    | cp when cp >= 0x2336 && cp <= 0x237a => L
    | cp when cp >= 0x237b && cp <= 0x2394 => ON
    | cp when cp >= 0x2396 && cp <= 0x2487 => ON
    | cp when cp >= 0x2488 && cp <= 0x249b => EN
    | cp when cp >= 0x249c && cp <= 0x24e9 => L
    | cp when cp >= 0x24ea && cp <= 0x26ab => ON
    | cp when cp >= 0x26ad && cp <= 0x27ff => ON
    | cp when cp >= 0x2800 && cp <= 0x28ff => L
    | cp when cp >= 0x2900 && cp <= 0x2bff => ON
    | cp when cp >= 0x2c00 && cp <= 0x2ce4 => L
    | cp when cp >= 0x2ce5 && cp <= 0x2cea => ON
    | cp when cp >= 0x2ceb && cp <= 0x2cee => L
    | cp when cp >= 0x2cef && cp <= 0x2cf1 => NSM
    | cp when cp >= 0x2cf2 && cp <= 0x2cf8 => L
    | cp when cp >= 0x2cf9 && cp <= 0x2cff => ON
    | cp when cp >= 0x2d00 && cp <= 0x2d7e => L
    | cp when cp >= 0x2d80 && cp <= 0x2ddf => L
    | cp when cp >= 0x2de0 && cp <= 0x2dff => NSM
    | cp when cp >= 0x2e00 && cp <= 0x2fff => ON
    | cp when cp >= 0x3001 && cp <= 0x3004 => ON
    | cp when cp >= 0x3005 && cp <= 0x3007 => L
    | cp when cp >= 0x3008 && cp <= 0x3020 => ON
    | cp when cp >= 0x3021 && cp <= 0x3029 => L
    | cp when cp >= 0x302a && cp <= 0x302d => NSM
    | cp when cp >= 0x302e && cp <= 0x302f => L
    | cp when cp >= 0x3031 && cp <= 0x3035 => L
    | cp when cp >= 0x3036 && cp <= 0x3037 => ON
    | cp when cp >= 0x3038 && cp <= 0x303c => L
    | cp when cp >= 0x303d && cp <= 0x3040 => ON
    | cp when cp >= 0x3041 && cp <= 0x3098 => L
    | cp when cp >= 0x3099 && cp <= 0x309a => NSM
    | cp when cp >= 0x309b && cp <= 0x309c => ON
    | cp when cp >= 0x309d && cp <= 0x309f => L
    | cp when cp >= 0x30a1 && cp <= 0x30fa => L
    | cp when cp >= 0x30fc && cp <= 0x31bf => L
    | cp when cp >= 0x31c0 && cp <= 0x31ef => ON
    | cp when cp >= 0x31f0 && cp <= 0x321c => L
    | cp when cp >= 0x321d && cp <= 0x321f => ON
    | cp when cp >= 0x3220 && cp <= 0x324f => L
    | cp when cp >= 0x3250 && cp <= 0x325f => ON
    | cp when cp >= 0x3260 && cp <= 0x327b => L
    | cp when cp >= 0x327c && cp <= 0x327e => ON
    | cp when cp >= 0x327f && cp <= 0x32b0 => L
    | cp when cp >= 0x32b1 && cp <= 0x32bf => ON
    | cp when cp >= 0x32c0 && cp <= 0x32cb => L
    | cp when cp >= 0x32cc && cp <= 0x32cf => ON
    | cp when cp >= 0x32d0 && cp <= 0x3376 => L
    | cp when cp >= 0x3377 && cp <= 0x337a => ON
    | cp when cp >= 0x337b && cp <= 0x33dd => L
    | cp when cp >= 0x33de && cp <= 0x33df => ON
    | cp when cp >= 0x33e0 && cp <= 0x33fe => L
    | cp when cp >= 0x3400 && cp <= 0x4dbf => L
    | cp when cp >= 0x4dc0 && cp <= 0x4dff => ON
    | cp when cp >= 0x4e00 && cp <= 0xa48f => L
    | cp when cp >= 0xa490 && cp <= 0xa4cf => ON
    | cp when cp >= 0xa4d0 && cp <= 0xa60c => L
    | cp when cp >= 0xa60d && cp <= 0xa60f => ON
    | cp when cp >= 0xa610 && cp <= 0xa66e => L
    | cp when cp >= 0xa66f && cp <= 0xa672 => NSM
    | cp when cp >= 0xa674 && cp <= 0xa67d => NSM
    | cp when cp >= 0xa67e && cp <= 0xa67f => ON
    | cp when cp >= 0xa680 && cp <= 0xa69d => L
    | cp when cp >= 0xa69e && cp <= 0xa69f => NSM
    | cp when cp >= 0xa6a0 && cp <= 0xa6ef => L
    | cp when cp >= 0xa6f0 && cp <= 0xa6f1 => NSM
    | cp when cp >= 0xa6f2 && cp <= 0xa6ff => L
    | cp when cp >= 0xa700 && cp <= 0xa721 => ON
    | cp when cp >= 0xa722 && cp <= 0xa787 => L
    | cp when cp >= 0xa789 && cp <= 0xa801 => L
    | cp when cp >= 0xa803 && cp <= 0xa805 => L
    | cp when cp >= 0xa807 && cp <= 0xa80a => L
    | cp when cp >= 0xa80c && cp <= 0xa824 => L
    | cp when cp >= 0xa825 && cp <= 0xa826 => NSM
    | cp when cp >= 0xa828 && cp <= 0xa82f => ON
    | cp when cp >= 0xa830 && cp <= 0xa837 => L
    | cp when cp >= 0xa838 && cp <= 0xa83f => ET
    | cp when cp >= 0xa840 && cp <= 0xa873 => L
    | cp when cp >= 0xa874 && cp <= 0xa87f => ON
    | cp when cp >= 0xa880 && cp <= 0xa8c3 => L
    | cp when cp >= 0xa8c4 && cp <= 0xa8cd => NSM
    | cp when cp >= 0xa8ce && cp <= 0xa8df => L
    | cp when cp >= 0xa8e0 && cp <= 0xa8f1 => NSM
    | cp when cp >= 0xa8f2 && cp <= 0xa8fe => L
    | cp when cp >= 0xa900 && cp <= 0xa925 => L
    | cp when cp >= 0xa926 && cp <= 0xa92d => NSM
    | cp when cp >= 0xa92e && cp <= 0xa946 => L
    | cp when cp >= 0xa947 && cp <= 0xa951 => NSM
    | cp when cp >= 0xa952 && cp <= 0xa97f => L
    | cp when cp >= 0xa980 && cp <= 0xa982 => NSM
    | cp when cp >= 0xa983 && cp <= 0xa9b2 => L
    | cp when cp >= 0xa9b4 && cp <= 0xa9b5 => L
    | cp when cp >= 0xa9b6 && cp <= 0xa9b9 => NSM
    | cp when cp >= 0xa9ba && cp <= 0xa9bb => L
    | cp when cp >= 0xa9bc && cp <= 0xa9bd => NSM
    | cp when cp >= 0xa9be && cp <= 0xa9e4 => L
    | cp when cp >= 0xa9e6 && cp <= 0xaa28 => L
    | cp when cp >= 0xaa29 && cp <= 0xaa2e => NSM
    | cp when cp >= 0xaa2f && cp <= 0xaa30 => L
    | cp when cp >= 0xaa31 && cp <= 0xaa32 => NSM
    | cp when cp >= 0xaa33 && cp <= 0xaa34 => L
    | cp when cp >= 0xaa35 && cp <= 0xaa3f => NSM
    | cp when cp >= 0xaa40 && cp <= 0xaa42 => L
    | cp when cp >= 0xaa44 && cp <= 0xaa4b => L
    | cp when cp >= 0xaa4d && cp <= 0xaa7b => L
    | cp when cp >= 0xaa7d && cp <= 0xaaaf => L
    | cp when cp >= 0xaab2 && cp <= 0xaab4 => NSM
    | cp when cp >= 0xaab5 && cp <= 0xaab6 => L
    | cp when cp >= 0xaab7 && cp <= 0xaab8 => NSM
    | cp when cp >= 0xaab9 && cp <= 0xaabd => L
    | cp when cp >= 0xaabe && cp <= 0xaabf => NSM
    | cp when cp >= 0xaac2 && cp <= 0xaaeb => L
    | cp when cp >= 0xaaec && cp <= 0xaaed => NSM
    | cp when cp >= 0xaaee && cp <= 0xaaf5 => L
    | cp when cp >= 0xaaf6 && cp <= 0xab00 => NSM
    | cp when cp >= 0xab01 && cp <= 0xabe4 => L
    | cp when cp >= 0xabe6 && cp <= 0xabe7 => L
    | cp when cp >= 0xabe9 && cp <= 0xabec => L
    | cp when cp >= 0xabed && cp <= 0xabef => NSM
    | cp when cp >= 0xabf0 && cp <= 0xfb1c => L
    | cp when cp >= 0xfb1f && cp <= 0xfb28 => R
    | cp when cp >= 0xfb2a && cp <= 0xfb4f => R
    | cp when cp >= 0xfb50 && cp <= 0xfd3d => AL
    | cp when cp >= 0xfd3e && cp <= 0xfd4f => ON
    | cp when cp >= 0xfd50 && cp <= 0xfdfc => AL
    | cp when cp >= 0xfdfd && cp <= 0xfdff => ON
    | cp when cp >= 0xfe00 && cp <= 0xfe0f => NSM
    | cp when cp >= 0xfe10 && cp <= 0xfe1f => ON
    | cp when cp >= 0xfe20 && cp <= 0xfe2f => NSM
    | cp when cp >= 0xfe30 && cp <= 0xfe4f => ON
    | cp when cp >= 0xfe52 && cp <= 0xfe53 => CS
    | cp when cp >= 0xfe56 && cp <= 0xfe5e => ON
    | cp when cp >= 0xfe60 && cp <= 0xfe61 => ON
    | cp when cp >= 0xfe62 && cp <= 0xfe63 => ES
    | cp when cp >= 0xfe64 && cp <= 0xfe68 => ON
    | cp when cp >= 0xfe69 && cp <= 0xfe6a => ET
    | cp when cp >= 0xfe6b && cp <= 0xfe6f => ON
    | cp when cp >= 0xfe70 && cp <= 0xfefe => AL
    | cp when cp >= 0xfeff && cp <= 0xff00 => BN
    | cp when cp >= 0xff01 && cp <= 0xff02 => ON
    | cp when cp >= 0xff03 && cp <= 0xff05 => ET
    | cp when cp >= 0xff06 && cp <= 0xff0a => ON
    | cp when cp >= 0xff0e && cp <= 0xff0f => CS
    | cp when cp >= 0xff10 && cp <= 0xff19 => EN
    | cp when cp >= 0xff1b && cp <= 0xff20 => ON
    | cp when cp >= 0xff21 && cp <= 0xff3a => L
    | cp when cp >= 0xff3b && cp <= 0xff40 => ON
    | cp when cp >= 0xff41 && cp <= 0xff5a => L
    | cp when cp >= 0xff5b && cp <= 0xff65 => ON
    | cp when cp >= 0xff66 && cp <= 0xffdf => L
    | cp when cp >= 0xffe0 && cp <= 0xffe1 => ET
    | cp when cp >= 0xffe2 && cp <= 0xffe4 => ON
    | cp when cp >= 0xffe5 && cp <= 0xffe7 => ET
    | cp when cp >= 0xffe8 && cp <= 0xffff => ON
    | cp when cp >= 0x10000 && cp <= 0x10100 => L
    | cp when cp >= 0x10102 && cp <= 0x1013f => L
    | cp when cp >= 0x10140 && cp <= 0x1018c => ON
    | cp when cp >= 0x1018d && cp <= 0x1018f => L
    | cp when cp >= 0x10190 && cp <= 0x101cf => ON
    | cp when cp >= 0x101d0 && cp <= 0x101fc => L
    | cp when cp >= 0x101fd && cp <= 0x1027f => NSM
    | cp when cp >= 0x10280 && cp <= 0x102df => L
    | cp when cp >= 0x102e1 && cp <= 0x102ff => EN
    | cp when cp >= 0x10300 && cp <= 0x10375 => L
    | cp when cp >= 0x10376 && cp <= 0x1037f => NSM
    | cp when cp >= 0x10380 && cp <= 0x107ff => L
    | cp when cp >= 0x10800 && cp <= 0x1091e => R
    | cp when cp >= 0x10920 && cp <= 0x10a00 => R
    | cp when cp >= 0x10a01 && cp <= 0x10a0f => NSM
    | cp when cp >= 0x10a10 && cp <= 0x10a37 => R
    | cp when cp >= 0x10a38 && cp <= 0x10a3f => NSM
    | cp when cp >= 0x10a40 && cp <= 0x10ae4 => R
    | cp when cp >= 0x10ae5 && cp <= 0x10aea => NSM
    | cp when cp >= 0x10aeb && cp <= 0x10b38 => R
    | cp when cp >= 0x10b39 && cp <= 0x10b3f => ON
    | cp when cp >= 0x10b40 && cp <= 0x10cff => R
    | cp when cp >= 0x10d00 && cp <= 0x10d23 => AL
    | cp when cp >= 0x10d24 && cp <= 0x10d2f => NSM
    | cp when cp >= 0x10d30 && cp <= 0x10eff => AN
    | cp when cp >= 0x10f00 && cp <= 0x10f2f => R
    | cp when cp >= 0x10f30 && cp <= 0x10f45 => AL
    | cp when cp >= 0x10f46 && cp <= 0x10f50 => NSM
    | cp when cp >= 0x10f51 && cp <= 0x10fdf => AL
    | cp when cp >= 0x10fe0 && cp <= 0x10fff => R
    | cp when cp >= 0x11002 && cp <= 0x11037 => L
    | cp when cp >= 0x11038 && cp <= 0x11046 => NSM
    | cp when cp >= 0x11047 && cp <= 0x11051 => L
    | cp when cp >= 0x11052 && cp <= 0x11065 => ON
    | cp when cp >= 0x11066 && cp <= 0x1107e => L
    | cp when cp >= 0x1107f && cp <= 0x11081 => NSM
    | cp when cp >= 0x11082 && cp <= 0x110b2 => L
    | cp when cp >= 0x110b3 && cp <= 0x110b6 => NSM
    | cp when cp >= 0x110b7 && cp <= 0x110b8 => L
    | cp when cp >= 0x110b9 && cp <= 0x110ba => NSM
    | cp when cp >= 0x110bb && cp <= 0x110ff => L
    | cp when cp >= 0x11100 && cp <= 0x11102 => NSM
    | cp when cp >= 0x11103 && cp <= 0x11126 => L
    | cp when cp >= 0x11127 && cp <= 0x1112b => NSM
    | cp when cp >= 0x1112d && cp <= 0x11135 => NSM
    | cp when cp >= 0x11136 && cp <= 0x11172 => L
    | cp when cp >= 0x11174 && cp <= 0x1117f => L
    | cp when cp >= 0x11180 && cp <= 0x11181 => NSM
    | cp when cp >= 0x11182 && cp <= 0x111b5 => L
    | cp when cp >= 0x111b6 && cp <= 0x111be => NSM
    | cp when cp >= 0x111bf && cp <= 0x111c8 => L
    | cp when cp >= 0x111c9 && cp <= 0x111cc => NSM
    | cp when cp >= 0x111cd && cp <= 0x1122e => L
    | cp when cp >= 0x1122f && cp <= 0x11231 => NSM
    | cp when cp >= 0x11232 && cp <= 0x11233 => L
    | cp when cp >= 0x11236 && cp <= 0x11237 => NSM
    | cp when cp >= 0x11238 && cp <= 0x1123d => L
    | cp when cp >= 0x1123e && cp <= 0x1127f => NSM
    | cp when cp >= 0x11280 && cp <= 0x112de => L
    | cp when cp >= 0x112e0 && cp <= 0x112e2 => L
    | cp when cp >= 0x112e3 && cp <= 0x112ef => NSM
    | cp when cp >= 0x112f0 && cp <= 0x112ff => L
    | cp when cp >= 0x11300 && cp <= 0x11301 => NSM
    | cp when cp >= 0x11302 && cp <= 0x1133a => L
    | cp when cp >= 0x1133b && cp <= 0x1133c => NSM
    | cp when cp >= 0x1133d && cp <= 0x1133f => L
    | cp when cp >= 0x11341 && cp <= 0x11365 => L
    | cp when cp >= 0x11366 && cp <= 0x113ff => NSM
    | cp when cp >= 0x11400 && cp <= 0x11437 => L
    | cp when cp >= 0x11438 && cp <= 0x1143f => NSM
    | cp when cp >= 0x11440 && cp <= 0x11441 => L
    | cp when cp >= 0x11442 && cp <= 0x11444 => NSM
    | cp when cp >= 0x11447 && cp <= 0x1145d => L
    | cp when cp >= 0x1145f && cp <= 0x114b2 => L
    | cp when cp >= 0x114b3 && cp <= 0x114b8 => NSM
    | cp when cp >= 0x114bb && cp <= 0x114be => L
    | cp when cp >= 0x114bf && cp <= 0x114c0 => NSM
    | cp when cp >= 0x114c2 && cp <= 0x114c3 => NSM
    | cp when cp >= 0x114c4 && cp <= 0x115b1 => L
    | cp when cp >= 0x115b2 && cp <= 0x115b7 => NSM
    | cp when cp >= 0x115b8 && cp <= 0x115bb => L
    | cp when cp >= 0x115bc && cp <= 0x115bd => NSM
    | cp when cp >= 0x115bf && cp <= 0x115c0 => NSM
    | cp when cp >= 0x115c1 && cp <= 0x115db => L
    | cp when cp >= 0x115dc && cp <= 0x115ff => NSM
    | cp when cp >= 0x11600 && cp <= 0x11632 => L
    | cp when cp >= 0x11633 && cp <= 0x1163a => NSM
    | cp when cp >= 0x1163b && cp <= 0x1163c => L
    | cp when cp >= 0x1163f && cp <= 0x11640 => NSM
    | cp when cp >= 0x11641 && cp <= 0x1165f => L
    | cp when cp >= 0x11660 && cp <= 0x1167f => ON
    | cp when cp >= 0x11680 && cp <= 0x116aa => L
    | cp when cp >= 0x116ae && cp <= 0x116af => L
    | cp when cp >= 0x116b0 && cp <= 0x116b5 => NSM
    | cp when cp >= 0x116b8 && cp <= 0x1171c => L
    | cp when cp >= 0x1171d && cp <= 0x1171f => NSM
    | cp when cp >= 0x11720 && cp <= 0x11721 => L
    | cp when cp >= 0x11722 && cp <= 0x11725 => NSM
    | cp when cp >= 0x11727 && cp <= 0x1172f => NSM
    | cp when cp >= 0x11730 && cp <= 0x1182e => L
    | cp when cp >= 0x1182f && cp <= 0x11837 => NSM
    | cp when cp >= 0x11839 && cp <= 0x1183a => NSM
    | cp when cp >= 0x1183b && cp <= 0x119d3 => L
    | cp when cp >= 0x119d4 && cp <= 0x119db => NSM
    | cp when cp >= 0x119dc && cp <= 0x119df => L
    | cp when cp >= 0x119e1 && cp <= 0x11a00 => L
    | cp when cp >= 0x11a01 && cp <= 0x11a06 => NSM
    | cp when cp >= 0x11a07 && cp <= 0x11a08 => L
    | cp when cp >= 0x11a09 && cp <= 0x11a0a => NSM
    | cp when cp >= 0x11a0b && cp <= 0x11a32 => L
    | cp when cp >= 0x11a33 && cp <= 0x11a38 => NSM
    | cp when cp >= 0x11a39 && cp <= 0x11a3a => L
    | cp when cp >= 0x11a3b && cp <= 0x11a3e => NSM
    | cp when cp >= 0x11a3f && cp <= 0x11a46 => L
    | cp when cp >= 0x11a47 && cp <= 0x11a4f => NSM
    | cp when cp >= 0x11a51 && cp <= 0x11a56 => NSM
    | cp when cp >= 0x11a57 && cp <= 0x11a58 => L
    | cp when cp >= 0x11a59 && cp <= 0x11a5b => NSM
    | cp when cp >= 0x11a5c && cp <= 0x11a89 => L
    | cp when cp >= 0x11a8a && cp <= 0x11a96 => NSM
    | cp when cp >= 0x11a98 && cp <= 0x11a99 => NSM
    | cp when cp >= 0x11a9a && cp <= 0x11c2f => L
    | cp when cp >= 0x11c30 && cp <= 0x11c3d => NSM
    | cp when cp >= 0x11c3e && cp <= 0x11c91 => L
    | cp when cp >= 0x11c92 && cp <= 0x11ca8 => NSM
    | cp when cp >= 0x11caa && cp <= 0x11cb0 => NSM
    | cp when cp >= 0x11cb2 && cp <= 0x11cb3 => NSM
    | cp when cp >= 0x11cb5 && cp <= 0x11cff => NSM
    | cp when cp >= 0x11d00 && cp <= 0x11d30 => L
    | cp when cp >= 0x11d31 && cp <= 0x11d45 => NSM
    | cp when cp >= 0x11d47 && cp <= 0x11d4f => NSM
    | cp when cp >= 0x11d50 && cp <= 0x11d8f => L
    | cp when cp >= 0x11d90 && cp <= 0x11d92 => NSM
    | cp when cp >= 0x11d93 && cp <= 0x11d94 => L
    | cp when cp >= 0x11d98 && cp <= 0x11ef2 => L
    | cp when cp >= 0x11ef3 && cp <= 0x11ef4 => NSM
    | cp when cp >= 0x11ef5 && cp <= 0x11fd4 => L
    | cp when cp >= 0x11fd5 && cp <= 0x11fdc => ON
    | cp when cp >= 0x11fdd && cp <= 0x11fe0 => ET
    | cp when cp >= 0x11fe1 && cp <= 0x11ffe => ON
    | cp when cp >= 0x11fff && cp <= 0x16aef => L
    | cp when cp >= 0x16af0 && cp <= 0x16af4 => NSM
    | cp when cp >= 0x16af5 && cp <= 0x16b2f => L
    | cp when cp >= 0x16b30 && cp <= 0x16b36 => NSM
    | cp when cp >= 0x16b37 && cp <= 0x16f4e => L
    | cp when cp >= 0x16f50 && cp <= 0x16f8e => L
    | cp when cp >= 0x16f8f && cp <= 0x16f92 => NSM
    | cp when cp >= 0x16f93 && cp <= 0x16fe1 => L
    | cp when cp >= 0x16fe3 && cp <= 0x1bc9c => L
    | cp when cp >= 0x1bc9d && cp <= 0x1bc9e => NSM
    | cp when cp >= 0x1bca0 && cp <= 0x1cfff => BN
    | cp when cp >= 0x1d000 && cp <= 0x1d166 => L
    | cp when cp >= 0x1d167 && cp <= 0x1d169 => NSM
    | cp when cp >= 0x1d16a && cp <= 0x1d172 => L
    | cp when cp >= 0x1d173 && cp <= 0x1d17a => BN
    | cp when cp >= 0x1d17b && cp <= 0x1d182 => NSM
    | cp when cp >= 0x1d183 && cp <= 0x1d184 => L
    | cp when cp >= 0x1d185 && cp <= 0x1d18b => NSM
    | cp when cp >= 0x1d18c && cp <= 0x1d1a9 => L
    | cp when cp >= 0x1d1aa && cp <= 0x1d1ad => NSM
    | cp when cp >= 0x1d1ae && cp <= 0x1d1ff => L
    | cp when cp >= 0x1d200 && cp <= 0x1d241 => ON
    | cp when cp >= 0x1d242 && cp <= 0x1d244 => NSM
    | cp when cp >= 0x1d245 && cp <= 0x1d2df => ON
    | cp when cp >= 0x1d2e0 && cp <= 0x1d2ff => L
    | cp when cp >= 0x1d300 && cp <= 0x1d35f => ON
    | cp when cp >= 0x1d360 && cp <= 0x1d6da => L
    | cp when cp >= 0x1d6dc && cp <= 0x1d714 => L
    | cp when cp >= 0x1d716 && cp <= 0x1d74e => L
    | cp when cp >= 0x1d750 && cp <= 0x1d788 => L
    | cp when cp >= 0x1d78a && cp <= 0x1d7c2 => L
    | cp when cp >= 0x1d7c4 && cp <= 0x1d7cd => L
    | cp when cp >= 0x1d7ce && cp <= 0x1d7ff => EN
    | cp when cp >= 0x1d800 && cp <= 0x1d9ff => L
    | cp when cp >= 0x1da00 && cp <= 0x1da36 => NSM
    | cp when cp >= 0x1da37 && cp <= 0x1da3a => L
    | cp when cp >= 0x1da3b && cp <= 0x1da6c => NSM
    | cp when cp >= 0x1da6d && cp <= 0x1da74 => L
    | cp when cp >= 0x1da76 && cp <= 0x1da83 => L
    | cp when cp >= 0x1da85 && cp <= 0x1da9a => L
    | cp when cp >= 0x1da9b && cp <= 0x1e0ff => NSM
    | cp when cp >= 0x1e100 && cp <= 0x1e12f => L
    | cp when cp >= 0x1e130 && cp <= 0x1e136 => NSM
    | cp when cp >= 0x1e137 && cp <= 0x1e2eb => L
    | cp when cp >= 0x1e2ec && cp <= 0x1e2ef => NSM
    | cp when cp >= 0x1e2f0 && cp <= 0x1e2fe => L
    | cp when cp >= 0x1e2ff && cp <= 0x1e7ff => ET
    | cp when cp >= 0x1e800 && cp <= 0x1e8cf => R
    | cp when cp >= 0x1e8d0 && cp <= 0x1e8ff => NSM
    | cp when cp >= 0x1e900 && cp <= 0x1e943 => R
    | cp when cp >= 0x1e944 && cp <= 0x1e94a => NSM
    | cp when cp >= 0x1e94b && cp <= 0x1ec70 => R
    | cp when cp >= 0x1ec71 && cp <= 0x1eeef => AL
    | cp when cp >= 0x1eef0 && cp <= 0x1f0ff => ON
    | cp when cp >= 0x1f100 && cp <= 0x1f10a => EN
    | cp when cp >= 0x1f10b && cp <= 0x1f10f => ON
    | cp when cp >= 0x1f110 && cp <= 0x1f12e => L
    | cp when cp >= 0x1f130 && cp <= 0x1f169 => L
    | cp when cp >= 0x1f16a && cp <= 0x1f16f => ON
    | cp when cp >= 0x1f170 && cp <= 0x1f25f => L
    | cp when cp >= 0x1f260 && cp <= 0x1ffff => ON
    | cp when cp >= 0x20000 && cp <= 0xe0000 => L
    | cp when cp >= 0xe0001 && cp <= 0xe00ff => BN
    | cp when cp >= 0xe0100 && cp <= 0xeffff => NSM
    | _cp => Illegal
    };
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

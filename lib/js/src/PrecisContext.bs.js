// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var PrecisCodePoints$BsPrecis = require("./PrecisCodePoints.bs.js");

var viramas = /* :: */[
  2381,
  /* :: */[
    2509,
    /* :: */[
      2637,
      /* :: */[
        2765,
        /* :: */[
          2893,
          /* :: */[
            3021,
            /* :: */[
              3149,
              /* :: */[
                3277,
                /* :: */[
                  3387,
                  /* :: */[
                    3388,
                    /* :: */[
                      3405,
                      /* :: */[
                        3972,
                        /* :: */[
                          4153,
                          /* :: */[
                            5908,
                            /* :: */[
                              7083,
                              /* :: */[
                                43204,
                                /* :: */[
                                  43251,
                                  /* :: */[
                                    43252,
                                    /* :: */[
                                      43347,
                                      /* :: */[
                                        43766,
                                        /* :: */[
                                          68159,
                                          /* :: */[
                                            69702,
                                            /* :: */[
                                              69817,
                                              /* :: */[
                                                69939,
                                                /* :: */[
                                                  70080,
                                                  /* :: */[
                                                    70197,
                                                    /* :: */[
                                                      70378,
                                                      /* :: */[
                                                        70477,
                                                        /* :: */[
                                                          70722,
                                                          /* :: */[
                                                            70850,
                                                            /* :: */[
                                                              71103,
                                                              /* [] */0
                                                            ]
                                                          ]
                                                        ]
                                                      ]
                                                    ]
                                                  ]
                                                ]
                                              ]
                                            ]
                                          ]
                                        ]
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]
  ]
];

function greek(cp) {
  if (cp >= 834 && cp <= 1023) {
    return true;
  } else if (cp >= 7462) {
    return cp <= 8190;
  } else {
    return false;
  }
}

function hebrew(cp) {
  if (cp >= 1425) {
    return cp <= 1524;
  } else {
    return false;
  }
}

function hiragana(cps) {
  return List.fold_left((function (a, cp) {
                if (a) {
                  var cp$1 = cp;
                  if (cp$1 >= 12353) {
                    return cp$1 <= 12448;
                  } else {
                    return false;
                  }
                } else {
                  return false;
                }
              }), true, cps);
}

function katakana(cps) {
  return List.fold_left((function (a, cp) {
                if (a) {
                  var cp$1 = cp;
                  if (cp$1 >= 12441) {
                    return cp$1 <= 12799;
                  } else {
                    return false;
                  }
                } else {
                  return false;
                }
              }), true, cps);
}

function arabicIndicDigits(param) {
  return List.fold_left((function (v, cp) {
                if (v) {
                  return !(cp >= 1776 && cp <= 1785);
                } else {
                  return false;
                }
              }), true, param);
}

function context(codePointList) {
  var _codePointList = codePointList;
  var _precisCodePoints = List.map(PrecisCodePoints$BsPrecis.fromCodePoint, codePointList);
  var _acc = /* [] */0;
  var _precisAcc = /* [] */0;
  while(true) {
    var precisAcc = _precisAcc;
    var acc = _acc;
    var precisCodePoints = _precisCodePoints;
    var codePointList$1 = _codePointList;
    if (precisCodePoints) {
      var precisTail = precisCodePoints[1];
      var cc = precisCodePoints[0];
      var exit = 0;
      if (precisTail) {
        var match = precisTail[0];
        if (match >= 2) {
          exit = 1;
        } else {
          var match$1 = precisTail[1];
          if (match$1) {
            var precisTail$1 = match$1[1];
            var cc2 = match$1[0];
            if (codePointList$1) {
              var match$2 = codePointList$1[1];
              if (match$2) {
                var cpTail = match$2[1];
                var cp2 = match$2[0];
                var cp1 = codePointList$1[0];
                var exit$1 = 0;
                var exit$2 = 0;
                if (cpTail && cp2 === 183) {
                  var cp3 = cpTail[0];
                  if (cp1 === 183 && cp1 === cp3) {
                    _precisAcc = Pervasives.$at(/* :: */[
                          cc2,
                          /* :: */[
                            match,
                            /* :: */[
                              cc,
                              /* [] */0
                            ]
                          ]
                        ], precisAcc);
                    _acc = Pervasives.$at(/* :: */[
                          cp3,
                          /* :: */[
                            cp2,
                            /* :: */[
                              cp1,
                              /* [] */0
                            ]
                          ]
                        ], acc);
                    _precisCodePoints = precisTail$1;
                    _codePointList = cpTail[1];
                    continue ;
                  } else {
                    return false;
                  }
                } else {
                  exit$2 = 3;
                }
                if (exit$2 === 3) {
                  if (cp2 === 8204) {
                    if (List.mem(cp1, viramas) || false) {
                      _precisAcc = Pervasives.$at(/* :: */[
                            match,
                            /* :: */[
                              cc,
                              /* [] */0
                            ]
                          ], precisAcc);
                      _acc = Pervasives.$at(/* :: */[
                            cp2,
                            /* :: */[
                              cp1,
                              /* [] */0
                            ]
                          ], acc);
                      _precisCodePoints = Pervasives.$at(/* :: */[
                            cc2,
                            /* [] */0
                          ], precisTail$1);
                      _codePointList = cpTail;
                      continue ;
                    } else {
                      return false;
                    }
                  } else if (cp2 === 8205) {
                    if (List.mem(cp1, viramas)) {
                      _precisAcc = Pervasives.$at(/* :: */[
                            match,
                            /* :: */[
                              cc,
                              /* [] */0
                            ]
                          ], precisAcc);
                      _acc = Pervasives.$at(/* :: */[
                            cp2,
                            /* :: */[
                              cp1,
                              /* [] */0
                            ]
                          ], acc);
                      _precisCodePoints = Pervasives.$at(/* :: */[
                            cc2,
                            /* [] */0
                          ], precisTail$1);
                      _codePointList = cpTail;
                      continue ;
                    } else {
                      return false;
                    }
                  } else if (cp2 === 1523 || cp2 === 1524) {
                    if (hebrew(cp1)) {
                      _precisAcc = Pervasives.$at(/* :: */[
                            match,
                            /* :: */[
                              cc,
                              /* [] */0
                            ]
                          ], precisAcc);
                      _acc = Pervasives.$at(/* :: */[
                            cp2,
                            /* :: */[
                              cp1,
                              /* [] */0
                            ]
                          ], acc);
                      _precisCodePoints = Pervasives.$at(/* :: */[
                            cc2,
                            /* [] */0
                          ], precisTail$1);
                      _codePointList = cpTail;
                      continue ;
                    } else {
                      return false;
                    }
                  } else if (cpTail && cp2 === 885) {
                    var cp3$1 = cpTail[0];
                    if (greek(cp3$1)) {
                      _precisAcc = Pervasives.$at(/* :: */[
                            cc2,
                            /* :: */[
                              match,
                              /* :: */[
                                cc,
                                /* [] */0
                              ]
                            ]
                          ], precisAcc);
                      _acc = Pervasives.$at(/* :: */[
                            cp3$1,
                            /* :: */[
                              cp2,
                              /* :: */[
                                cp1,
                                /* [] */0
                              ]
                            ]
                          ], acc);
                      _precisCodePoints = precisTail$1;
                      _codePointList = cpTail[1];
                      continue ;
                    } else {
                      return false;
                    }
                  } else {
                    exit$1 = 2;
                  }
                }
                if (exit$1 === 2) {
                  if (cp2 === 12539) {
                    if (hiragana(Pervasives.$at(acc, codePointList$1)) || katakana(Pervasives.$at(acc, codePointList$1)) || (Pervasives.$at(acc, codePointList$1), false)) {
                      _precisAcc = Pervasives.$at(/* :: */[
                            match,
                            /* :: */[
                              cc,
                              /* [] */0
                            ]
                          ], precisAcc);
                      _acc = Pervasives.$at(/* :: */[
                            cp2,
                            /* :: */[
                              cp1,
                              /* [] */0
                            ]
                          ], acc);
                      _precisCodePoints = Pervasives.$at(/* :: */[
                            cc2,
                            /* [] */0
                          ], precisTail$1);
                      _codePointList = cpTail;
                      continue ;
                    } else {
                      return false;
                    }
                  } else if (cp2 >= 1632 && cp2 <= 1641 && arabicIndicDigits(Pervasives.$at(acc, codePointList$1))) {
                    _precisAcc = Pervasives.$at(/* :: */[
                          match,
                          /* :: */[
                            cc,
                            /* [] */0
                          ]
                        ], precisAcc);
                    _acc = Pervasives.$at(/* :: */[
                          cp2,
                          /* :: */[
                            cp1,
                            /* [] */0
                          ]
                        ], acc);
                    _precisCodePoints = Pervasives.$at(/* :: */[
                          cc2,
                          /* [] */0
                        ], precisTail$1);
                    _codePointList = cpTail;
                    continue ;
                  } else {
                    return false;
                  }
                }
                
              } else {
                return false;
              }
            } else {
              return false;
            }
          } else {
            exit = 1;
          }
        }
      } else {
        exit = 1;
      }
      if (exit === 1) {
        _precisAcc = Pervasives.$at(/* :: */[
              cc,
              /* [] */0
            ], precisAcc);
        _acc = Pervasives.$at(/* :: */[
              List.hd(codePointList$1),
              /* [] */0
            ], acc);
        _precisCodePoints = precisTail;
        _codePointList = List.tl(codePointList$1);
        continue ;
      }
      
    } else {
      return true;
    }
  };
}

exports.context = context;
/* No side effect */
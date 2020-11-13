#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 20 May 2019
# Precis Code-Generator ReasonML
# https://github.com/NineFX/smeagol/blob/master/spec/code_gen/precis_cp.txt

fp = open('unicodedata.txt', 'r')

ranges = []

line = fp.readline()
lowercase = {}
prev = ""
start = 0
a = set()

while line:
  line = fp.readline()
  if len(line) < 2: break
  linesplit = line.split(";")
  code = linesplit[4]
  if code != prev:
    value = int(linesplit[0],16)
    ranges.append((start, value, prev if len(prev) != 0 else "Illegal"))
    start = value
    prev = code

def splitHalf(listy):
    if len(listy) <= 2:
        print("switch (point) {")
        for item in listy:
            if item[0] == item[1] - 1:
                print(" | point when (point == " + str(item[0]) + ") => " + str(item[2]))
            else:
                print(" | point when (point >= " + str(item[0]) + " && point < " + str(item[1]) +") => " + str(item[2]))
        print("| _point => raise(PrecisUtils.PrecisError(BidiError))")
        print("}")
        return
    splitValue = listy[len(listy)//2]
    firstHalf = listy[:len(listy)//2]
    secondHalf = listy[len(listy)//2:]
    print("if (point < " +str(splitValue[0]) + ") {")
    splitHalf(firstHalf)
    print("} else {")
    splitHalf(secondHalf)
    print("}")
splitHalf(ranges)

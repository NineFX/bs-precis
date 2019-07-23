#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 31 May 2019
# Precis Code-Generator ReasonML
# https://github.com/NineFX/smeagol/blob/master/spec/code_gen/precis_cp.txt

fp = open('unicodedata.txt', 'r')

ranges = []

line = fp.readline()
lowercase = {}

while line:
  line = fp.readline()
  if len(line) < 2: break
  linesplit = line.split(";")
  lowermapping = linesplit[13]
  if lowermapping:
    lowermap = int(lowermapping, 16)
    original = int(linesplit[0], 16)
    ranges.append([original, lowermap])

def splitHalf(listy):
  if(len(listy) <= 2):
    print("switch (point) { ")
    for item in listy:
      print("| " + str(item[0]) + " => " + str(item[1]))
    print("| point => point")
    print("}")
    return  
  splitValue = listy[len(listy)//2]
  firstHalf = listy[:(len(listy))//2]
  secondHalf = listy[(len(listy))//2:]
  print("if (point < "+str(splitValue[0]) +")")
  print("{")
  splitHalf(firstHalf)
  print("} else {")
  splitHalf(secondHalf)
  print("}")
 
splitHalf(ranges)

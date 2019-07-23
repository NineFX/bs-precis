#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 3 June 2019
# Precis Code-Generator ReasonML
# https://github.com/NineFX/smeagol/blob/master/spec/code_gen/precis_cp.txt

fp = open('precis_cp.txt', 'r')

ranges = []

line = fp.readline()
code = "DISALLOWED"
prev = "DISALLOWED"
firstOccurence = 0
count = 0

while line:
  count += 1
  line = fp.readline()
  if len(line) < 2: break
  linesplit = line.split(";")
  codepoint = int(linesplit[0])
  code = linesplit[1][:-1]
  if code != prev:
    ranges.append([firstOccurence, codepoint - 1, prev])
    firstOccurence = count
    prev = code
ranges.append([firstOccurence, count, code])

# Binary Tree

def splitHalf(listy):
  if(len(listy) <= 2):
    print("switch (point) { ")
    for item in listy:
      print("| point when (point >= " + str(item[0]) + ") && (point <= " + str(item[1]) + ") =>" + item[2])
    print("| _point => DISALLOWED")
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
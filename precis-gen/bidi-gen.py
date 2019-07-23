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
    if(start == value - 1):
        print ("| cp when cp == " +  hex(start) + " =>" + (prev if len(prev) == 0 else " Illegal"))
    else:
      print("| cp when cp >= "+ hex(start) + " && cp <= " + hex(value - 1) + " => "+ prev)
    start = value
    prev = code

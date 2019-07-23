#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 13 May 2019
# Precis Code-Generator ReasonML
# https://github.com/NineFX/smeagol/blob/master/spec/code_gen/precis_cp.txt

fp = open('unicodedata.txt', 'r')

ranges = []

line = fp.readline()

while line:
  line = fp.readline()
  if len(line) < 2: break
  linesplit = line.split(";")
  print("|> add(0x" + linesplit[0] + ", " + str(linesplit[1:13]) + ")")

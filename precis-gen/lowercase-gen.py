#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 13 May 2019
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
    if lowermap in lowercase:
      lowercase[lowermap].append(original)
    else:
      lowercase[lowermap] = [original]

for key in lowercase.keys():
  for i, mapping in enumerate(lowercase[key]):
    # Realized there were no repeats, so the logic may seem backwards
    print("| key when key == " + hex(mapping) + " => " + hex(key))

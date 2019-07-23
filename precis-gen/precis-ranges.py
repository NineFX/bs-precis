#!/usr/local/bin/python3
# Copyright 2019 NineFx Inc.
# Justin Baum
# 13 May 2019
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

CONTEXTO = "| x when "
CONTEXTJ = "| x when "
PVALID = "| x when "
UNASSIGNED = "| x when "
FREE_PVAL = "| x when "
DISALLOWED = "| x when "

for i in range(len(ranges)):
  if (ranges[i][0] != ranges[i][1]):
    s = "(x >= " + str(ranges[i][0]) + " && x <= " + str(ranges[i][1]) + ") ||" 
  else:
    s = "(x == " + str(ranges[i][0]) + ") ||"
  if ranges[i][2] == "CONTEXTO":
    CONTEXTO += s + "\n"
  elif ranges[i][2] == "CONTEXTJ":
    CONTEXTJ += s + "\n"
  elif ranges[i][2] == "PVALID":
    PVALID += s + "\n"
  elif ranges[i][2] == "UNASSIGNED":
    UNASSIGNED += s + "\n"
  elif ranges[i][2] == "FREE_PVAL":
    FREE_PVAL += s + "\n"
  elif ranges[i][2] == "DISALLOWED":
    DISALLOWED += s + "\n"
  else:
    raise(Exception("There's a missing "))

CONTEXTO = CONTEXTO[:-4] + " => CONTEXTO"
CONTEXTJ = CONTEXTJ[:-4] +" => CONTEXTJ"
PVALID = PVALID[:-4] + " => PVALID"
UNASSIGNED = UNASSIGNED[:-4] +  " => UNASSIGNED"
FREE_PVAL = FREE_PVAL[:-4] + " => FREEPVAL"
DISALLOWED = DISALLOWED[:-4] + " => DISALLOWED"

print("switch x {")
print(CONTEXTO)
print(CONTEXTJ)
print(PVALID)
print(UNASSIGNED)
print(FREE_PVAL)
print(DISALLOWED)
print("}")

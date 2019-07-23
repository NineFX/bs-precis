# Copyright 2019
# NineFX Inc.
# generate-json-tests.py
# Justin Baum
# 22 July 2019

import json
import precis_i18n as precis
import sys
import random

def byte_range(first, last):
    return list(range(first, last+1))

first_values = byte_range(0x00, 0x7F) + byte_range(0xC2, 0xF4)
trailing_values = byte_range(0x80, 0xBF)

def random_utf8_seq():
    first = random.choice(first_values)
    if first <= 0x7F:
        return bytes([first])
    elif first <= 0xDF:
        return bytes([first, random.choice(trailing_values)])
    elif first == 0xE0:
        return bytes([first, random.choice(byte_range(0xA0, 0xBF)), random.choice(trailing_values)])
    elif first == 0xED:
        return bytes([first, random.choice(byte_range(0x80, 0x9F)), random.choice(trailing_values)])
    elif first <= 0xEF:
        return bytes([first, random.choice(trailing_values), random.choice(trailing_values)])
    elif first == 0xF0:
        return bytes([first, random.choice(byte_range(0x90, 0xBF)), random.choice(trailing_values), random.choice(trailing_values)])
    elif first <= 0xF3:
        return bytes([first, random.choice(trailing_values), random.choice(trailing_values), random.choice(trailing_values)])
    elif first == 0xF4:
        return bytes([first, random.choice(byte_range(0x80, 0x8F)), random.choice(trailing_values), random.choice(trailing_values)])

def get_random():
    return ("".join(str(random_utf8_seq(), "utf8") for i in range(3)))

profiles = ["UsernameCasePreserved", "UsernameCaseMapped", "NicknameCaseMapped", "OpaqueString"]

tests = []
if len(sys.argv) == 1:
   exit(1) 

for i in range(int(sys.argv[1])):
    nput = get_random()
    for profile in profiles:
        precisprofile = precis.get_profile(profile)
        try:
            output = precisprofile.enforce(nput)
        except:
            output = None
        tests.append({"profile": profile, "input":nput, "output":output, "error":None})
print(json.dumps(tests))

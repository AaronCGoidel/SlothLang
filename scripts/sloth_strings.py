#!/usr/bin/env python3
import sys

text = " ".join(sys.argv[1:])

for ch in text:
    print("slothy {} # push character '{}'".format("sloth " * ord(ch), ch))
    print("sloth sloth sloth sloth sloth sloth sloth sloth and sloth sloth")

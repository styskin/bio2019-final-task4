#!/usr/bin/env python

import sys

for line in sys.stdin.readlines():
    line = line.strip()
    print line[::-1]

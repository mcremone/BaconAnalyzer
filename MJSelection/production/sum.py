#!/usr/bin/env python
# -*- coding: utf-8 -*

file = open ("size", "r")
sum = 0
for aline in file:
    if aline.find("size")!=-1:
        file_line_values = aline.split("=")
        sum = sum + float(file_line_values[1])

print sum/1024/1024/1024/1024

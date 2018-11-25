#!/usr/bin/python
# -*- coding: utf-8 -*-
import os

fh = open('commands1.txt')
for line in fh:
    # in python 2
    # print line
    # in python 3
    name, text = line.split("\t")
    print(name)
    print(text)
    os.system('espeak -v et \"' + text + '!\" --stdout | lame -b128 - ' + name +'.mp3')
fh.close()
 

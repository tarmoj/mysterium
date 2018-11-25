#!/usr/bin/python
# -*- coding: utf-8 -*-
import os

fh = open('commands1.txt')
for line in fh:
	messageParts = line.split("\t")
	name = messageParts[0]
	text = messageParts[1].rstrip("\n")
	print(name)
	print(text)
	if len(messageParts)>=2:
		#os.system('espeak -v et -s 250 \"' + text + '!\"') # kuula
		os.system('espeak -v et -s 250 \"' + text + '!\" --stdout | lame -b128 - ' + name +'.mp3') #mp3
fh.close()
 

#!/usr/bin/env python

import time

def test1(index):
	print "Now in Python", index
	yield index
	print "Now in Python", index + 1
	yield index+1
	print "Now in Python", index + 2
    	yield index+2
    	print "Now in Python", index + 3
	yield index+3

f = None
def start(index):
    	global f
	f = test1(index)
    	return
def resume():
	return f.next()
	

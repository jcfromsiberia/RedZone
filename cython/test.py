#!/usr/bin/env python
#-*- coding: utf-8 -*-
__author__ = 'jc'

from RedZone import *

with open('test.json', 'rt') as f:
    json = eval(f.read().replace("true", "True").replace("false", "False").replace("null", "None"))

    context = Context(json)
    tpl = FileTemplate('test.tpl')

    print tpl.render(context)

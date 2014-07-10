#!/usr/bin/env python
#-*- coding: utf-8 -*-
__author__ = 'jc'

from RedZone import *

from RedZone import *

context = Context({
    "items": [
        {"text": "Hello World!", "active": True},
        {"text": "Foo", "active": True},
        {"text": "Bar", "active": False}
    ],
    "numbers": {
        "first": 5,
        "second": 11,
        "third": True
    }
})
tpl = FileTemplate('test.tpl')

print tpl.render(context)

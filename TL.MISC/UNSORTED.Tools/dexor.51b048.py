#!/usr/local/bin/python
# coding: utf-8
import os, sys
decrypt = sys.argv[1].decode('string_escape')
done = ""
table_key = 0xd6d5c56d
k1 = table_key & 0xff
k2 = (table_key >> 8) & 0xff
k3 = (table_key >> 16) & 0xff
k4 = (table_key >> 24) & 0xff
for words in decrypt: done += str(unichr((((ord(words) ^ k1) ^ k2) ^k3) ^ k4))
print "Decryped string:", done

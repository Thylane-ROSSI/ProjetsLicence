#!/usr/bin/env python3

from scapy.all import *
a = IP()
a.dst = '1.2.3.4'
b = ICMP()

for i in range(1,65):
	a.ttl = i
	send(a/b)

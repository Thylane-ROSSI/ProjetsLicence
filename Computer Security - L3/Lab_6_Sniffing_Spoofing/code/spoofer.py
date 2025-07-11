#!/usr/bin/env python3

from scapy.all import *
a = IP(src='10.9.0.1') 
b = ICMP() 
p = a/b
send(p)

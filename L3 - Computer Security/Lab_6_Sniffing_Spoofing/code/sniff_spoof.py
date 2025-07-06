From scapy.all import *
  
def spoof_pkt(pkt):
    print(pkt[IP].src)
    print(pkt[IP].dst)
    pkt.show()

    a = IP(src=pkt[IP].dst, dst=pkt[IP].src, ihl=pkt[IP].ihl)
    b = ICMP(type=0, seq=pkt[ICMP].seq, id=pkt[ICMP].id)
    new_pkt = a/b/pkt[Raw]

    print(  new_pkt[IP].src    )
    print(  new_pkt[IP].dst    )

    send(new_pkt)

pkt = sniff(filter="icmp", prn=spoof_pkt)

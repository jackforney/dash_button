#Code from Ted Benson's medium.com article:
#"How I Hacked Amazon’s $5 WiFi Button to track Baby Data"

from scapy.all import *

def arp_display(pkt):
  if pkt[ARP].op == 1: #who-has (request)
    if pkt[ARP].psrc == '0.0.0.0': # ARP Probe
      print "ARP Probe from: " + pkt[ARP].hwsrc # 

print sniff(prn=arp_display, filter="arp", store=0, count=10)

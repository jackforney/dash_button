#Similar to find_dashbutton.py
#Prints defined name of dashbutton using hard-coded MAC address

from scapy.all import *

def arp_display(pkt):
  if pkt[ARP].op == 1: #who-has (request)
    if pkt[ARP].psrc == '0.0.0.0': # ARP Probe
      if pkt[ARP].hwsrc == 'a0:02:dc:0c:43:d3':  #detect button-specific MAC Address
        print 'Pressed ON Button'
      #elif pkt[ARP].hwsrc == '<another MAC Address>':
        #print 'Press <another button>'
      else:
        print "ARP Probe from: " + pkt[ARP].hwsrc

print sniff(prn=arp_display, filter="arp", store=0, count=10)

'''
Sends SMS text on press of dash button
'''

from scapy.all import *
from twilio.rest import TwilioRestClient

account_sid = "<ACCOUNT_ID>"  #twilio account ID
auth_token = "<AUTH_TOKEN>"   #twilio authentication token
client = TwilioRestClient(account_sid, auth_token)

def sendSMS():
  client.messages.create(
	to="<SEND-TO NUMBER>",      
	from_="<SEND-FROM NUMBER>", #this must be a twilio number
	body="Sent using an Amazon Dash Button!",  #body of text
)
  print "message sent"
  return


def arp_display(pkt):
  if pkt[ARP].op == 1: 
    if pkt[ARP].psrc == '0.0.0.0':
      if pkt[ARP].hwsrc == 'a0:02:dc:0c:43:d3': #is recognized as my dash button
        sendSMS()

while True:
  print sniff(prn=arp_display, filter="arp", store=0, count=10)




# simple_linux_network_bandwith
Very simple linux network interface monitor
# RUN
```bash
$./net_bandwith -h
Usage: ./net_bandwith
	-h        // help 
	-l        // list interfaces
	-m        // unit: mbps
	-k        // unit: kbps
	-b        // unit: bps
	-a <nic>  // add nic to report list
	-n <time> // time in secound. default infinit
  
$./net_bandwith -a eth0 -a eth1
##############
Interfaces: eth0	eth1	
Unit: mbps
Loop: infinit
##############
NIC(TX,RX): eth0(0.0, 0.0)  eth1(0.0, 0.0)  
NIC(TX,RX): eth0(506.7, 5203.8)  eth1(5154.8, 464.8)  
NIC(TX,RX): eth0(510.9, 5311.2)  eth1(5265.5, 472.1)  
NIC(TX,RX): eth0(510.6, 5258.1)  eth1(5207.5, 467.5)  
NIC(TX,RX): eth0(501.8, 5125.3)  eth1(5078.9, 462.1)  
NIC(TX,RX): eth0(501.9, 5119.9)  eth1(5072.3, 461.2)  
NIC(TX,RX): eth0(501.1, 5058.5)  eth1(5010.5, 460.2)  
NIC(TX,RX): eth0(497.2, 5112.8)  eth1(5065.5, 457.0)  
NIC(TX,RX): eth0(490.4, 5079.9)  eth1(5035.4, 452.5)  
## AVGRAGE: eth0(502.6, 5158.7)  eth1(5111.3, 462.2)  
NIC(TX,RX): eth0(503.8, 5207.0)  eth1(5159.4, 463.0)  
NIC(TX,RX): eth0(601.9, 5271.0)  eth1(5111.2, 460.7)  
NIC(TX,RX): eth0(505.0, 5205.0)  eth1(5147.3, 455.4)  
NIC(TX,RX): eth0(499.5, 5248.7)  eth1(5202.6, 459.9)  
NIC(TX,RX): eth0(500.4, 5202.4)  eth1(5153.8, 458.5)  
NIC(TX,RX): eth0(489.0, 5138.7)  eth1(5093.7, 450.6)  
NIC(TX,RX): eth0(497.6, 5296.5)  eth1(5247.6, 455.3)  
NIC(TX,RX): eth0(498.9, 5337.6)  eth1(5291.7, 459.5)  
NIC(TX,RX): eth0(492.6, 5227.5)  eth1(5178.6, 450.6)  
NIC(TX,RX): eth0(491.2, 5059.5)  eth1(5013.1, 451.5)  
## AVGRAGE: eth0(505.6, 5192.4)  eth1(5138.3, 459.0)  
NIC(TX,RX): eth0(499.9, 5137.1)  eth1(5089.5, 458.5)  
^C




# linux_network_bandwith
Very simple linux network interface monitor
# RUN
```bash
$ ./net_bandwidth --help                           
  --help                print this help
  --list                list NICs
  --add arg             add NIC to monitor [default: All]
  --unit arg            set Unit(Kb, KB, MB, GB) [default:KB]
  --period arg          set print period(in milisecond) [default:1000]
  --duration arg        set monitoring duration(in second) [default:-1]

$ ./net_bandwidth --add lo  --unit Kb --duration 5 
Montor Network Interfaces:
	 Duration: 5
	 Period: 1000
	 Unit: Kb
	 UnitDiv: 128
	 NICs: lo 
   lo(rx:    0, rx:    0)  
   lo(rx:  537, rx:  537)  
   lo(rx:  396, rx:  396)  
   lo(rx:  417, rx:  417)  
   lo(rx:  471, rx:  471)  



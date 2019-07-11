#ifndef NET_BANDWITH_HPP
#define NET_BANDWITH_HPP
#include<iostream> 
#include<vector> 
#include<string> 
enum Unit {mbps, kbps, bps };
class Nic{
    private:
        std::string nic_name;
        long old_rx_bytes;
        long old_tx_bytes;
        long sum_rx;
        long sum_tx;
        long num_rx;
        long num_tx;
        long get_bytes(std::string);
    public:
        Nic(std::string name):
            nic_name{name},
            old_rx_bytes{0},
            old_tx_bytes{0},
            sum_rx{0},
            sum_tx{0},
            num_rx{0},
            num_tx{0}
        {};
        float rx_bandwith();
        float tx_bandwith();
        float rx_avg(){ return (num_rx==0)?0:sum_rx/num_rx;}
        float tx_avg(){ return (num_tx==0)?0:sum_tx/num_tx;}
        long rx_bytes();
        long tx_bytes();
        std::string get_name(){ return nic_name;}
};
bool is_linux();
std::vector<std::string> get_interfaces();
void report(
        std::vector<std::string> r_nics, 
        long num,
        Unit unit);

#endif

#include<iostream> 
#include<vector> 
#include<cstdlib> 
#include<string> 
#include<fstream> 
#include<thread>
#include<chrono>
#include <dirent.h>
#include "net_bandwith.hpp"
using namespace std;

float Nic::rx_bandwith()
{
    if(!old_rx_bytes){
        old_rx_bytes = rx_bytes();
        return 0;
    }
    long new_rx_bytes = rx_bytes();
    float bits = 8 * (new_rx_bytes - old_rx_bytes);
    old_rx_bytes = new_rx_bytes;
    num_rx++;
    sum_rx += bits;
    return bits;
}
float Nic::tx_bandwith()
{
    if(!old_tx_bytes){
        old_tx_bytes = tx_bytes();
        return 0;
    }
    long new_tx_bytes = tx_bytes();
    float bits = 8 * (new_tx_bytes - old_tx_bytes);
    old_tx_bytes = new_tx_bytes;
    num_tx++;
    sum_tx += bits;
    return bits;
}

long Nic::get_bytes(string fname)
{
    string f_name = "/sys/class/net/"+nic_name+"/statistics/"+fname;
    ifstream x_bytes(f_name);
    if(x_bytes.is_open()){
        string bytes;
        x_bytes >> bytes;
        return atol(bytes.c_str());
    }else{
        throw string("Can't open ") + f_name;
    }
}
long Nic::rx_bytes()
{
    return get_bytes("rx_bytes");
}
long Nic::tx_bytes()
{
    return get_bytes("tx_bytes");
}
bool is_linux()
{
    ifstream lo("/sys/class/net/lo/address");
    if(lo.is_open()) return true;
    return false;
}

vector<string> get_interfaces()
{
    vector<string> nics;
    DIR *dp;
    struct dirent *ep;     
    dp = opendir("/sys/class/net/");

    if (dp != NULL)
    {
        while (ep = readdir (dp))
            if(ep->d_name[0] != '.')
                nics.push_back(ep->d_name);
        (void)closedir(dp);
    }
    return nics;
}
void report(vector<string> nics_name, long num, Unit unit)
{
    vector<Nic> nics;
    char out[50];

    for(auto& nic: nics_name){
        nics.push_back(nic);
    }

    cout << "##############\n";
    cout << "# Interfaces: ";
    for(auto& nic: nics)
        cout << nic.get_name() << "\t";
    cout << endl;
    cout << "# Unit: ";
    switch(unit){
        case mbps: 
            cout << "mbps" << endl;
            break;
        case kbps: 
            cout << "kbps" << endl;
            break;
        default:    
            cout << "bps" << endl;
    }
    cout << "# Loop: ";
    if(num == 0) cout << "infinit";
    else cout << num ;
    cout << "\n##############\n";
    long i = 0;
    while(num == 0 || i < num){
        i++;
        if(i % 10 == 0){
            printf("## AVGRAGE: ");
            for(auto& nic: nics){
                float arx = nic.rx_avg();
                float atx = nic.tx_avg();
                switch(unit){
                    case mbps: 
                        atx /= (1024*1024); 
                        arx /= (1024*1024); 
                        break;
                    case kbps: 
                        atx /= 1024; 
                        arx /= 1024; 
                        break;
                }
                snprintf(out, 50,"%s(%2.1f, %2.1f) ",
                        nic.get_name().c_str(),
                        atx, arx);
                printf("%-15s ", out);
            }
            cout << endl;
        }
        printf("NIC(TX,RX): ");
        for(auto& nic: nics){
            float tx = nic.tx_bandwith();
            float rx = nic.rx_bandwith();
            switch(unit){
                case mbps: 
                    tx /= (1024*1024); 
                    rx /= (1024*1024); 
                    break;
                case kbps: 
                    tx /= 1024; 
                    rx /= 1024; 
                    break;
            }
            snprintf(out, 50,"%s(%2.1f, %2.1f) ",
                    nic.get_name().c_str(),
                    tx, rx);
            printf("%-15s ", out);
        }
        cout << endl;
        chrono::milliseconds timespan(1000); 
        this_thread::sleep_for(timespan);
    }
}



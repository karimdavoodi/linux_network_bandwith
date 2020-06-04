#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include "net_bandwidth.hpp"
using namespace std;
const vector<string> System::get_interfaces()
{
    vector<string> nics;
    if(!check_sys_fs())
        return nics;
    for(auto nic : boost::filesystem::directory_iterator("/sys/class/net")){
        string name = nic.path().filename().c_str();
        nics.push_back(name);
    }
    return nics;
}
bool System::check_sys_fs()
{
    return boost::filesystem::exists("/sys/class/net");
}
long Interfaces::get_tx()
{
    long current = file_to_long("/sys/class/net/"+name+"/statistics/tx_bytes"); 
    long tmp = tx;
    long diff = current - tx;
    tx = current;
    return tmp ? diff : 0 ;
}
long Interfaces::get_rx()
{
    long current = file_to_long("/sys/class/net/"+name+"/statistics/rx_bytes"); 
    long tmp = rx;
    long diff = current - rx;
    rx = current;
    return tmp ? diff : 0 ;
}
long Interfaces::file_to_long(const string name) const
{
    if(boost::filesystem::exists(name)){
        ifstream file(name);
        if(file.is_open()){
            std::string content((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
            if(content.back() == '\n') content.pop_back();
            return stol(content);
        }
    }
    return 0;
}

#pragma onc;
#include<iostream> 
#include<vector> 
#include<string> 
using namespace std;
enum class Unit { Kb, KB, MB, GB };
const vector<string> unit_str {"Kb", "KB", "MB", "GB"};
class System {
    public:
        static const vector<string> get_interfaces();
        static bool check_sys_fs();
};

class Interfaces {
    private: 
        string name;
        long rx;
        long tx;
    public:
        Interfaces(const string name):name(name),rx(0),tx(0){};
        const string get_name(){ return name; }
        long get_tx();
        long get_rx();
    private:
        long file_to_long(const string path) const;
};

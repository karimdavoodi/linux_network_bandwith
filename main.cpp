#include<iostream> 
#include <unistd.h>
#include <cstdlib>
#include "net_bandwith.hpp"
#define VERSION "0.0.1"

using namespace std;
int main(int argc, char* argv[])
{
    vector<string> nics_name_all = get_interfaces();      
    vector<string> nics_name_add;      
    long num = 0;
    Unit unit = mbps;
    bool exit = false;
    int c ;
    while( ( c = getopt (argc, argv, "n:a:hlmkb") ) != -1 ) 
    {
        switch(c)
        {
            case 'm': unit = mbps; break;
            case 'k': unit = kbps; break;
            case 'b': unit = bps;  break;
            case 'a':
                if(optarg) nics_name_add.push_back(optarg);
                break;
            case 'n':
                if(optarg) num = std::atol(optarg) ;
                break;
            case 'l':
                cout << "All NICS:\n";
                for(auto& nic: nics_name_all){
                    cout << nic << endl;
                }
                exit = true;
                break;
            case 'h':
                cout << "Usage: " << argv[0] << endl;
                cout << "\t-h        // help " << endl;
                cout << "\t-l        // list interfaces" << endl;
                cout << "\t-m        // unit: mbps" << endl;
                cout << "\t-k        // unit: kbps" << endl;
                cout << "\t-b        // unit: bps" << endl;
                cout << "\t-a <nic>  // add nic to report list" << endl;
                cout << "\t-n <time> // time in secound. default infinit" << endl;
                exit = true;
                break;
        }
    }
    if(argc < 2){
        cout << argv[0] << " version:" << VERSION;
        cout << ", type -h for help\n";
    }
    if(!is_linux()){
        cout << "Sorry, not work here!\n";
        return 0;
    }
    if(!exit){
        if(nics_name_add.size()>0)
            report(nics_name_add, num, unit);
        else
            report(nics_name_all, num, unit);
    }
    return 0;
}

#include <iostream> 
#include <thread> 
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include "net_bandwidth.hpp"

using namespace std;
int main(int argc, char* argv[])
{
    Unit unit {Unit::KB};
    vector<Interfaces> nics {};
    int period {1000};
    int duration {-1};

    namespace po = boost::program_options;
    
    po::options_description desc;
    desc.add_options()
        ("help", "print this help")
        ("list", "list NICs")
        ("add", po::value<vector<string>>(), "add NIC to monitor [default: All]")
        ("unit", po::value<string>(), "set Unit(Kb, KB, MB, GB) [default:KB]")
        ("period", po::value<int>(), "set print period(in milisecond) [default:1000]")
        ("duration", po::value<int>(), "set monitoring duration(in second) [default:-1]")
        ;

    ///////  Check Arguments ///////////////////////////
    po::variables_map vmap;
    po::store(po::parse_command_line(argc, argv, desc), vmap);
    po::notify(vmap);
    if(vmap.count("help")){
        std::cout << desc;
        return 0;
    }
    if(vmap.count("list")){
        cout << "List of interfaces:\n";
        for(const auto nic: System::get_interfaces()){
            cout << '\t' << nic << '\n';
        }
        return 0;
    }
    if(vmap.count("unit")){
        const auto str = vmap["unit"].as<string>();
        if(str == "Kb") unit = Unit::Kb;
        else if(str == "KB") unit = Unit::KB;
        else if(str == "MB") unit = Unit::MB;
        else if(str == "GB") unit = Unit::GB;
    }
    if(vmap.count("add")){
        const auto nics_str = vmap["add"].as<vector<string>>();
        for(const string nic_str : nics_str){
            nics.emplace_back(nic_str);
        }
    }else{
        for(const auto nic_str : System::get_interfaces()){
            if(boost::filesystem::exists("/sys/class/net/" + nic_str + "/device"))
                nics.emplace_back(nic_str);
        }
    }
    if(vmap.count("period")){
        period = vmap["period"].as<int>();
    }
    if(vmap.count("duration")){
        duration = vmap["duration"].as<int>();
    }

    ///////  Start Monitoring ///////////////////////////
    long unit_div = (1<<10) / 8;
    if(unit == Unit::KB) unit_div = (1<<10);
    else if(unit == Unit::MB) unit_div = (1<<20);
    else if(unit == Unit::GB) unit_div = (1<<30);
    time_t now = time(NULL);
    cout << "\nDuration: " << duration
         << "\nPeriod: " << period
         << "\nUnit: " << unit_str[size_t(unit)]
         << "\nNICs: ";
    for(auto& nic : nics){
        cout << nic.get_name() << ' ';
    }
    cout << "\n------------------------------" << endl;
    while(true){
        string line;
        for(auto& nic : nics){
            auto out = boost::format("%5s(rx:%-5u, tx:%-5u) ") 
                        % nic.get_name()        
                        % (nic.get_rx() / unit_div)
                        % (nic.get_tx() / unit_div);
            line += out.str();
        }
        cout << line << endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000 * period));
        if(duration != -1 &&  duration + now <= time(NULL)) break;
    }
}

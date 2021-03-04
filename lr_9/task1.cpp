#include <iostream>
using namespace std;

namespace extra_info{
    enum engine{jet, screw};
    enum units{kilograms, tons, pounds, miles, kilometers, meters, feet};
    enum gas {hydrogen, helium};
};

class Airship{
    int goods;
    int passangers;
    extra_info::units goods_unts;
public:
    Airship(int gds, int pssngrs, extra_info::units gd_unts = extra_info::kilograms):
        goods(gds), passangers(pssngrs), goods_unts(gd_unts) {}
    void print_airship(){
        cout << "goods = " << goods;
        switch(goods_unts){
        case extra_info::kilograms:
            cout << "kilograms" << endl;
            break;
        case extra_info::tons:
            cout << "tons" << endl;
            break;
        case extra_info::pounds:
            cout << "pounds" << endl;
            break;
        default:
            cout << "units" << endl;  
            break;              
        }
    }
};


class Airplain : public Airship{
    int flight;
    extra_info::units flight_unts;
    extra_info::engine engn;
public:
    Airplain(int flght, int gds, int pssngrs, extra_info::units gd_unts = extra_info::kilograms, 
        extra_info::units fl_unts = extra_info::miles, extra_info::engine eng = extra_info::jet):
            Airship(gds, pssngrs, gd_unts), flight(flght), flight_unts(fl_unts), engn(eng) {}
    void print_airplain(){
        print_airship();
        cout << "flight = " << flight;
        switch(flight_unts){
        case extra_info::miles:
            cout << "miles" << endl;
            break;
        case extra_info::kilometers:
            cout << "kilometers" << endl;
            break;
        default:
            cout << "units" << endl;
            break;                
        }
        cout << "engine = ";
        switch (engn){
        case extra_info::jet:
            cout << "jet" << endl;
            break;
        case extra_info::screw:
            cout << "screw" << endl;
        default:
            cout << "default" << endl;
            break;
        }
        
    }
};    

class Balloon: public Airship{
    extra_info::gas gas_type;
    int max_rise;
    extra_info::units max_rise_unts;
public:
    Balloon(int mx_rs, int gds, int pssngrs, extra_info::units gd_unts = extra_info::kilograms,
        extra_info::gas gs_tp = extra_info::helium, extra_info::units mx_rs_unts = extra_info::feet):
            Airship(gds, pssngrs, gd_unts), gas_type(gs_tp), max_rise(mx_rs), max_rise_unts(mx_rs_unts) {}
    void print_balloon(){
        print_airship();
        cout << "max rise = " << max_rise_unts;
        switch(max_rise_unts){
        case extra_info::feet:
            cout << "feet" << endl;
            break;
        case extra_info::meters:
            cout << "meters" << endl;
            break;
        default:
            cout << "units" << endl;  
            break;
        }
        cout << "gas = ";
        switch(gas_type){
        case extra_info::hydrogen:
            cout << "hydrogen" << endl;
            break;
        case extra_info::helium:
            cout << "helium" << endl;
            break;
        default:
            cout << "default" << endl;
            break;
        }
    }
};


int main(){
    
    return 0;
}
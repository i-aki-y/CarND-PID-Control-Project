#include "PID.h"
#include    <sstream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {
    if(ofs.is_open()){
        ofs.close();
    }
}

void PID::Init(double kp, double ki, double kd) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
    max_cte_hist_size = 100;
    std::stringstream fname;
    fname << "log_" << Kp << "_" << Ki << "_" << Kd << ".dat";
    if(!ofs.is_open()){
        ofs.open("./" + fname.str());
        ofs << "cte" << "," << "speed" << "," << "angle" << "," << "steer_value" << ","
            << "cte_diff" << ","  << "cte_integ" << std::endl;
    }
}

void PID::UpdateError(double cte) {

    double cte_prev;
    if(cte_hist.size() > 0){
        cte_prev = cte_hist.back();
    }else{
        cte_prev = cte;
    }

    cte_diff = cte - cte_prev;

    cte_hist.push_back(cte);
    if(cte_hist.size() > max_cte_hist_size){
        cte_hist.pop_front();
    }

    cte_integ = 0;
    for(double val: cte_hist){
        cte_integ += val;
    }
    cte_integ /=  cte_hist.size();

}

double PID::TotalError() {
}


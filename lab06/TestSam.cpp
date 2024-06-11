#include "SAM.h"

int main(){
    ADAI::SAM model;
    double h = 500.0;
    std::pair<double, double> ans = model(h);
    std::cout << "Показатели: " << ADAI::SAM::get_p(h) << "Па, " << ADAI::SAM::get_ro(h) << "кг/м3," << ADAI::SAM::get_A(h) << "м/c\n";


}

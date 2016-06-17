#include <iostream>
#include "Pump.h"

using namespace std;

int main() {

    Pump *pump = new Pump();
    pump->setStyle(Pump::Style::API_DOUBLE_SUCTION);
    return 0;
}
#ifndef AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H
#define AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H

class SolidLoadChargeMaterial;

std::vector<SolidLoadChargeMaterial> SQLite::get_default_solid_load_charge_materials() {
    return {
        {"Aluminum", 0.2479, 169, 0.2601, 1215},
        {"Babbitt, lead base", 0.0389, 26.2, 0.038, 462},
        {"Babbitt, tin base", 0.0709, 34.1, 0.0631, 464},
        {"Bismuth", 0.033, 18.5, 0.0351, 518},
        {"Brass, Muntz metal", 0.1051, 69, 0.1249, 1630},
        {"Brass, red", 0.1039, 86.5, 0.1151, 1952},
        {"Brass,yellow", 0.1051, 71, 0.123, 1688},
        {"Bronze, bearing", 0.0951, 79.9, 0.1089, 1832},
        {"Bronze, aluminum", 0.1261, 98.6, 0.1249, 1922},
        {"Bronze, bell metal", 0.1001, 76.3, 0.1189, 1634},
        {"Bronze, gun metal", 0.107, 84.2, 0.106, 1850},
        {"Bronze, tobin", 0.107, 73.5, 0.124, 1625},
        {"Carbon Steel", 0.16, 60, 0.175, 2800},
        {"Copper", 0.1039, 91, 0.1111, 1982},
        {"Die casting metal", 0.236, 163, 0.241, 1150},
        {"Die casting metal", 0.038, 17.5, 0.037, 600},
        {"Die casting metal", 0.07, 30.2, 0.0621, 450},
        {"Die casting metal", 0.1029, 48, 0.138, 780},
        {"German silver", 0.1089, 86.2, 0.123, 1850},
        {"Gold", 0.033, 28.5, 0.0339, 1945},
        {"Inconel - 600", 0.14, 50, 0.155, 2500},
        {"Iron, cast, gray", 0.1901, 41.4, 0.2051, 2246},
        {"Iron, cast, white", 0.1801, 60.3, 0.1951, 2102},
        {"Iron, pig", 0.1531, 83.6, 0.1681, 2012},
        {"Iron, pure", 0.1679, 117, 0.15, 2802},
        {"Lead", 0.032, 10, 0.0339, 621},
        {"Linotype", 0.0361, 21.5, 0.0361, 486},
        {"Magnesium", 0.272, 83.7, 0.2661, 1204},
        {"Manganese", 0.171, 66, 0.192, 2246},
        {"Monel metal", 0.129, 117.4, 0.139, 2415},
        {"Nickel 60 to 2644 F", 0.134, 131.5, 0.133, 2644},
        {"Silver", 0.0631, 46.8, 0.07, 1762},
        {"solder, bismuth", 0.0399, 16.4, 0.0389, 232},
        {"Solder, plumbers", 0.0511, 23, 0.049, 414},
        {"Stainless Steel - 300 series", 0.14, 117.15, 0.16, 2550},
        {"Stainless Steel - 410", 0.12, 48, 0.14, 2800},
        {"Tin", 0.069, 25, 0.0638, 450},
        {"Zinc", 0.107, 48, 0.1459, 786},
        {"Refractory", 0.2501, 425, 0.26, 5000},
        {"Ladle Refractory", 0.2501, 425, 0.26, 5000}
    };
}

#endif //AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H
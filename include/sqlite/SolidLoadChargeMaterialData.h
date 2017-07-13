#ifndef AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H
#define AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H

class SolidLoadChargeMaterial;

std::vector<SolidLoadChargeMaterial> SQLite::get_default_solid_load_charge_materials() {
    return {
        {"Aluminum", 0.247910198232625, 169, 0.2601, 1215},
        {"Babbitt, Lead Base", 0.0389300214951039, 26.2, 0.038, 462},
        {"Babbitt, Tin Base", 0.0709338428469071, 34.1, 0.0631, 464},
        {"Bismuth", 0.0329591593026033, 18.5, 0.0351, 518},
        {"Brass, Muntz Metal", 0.105087174588011, 69, 0.1249, 1630},
        {"Brass, Red", 0.10389300214951, 86.5, 0.1151, 1952},
        {"Brass, Yellow", 0.105087174588011, 71, 0.123, 1688},
        {"Bronze, Bearing", 0.0950561261046095, 79.9, 0.1089, 1832},
        {"Bronze, Aluminum", 0.126104609505613, 98.6, 0.1249, 1922},
        {"Bronze, Bell Metal", 0.10007165034631, 76.3, 0.1189, 1634},
        {"Bronze, Gun Metal", 0.106997850489611, 84.2, 0.106, 1850},
        {"Bronze, Tobin", 0.106997850489611, 73.5, 0.124, 1625},
        {"Carbon Steel", 0.16, 60, 0.175, 2800},
        {"Copper", 0.10389300214951, 91, 0.1111, 1982},
        {"Die Casting Metal (Aluminum Alloy)", 0.235968473847624, 163, 0.241, 1150},
        {"Die Casting Metal (Lead Alloy)", 0.0379746835443038, 17.5, 0.037, 600},
        {"Die Casting Metal (Tin Alloy)", 0.069978504896107, 30.2, 0.0621, 450},
        {"Die Casting Metal (Zinc Alloy)", 0.10293766419871, 48, 0.138, 780},
        {"German Silver", 0.108908526391211, 86.2, 0.123, 1850},
        {"Gold", 0.0329591593026033, 28.5, 0.0339, 1945},
        {"Inconel - 600", 0.139957009792214, 50, 0.155, 2500},
        {"Iron, Cast, Gray", 0.190112252209219, 41.4, 0.2051, 2246},
        {"Iron, Cast, White", 0.180081203725818, 60.3, 0.1951, 2102},
        {"Iron, Pig", 0.153092906615715, 83.6, 0.1681, 2012},
        {"Iron, Pure", 0.167900644853117, 117, 0.15, 2802},
        {"Lead", 0.0320038213518032, 10, 0.0339, 621},
        {"Linotype", 0.0360640076427036, 21.5, 0.0361, 486},
        {"Magnesium", 0.272032481490327, 83.7, 0.2661, 1204},
        {"Manganese", 0.171005493193217, 66, 0.192, 2246},
        {"Monel Metal", 0.128970623358013, 117.4, 0.139, 2415},
        {"Nickel 60 to 2644 Degrees F", 0.133986147599713, 131.5, 0.133, 2644},
        {"Silver", 0.0630523047528063, 46.8, 0.07, 1762},
        {"Solder, Bismuth", 0.039885359445904, 16.4, 0.0389, 232},
        {"Solder, Plumbers", 0.0511105803678051, 23, 0.049, 414},
        {"Stainless Steel - 300 Series", 0.139957009792214, 117.15, 0.16, 2550},
        {"Stainless Steel - 410", 0.12, 48, 0.14, 2800},
        {"Tin", 0.0690231669453069, 25, 0.0638, 450},
        {"Zinc", 0.106997850489611, 48, 0.1459, 786},
        {"Refractory", 0.250059708621925, 425, 0.26, 5000},
        {"Ladle Refractory", 0.250059708621925, 425, 0.26, 5000}
    };
}

#endif //AMO_TOOLS_SUITE_SOLIDLOADCHARGEMATERIALDATA_H

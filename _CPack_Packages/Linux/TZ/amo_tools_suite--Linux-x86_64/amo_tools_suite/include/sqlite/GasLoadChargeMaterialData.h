#ifndef AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H
#define AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H

class GasLoadChargeMaterial;

std::vector<GasLoadChargeMaterial> SQLite::get_default_gas_load_charge_materials() {
    return {
        {"Water vapor - Near Atm. Pressure", 0.47},
        {"Steam - 50 PSIG, 400 degrees F", 0.4901},
        {"Steam - 150 PSIG, 500 degrees F", 0.5099},
        {"Steam - 600 PSIG, 700 degrees F", 0.5899},
        {"Air - Low Pressure", 0.245},
        {"Nitrogen - Low Pressure", 0.2501},
        {"Oxygen - Low Pressure", 0.23},
        {"Carbon Dioxide - Low Pressure", 0.24},
        {"Carbon Monoxide - Low Pressure", 0.2501},
        {"Hydrogen - Low Pressure", 3.45}
    };
}

#endif //AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H

#ifndef AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H
#define AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H

class GasLoadChargeMaterial;

std::vector<GasLoadChargeMaterial> SQLite::get_default_gas_load_charge_materials() {
    return {
        {"Water vapor - near atm. pressure", 0.47},
        {"Steam - 50 psig, 400 degree F", 0.4901},
        {"Steam - 150 psig, 500 degree F", 0.5099},
        {"Steam - 600 psig, 700 degree F", 0.5899},
        {"Air - low pressure", 0.245},
        {"Nitrogen - low pressure", 0.2501},
        {"Oxygen - low pressure", 0.23},
        {"Carbon dioxide - low pressure", 0.24},
        {"Carbon monoxide - low pressure", 0.2501},
        {"Hydrogen - low pressure", 3.45}
    };
}

#endif //AMO_TOOLS_SUITE_GASLOADCHARGEMATERIALDATA_H

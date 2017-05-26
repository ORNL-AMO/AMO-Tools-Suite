#ifndef AMO_TOOLS_SUITE_LIQUIDLOADCHARGEMATERIALDATA_H
#define AMO_TOOLS_SUITE_LIQUIDLOADCHARGEMATERIALDATA_H

class LiquidLoadChargeMaterial;

std::vector<LiquidLoadChargeMaterial> SQLite::get_default_liquid_load_charge_materials() {
    return {
            {"Crude", 0.6501, 105, 0.55, 900},
            {"Water - Std. Atms. Pressure", 1, 970.3, 0.47, 212},
            {"Water - 150 PSIG", 1.0499, 868, 0.54, 365},
            {"Acetic Acid", 0.5099, 174, 0.4, 244},
            {"Acetone", 0.347, 239, 0.4, 130},
            {"Alcohol - Ethyl", 0.648, 369, 0.45, 172},
            {"Alcohol - Methyl", 0.6009, 481, 0.3301, 151},
            {"Benzene", 0.423, 170, 0.3301, 176},
            {"Bromine", 0.107, 82, 0.0549, 142},
            {"Carbon Tetrachloride", 0.215, 83.5, 0.2501, 170},
            {"Fuel Oil No. 2 (Average)", 0.5701, 105, 0.55, 375},
            {"Fuel Oil No. 6 (Average)", 0.5799, 108, 0.55, 600},
            {"Kerosene", 0.5701, 260, 0.62, 260}
    };
}

#endif //AMO_TOOLS_SUITE_LIQUIDLOADCHARGEMATERIALDATA_H

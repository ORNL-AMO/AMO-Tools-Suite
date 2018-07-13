#ifndef AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIALDATA_H
#define AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIALDATA_H

class SolidLiquidFlueGasMaterial;

std::vector<SolidLiquidFlueGasMaterial> SQLite::get_default_solid_liquid_flue_gas_materials() {
    return {
           /* {"Anthracite", 83.7, 1.9, 0.9, 0.7, 2.3, 0, 10.5},
            {"Pittsburgh #8 Bituminous, Oh or Pa", 74.0, 5.1, 1.6, 2.3, 7.9, 0, 9.1},
            {"Illinois #6 Bituminous, Illinois", 69.0, 4.9, 1.0, 4.3, 10.0, 0, 10.8},
            {"Upper Freeport Bituminous, Pennsylvania", 74.9, 4.7, 1.27, 0.76, 4.97, 0, 13.4},
            {"SpringCreek Subbituminous, Wyoming", 70.3, 5.0, 0.96, 0.35, 17.69, 0, 5.7},
            {"Decker Subbituminous, Montana", 72.0, 5.0, 0.95, 0.44, 16.41, 0, 5.2},
            {"Lignite, North Dakota", 63.3, 4.5, 1.0, 1.1, 19.0, 0, 11.1},
            {"Lignite (S. Hallsville), Texas", 66.3, 4.9, 1.0, 1.2, 16.2, 0, 10.4},
            {"Lignite (Bryan), Texas", 33.8, 3.3, 0.4, 1.0, 11.1, 0, 50.4},
            {"Lignite (San Miguel), Texas", 18.4, 2.3, 0.29, 1.2, 9.01, 0, 68.8},
            {"Fuel Oil No. 1 (Average)", 86.30, 13.70, 0.05, 0.26, 0, 0, 0},
            {"Fuel Oil No. 2 (Average)", 87.15, 12.85, 0.05, 0.53, 0, 0, 0},
            {"Fuel Oil No. 4 (Average)", 87.85, 11.80, 0, 1.01, 0, 0, 0.05},
            {"Fuel Oil No. 5 (Average)", 87.85, 11.25, 0, 1.75, 0, 0, 0.05},
            {"Fuel Oil No. 6 (Average)", 88.35, 10.75, 0, 2.10, 0, 0, 0.26},
            {"Pine Bark", 53.4, 5.6, 0.1, 0.1, 37.9, 0, 2.9},
            {"Oak Bark", 49.7, 5.4, 0.2, 0.1, 39.3, 0, 5.3},
            {"Spruce Bark*", 51.8, 5.7, 0.2, 0.1, 38.4, 0, 3.8},
            {"Redwood Bark*", 51.9, 5.1, 0.1, 0.1, 42.4, 0, 0.4}
            */
            {"Typical Bituminous Coal - US", 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5},
            {"Typical Anthracite - US", 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8},
            {"Typical Lignite - US", 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8},
            {"Fuel Oil #2", 86.6, 12.8, 0.5, 0, 0, 0, 0.1},
            {"Fuel Oil #6", 87.1, 10.6, 2.1, 0.2, 0, 0, 0},
            {"Typical Wood", 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2}
    };
}

#endif //AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIALDATA_H

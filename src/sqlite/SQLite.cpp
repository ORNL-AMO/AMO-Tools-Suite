#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <sqlite/SolidLoadChargeMaterialData.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <sqlite/GasLoadChargeMaterialData.h>
#include <sqlite/LiquidLoadChargeMaterialData.h>
#include <sqlite/GasFlueGasMaterialData.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <sqlite/SolidLiquidFlueGasMaterialData.h>

SQLite::SQLite(std::string const & db_name, bool init_db)
        :
        SQLiteWrapper(db_name, init_db)
{
    execute_command("PRAGMA locking_mode = EXCLUSIVE;");
    execute_command("PRAGMA journal_mode = OFF;");
    execute_command("PRAGMA synchronous = OFF;");
    // Turn this to ON for Foreign Key constraints.
    // This must be turned ON for every connection
    execute_command("PRAGMA foreign_keys = ON;");

    if ( init_db ) {
        create_tables();
        insert_default_data();
    }

    create_select_stmt();
}

SQLite::~SQLite()
{
    sqlite3_finalize(m_solid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_single_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_single_stmt);
}

std::string SQLiteWrapper::convert_text( const unsigned char * text ) {
    return std::string( reinterpret_cast< const char* >( text ) );
}

std::vector<SolidLoadChargeMaterial> SQLite::getSolidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
	    auto const ID = sqlite3_column_int(stmt, 0);
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 2);
        auto const latentHeat = sqlite3_column_double(stmt, 3);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 4);
        auto const meltingPoint = sqlite3_column_double(stmt, 5);
        return SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint, ID);
    };
    return get_all_objects<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_stmt, cb);
}

SolidLoadChargeMaterial SQLite::getSolidLoadChargeMaterial(int const id) const
{
    auto cb = [id] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 2);
        auto const latentHeat = sqlite3_column_double(stmt, 3);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 4);
        auto const meltingPoint = sqlite3_column_double(stmt, 5);
        return SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint, id);
    };
    return get_object<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<GasLoadChargeMaterial> SQLite::getGasLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 2);
        return GasLoadChargeMaterial(substance, specificHeatVapor);
    };
    return get_all_objects<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_stmt, cb);
}

GasLoadChargeMaterial SQLite::getGasLoadChargeMaterial(int const id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 2);
        return GasLoadChargeMaterial(substance, specificHeatVapor);
    };
    return get_object<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<LiquidLoadChargeMaterial> SQLite::getLiquidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 2);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 4);
        auto const latentHeat = sqlite3_column_double(stmt, 5);
        return LiquidLoadChargeMaterial(substance, specificHeatLiquid, vaporizingTemperature, latentHeat, specificHeatVapor);
    };
    return get_all_objects<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_stmt, cb);
}

LiquidLoadChargeMaterial SQLite::getLiquidLoadChargeMaterial(int const id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 2);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 4);
        auto const latentHeat = sqlite3_column_double(stmt, 5);
        return LiquidLoadChargeMaterial(substance, specificHeatLiquid, vaporizingTemperature, latentHeat, specificHeatVapor);
    };
    return get_object<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<SolidLiquidFlueGasMaterial> SQLite::getSolidLiquidFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const carbon = sqlite3_column_double(stmt, 2);
        auto const hydrogen = sqlite3_column_double(stmt, 3);
        auto const sulphur = sqlite3_column_double(stmt, 4);
        auto const inertAsh = sqlite3_column_double(stmt, 5);
        auto const o2 = sqlite3_column_double(stmt, 6);
        auto const moisture = sqlite3_column_double(stmt, 7);
        auto const nitrogen = sqlite3_column_double(stmt, 8);
        return SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                          o2 * 100, moisture * 100, nitrogen * 100);
    };
    return get_all_objects<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_stmt, cb);
}

SolidLiquidFlueGasMaterial SQLite::getSolidLiquidFlueGasMaterial(int const id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const carbon = sqlite3_column_double(stmt, 2);
        auto const hydrogen = sqlite3_column_double(stmt, 3);
        auto const sulphur = sqlite3_column_double(stmt, 4);
        auto const inertAsh = sqlite3_column_double(stmt, 5);
        auto const o2 = sqlite3_column_double(stmt, 6);
        auto const moisture = sqlite3_column_double(stmt, 7);
        auto const nitrogen = sqlite3_column_double(stmt, 8);
        return SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                          o2 * 100, moisture * 100, nitrogen * 100);
    };
    return get_object<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_single_stmt, id, cb);
}

std::vector<GasCompositions> SQLite::getGasFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const CH4 = sqlite3_column_double(stmt, 2);
        auto const C2H6 = sqlite3_column_double(stmt, 3);
        auto const N2 = sqlite3_column_double(stmt, 4);
        auto const H2 = sqlite3_column_double(stmt, 5);
        auto const C3H8 = sqlite3_column_double(stmt, 6);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 7);
        auto const H2O = sqlite3_column_double(stmt, 8);
        auto const CO = sqlite3_column_double(stmt, 9);
        auto const CO2 = sqlite3_column_double(stmt, 10);
        auto const SO2 = sqlite3_column_double(stmt, 11);
        auto const O2 = sqlite3_column_double(stmt, 12);
        return GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    };
    return get_all_objects<GasCompositions>(m_gas_flue_gas_materials_select_stmt, cb);
}

GasCompositions SQLite::getGasFlueGasMaterial(int const id) const
{

    auto cb = [] (sqlite3_stmt * stmt) {
        std::string const substance = SQLiteWrapper::convert_text(sqlite3_column_text(stmt, 1));
        auto const CH4 = sqlite3_column_double(stmt, 2);
        auto const C2H6 = sqlite3_column_double(stmt, 3);
        auto const N2 = sqlite3_column_double(stmt, 4);
        auto const H2 = sqlite3_column_double(stmt, 5);
        auto const C3H8 = sqlite3_column_double(stmt, 6);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 7);
        auto const H2O = sqlite3_column_double(stmt, 8);
        auto const CO = sqlite3_column_double(stmt, 9);
        auto const CO2 = sqlite3_column_double(stmt, 10);
        auto const SO2 = sqlite3_column_double(stmt, 11);
        auto const O2 = sqlite3_column_double(stmt, 12);
        return GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    };
    return get_object<GasCompositions>(m_gas_flue_gas_materials_select_single_stmt, id, cb);
}

void SQLite::create_select_stmt()
{
    std::string const select_solid_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials)";

    prepare_statement(m_solid_load_charge_materials_select_stmt, select_solid_load_charge_materials);

    std::string const select_single_solid_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_solid_load_charge_materials_select_single_stmt, select_single_solid_load_charge_materials);

    std::string const select_gas_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials)";

    prepare_statement(m_gas_load_charge_materials_select_stmt, select_gas_load_charge_materials);

    std::string const select_single_gas_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_gas_load_charge_materials_select_single_stmt, select_single_gas_load_charge_materials);

    std::string const select_liquid_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials)";

    prepare_statement(m_liquid_load_charge_materials_select_stmt, select_liquid_load_charge_materials);

    std::string const select_single_liquid_load_charge_materials =
        R"(SELECT id, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_liquid_load_charge_materials_select_single_stmt, select_single_liquid_load_charge_materials);

    std::string const select_solid_liquid_flue_gas_materials =
            R"(SELECT id, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_stmt, select_solid_liquid_flue_gas_materials);

    std::string const select_single_solid_liquid_flue_gas_materials =
            R"(SELECT id, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_single_stmt, select_single_solid_liquid_flue_gas_materials);

    std::string const select_gas_flue_gas_materials =
            R"(SELECT id, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene
           FROM gas_flue_gas_materials)";

    prepare_statement(m_gas_flue_gas_materials_select_stmt, select_gas_flue_gas_materials);

    std::string const select_single_gas_flue_gas_materials =
            R"(SELECT id, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene
           FROM gas_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_gas_flue_gas_materials_select_single_stmt, select_single_gas_flue_gas_materials);
}

void SQLite::create_tables()
{
    const std::string solid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_load_charge_materials (
           id integer PRIMARY KEY AUTOINCREMENT,
           substance text NOT NULL DEFAULT "",
           mean_specific_heat_of_solid real NOT NULL, -- Btu/lb.F
           latent_heat_of_fusion real NOT NULL, -- Btu/lb.
           mean_specific_heat_of_liquid real NOT NULL, -- Btu/lb.F
           melting_point real NOT NULL, -- F.
           UNIQUE (substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                   mean_specific_heat_of_liquid, melting_point)
                  );)";

    execute_command(solid_load_charge_materials_table_sql);

    const std::string solid_load_charge_materials_insert_sql =
        R"(INSERT INTO solid_load_charge_materials(substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                                                   mean_specific_heat_of_liquid, melting_point)
           VALUES (?,?,?,?,?))";

    prepare_statement(m_solid_load_charge_materials_insert_stmt, solid_load_charge_materials_insert_sql);

    const std::string gas_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             UNIQUE (substance, mean_specific_heat_of_vapor)
            );)";

    execute_command(gas_load_charge_materials_table_sql);

    const std::string gas_load_charge_materials_insert_sql =
        R"(INSERT INTO gas_load_charge_materials(substance,mean_specific_heat_of_vapor) VALUES (?,?))";

    prepare_statement(m_gas_load_charge_materials_insert_stmt, gas_load_charge_materials_insert_sql);

    const std::string liquid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS liquid_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             mean_specific_heat_of_liquid real NOT NULL, -- kJ/kg.F
             latent_heat_of_vaporisation real NOT NULL, -- Btu/lb.
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             boiling_point real NOT NULL, -- F.
             UNIQUE (substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                     mean_specific_heat_of_vapor, boiling_point)
          );)";

    execute_command(liquid_load_charge_materials_table_sql);

    const std::string liquid_load_charge_materials_insert_sql =
        R"(INSERT INTO liquid_load_charge_materials(substance, mean_specific_heat_of_liquid,
                                                    latent_heat_of_vaporisation, mean_specific_heat_of_vapor,
                                                    boiling_point)
           VALUES (?,?,?,?,?))";

    prepare_statement(m_liquid_load_charge_materials_insert_stmt, liquid_load_charge_materials_insert_sql);

    const std::string solid_liquid_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_liquid_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             carbon real NOT NULL, --C
             hydrogen real NOT NULL, -- H2
             nitrogen real NOT NULL, -- N2
             sulfur real NOT NULL, -- S
             oxygen real NOT NULL, -- O2
             moisture real NOT NULL, -- H20
             ash real NOT NULL, -- ash
             UNIQUE (substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash)
      );)";

    execute_command(solid_liquid_flue_gas_materials_table_sql);

    const std::string solid_liquid_flue_gas_materials_insert_sql =
        R"(INSERT INTO solid_liquid_flue_gas_materials(substance, carbon, hydrogen, nitrogen, sulfur, oxygen,
                                                       moisture, ash)
           VALUES (?,?,?,?,?,?,?,?))";

    prepare_statement(m_solid_liquid_flue_gas_materials_insert_stmt, solid_liquid_flue_gas_materials_insert_sql);

    const std::string gas_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             hydrogen real NOT NULL, -- H2
             methane real NOT NULL, -- CH4
             ethylene real NOT NULL, -- C2H4
             ethane real NOT NULL, -- C2H6
             sulfur_dioxide real NOT NULL, -- SO2
             carbon_monoxide real NOT NULL, -- CO
             carbon_dioxide real NOT NULL, -- CO2
             nitrogen real NOT NULL, -- N2
             oxygen real NOT NULL, -- O2
             hydrogen_sulfide real NOT NULL, -- H2S
             benzene real NOT NULL, -- C2H4
             UNIQUE (substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide, carbon_monoxide, carbon_dioxide,
                     nitrogen, oxygen, hydrogen_sulfide, benzene)
      );)";

    execute_command(gas_flue_gas_materials_table_sql);

    const std::string gas_flue_gas_materials_insert_sql =
        R"(INSERT INTO gas_flue_gas_materials(substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene)
           VALUES (?,?,?,?,?,?,?,?,?,?,?,?))";

    prepare_statement(m_gas_flue_gas_materials_insert_stmt, gas_flue_gas_materials_insert_sql);
}

void SQLite::insert_default_data()
{
    for( auto const & material : get_default_solid_load_charge_materials() ) {
        insert_solid_load_charge_materials(material);
    }
    for( auto const & material : get_default_gas_load_charge_materials() ) {
        insert_gas_load_charge_materials(material);
    }
    for( auto const & material : get_default_liquid_load_charge_materials() ) {
        insert_liquid_load_charge_materials(material);
    }
    for( auto const & material : get_default_solid_liquid_flue_gas_materials() ) {
        insert_solid_liquid_flue_gas_materials(material);
    }
    for( auto const & material : get_default_gas_flue_gas_materials() ) {
        insert_gas_flue_gas_materials(material);
    }
}

bool SQLite::insert_solid_load_charge_materials(SolidLoadChargeMaterial const & material)
{
    bind_value(m_solid_load_charge_materials_insert_stmt, 1, material.getSubstance());
    bind_value(m_solid_load_charge_materials_insert_stmt, 2, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 3, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_insert_stmt, 4, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 5, material.getMeltingPoint());

    int rc = step_command(m_solid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insert_gas_load_charge_materials(GasLoadChargeMaterial const & material)
{
    bind_value(m_gas_load_charge_materials_insert_stmt, 1, material.getSubstance());
    bind_value(m_gas_load_charge_materials_insert_stmt, 2, material.getSpecificHeatVapor());

    int rc = step_command(m_gas_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insert_liquid_load_charge_materials(LiquidLoadChargeMaterial const & material)
{
    bind_value(m_liquid_load_charge_materials_insert_stmt, 1, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 2, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 3, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 4, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 5, material.getVaporizingTemperature());

    int rc = step_command(m_liquid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insert_solid_liquid_flue_gas_materials(SolidLiquidFlueGasMaterial const & material)
{
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 1, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 2, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 3, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 4, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 5, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 6, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 7, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 8, material.getNitrogen());

    int rc = step_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insert_gas_flue_gas_materials(GasCompositions const & comps)
{
    bind_value(m_gas_flue_gas_materials_insert_stmt, 1, comps.getSubstance());
    bind_value(m_gas_flue_gas_materials_insert_stmt, 2, comps.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 3, comps.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 4, comps.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 5, comps.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 6, comps.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 7, comps.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 8, comps.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 9, comps.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 10, comps.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 11, comps.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 12, comps.getGasByVol("O2"));

    int rc = step_command(m_gas_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_insert_stmt);
    return valid_insert;
}

SQLiteWrapper::SQLiteWrapper( std::shared_ptr<sqlite3> const & db )
    :
    m_db(db)
{}

SQLiteWrapper::SQLiteWrapper( std::string const & db_name, bool init_db )
{
    bool ok = true;
    bool in_memory = (db_name == ":memory:");
    char *err_msg = 0;
	int rc;

    if ( init_db ) {
        // Test if we can create a new file named db_name
        if ( !in_memory ) {
            std::ofstream test(db_name, std::ofstream::out | std::ofstream::trunc);
            if ( test.is_open() ) {
                test.close();
            } else {
                ok = false;
            }
        }

        // Test if we can write to the database
        // If we can't then there are probably locks on the database
        if ( ok ) {
            sqlite3_open_v2(db_name.c_str(), &m_connection, SQLITE_OPEN_READWRITE, nullptr);
            char * zErrMsg = nullptr;
            rc = sqlite3_exec(m_connection, "CREATE TABLE Test(x INTEGER PRIMARY KEY)", nullptr, 0, &zErrMsg);
            sqlite3_exec(m_connection, "DROP TABLE IF EXISTS Test", nullptr, 0, &zErrMsg);
            sqlite3_close(m_connection);
            if ( rc ) {
                std::cerr << "Non-exclusive lock on existing database: " << sqlite3_errmsg(m_connection) << std::endl;
                ok = false;
            } else {
                if (!in_memory) {
                    // Remove test db
                    rc = remove( db_name.c_str() );
                    if ( rc ) {
                        std::cerr << "Can't remove old database: " << sqlite3_errmsg(m_connection) << std::endl;
                        ok = false;
                    }
                }
            }
            sqlite3_free(zErrMsg);
        }
    }

    if ( ok ) {
        // Now open the output db for the duration of the simulation
        rc = sqlite3_open_v2(db_name.c_str(), &m_connection, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        m_db = std::shared_ptr<sqlite3>(m_connection, sqlite3_close);
        if ( rc ) {
            std::cerr << "Can't open new database: " << sqlite3_errmsg(m_connection) << std::endl;
            ok = false;
        }
    }

    if ( !ok ) {
//        throw std::runtime_error("Failed to connect to SQLite database.");
        std::cerr << "Failed to connect to SQLite database." << err_msg << std::endl;
    }
}

int SQLiteWrapper::execute_command(std::string const & command_buffer) const
{
    char *err_msg = 0;
    int rc = sqlite3_exec(m_db.get(), command_buffer.c_str(), nullptr, 0, &err_msg);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_exec failed: " << err_msg << std::endl;
    }
    sqlite3_free(err_msg);
    return rc;
}

int SQLiteWrapper::prepare_statement(sqlite3_stmt * & stmt, std::string const & stmt_buffer) const
{
    int rc = sqlite3_prepare_v2(m_db.get(), stmt_buffer.c_str(), -1, &stmt, nullptr);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_prepare_v2 failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, std::string const & text_buffer) const
{
    int rc = sqlite3_bind_text(stmt, stmt_insert_col_index, text_buffer.c_str(), -1, SQLITE_TRANSIENT);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_text failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert) const
{
    int rc = sqlite3_bind_int(stmt, stmt_insert_col_index, int_to_insert);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_int failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, double const double_to_insert) const
{
    int rc = sqlite3_bind_double(stmt, stmt_insert_col_index, double_to_insert);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_double failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index) const
{
    int rc = sqlite3_bind_null(stmt, stmt_insert_col_index);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_null failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, bool const value_to_insert) const
{
    return bind_value(stmt,stmt_insert_col_index, value_to_insert ? 1 : 0);
}

int SQLiteWrapper::bind_foreign_key(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert) const
{
    int rc = -1;
    if ( int_to_insert > 0 ) {
        rc = sqlite3_bind_int(stmt, stmt_insert_col_index, int_to_insert);
    } else {
        rc = sqlite3_bind_null(stmt, stmt_insert_col_index);
    }
    if ( rc != SQLITE_OK ) {
        std::cerr << "bind_foreign_key failed" << std::endl;
    }
    return rc;
}

bool SQLiteWrapper::step_validity( int const rc ) const
{
    switch(rc) {
    case SQLITE_DONE:
    case SQLITE_OK:
    case SQLITE_ROW:
        return true;
    default:
        break;
    }
    return false;
}

int SQLiteWrapper::step_command(sqlite3_stmt * stmt) const
{
    int rc = sqlite3_step(stmt);
    switch(rc) {
    case SQLITE_DONE:
    case SQLITE_OK:
    case SQLITE_ROW:
        break;
    default:
        std::cerr << "sqlite3_step failed: " << sqlite3_errmsg(m_db.get()) << std::endl;
        break;
    }

    return rc;
}

int SQLiteWrapper::reset_command(sqlite3_stmt * stmt) const
{
    return sqlite3_reset(stmt);
}

void SQLiteWrapper::begin_transaction() const
{
    execute_command("BEGIN;");
}

void SQLiteWrapper::commit_transaction() const
{
    execute_command("COMMIT;");
}

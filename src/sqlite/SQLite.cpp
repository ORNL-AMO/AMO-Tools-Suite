#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>
#include <sqlite/SolidLoadChargeMaterialData.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <sqlite/GasLoadChargeMaterialData.h>
#include <sqlite/LiquidLoadChargeMaterialData.h>
#include <sqlite/GasFlueGasMaterialData.h>
#include <sqlite/AtmosphereSpecificHeatData.h>
#include <sqlite/WallLossesSurfaceData.h>
#include <calculator/motor/MotorData.h>

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <sqlite/SolidLiquidFlueGasMaterialData.h>
#include <sqlite/MotorData.h>

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
        create_insert_stmt();
        insert_default_data();
    } else {
        create_insert_stmt();
    }

    create_select_stmt();
    create_update_and_delete_stmt();
}

SQLite::~SQLite()
{
    sqlite3_finalize(m_solid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_select_custom_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_update_stmt);
    sqlite3_finalize(m_solid_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_gas_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_stmt);
    sqlite3_finalize(m_gas_load_charge_materials_select_single_stmt);
	sqlite3_finalize(m_gas_load_charge_materials_select_custom_stmt);
	sqlite3_finalize(m_gas_load_charge_materials_update_stmt);
	sqlite3_finalize(m_gas_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_liquid_load_charge_materials_insert_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_single_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_select_custom_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_update_stmt);
    sqlite3_finalize(m_liquid_load_charge_materials_delete_stmt);

    sqlite3_finalize(m_solid_liquid_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_single_stmt);
    sqlite3_finalize(m_solid_liquid_flue_gas_materials_select_custom_stmt);
	sqlite3_finalize(m_solid_liquid_flue_gas_materials_update_stmt);
	sqlite3_finalize(m_solid_liquid_flue_gas_materials_delete_stmt);

    sqlite3_finalize(m_gas_flue_gas_materials_insert_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_single_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_select_custom_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_update_stmt);
    sqlite3_finalize(m_gas_flue_gas_materials_delete_stmt);

    sqlite3_finalize(m_atmosphere_specific_heat_insert_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_single_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_select_custom_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_update_stmt);
    sqlite3_finalize(m_atmosphere_specific_heat_delete_stmt);

    sqlite3_finalize(m_wall_losses_surface_insert_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_single_stmt);
    sqlite3_finalize(m_wall_losses_surface_select_custom_stmt);
    sqlite3_finalize(m_wall_losses_surface_update_stmt);
    sqlite3_finalize(m_wall_losses_surface_delete_stmt);

    sqlite3_finalize(m_motor_data_insert_stmt);
    sqlite3_finalize(m_motor_data_select_stmt);
    sqlite3_finalize(m_motor_data_select_single_stmt);
    sqlite3_finalize(m_motor_data_select_custom_stmt);
    sqlite3_finalize(m_motor_data_update_stmt);
    sqlite3_finalize(m_motor_data_delete_stmt);
}

std::string SQLiteWrapper::convert_text( const unsigned char * text ) {
    return std::string( reinterpret_cast< const char* >( text ) );
}

std::vector<SolidLoadChargeMaterial> SQLite::getSolidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
	    auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
        slcm.setID(ID);
	    return slcm;
    };
    return get_all_objects<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_stmt, cb);
}

SolidLoadChargeMaterial SQLite::getSolidLoadChargeMaterialById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
	    slcm.setID(id);
        return slcm;
    };
    return get_object<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<SolidLoadChargeMaterial> SQLite::getCustomSolidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused in selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatSolid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 5);
        auto const meltingPoint = sqlite3_column_double(stmt, 6);
        auto slcm = SolidLoadChargeMaterial(substance, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint);
        slcm.setID(ID);
        return slcm;
    };
    return get_all_objects<SolidLoadChargeMaterial>(m_solid_load_charge_materials_select_custom_stmt, cb);
}

std::vector<GasLoadChargeMaterial> SQLite::getGasLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_all_objects<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_stmt, cb);
}

GasLoadChargeMaterial SQLite::getGasLoadChargeMaterialById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_object<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<GasLoadChargeMaterial> SQLite::getCustomGasLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const ID = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1); // secondary ID - unused for selects
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatVapor = sqlite3_column_double(stmt, 3);
        auto glcm = GasLoadChargeMaterial(substance, specificHeatVapor);
        glcm.setID(static_cast<std::size_t>(ID));
        return glcm;
    };
    return get_all_objects<GasLoadChargeMaterial>(m_gas_load_charge_materials_select_custom_stmt, cb);
}

std::vector<LiquidLoadChargeMaterial> SQLite::getLiquidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_all_objects<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_stmt, cb);
}

LiquidLoadChargeMaterial SQLite::getLiquidLoadChargeMaterialById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_object<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_single_stmt, id, cb);
}

std::vector<LiquidLoadChargeMaterial> SQLite::getCustomLiquidLoadChargeMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeatLiquid = sqlite3_column_double(stmt, 3);
        auto const latentHeat = sqlite3_column_double(stmt, 4);
        auto const specificHeatVapor = sqlite3_column_double(stmt, 5);
        auto const vaporizingTemperature = sqlite3_column_double(stmt, 6);
        auto llcm = LiquidLoadChargeMaterial(substance, specificHeatLiquid, latentHeat, specificHeatVapor, vaporizingTemperature);
        llcm.setID(id);
        return llcm;
    };
    return get_all_objects<LiquidLoadChargeMaterial>(m_liquid_load_charge_materials_select_custom_stmt, cb);
}

std::vector<SolidLiquidFlueGasMaterial> SQLite::getSolidLiquidFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                          o2 * 100, moisture * 100, nitrogen * 100);
	    slfgm.setID(id);
        return slfgm;
    };
    return get_all_objects<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_stmt, cb);
}

std::vector<SolidLiquidFlueGasMaterial> SQLite::getCustomSolidLiquidFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                                o2 * 100, moisture * 100, nitrogen * 100);
        slfgm.setID(id);
        return slfgm;
    };
    return get_all_objects<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_custom_stmt, cb);
}

SolidLiquidFlueGasMaterial SQLite::getSolidLiquidFlueGasMaterialById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const carbon = sqlite3_column_double(stmt, 3);
        auto const hydrogen = sqlite3_column_double(stmt, 4);
        auto const sulphur = sqlite3_column_double(stmt, 5);
        auto const inertAsh = sqlite3_column_double(stmt, 6);
        auto const o2 = sqlite3_column_double(stmt, 7);
        auto const moisture = sqlite3_column_double(stmt, 8);
        auto const nitrogen = sqlite3_column_double(stmt, 9);
        auto slfgm = SolidLiquidFlueGasMaterial(substance, carbon * 100, hydrogen * 100, sulphur * 100, inertAsh * 100,
                                          o2 * 100, moisture * 100, nitrogen * 100);
        slfgm.setID(id);
        return slfgm;
    };
    return get_object<SolidLiquidFlueGasMaterial>(m_solid_liquid_flue_gas_materials_select_single_stmt, id, cb);
}

std::vector<GasCompositions> SQLite::getGasFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_all_objects<GasCompositions>(m_gas_flue_gas_materials_select_stmt, cb);
}

GasCompositions SQLite::getGasFlueGasMaterialById(int id) const
{

    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_object<GasCompositions>(m_gas_flue_gas_materials_select_single_stmt, id, cb);
}

std::vector<GasCompositions> SQLite::getCustomGasFlueGasMaterials() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const CH4 = sqlite3_column_double(stmt, 3);
        auto const C2H6 = sqlite3_column_double(stmt, 4);
        auto const N2 = sqlite3_column_double(stmt, 5);
        auto const H2 = sqlite3_column_double(stmt, 6);
        auto const C3H8 = sqlite3_column_double(stmt, 7);
        auto const C4H10_CnH2n = sqlite3_column_double(stmt, 8);
        auto const H2O = sqlite3_column_double(stmt, 9);
        auto const CO = sqlite3_column_double(stmt, 10);
        auto const CO2 = sqlite3_column_double(stmt, 11);
        auto const SO2 = sqlite3_column_double(stmt, 12);
        auto const O2 = sqlite3_column_double(stmt, 13);
        auto const heatingValue = sqlite3_column_double(stmt, 14);
        auto const heatingValueVolume = sqlite3_column_double(stmt, 15);
        auto const specificGravity = sqlite3_column_double(stmt, 16);
        auto comp = GasCompositions(substance, CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2, heatingValue, heatingValueVolume, specificGravity);
        comp.setID(id);
        return comp;
    };
    return get_all_objects<GasCompositions>(m_gas_flue_gas_materials_select_custom_stmt, cb);
}

std::vector<Atmosphere> SQLite::getAtmosphereSpecificHeat() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_all_objects<Atmosphere>(m_atmosphere_specific_heat_select_stmt, cb);
}

std::vector<Atmosphere> SQLite::getCustomAtmosphereSpecificHeat() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_all_objects<Atmosphere>(m_atmosphere_specific_heat_select_custom_stmt, cb);
}

Atmosphere SQLite::getAtmosphereSpecificHeatById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const substance = convert_text(sqlite3_column_text(stmt, 2));
        auto const specificHeat = sqlite3_column_double(stmt, 3);
        auto a = Atmosphere(substance, specificHeat);
        a.setID(id);
        return a;
    };
    return get_object<Atmosphere>(m_atmosphere_specific_heat_select_single_stmt, id, cb);
}

std::vector<WallLosses> SQLite::getWallLossesSurface() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_all_objects<WallLosses>(m_wall_losses_surface_select_stmt, cb);
}

std::vector<WallLosses> SQLite::getCustomWallLossesSurface() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_all_objects<WallLosses>(m_wall_losses_surface_select_custom_stmt, cb);
}

WallLosses SQLite::getWallLossesSurfaceById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        std::string const surface = convert_text(sqlite3_column_text(stmt, 2));
        auto const conditionFactor = sqlite3_column_double(stmt, 3);
        auto wl = WallLosses(surface, conditionFactor);
        wl.setID(id);
        return wl;
    };
    return get_object<WallLosses>(m_wall_losses_surface_select_single_stmt, id, cb);
}

std::vector<MotorData> SQLite::getMotorData() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const catalog = convert_text(sqlite3_column_text(stmt, 4));
        auto const motorType = convert_text(sqlite3_column_text(stmt, 5));
        auto const hp = sqlite3_column_int(stmt, 6);
        auto const speed = sqlite3_column_int(stmt, 7);
        auto const fullLoadSpeed = sqlite3_column_int(stmt, 8);
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 9));
        auto const frameNumber = convert_text(sqlite3_column_text(stmt, 10));
        auto const voltageRating = sqlite3_column_int(stmt, 11);
        auto const purpose = convert_text(sqlite3_column_text(stmt, 12));
        auto const uFrame = sqlite3_column_int(stmt, 13);
        auto const cFace = sqlite3_column_int(stmt, 14);
        auto const verticalShaft = sqlite3_column_int(stmt, 15);
        auto const dFlange = sqlite3_column_int(stmt, 16);
        auto const serviceFactor = sqlite3_column_double(stmt, 17);
        auto const insulationClass = convert_text(sqlite3_column_text(stmt, 18));
        auto const weight = sqlite3_column_double(stmt, 19);
        auto const listPrice = sqlite3_column_double(stmt, 20);
        auto const windingResistance = sqlite3_column_double(stmt, 21);
        auto const warranty = sqlite3_column_double(stmt, 22);
        auto const rotorBars = sqlite3_column_int(stmt, 23);
        auto const statorSlots = sqlite3_column_int(stmt, 24);
        auto const efficiency100 = sqlite3_column_double(stmt, 25);
        auto const efficiency75 = sqlite3_column_double(stmt, 26);
        auto const efficiency50 = sqlite3_column_double(stmt, 27);
        auto const efficiency25 = sqlite3_column_double(stmt, 28);
        auto const powerFactor100 = sqlite3_column_double(stmt, 29);
        auto const powerFactor75 = sqlite3_column_double(stmt, 30);
        auto const powerFactor50 = sqlite3_column_double(stmt, 31);
        auto const powerFactor25 = sqlite3_column_double(stmt, 32);
        auto const torqueFullLoad = sqlite3_column_double(stmt, 33);
        auto const torqueBreakDown = sqlite3_column_double(stmt, 34);
        auto const torqueLockedRotor = sqlite3_column_double(stmt, 35);
        auto const ampsFullLoad = sqlite3_column_double(stmt, 36);
        auto const ampsIdle = sqlite3_column_double(stmt, 37);
        auto const ampsLockedRotor = sqlite3_column_double(stmt, 38);
        auto const stalledRotorTimeHot = sqlite3_column_double(stmt, 39);
        auto const stalledRotorTimeCold = sqlite3_column_double(stmt, 40);
        auto const peakVoltage0ms = sqlite3_column_double(stmt, 41);
        auto const peakVoltage5ms = sqlite3_column_double(stmt, 42);

        auto m = MotorData(manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                           uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                           rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                           powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                           stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms);
	    m.setId(id);
        return m;
    };
    return get_all_objects<MotorData>(m_motor_data_select_stmt, cb);
}

std::vector<MotorData> SQLite::getCustomMotorData() const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const id = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const catalog = convert_text(sqlite3_column_text(stmt, 4));
        auto const motorType = convert_text(sqlite3_column_text(stmt, 5));
        auto const hp = sqlite3_column_int(stmt, 6);
        auto const speed = sqlite3_column_int(stmt, 7);
        auto const fullLoadSpeed = sqlite3_column_int(stmt, 8);
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 9));
        auto const frameNumber = convert_text(sqlite3_column_text(stmt, 10));
        auto const voltageRating = sqlite3_column_int(stmt, 11);
        auto const purpose = convert_text(sqlite3_column_text(stmt, 12));
        auto const uFrame = sqlite3_column_int(stmt, 13);
        auto const cFace = sqlite3_column_int(stmt, 14);
        auto const verticalShaft = sqlite3_column_int(stmt, 15);
        auto const dFlange = sqlite3_column_int(stmt, 16);
        auto const serviceFactor = sqlite3_column_double(stmt, 17);
        auto const insulationClass = convert_text(sqlite3_column_text(stmt, 18));
        auto const weight = sqlite3_column_double(stmt, 19);
        auto const listPrice = sqlite3_column_double(stmt, 20);
        auto const windingResistance = sqlite3_column_double(stmt, 21);
        auto const warranty = sqlite3_column_double(stmt, 22);
        auto const rotorBars = sqlite3_column_int(stmt, 23);
        auto const statorSlots = sqlite3_column_int(stmt, 24);
        auto const efficiency100 = sqlite3_column_double(stmt, 25);
        auto const efficiency75 = sqlite3_column_double(stmt, 26);
        auto const efficiency50 = sqlite3_column_double(stmt, 27);
        auto const efficiency25 = sqlite3_column_double(stmt, 28);
        auto const powerFactor100 = sqlite3_column_double(stmt, 29);
        auto const powerFactor75 = sqlite3_column_double(stmt, 30);
        auto const powerFactor50 = sqlite3_column_double(stmt, 31);
        auto const powerFactor25 = sqlite3_column_double(stmt, 32);
        auto const torqueFullLoad = sqlite3_column_double(stmt, 33);
        auto const torqueBreakDown = sqlite3_column_double(stmt, 34);
        auto const torqueLockedRotor = sqlite3_column_double(stmt, 35);
        auto const ampsFullLoad = sqlite3_column_double(stmt, 36);
        auto const ampsIdle = sqlite3_column_double(stmt, 37);
        auto const ampsLockedRotor = sqlite3_column_double(stmt, 38);
        auto const stalledRotorTimeHot = sqlite3_column_double(stmt, 39);
        auto const stalledRotorTimeCold = sqlite3_column_double(stmt, 40);
        auto const peakVoltage0ms = sqlite3_column_double(stmt, 41);
        auto const peakVoltage5ms = sqlite3_column_double(stmt, 42);

        auto m = MotorData(manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                           uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                           rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                           powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                           stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms);
	    m.setId(id);
        return m;
    };
    return get_all_objects<MotorData>(m_motor_data_select_custom_stmt, cb);
}

MotorData SQLite::getMotorDataById(int id) const
{
    auto cb = [] (sqlite3_stmt * stmt) {
        auto const dbId = sqlite3_column_int(stmt, 0);
        sqlite3_column_int(stmt, 1);
        auto const manufacturer = convert_text(sqlite3_column_text(stmt, 2));
        auto const model = convert_text(sqlite3_column_text(stmt, 3));
        auto const catalog = convert_text(sqlite3_column_text(stmt, 4));
        auto const motorType = convert_text(sqlite3_column_text(stmt, 5));
        auto const hp = sqlite3_column_int(stmt, 6);
        auto const speed = sqlite3_column_int(stmt, 7);
        auto const fullLoadSpeed = sqlite3_column_int(stmt, 8);
        auto const enclosureType = convert_text(sqlite3_column_text(stmt, 9));
        auto const frameNumber = convert_text(sqlite3_column_text(stmt, 10));
        auto const voltageRating = sqlite3_column_int(stmt, 11);
        auto const purpose = convert_text(sqlite3_column_text(stmt, 12));
        auto const uFrame = sqlite3_column_int(stmt, 13);
        auto const cFace = sqlite3_column_int(stmt, 14);
        auto const verticalShaft = sqlite3_column_int(stmt, 15);
        auto const dFlange = sqlite3_column_int(stmt, 16);
        auto const serviceFactor = sqlite3_column_double(stmt, 17);
        auto const insulationClass = convert_text(sqlite3_column_text(stmt, 18));
        auto const weight = sqlite3_column_double(stmt, 19);
        auto const listPrice = sqlite3_column_double(stmt, 20);
        auto const windingResistance = sqlite3_column_double(stmt, 21);
        auto const warranty = sqlite3_column_double(stmt, 22);
        auto const rotorBars = sqlite3_column_int(stmt, 23);
        auto const statorSlots = sqlite3_column_int(stmt, 24);
        auto const efficiency100 = sqlite3_column_double(stmt, 25);
        auto const efficiency75 = sqlite3_column_double(stmt, 26);
        auto const efficiency50 = sqlite3_column_double(stmt, 27);
        auto const efficiency25 = sqlite3_column_double(stmt, 28);
        auto const powerFactor100 = sqlite3_column_double(stmt, 29);
        auto const powerFactor75 = sqlite3_column_double(stmt, 30);
        auto const powerFactor50 = sqlite3_column_double(stmt, 31);
        auto const powerFactor25 = sqlite3_column_double(stmt, 32);
        auto const torqueFullLoad = sqlite3_column_double(stmt, 33);
        auto const torqueBreakDown = sqlite3_column_double(stmt, 34);
        auto const torqueLockedRotor = sqlite3_column_double(stmt, 35);
        auto const ampsFullLoad = sqlite3_column_double(stmt, 36);
        auto const ampsIdle = sqlite3_column_double(stmt, 37);
        auto const ampsLockedRotor = sqlite3_column_double(stmt, 38);
        auto const stalledRotorTimeHot = sqlite3_column_double(stmt, 39);
        auto const stalledRotorTimeCold = sqlite3_column_double(stmt, 40);
        auto const peakVoltage0ms = sqlite3_column_double(stmt, 41);
        auto const peakVoltage5ms = sqlite3_column_double(stmt, 42);

        auto m = MotorData(manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                           uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                           rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                           powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                           stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms);
	    m.setId(dbId);
        return m;
    };
    return get_object<MotorData>(m_motor_data_select_single_stmt, id, cb);
}

void SQLite::create_select_stmt()
{
    std::string const select_solid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials)";

    prepare_statement(m_solid_load_charge_materials_select_stmt, select_solid_load_charge_materials);

    std::string const select_single_solid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_solid_load_charge_materials_select_single_stmt, select_single_solid_load_charge_materials);

    std::string const select_custom_solid_load_charge_materials =
            R"(SELECT id, sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                  mean_specific_heat_of_liquid, melting_point
           FROM solid_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_solid_load_charge_materials_select_custom_stmt, select_custom_solid_load_charge_materials);

    std::string const select_gas_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials)";

    prepare_statement(m_gas_load_charge_materials_select_stmt, select_gas_load_charge_materials);

    std::string const select_single_gas_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_gas_load_charge_materials_select_single_stmt, select_single_gas_load_charge_materials);

    std::string const select_custom_gas_load_charge_materials =
            R"(SELECT id, sid, substance, mean_specific_heat_of_vapor
           FROM gas_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_gas_load_charge_materials_select_custom_stmt, select_custom_gas_load_charge_materials);

    std::string const select_liquid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials)";

    prepare_statement(m_liquid_load_charge_materials_select_stmt, select_liquid_load_charge_materials);

    std::string const select_single_liquid_load_charge_materials =
        R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials
           WHERE id = ?)";

    prepare_statement(m_liquid_load_charge_materials_select_single_stmt, select_single_liquid_load_charge_materials);

    std::string const select_custom_liquid_load_charge_materials =
            R"(SELECT id, sid, substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                  mean_specific_heat_of_vapor, boiling_point
           FROM liquid_load_charge_materials
           WHERE sid = 1)";

    prepare_statement(m_liquid_load_charge_materials_select_custom_stmt, select_custom_liquid_load_charge_materials);

    std::string const select_solid_liquid_flue_gas_materials =
            R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_stmt, select_solid_liquid_flue_gas_materials);

    std::string const select_single_solid_liquid_flue_gas_materials =
            R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_single_stmt, select_single_solid_liquid_flue_gas_materials);

    std::string const select_custom_solid_liquid_flue_gas_materials =
            R"(SELECT id, sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen, moisture, ash
           FROM solid_liquid_flue_gas_materials
           WHERE sid = 1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_select_custom_stmt, select_custom_solid_liquid_flue_gas_materials);

    std::string const select_gas_flue_gas_materials =
            R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials)";

    prepare_statement(m_gas_flue_gas_materials_select_stmt, select_gas_flue_gas_materials);

    std::string const select_single_gas_flue_gas_materials =
            R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials
           WHERE id = ?)";

    prepare_statement(m_gas_flue_gas_materials_select_single_stmt, select_single_gas_flue_gas_materials);

    std::string const select_custom_gas_flue_gas_materials =
            R"(SELECT id, sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity
           FROM gas_flue_gas_materials
           WHERE sid = 1)";

    prepare_statement(m_gas_flue_gas_materials_select_custom_stmt, select_custom_gas_flue_gas_materials);

    std::string const select_atmosphere_specific_heat =
            R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat)";

    prepare_statement(m_atmosphere_specific_heat_select_stmt, select_atmosphere_specific_heat);

    std::string const select_single_atmosphere_specific_heat =
            R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat
           WHERE id = ?)";

    prepare_statement(m_atmosphere_specific_heat_select_single_stmt, select_single_atmosphere_specific_heat);

    std::string const select_custom_atmosphere_specific_heat =
            R"(SELECT id, sid, substance, specificHeat
           FROM atmosphere_specific_heat
           WHERE sid = 1)";

    prepare_statement(m_atmosphere_specific_heat_select_custom_stmt, select_custom_atmosphere_specific_heat);

    std::string const select_wall_losses_surface =
            R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface)";

    prepare_statement(m_wall_losses_surface_select_stmt, select_wall_losses_surface);

    std::string const select_single_wall_losses_surface =
            R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface
           WHERE id = ?)";

    prepare_statement(m_wall_losses_surface_select_single_stmt, select_single_wall_losses_surface);

    std::string const select_custom_wall_losses_surface =
            R"(SELECT id, sid, surface, conditionFactor
           FROM wall_losses_surface
           WHERE sid = 1)";

    prepare_statement(m_wall_losses_surface_select_custom_stmt, select_custom_wall_losses_surface);

    std::string const select_motor_data =
            R"(SELECT id, sid, manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                    uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                    rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                    powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                    stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms
           FROM motor_data)";

    prepare_statement(m_motor_data_select_stmt, select_motor_data);

    std::string const select_single_motor_data =
            R"(SELECT id, sid, manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                    uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                    rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                    powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                    stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms
           FROM motor_data
           WHERE id = ?)";

    prepare_statement(m_motor_data_select_single_stmt, select_single_motor_data);

    std::string const select_custom_motor_data =
            R"(SELECT id, sid, manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                    uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                    rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                    powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                    stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms
           FROM motor_data
           WHERE sid = 1)";

    prepare_statement(m_motor_data_select_custom_stmt, select_custom_motor_data);
}

void SQLite::create_update_and_delete_stmt() {
    std::string const delete_solid_load_charge_materials =
            R"(DELETE from solid_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_solid_load_charge_materials_delete_stmt, delete_solid_load_charge_materials);

    std::string const update_custom_solid_load_charge_materials =
            R"(UPDATE solid_load_charge_materials
               SET substance=?, mean_specific_heat_of_solid=?, latent_heat_of_fusion=?, mean_specific_heat_of_liquid=?, melting_point=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_solid_load_charge_materials_update_stmt, update_custom_solid_load_charge_materials);

    std::string const delete_gas_load_charge_materials =
            R"(DELETE from gas_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_gas_load_charge_materials_delete_stmt, delete_gas_load_charge_materials);

    std::string const update_gas_load_charge_materials =
            R"(UPDATE gas_load_charge_materials
               SET substance=?, mean_specific_heat_of_vapor=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_gas_load_charge_materials_update_stmt, update_gas_load_charge_materials);

    std::string const delete_liquid_load_charge_materials =
            R"(DELETE from liquid_load_charge_materials where id=? and sid=1)";

    prepare_statement(m_liquid_load_charge_materials_delete_stmt, delete_liquid_load_charge_materials);

    std::string const update_liquid_load_charge_materials =
            R"(UPDATE liquid_load_charge_materials
               SET substance=?, mean_specific_heat_of_liquid=?, latent_heat_of_vaporisation=?, mean_specific_heat_of_vapor=?, boiling_point=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_liquid_load_charge_materials_update_stmt, update_liquid_load_charge_materials);

    std::string const delete_solid_liquid_flue_gas_materials =
            R"(DELETE from solid_liquid_flue_gas_materials where id=? and sid=1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_delete_stmt, delete_solid_liquid_flue_gas_materials);

    std::string const update_solid_liquid_flue_gas_materials =
            R"(UPDATE solid_liquid_flue_gas_materials
               SET substance=?, carbon=?, hydrogen=?, nitrogen=?, sulfur=?, oxygen=?, moisture=?, ash=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_solid_liquid_flue_gas_materials_update_stmt, update_solid_liquid_flue_gas_materials);

    std::string const delete_gas_flue_gas_materials =
            R"(DELETE from gas_flue_gas_materials where id=? and sid=1)";

    prepare_statement(m_gas_flue_gas_materials_delete_stmt, delete_gas_flue_gas_materials);

    std::string const update_gas_flue_gas_materials =
            R"(UPDATE gas_flue_gas_materials
               SET substance=?, hydrogen=?, methane=?, ethylene=?, ethane=?, sulfur_dioxide=?, carbon_monoxide=?,
               carbon_dioxide=?, nitrogen=?, oxygen=?, hydrogen_sulfide=?, benzene=?, heatingValue=?,
               heatingValueVolume=?, specificGravity=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_gas_flue_gas_materials_update_stmt, update_gas_flue_gas_materials);

    std::string const delete_atmosphere_specific_heat =
            R"(DELETE from atmosphere_specific_heat where id=? and sid=1)";

    prepare_statement(m_atmosphere_specific_heat_delete_stmt, delete_atmosphere_specific_heat);

    std::string const update_atmosphere_specific_heat =
            R"(UPDATE atmosphere_specific_heat
               SET substance=?, specificHeat=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_atmosphere_specific_heat_update_stmt, update_atmosphere_specific_heat);

    std::string const delete_wall_losses_surface =
            R"(DELETE from wall_losses_surface where id=? and sid=1)";

    prepare_statement(m_wall_losses_surface_delete_stmt, delete_wall_losses_surface);

    std::string const update_wall_losses_surface =
            R"(UPDATE wall_losses_surface
               SET surface=?, conditionFactor=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_wall_losses_surface_update_stmt, update_wall_losses_surface);


    std::string const delete_motor_data =
            R"(DELETE from motor_data where id=? and sid=1)";

    prepare_statement(m_motor_data_delete_stmt, delete_motor_data);

    std::string const update_motor_data =
            R"(UPDATE motor_data
               SET manufacturer=?, model=?, catalog=?, motorType=?, hp=?, speed=?, fullLoadSpeed=?, enclosureType=?, frameNumber=?,
               voltageRating=?, purpose=?, uFrame=?, cFace=?, verticalShaft=?, dFlange=?, serviceFactor=?, insulationClass=?,
               weight=?, listPrice=?, windingResistance=?, warranty=?, rotorBars=?, statorSlots=?, efficiency100=?, efficiency75=?,
               efficiency50=?, efficiency25=?, powerFactor100=?, powerFactor75=?, powerFactor50=?, powerFactor25=?, torqueFullLoad=?,
               torqueBreakDown=?, torqueLockedRotor=?, ampsFullLoad=?, ampsIdle=?, ampsLockedRotor=?, stalledRotorTimeHot=?,
               stalledRotorTimeCold=?, peakVoltage0ms=?, peakVoltage5ms=?
               WHERE id=? AND sid = 1)";

    prepare_statement(m_motor_data_update_stmt, update_motor_data);
}

void SQLite::create_insert_stmt() {
    const std::string solid_load_charge_materials_insert_sql =
            R"(INSERT INTO solid_load_charge_materials(sid, substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                                                   mean_specific_heat_of_liquid, melting_point)
           VALUES (?,?,?,?,?,?))";

    prepare_statement(m_solid_load_charge_materials_insert_stmt, solid_load_charge_materials_insert_sql);

    const std::string gas_load_charge_materials_insert_sql =
            R"(INSERT INTO gas_load_charge_materials(sid, substance,mean_specific_heat_of_vapor) VALUES (?,?,?))";

    prepare_statement(m_gas_load_charge_materials_insert_stmt, gas_load_charge_materials_insert_sql);

    const std::string liquid_load_charge_materials_insert_sql =
            R"(INSERT INTO liquid_load_charge_materials(sid, substance, mean_specific_heat_of_liquid,
                                                    latent_heat_of_vaporisation, mean_specific_heat_of_vapor,
                                                    boiling_point)
           VALUES (?,?,?,?,?,?))";

    prepare_statement(m_liquid_load_charge_materials_insert_stmt, liquid_load_charge_materials_insert_sql);

    const std::string solid_liquid_flue_gas_materials_insert_sql =
            R"(INSERT INTO solid_liquid_flue_gas_materials(sid, substance, carbon, hydrogen, nitrogen, sulfur, oxygen,
                                                       moisture, ash)
           VALUES (?,?,?,?,?,?,?,?,?))";

    prepare_statement(m_solid_liquid_flue_gas_materials_insert_stmt, solid_liquid_flue_gas_materials_insert_sql);

    const std::string gas_flue_gas_materials_insert_sql =
            R"(INSERT INTO gas_flue_gas_materials(sid, substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide,
                  carbon_monoxide, carbon_dioxide, nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity)
           VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?))";

    prepare_statement(m_gas_flue_gas_materials_insert_stmt, gas_flue_gas_materials_insert_sql);

    const std::string atmosphere_specific_heat_insert_sql =
            R"(INSERT INTO atmosphere_specific_heat(sid, substance, specificHeat)
           VALUES (?,?,?))";

    prepare_statement(m_atmosphere_specific_heat_insert_stmt, atmosphere_specific_heat_insert_sql);

    const std::string wall_losses_surface_insert_sql =
            R"(INSERT INTO wall_losses_surface(sid, surface, conditionFactor)
           VALUES (?,?,?))";

    prepare_statement(m_wall_losses_surface_insert_stmt, wall_losses_surface_insert_sql);

    const std::string motor_data_insert_sql =
            R"(INSERT INTO motor_data(sid, manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                    uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                    rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                    powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                    stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms)
           VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?))";

    // 42 entries

    prepare_statement(m_motor_data_insert_stmt, motor_data_insert_sql);
}


void SQLite::create_tables()
{
    const std::string solid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_load_charge_materials (
           id integer PRIMARY KEY AUTOINCREMENT,
           sid integer NOT NULL,
           substance text NOT NULL DEFAULT "" UNIQUE,
           mean_specific_heat_of_solid real NOT NULL, -- Btu/lb.F
           latent_heat_of_fusion real NOT NULL, -- Btu/lb.
           mean_specific_heat_of_liquid real NOT NULL, -- Btu/lb.F
           melting_point real NOT NULL, -- F.
           UNIQUE (substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                   mean_specific_heat_of_liquid, melting_point)
                  );)";

    execute_command(solid_load_charge_materials_table_sql);

    const std::string gas_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             UNIQUE (substance, mean_specific_heat_of_vapor)
            );)";

    execute_command(gas_load_charge_materials_table_sql);

    const std::string liquid_load_charge_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS liquid_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             mean_specific_heat_of_liquid real NOT NULL, -- kJ/kg.F
             latent_heat_of_vaporisation real NOT NULL, -- Btu/lb.
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             boiling_point real NOT NULL, -- F.
             UNIQUE (substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                     mean_specific_heat_of_vapor, boiling_point)
          );)";

    execute_command(liquid_load_charge_materials_table_sql);

    const std::string solid_liquid_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS solid_liquid_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
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

    const std::string gas_flue_gas_materials_table_sql =
        R"(CREATE TABLE IF NOT EXISTS gas_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
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
             heatingValue real NOT NULL, -- HV
             heatingValueVolume real NOT NULL, -- HvVolume
             specificGravity real NOT NULL, -- specificGrav
             UNIQUE (substance, hydrogen, methane, ethylene, ethane, sulfur_dioxide, carbon_monoxide, carbon_dioxide,
                     nitrogen, oxygen, hydrogen_sulfide, benzene, heatingValue, heatingValueVolume, specificGravity)
      );)";

    execute_command(gas_flue_gas_materials_table_sql);

    const std::string atmosphere_specific_heat_table_sql =
            R"(CREATE TABLE IF NOT EXISTS atmosphere_specific_heat (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             substance text NOT NULL DEFAULT "" UNIQUE,
             specificHeat real NOT NULL, -- Btu/(scf.F)
             UNIQUE (substance, specificHeat)
      );)";

    execute_command(atmosphere_specific_heat_table_sql);

    const std::string wall_losses_surface_table_sql =
            R"(CREATE TABLE IF NOT EXISTS wall_losses_surface (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             surface text NOT NULL DEFAULT "" UNIQUE,
             conditionFactor real NOT NULL, -- unitless
             UNIQUE (surface, conditionFactor)
      );)";

    execute_command(wall_losses_surface_table_sql);

    const std::string motor_table_sql =
            R"(CREATE TABLE IF NOT EXISTS motor_data (
             id integer PRIMARY KEY AUTOINCREMENT,
             sid integer NOT NULL,
             manufacturer text NOT NULL DEFAULT "" UNIQUE,
             model text NOT NULL,
             catalog text NOT NULL,
             motorType text NOT NULL,
             hp integer NOT NULL,
             speed integer NOT NULL,
             fullLoadSpeed integer NOT NULL,
             enclosureType text NOT NULL,
             frameNumber text NOT NULL,
             voltageRating integer NOT NULL,
             purpose text NOT NULL,
             uFrame integer NOT NULL,
             cFace integer NOT NULL,
             verticalShaft integer NOT NULL,
             dFlange integer NOT NULL,
             serviceFactor real NOT NULL,
             insulationClass text NOT NULL,
             weight real NOT NULL, -- lbs,
             listPrice real NOT NULL, -- US dollars,
             windingResistance real NOT NULL, -- mOhms at 25C,
             warranty real NOT NULL, -- years,
             rotorBars integer NOT NULL,
             statorSlots integer NOT NULL,
             efficiency100 real NOT NULL,
             efficiency75 real NOT NULL,
             efficiency50 real NOT NULL,
             efficiency25 real NOT NULL,
             powerFactor100 real NOT NULL,
             powerFactor75 real NOT NULL,
             powerFactor50 real NOT NULL,
             powerFactor25 real NOT NULL,
             torqueFullLoad real NOT NULL,
             torqueBreakDown real NOT NULL,
             torqueLockedRotor real NOT NULL,
             ampsFullLoad real NOT NULL,
             ampsIdle real NOT NULL,
             ampsLockedRotor real NOT NULL,
             stalledRotorTimeHot real NOT NULL, -- seconds,
             stalledRotorTimeCold real NOT NULL, -- seconds,
             peakVoltage0ms real NOT NULL,
             peakVoltage5ms real NOT NULL,
             UNIQUE (manufacturer, model, catalog, motorType, hp, speed, fullLoadSpeed, enclosureType, frameNumber, voltageRating, purpose,
                    uFrame, cFace, verticalShaft, dFlange, serviceFactor, insulationClass, weight, listPrice, windingResistance, warranty,
                    rotorBars, statorSlots, efficiency100, efficiency75, efficiency50, efficiency25, powerFactor100, powerFactor75, powerFactor50,
                    powerFactor25, torqueFullLoad, torqueBreakDown, torqueLockedRotor, ampsFullLoad, ampsIdle, ampsLockedRotor, stalledRotorTimeHot,
                    stalledRotorTimeCold, peakVoltage0ms, peakVoltage5ms)
      );)";

    execute_command(motor_table_sql);
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
    for( auto const & material : get_default_atmosphere_specific_heat() ) {
        insert_atmosphere_specific_heat(material);
    }
    for( auto const & surface : get_default_wall_losses_surface() ) {
        insert_wall_losses_surface(surface);
    }
	for( auto const & motor : get_default_motor_data() ) {
		insert_motor_data(motor);
    }
}

bool SQLite::insert_solid_load_charge_materials(SolidLoadChargeMaterial const & material)
{
    bind_value(m_solid_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_solid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 6, material.getMeltingPoint());

    int rc = step_command(m_solid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertSolidLoadChargeMaterials(SolidLoadChargeMaterial const & material)
{
    bind_value(m_solid_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_solid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_insert_stmt, 6, material.getMeltingPoint());

    int rc = step_command(m_solid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteSolidLoadChargeMaterial(const int id) {
	if (isDefaultMaterial(id, get_default_solid_load_charge_materials().size())) {
        return false;
    }
	bind_value(m_solid_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_solid_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
	reset_command(m_solid_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateSolidLoadChargeMaterial(SolidLoadChargeMaterial const & material) {
    if (isDefaultMaterial(material.getID(), get_default_solid_load_charge_materials().size())) {
        return false;
    }
    bind_value(m_solid_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_solid_load_charge_materials_update_stmt, 2, material.getSpecificHeatSolid());
    bind_value(m_solid_load_charge_materials_update_stmt, 3, material.getLatentHeat());
    bind_value(m_solid_load_charge_materials_update_stmt, 4, material.getSpecificHeatLiquid());
    bind_value(m_solid_load_charge_materials_update_stmt, 5, material.getMeltingPoint());
    bind_value(m_solid_load_charge_materials_update_stmt, 6, material.getID());

    int rc = step_command(m_solid_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_gas_load_charge_materials(GasLoadChargeMaterial const & material)
{
    bind_value(m_gas_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_gas_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_gas_load_charge_materials_insert_stmt, 3, material.getSpecificHeatVapor());

    int rc = step_command(m_gas_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertGasLoadChargeMaterials(GasLoadChargeMaterial const & material)
{
    bind_value(m_gas_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_gas_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_gas_load_charge_materials_insert_stmt, 3, material.getSpecificHeatVapor());

    int rc = step_command(m_gas_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteGasLoadChargeMaterial(int const id) {
    if (isDefaultMaterial(id, get_default_gas_load_charge_materials().size())) {
        return false;
    }
    bind_value(m_gas_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_gas_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateGasLoadChargeMaterial(GasLoadChargeMaterial const & material) {
    if (isDefaultMaterial(material.getID(), get_default_gas_load_charge_materials().size())) {
        return false;
    }
    bind_value(m_gas_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_gas_load_charge_materials_update_stmt, 2, material.getSpecificHeatVapor());
    bind_value(m_gas_load_charge_materials_update_stmt, 3, material.getID());

    int rc = step_command(m_gas_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_liquid_load_charge_materials(LiquidLoadChargeMaterial const & material)
{
    bind_value(m_liquid_load_charge_materials_insert_stmt, 1, 0);
    bind_value(m_liquid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 6, material.getVaporizingTemperature());

    int rc = step_command(m_liquid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertLiquidLoadChargeMaterials(LiquidLoadChargeMaterial const & material)
{
    bind_value(m_liquid_load_charge_materials_insert_stmt, 1, 1);
    bind_value(m_liquid_load_charge_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 3, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 4, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 5, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_insert_stmt, 6, material.getVaporizingTemperature());

    int rc = step_command(m_liquid_load_charge_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteLiquidLoadChargeMaterial(const int id) {
    if (isDefaultMaterial(id, get_default_liquid_load_charge_materials().size())) {
        return false;
    }
    bind_value(m_liquid_load_charge_materials_delete_stmt, 1, id);
    int rc = step_command(m_liquid_load_charge_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateLiquidLoadChargeMaterial(LiquidLoadChargeMaterial const & material) {
    if (isDefaultMaterial(material.getID(), get_default_liquid_load_charge_materials().size())) {
        return false;
    }
    bind_value(m_liquid_load_charge_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_liquid_load_charge_materials_update_stmt, 2, material.getSpecificHeatLiquid());
    bind_value(m_liquid_load_charge_materials_update_stmt, 3, material.getLatentHeat());
    bind_value(m_liquid_load_charge_materials_update_stmt, 4, material.getSpecificHeatVapor());
    bind_value(m_liquid_load_charge_materials_update_stmt, 5, material.getVaporizingTemperature());
    bind_value(m_liquid_load_charge_materials_update_stmt, 6, material.getID());

    int rc = step_command(m_liquid_load_charge_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_liquid_load_charge_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_solid_liquid_flue_gas_materials(SolidLiquidFlueGasMaterial const & material)
{
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 1, 0);
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 3, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 4, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 6, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 7, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 8, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 9, material.getNitrogen());

    int rc = step_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::insertSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const & material) const {
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 1, 1);
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 2, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 3, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 4, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 6, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 7, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 8, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_insert_stmt, 9, material.getNitrogen());

    int rc = step_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteSolidLiquidFlueGasMaterial(const int id) {
    if (isDefaultMaterial(id, get_default_solid_liquid_flue_gas_materials().size())) {
        return false;
    }
    bind_value(m_solid_liquid_flue_gas_materials_delete_stmt, 1, id);
    int rc = step_command(m_solid_liquid_flue_gas_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const & material) {
    if (isDefaultMaterial(material.getID(), get_default_solid_liquid_flue_gas_materials().size())) {
        return false;
    }
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 2, material.getCarbon());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 3, material.getHydrogen());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 4, material.getNitrogen());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 5, material.getSulphur());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 6, material.getO2());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 7, material.getMoisture());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 8, material.getInertAsh());
    bind_value(m_solid_liquid_flue_gas_materials_update_stmt, 9, material.getID());

    int rc = step_command(m_solid_liquid_flue_gas_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_solid_liquid_flue_gas_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_gas_flue_gas_materials(GasCompositions const & comps)
{
    bind_value(m_gas_flue_gas_materials_insert_stmt, 1, 0);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 2, comps.getSubstance());
    bind_value(m_gas_flue_gas_materials_insert_stmt, 3, comps.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 4, comps.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 5, comps.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 6, comps.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 7, comps.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 8, comps.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 9, comps.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 10, comps.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 11, comps.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 12, comps.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 13, comps.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 14, comps.heatingValue);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 15, comps.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 16, comps.specificGravity);

    int rc = step_command(m_gas_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_insert_stmt);
    return valid_insert;
}

// used for inserting custom materials, part of the public API
bool SQLite::insertGasFlueGasMaterial(GasCompositions const & comps) const {
    bind_value(m_gas_flue_gas_materials_insert_stmt, 1, 1);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 2, comps.getSubstance());
    bind_value(m_gas_flue_gas_materials_insert_stmt, 3, comps.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 4, comps.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 5, comps.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 6, comps.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 7, comps.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 8, comps.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 9, comps.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 10, comps.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 11, comps.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 12, comps.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 13, comps.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_insert_stmt, 14, comps.heatingValue);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 15, comps.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_insert_stmt, 16, comps.specificGravity);

    int rc = step_command(m_gas_flue_gas_materials_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteGasFlueGasMaterial(const int id) {
    if (isDefaultMaterial(id, get_default_gas_flue_gas_materials().size())) {
        return false;
    }
    bind_value(m_gas_flue_gas_materials_delete_stmt, 1, id);
    int rc = step_command(m_gas_flue_gas_materials_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_delete_stmt);
    return valid_command;
}

bool SQLite::updateGasFlueGasMaterial(GasCompositions const & material ) {
    if (isDefaultMaterial(material.getID(), get_default_gas_flue_gas_materials().size())) {
        return false;
    }
    bind_value(m_gas_flue_gas_materials_update_stmt, 1, material.getSubstance());
    bind_value(m_gas_flue_gas_materials_update_stmt, 2, material.getGasByVol("CH4"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 3, material.getGasByVol("C2H6"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 4, material.getGasByVol("N2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 5, material.getGasByVol("H2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 6, material.getGasByVol("C3H8"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 7, material.getGasByVol("C4H10_CnH2n"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 8, material.getGasByVol("H2O"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 9, material.getGasByVol("CO"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 10, material.getGasByVol("CO2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 11, material.getGasByVol("SO2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 12, material.getGasByVol("O2"));
    bind_value(m_gas_flue_gas_materials_update_stmt, 13, material.heatingValue);
    bind_value(m_gas_flue_gas_materials_update_stmt, 14, material.heatingValueVolume);
    bind_value(m_gas_flue_gas_materials_update_stmt, 15, material.specificGravity);
    bind_value(m_gas_flue_gas_materials_update_stmt, 16, material.getID());

    int rc = step_command(m_gas_flue_gas_materials_update_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_gas_flue_gas_materials_update_stmt);
    return valid_command;
}

bool SQLite::insert_atmosphere_specific_heat(Atmosphere const & sh)
{
    bind_value(m_atmosphere_specific_heat_insert_stmt, 1, 0);
    bind_value(m_atmosphere_specific_heat_insert_stmt, 2, sh.getSubstance());
    bind_value(m_atmosphere_specific_heat_insert_stmt, 3, sh.getSpecificHeat());

    int rc = step_command(m_atmosphere_specific_heat_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_insert_stmt);
    return valid_insert;
}

// part of the public API used to insert custom materials
bool SQLite::insertAtmosphereSpecificHeat(Atmosphere const & material) {
    bind_value(m_atmosphere_specific_heat_insert_stmt, 1, 1);
    bind_value(m_atmosphere_specific_heat_insert_stmt, 2, material.getSubstance());
    bind_value(m_atmosphere_specific_heat_insert_stmt, 3, material.getSpecificHeat());

    int rc = step_command(m_atmosphere_specific_heat_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteAtmosphereSpecificHeat(const int id) {
    if (isDefaultMaterial(id, get_default_atmosphere_specific_heat().size())) {
        return false;
    }
    bind_value(m_atmosphere_specific_heat_delete_stmt, 1, id);
    int rc = step_command(m_atmosphere_specific_heat_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_delete_stmt);
    return valid_command;
}

bool SQLite::updateAtmosphereSpecificHeat(Atmosphere const &material){
    if (isDefaultMaterial(material.getID(), get_default_atmosphere_specific_heat().size())) {
        return false;
    }
    bind_value(m_atmosphere_specific_heat_update_stmt, 1, material.getSubstance());
    bind_value(m_atmosphere_specific_heat_update_stmt, 2, material.getSpecificHeat());
    bind_value(m_atmosphere_specific_heat_update_stmt, 3, material.getID());

    int rc = step_command(m_atmosphere_specific_heat_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_atmosphere_specific_heat_update_stmt);
    return valid_insert;
}

bool SQLite::insert_wall_losses_surface(WallLosses const & cf)
{
    bind_value(m_wall_losses_surface_insert_stmt, 1, 0);
    bind_value(m_wall_losses_surface_insert_stmt, 2, cf.getSurface());
    bind_value(m_wall_losses_surface_insert_stmt, 3, cf.getConditionFactor());

    int rc = step_command(m_wall_losses_surface_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_insert_stmt);
    return valid_insert;
}

bool SQLite::insertWallLossesSurface(WallLosses const & material)
{
    bind_value(m_wall_losses_surface_insert_stmt, 1, 1);
    bind_value(m_wall_losses_surface_insert_stmt, 2, material.getSurface());
    bind_value(m_wall_losses_surface_insert_stmt, 3, material.getConditionFactor());

    int rc = step_command(m_wall_losses_surface_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteWallLossesSurface(int id) {
    if (isDefaultMaterial(id, get_default_wall_losses_surface().size())) {
        return false;
    }
    bind_value(m_wall_losses_surface_delete_stmt, 1, id);
    int rc = step_command(m_wall_losses_surface_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_wall_losses_surface_delete_stmt);
    return valid_command;
}

bool SQLite::updateWallLossesSurface(WallLosses const &material) {
    if (isDefaultMaterial(material.getID(), get_default_wall_losses_surface().size())) {
        return false;
    }
    bind_value(m_wall_losses_surface_update_stmt, 1, material.getSurface());
    bind_value(m_wall_losses_surface_update_stmt, 2, material.getConditionFactor());
    bind_value(m_wall_losses_surface_update_stmt, 3, material.getID());

    int rc = step_command(m_wall_losses_surface_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_wall_losses_surface_update_stmt);
    return valid_insert;
}

bool SQLite::insert_motor_data(MotorData const & m)
{
    bind_value(m_motor_data_insert_stmt, 1, 0);
    bind_value(m_motor_data_insert_stmt, 2, m.manufacturer);
    bind_value(m_motor_data_insert_stmt, 3, m.model);
    bind_value(m_motor_data_insert_stmt, 4, m.catalog);
    bind_value(m_motor_data_insert_stmt, 5, m.motorType);
    bind_value(m_motor_data_insert_stmt, 6, m.hp);
    bind_value(m_motor_data_insert_stmt, 7, m.speed);
    bind_value(m_motor_data_insert_stmt, 8, m.fullLoadSpeed);
    bind_value(m_motor_data_insert_stmt, 9, m.enclosureType);
    bind_value(m_motor_data_insert_stmt, 10, m.frameNumber);
    bind_value(m_motor_data_insert_stmt, 11, m.voltageRating);
    bind_value(m_motor_data_insert_stmt, 12, m.purpose);
    bind_value(m_motor_data_insert_stmt, 13, m.uFrame);
    bind_value(m_motor_data_insert_stmt, 14, m.cFace);
    bind_value(m_motor_data_insert_stmt, 15, m.verticalShaft);
    bind_value(m_motor_data_insert_stmt, 16, m.dFlange);
    bind_value(m_motor_data_insert_stmt, 17, m.serviceFactor);
    bind_value(m_motor_data_insert_stmt, 18, m.insulationClass);
    bind_value(m_motor_data_insert_stmt, 19, m.weight);
    bind_value(m_motor_data_insert_stmt, 20, m.listPrice);
    bind_value(m_motor_data_insert_stmt, 21, m.windingResistance);
    bind_value(m_motor_data_insert_stmt, 22, m.warranty);
    bind_value(m_motor_data_insert_stmt, 23, m.rotorBars);
    bind_value(m_motor_data_insert_stmt, 24, m.statorSlots);
    bind_value(m_motor_data_insert_stmt, 25, m.efficiency100);
    bind_value(m_motor_data_insert_stmt, 26, m.efficiency75);
    bind_value(m_motor_data_insert_stmt, 27, m.efficiency50);
    bind_value(m_motor_data_insert_stmt, 28, m.efficiency25);
    bind_value(m_motor_data_insert_stmt, 29, m.powerFactor100);
    bind_value(m_motor_data_insert_stmt, 30, m.powerFactor75);
    bind_value(m_motor_data_insert_stmt, 31, m.powerFactor50);
    bind_value(m_motor_data_insert_stmt, 32, m.powerFactor25);
    bind_value(m_motor_data_insert_stmt, 33, m.torqueFullLoad);
    bind_value(m_motor_data_insert_stmt, 34, m.torqueBreakDown);
    bind_value(m_motor_data_insert_stmt, 35, m.torqueLockedRotor);
    bind_value(m_motor_data_insert_stmt, 36, m.ampsFullLoad);
    bind_value(m_motor_data_insert_stmt, 37, m.ampsIdle);
    bind_value(m_motor_data_insert_stmt, 38, m.ampsLockedRotor);
    bind_value(m_motor_data_insert_stmt, 39, m.stalledRotorTimeHot);
    bind_value(m_motor_data_insert_stmt, 40, m.stalledRotorTimeCold);
    bind_value(m_motor_data_insert_stmt, 41, m.peakVoltage0ms);
    bind_value(m_motor_data_insert_stmt, 42, m.peakVoltage5ms);

    int rc = step_command(m_motor_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_insert_stmt);
    return valid_insert;
}

// public API for inserts
bool SQLite::insertMotorData(MotorData const & m){
    bind_value(m_motor_data_insert_stmt, 1, 1);
    bind_value(m_motor_data_insert_stmt, 2, m.manufacturer);
    bind_value(m_motor_data_insert_stmt, 3, m.model);
    bind_value(m_motor_data_insert_stmt, 4, m.catalog);
    bind_value(m_motor_data_insert_stmt, 5, m.motorType);
    bind_value(m_motor_data_insert_stmt, 6, m.hp);
    bind_value(m_motor_data_insert_stmt, 7, m.speed);
    bind_value(m_motor_data_insert_stmt, 8, m.fullLoadSpeed);
    bind_value(m_motor_data_insert_stmt, 9, m.enclosureType);
    bind_value(m_motor_data_insert_stmt, 10, m.frameNumber);
    bind_value(m_motor_data_insert_stmt, 11, m.voltageRating);
    bind_value(m_motor_data_insert_stmt, 12, m.purpose);
    bind_value(m_motor_data_insert_stmt, 13, m.uFrame);
    bind_value(m_motor_data_insert_stmt, 14, m.cFace);
    bind_value(m_motor_data_insert_stmt, 15, m.verticalShaft);
    bind_value(m_motor_data_insert_stmt, 16, m.dFlange);
    bind_value(m_motor_data_insert_stmt, 17, m.serviceFactor);
    bind_value(m_motor_data_insert_stmt, 18, m.insulationClass);
    bind_value(m_motor_data_insert_stmt, 19, m.weight);
    bind_value(m_motor_data_insert_stmt, 20, m.listPrice);
    bind_value(m_motor_data_insert_stmt, 21, m.windingResistance);
    bind_value(m_motor_data_insert_stmt, 22, m.warranty);
    bind_value(m_motor_data_insert_stmt, 23, m.rotorBars);
    bind_value(m_motor_data_insert_stmt, 24, m.statorSlots);
    bind_value(m_motor_data_insert_stmt, 25, m.efficiency100);
    bind_value(m_motor_data_insert_stmt, 26, m.efficiency75);
    bind_value(m_motor_data_insert_stmt, 27, m.efficiency50);
    bind_value(m_motor_data_insert_stmt, 28, m.efficiency25);
    bind_value(m_motor_data_insert_stmt, 29, m.powerFactor100);
    bind_value(m_motor_data_insert_stmt, 30, m.powerFactor75);
    bind_value(m_motor_data_insert_stmt, 31, m.powerFactor50);
    bind_value(m_motor_data_insert_stmt, 32, m.powerFactor25);
    bind_value(m_motor_data_insert_stmt, 33, m.torqueFullLoad);
    bind_value(m_motor_data_insert_stmt, 34, m.torqueBreakDown);
    bind_value(m_motor_data_insert_stmt, 35, m.torqueLockedRotor);
    bind_value(m_motor_data_insert_stmt, 36, m.ampsFullLoad);
    bind_value(m_motor_data_insert_stmt, 37, m.ampsIdle);
    bind_value(m_motor_data_insert_stmt, 38, m.ampsLockedRotor);
    bind_value(m_motor_data_insert_stmt, 39, m.stalledRotorTimeHot);
    bind_value(m_motor_data_insert_stmt, 40, m.stalledRotorTimeCold);
    bind_value(m_motor_data_insert_stmt, 41, m.peakVoltage0ms);
    bind_value(m_motor_data_insert_stmt, 42, m.peakVoltage5ms);

    int rc = step_command(m_motor_data_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_insert_stmt);
    return valid_insert;
}

bool SQLite::deleteMotorData(int id) {
    if (isDefaultMaterial(id, get_default_motor_data().size())) {
        return false;
    }
    bind_value(m_motor_data_delete_stmt, 1, id);
    int rc = step_command(m_motor_data_delete_stmt);
    bool valid_command = step_validity(rc);
    reset_command(m_motor_data_delete_stmt);
    return valid_command;
}

bool SQLite::updateMotorData(MotorData const & m) {
    if (isDefaultMaterial(m.id, get_default_motor_data().size())) {
        return false;
    }
    bind_value(m_motor_data_update_stmt, 1, m.manufacturer);
    bind_value(m_motor_data_update_stmt, 2, m.model);
    bind_value(m_motor_data_update_stmt, 3, m.catalog);
    bind_value(m_motor_data_update_stmt, 4, m.motorType);
    bind_value(m_motor_data_update_stmt, 5, m.hp);
    bind_value(m_motor_data_update_stmt, 6, m.speed);
    bind_value(m_motor_data_update_stmt, 7, m.fullLoadSpeed);
    bind_value(m_motor_data_update_stmt, 8, m.enclosureType);
    bind_value(m_motor_data_update_stmt, 9, m.frameNumber);
    bind_value(m_motor_data_update_stmt, 10, m.voltageRating);
    bind_value(m_motor_data_update_stmt, 11, m.purpose);
    bind_value(m_motor_data_update_stmt, 12, m.uFrame);
    bind_value(m_motor_data_update_stmt, 13, m.cFace);
    bind_value(m_motor_data_update_stmt, 14, m.verticalShaft);
    bind_value(m_motor_data_update_stmt, 15, m.dFlange);
    bind_value(m_motor_data_update_stmt, 16, m.serviceFactor);
    bind_value(m_motor_data_update_stmt, 17, m.insulationClass);
    bind_value(m_motor_data_update_stmt, 18, m.weight);
    bind_value(m_motor_data_update_stmt, 19, m.listPrice);
    bind_value(m_motor_data_update_stmt, 20, m.windingResistance);
    bind_value(m_motor_data_update_stmt, 21, m.warranty);
    bind_value(m_motor_data_update_stmt, 22, m.rotorBars);
    bind_value(m_motor_data_update_stmt, 23, m.statorSlots);
    bind_value(m_motor_data_update_stmt, 24, m.efficiency100);
    bind_value(m_motor_data_update_stmt, 25, m.efficiency75);
    bind_value(m_motor_data_update_stmt, 26, m.efficiency50);
    bind_value(m_motor_data_update_stmt, 27, m.efficiency25);
    bind_value(m_motor_data_update_stmt, 28, m.powerFactor100);
    bind_value(m_motor_data_update_stmt, 29, m.powerFactor75);
    bind_value(m_motor_data_update_stmt, 30, m.powerFactor50);
    bind_value(m_motor_data_update_stmt, 31, m.powerFactor25);
    bind_value(m_motor_data_update_stmt, 32, m.torqueFullLoad);
    bind_value(m_motor_data_update_stmt, 33, m.torqueBreakDown);
    bind_value(m_motor_data_update_stmt, 34, m.torqueLockedRotor);
    bind_value(m_motor_data_update_stmt, 35, m.ampsFullLoad);
    bind_value(m_motor_data_update_stmt, 36, m.ampsIdle);
    bind_value(m_motor_data_update_stmt, 37, m.ampsLockedRotor);
    bind_value(m_motor_data_update_stmt, 38, m.stalledRotorTimeHot);
    bind_value(m_motor_data_update_stmt, 39, m.stalledRotorTimeCold);
    bind_value(m_motor_data_update_stmt, 40, m.peakVoltage0ms);
    bind_value(m_motor_data_update_stmt, 41, m.peakVoltage5ms);
    bind_value(m_motor_data_update_stmt, 42, m.id);

    int rc = step_command(m_motor_data_update_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_motor_data_update_stmt);
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

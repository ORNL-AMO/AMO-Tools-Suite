#ifndef AMO_LIBRARY_SQLITEWRAPPER_H
#define AMO_LIBRARY_SQLITEWRAPPER_H

#include <sqlite3.h>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <calculator/losses/GasFlueGasMaterial.h>

class SolidLoadChargeMaterial;
class LiquidLoadChargeMaterial;
class GasLoadChargeMaterial;
class GasCompositions;
class SolidLiquidFlueGasMaterial;
class Atmosphere;
class WallLosses;
class MotorData;

class SQLiteWrapper
{
protected:
    SQLiteWrapper( std::shared_ptr<sqlite3> const & db );

    SQLiteWrapper( std::string const & db_name, bool init_db = false );

    virtual ~SQLiteWrapper() {};

    int execute_command(std::string const & command_buffer) const;

    int prepare_statement(sqlite3_stmt * & stmt, std::string const & stmt_buffer) const;

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, std::string const & text_buffer) const;

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert) const;

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, double const double_to_insert) const;

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index) const;

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, const bool value_to_insert) const;

    int bind_foreign_key(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert) const;

    bool step_validity( int const rc ) const;

    int step_command(sqlite3_stmt * stmt) const;

    int reset_command(sqlite3_stmt * stmt) const;

    void begin_transaction() const;

    void commit_transaction() const;

    static std::string convert_text( const unsigned char * text );

    template< typename T >
    std::vector< T > get_all_objects(sqlite3_stmt * stmt, std::function< T(sqlite3_stmt *) > cb) const {
        std::vector< T > retVal;
        if (m_db)
        {
            while(step_command(stmt) == SQLITE_ROW)
            {
                retVal.push_back(cb(stmt));
            }
        }
        return retVal;
    }

    template< typename T >
    T get_object(sqlite3_stmt * stmt, int const id, std::function< T(sqlite3_stmt *) > cb) const {
        if (m_db) {
            bind_value(stmt, 1, id );
            int rc = step_command(stmt);
            step_validity(rc);
            if( rc == SQLITE_ROW ) {
                T retVal = cb(stmt);
                reset_command(stmt);
                return retVal;
            }
            reset_command(stmt);
            throw std::runtime_error("Invalid command during get_object");
        }
        throw std::runtime_error("No valid database connection");
    }

private:
    sqlite3 * m_connection = nullptr;
    std::shared_ptr<sqlite3> m_db;

};

class SQLite : SQLiteWrapper
{
public:
    // Open the DB and prepare for writing data
    // Create all of the tables on construction
    SQLite(std::string const & db_name, bool init_db = false);

    // Close database and free prepared statements
    virtual ~SQLite();

    std::vector<SolidLoadChargeMaterial> getSolidLoadChargeMaterials() const;
    SolidLoadChargeMaterial getSolidLoadChargeMaterialById(int id) const;
    std::vector<SolidLoadChargeMaterial> getCustomSolidLoadChargeMaterials() const;
    bool insertSolidLoadChargeMaterials(SolidLoadChargeMaterial const & material);
    bool deleteSolidLoadChargeMaterial(int id);
    bool updateSolidLoadChargeMaterial(SolidLoadChargeMaterial const & material);

    std::vector<GasLoadChargeMaterial> getGasLoadChargeMaterials() const;
    GasLoadChargeMaterial getGasLoadChargeMaterialById(int id) const;
    std::vector<GasLoadChargeMaterial> getCustomGasLoadChargeMaterials() const;
    bool insertGasLoadChargeMaterials(GasLoadChargeMaterial const & material);
	bool deleteGasLoadChargeMaterial(int id);
    bool updateGasLoadChargeMaterial(const GasLoadChargeMaterial & material);

    std::vector<LiquidLoadChargeMaterial> getLiquidLoadChargeMaterials() const;
    LiquidLoadChargeMaterial getLiquidLoadChargeMaterialById(int id) const;
    std::vector<LiquidLoadChargeMaterial> getCustomLiquidLoadChargeMaterials() const;
    bool insertLiquidLoadChargeMaterials(LiquidLoadChargeMaterial const & material);
    bool deleteLiquidLoadChargeMaterial(int id);
    bool updateLiquidLoadChargeMaterial(const LiquidLoadChargeMaterial & material);

    std::vector<SolidLiquidFlueGasMaterial> getSolidLiquidFlueGasMaterials() const;
    SolidLiquidFlueGasMaterial getSolidLiquidFlueGasMaterialById(int id) const;
    std::vector<SolidLiquidFlueGasMaterial> getCustomSolidLiquidFlueGasMaterials() const;
    bool insertSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const & material) const;
    bool deleteSolidLiquidFlueGasMaterial(int id);
    bool updateSolidLiquidFlueGasMaterial(SolidLiquidFlueGasMaterial const & material);

    std::vector<GasCompositions> getGasFlueGasMaterials() const;
    GasCompositions getGasFlueGasMaterialById(int id) const;
    std::vector<GasCompositions> getCustomGasFlueGasMaterials() const;
    bool insertGasFlueGasMaterial(GasCompositions const & material) const;
    bool deleteGasFlueGasMaterial(int id);
    bool updateGasFlueGasMaterial(GasCompositions const & material);

    std::vector<Atmosphere> getAtmosphereSpecificHeat() const;
    Atmosphere getAtmosphereSpecificHeatById(int id) const;
    std::vector<Atmosphere> getCustomAtmosphereSpecificHeat() const;
    bool insertAtmosphereSpecificHeat(Atmosphere const & material);
    bool updateAtmosphereSpecificHeat(Atmosphere const & material);
    bool deleteAtmosphereSpecificHeat(int id);

    std::vector<WallLosses> getWallLossesSurface() const;
    std::vector<WallLosses> getCustomWallLossesSurface() const;
    WallLosses getWallLossesSurfaceById(int id) const;
    bool insertWallLossesSurface(WallLosses const & material);
    bool deleteWallLossesSurface(int id);
    bool updateWallLossesSurface(WallLosses const & material);

    std::vector<MotorData> getMotorData() const;
    std::vector<MotorData> getCustomMotorData() const;
    MotorData getMotorDataById(int id) const;
    bool insertMotorData(MotorData const & motor);
    bool deleteMotorData(int id);
    bool updateMotorData(MotorData const & motor);

private:
    // returns true if the material id falls in the default material id range
    inline bool isDefaultMaterial(const int id, std::size_t const defaultMaterialsSize) {
        return static_cast<std::size_t>(id) <= defaultMaterialsSize;
    }

    sqlite3_stmt * m_solid_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_select_custom_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_update_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_delete_stmt = nullptr;

    sqlite3_stmt * m_gas_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_select_custom_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_update_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_delete_stmt = nullptr;

    sqlite3_stmt * m_liquid_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_select_custom_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_update_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_delete_stmt = nullptr;

    sqlite3_stmt * m_solid_liquid_flue_gas_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_select_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_select_single_stmt = nullptr;
	sqlite3_stmt * m_solid_liquid_flue_gas_materials_select_custom_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_update_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_delete_stmt = nullptr;

    sqlite3_stmt * m_gas_flue_gas_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_select_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_select_custom_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_update_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_delete_stmt = nullptr;

    sqlite3_stmt * m_atmosphere_specific_heat_insert_stmt = nullptr;
    sqlite3_stmt * m_atmosphere_specific_heat_select_stmt = nullptr;
    sqlite3_stmt * m_atmosphere_specific_heat_select_single_stmt = nullptr;
    sqlite3_stmt * m_atmosphere_specific_heat_select_custom_stmt = nullptr;
    sqlite3_stmt * m_atmosphere_specific_heat_update_stmt = nullptr;
    sqlite3_stmt * m_atmosphere_specific_heat_delete_stmt = nullptr;

    sqlite3_stmt * m_wall_losses_surface_insert_stmt = nullptr;
    sqlite3_stmt * m_wall_losses_surface_select_stmt = nullptr;
    sqlite3_stmt * m_wall_losses_surface_select_single_stmt = nullptr;
    sqlite3_stmt * m_wall_losses_surface_select_custom_stmt = nullptr;
    sqlite3_stmt * m_wall_losses_surface_update_stmt = nullptr;
    sqlite3_stmt * m_wall_losses_surface_delete_stmt = nullptr;

    sqlite3_stmt * m_motor_data_insert_stmt = nullptr;
    sqlite3_stmt * m_motor_data_select_stmt = nullptr;
	sqlite3_stmt * m_motor_data_select_single_stmt = nullptr;
    sqlite3_stmt * m_motor_data_select_custom_stmt = nullptr;
    sqlite3_stmt * m_motor_data_update_stmt = nullptr;
    sqlite3_stmt * m_motor_data_delete_stmt = nullptr;

    void create_select_stmt();

    void create_update_and_delete_stmt();

    void create_insert_stmt();

    void create_tables();

    bool insert_solid_load_charge_materials(SolidLoadChargeMaterial const & material);

    bool insert_gas_load_charge_materials(GasLoadChargeMaterial const & material);

    bool insert_liquid_load_charge_materials(LiquidLoadChargeMaterial const & material);

    bool insert_solid_liquid_flue_gas_materials(SolidLiquidFlueGasMaterial const & material);

    bool insert_gas_flue_gas_materials(GasCompositions const & comps);

    bool insert_atmosphere_specific_heat(Atmosphere const & material);

    bool insert_wall_losses_surface(WallLosses const & surface);

    bool insert_motor_data(MotorData const & m);

    void insert_default_data();

    std::vector<SolidLoadChargeMaterial> get_default_solid_load_charge_materials();

    std::vector<GasLoadChargeMaterial> get_default_gas_load_charge_materials();

    std::vector<LiquidLoadChargeMaterial> get_default_liquid_load_charge_materials();

    std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials();

    std::vector<GasCompositions> get_default_gas_flue_gas_materials();

    std::vector<Atmosphere> get_default_atmosphere_specific_heat();

    std::vector<WallLosses> get_default_wall_losses_surface();

    std::vector<MotorData> get_default_motor_data();
};


#endif //AMO_LIBRARY_SQLITEWRAPPER_H

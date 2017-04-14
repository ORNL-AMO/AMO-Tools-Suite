#ifndef AMO_LIBRARY_SQLITEWRAPPER_H
#define AMO_LIBRARY_SQLITEWRAPPER_H

#include <sqlite3.h>
#include <memory>
#include <string>
#include <vector>
#include <functional>

class SolidLoadChargeMaterial;
class LiquidLoadChargeMaterial;
class GasLoadChargeMaterial;

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
        T retVal;
        if (m_db)
        {
            bind_value(stmt, 1, id );
            int rc = step_command(stmt);
            bool valid_step = step_validity(rc);
            if( rc == SQLITE_ROW )
            {
                retVal = cb(stmt);
            }
            reset_command(stmt);
        }
        return retVal;
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

    SolidLoadChargeMaterial getSolidLoadChargeMaterial(int id) const;

    std::vector<GasLoadChargeMaterial> getGasLoadChargeMaterials() const;

    GasLoadChargeMaterial getGasLoadChargeMaterial(int id) const;

    std::vector<LiquidLoadChargeMaterial> getLiquidLoadChargeMaterials() const;

    LiquidLoadChargeMaterial getLiquidLoadChargeMaterial(int id) const;

//    std::vector<SolidLiquidFlueGasMaterial> getSolidLiquidFlueGasMaterials() const;
//
//    SolidLiquidFlueGasMaterial getSolidLiquidFlueGasMaterial(int id) const;
//
//    std::vector<GasFlueGasMaterial> getGasFlueGasMaterials() const;
//
//    GasFlueGasMaterial getGasFlueGasMaterial(int id) const;

private:
    sqlite3_stmt * m_solid_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_solid_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_gas_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_select_stmt = nullptr;
    sqlite3_stmt * m_liquid_load_charge_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_select_stmt = nullptr;
    sqlite3_stmt * m_solid_liquid_flue_gas_materials_select_single_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_insert_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_select_stmt = nullptr;
    sqlite3_stmt * m_gas_flue_gas_materials_select_single_stmt = nullptr;

    void create_select_stmt();

    void create_tables();

    bool insert_solid_load_charge_materials(SolidLoadChargeMaterial const & material);

    bool insert_gas_load_charge_materials(GasLoadChargeMaterial const & material);

    bool insert_liquid_load_charge_materials(LiquidLoadChargeMaterial const & material);

//    bool insert_solid_liquid_flue_gas_materials(SolidLiquidFlueGasMaterial const & material);

//    bool insert_gas_flue_gas_materials(GasFlueGasMaterial const & material);

    void insert_default_data();

    std::vector<SolidLoadChargeMaterial> get_default_solid_load_charge_materials();

    std::vector<GasLoadChargeMaterial> get_default_gas_load_charge_materials();

    std::vector<LiquidLoadChargeMaterial> get_default_liquid_load_charge_materials();

//    std::vector<SolidLiquidFlueGasMaterial> get_default_solid_liquid_flue_gas_materials();

//    std::vector<GasFlueGasMaterial> get_default_gas_flue_gas_materials();
};


#endif //AMO_LIBRARY_SQLITEWRAPPER_H

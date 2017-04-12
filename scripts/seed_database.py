import sqlite3
import seed_data


def create_data_tables(db_conn):
    c = db_conn.cursor()

    c.execute(
        '''CREATE TABLE IF NOT EXISTS gas_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             UNIQUE (substance, mean_specific_heat_of_vapor)
          );
         '''
    )

    c.execute(
        '''CREATE TABLE IF NOT EXISTS liquid_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             mean_specific_heat_of_liquid real NOT NULL, -- kJ/kg.F
             latent_heat_of_vaporisation real NOT NULL, -- Btu/lb.
             mean_specific_heat_of_vapor real NOT NULL, -- Btu/lb.F
             boiling_point real NOT NULL, -- F.
             UNIQUE (substance, mean_specific_heat_of_liquid, latent_heat_of_vaporisation,
                     mean_specific_heat_of_vapor, boiling_point)
          );
         '''
    )

    c.execute(
        '''CREATE TABLE IF NOT EXISTS solid_load_charge_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",
             mean_specific_heat_of_solid real NOT NULL, -- Btu/lb.F
             latent_heat_of_fusion real NOT NULL, -- Btu/lb.
             mean_specific_heat_of_liquid real NOT NULL, -- Btu/lb.F
             melting_point real NOT NULL, -- F.
             UNIQUE (substance, mean_specific_heat_of_solid, latent_heat_of_fusion,
                     mean_specific_heat_of_liquid, melting_point)
          );
         '''
    )

    c.execute(
        '''CREATE TABLE IF NOT EXISTS solid_liquid_flue_gas_materials (
             id integer PRIMARY KEY AUTOINCREMENT,
             substance text NOT NULL DEFAULT "",             
             carbon real NOT NULL, --C
             hydrogen real NOT NULL, -- H2
             nitrogen real NOT NULL, -- N2
             sulfur real NOT NULL, -- S
             oxygen real NOT NULL, -- O2
             moisture real NOT NULL, -- H20
             ash real NOT NULL, -- ash             
             UNIQUE (substance)
          );
         '''
    )

    c.execute(
        '''CREATE TABLE IF NOT EXISTS gas_flue_gas_materials (
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
             moisture real NOT NULL, -- H20                          s        
             UNIQUE (substance)
          );
         '''
    )


    db_conn.commit()


def drop_all_tables(db_conn):
    c = db_conn.cursor()
    c.execute('DROP TABLE IF EXISTS gas_load_charge_materials')
    c.execute('DROP TABLE IF EXISTS liquid_load_charge_materials')
    c.execute('DROP TABLE IF EXISTS solid_load_charge_materials')
    c.execute('DROP TABLE IF EXISTS solid_liquid_flue_gas_materials')
    c.execute('DROP TABLE IF EXISTS gas_flue_gas_materials')
    db_conn.commit()


def init_db(db_conn):
    db_conn.execute('''pragma foreign_keys=ON;''')
    drop_all_tables(db_conn)
    create_data_tables(db_conn)
    seed_data.add_gas_load_charge_materials(db_conn)
    seed_data.add_liquid_load_charge_materials(db_conn)
    seed_data.add_solid_load_charge_materials(db_conn)
    seed_data.add_solid_liquid_flue_gas_materials(db_conn)
    seed_data.add_gas_flue_gas_materials(db_conn)


if __name__ == '__main__':
    from argparse import ArgumentParser

    parser = ArgumentParser(description='Seed AMO Tools Suite database')

    parser.add_argument("sqlite_file", help="Location of SQLite database file")

    results = parser.parse_args()

    conn = sqlite3.connect(results.sqlite_file)
    init_db(conn)

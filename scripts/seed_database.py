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
        '''CREATE TABLE IF NOT EXISTS gaseous_fuel_composition (
             id integer PRIMARY KEY AUTOINCREMENT,
             fuel_name text NOT NULL DEFAULT "",
             us_state text NOT NULL DEFAULT "",
             ch4 real NOT NULL, -- methane %
             c2h6 real NOT NULL, -- ethane %
             n2 real NOT NULL, -- nitrogen %
             c3h8 real NOT NULL, -- propane %
             c4h10_cnh2n real NOT NULL, -- butane, other alkane %
             h2o real NOT NULL, -- water %
             co real NOT NULL, -- carbon monoxide %
             co2 real NOT NULL, -- carbon dioxide %
             so2 real NOT NULL, -- sulfur dioxide %
             o2 real NOT NULL, -- oxygen %             
             UNIQUE (fuel_name, us_state, ch4, c2h6, n2, c3h8, c4h10_cnh2n, h2o, co, co2, so2, o2)
          );
         '''
    )

    db_conn.commit()


def drop_all_tables(db_conn):
    c = db_conn.cursor()
    c.execute('DROP TABLE IF EXISTS gas_load_charge_materials')
    c.execute('DROP TABLE IF EXISTS liquid_load_charge_materials')
    c.execute('DROP TABLE IF EXISTS solid_load_charge_materials')
    db_conn.commit()


def init_db(db_conn):
    db_conn.execute('''pragma foreign_keys=ON;''')
    drop_all_tables(db_conn)
    create_data_tables(db_conn)
    seed_data.add_gas_load_charge_materials(db_conn)
    seed_data.add_liquid_load_charge_materials(db_conn)
    seed_data.add_solid_load_charge_materials(db_conn)


if __name__ == '__main__':
    from argparse import ArgumentParser

    parser = ArgumentParser(description='Seed AMO Tools Suite database')

    parser.add_argument("sqlite_file", help="Location of SQLite database file")

    results = parser.parse_args()

    conn = sqlite3.connect(results.sqlite_file)
    init_db(conn)

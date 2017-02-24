#include <sqlite/SQLite.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

SQLite::SQLite(std::string const & db_name)
    :
    SQLiteWrapper(db_name),
    m_test_insert_stmt(nullptr)
{
    execute_command("PRAGMA locking_mode = EXCLUSIVE;");
    execute_command("PRAGMA journal_mode = OFF;");
    execute_command("PRAGMA synchronous = OFF;");
    // Turn this to ON for Foreign Key constraints.
    // This must be turned ON for every connection
    execute_command("PRAGMA foreign_keys = ON;");

    create_test_table();
}

SQLite::~SQLite()
{
    sqlite3_finalize(m_test_insert_stmt);
}

void SQLite::create_test_table()
{
    const std::string test_tabel_sql =
        "CREATE TABLE Tests (TestIndex INTEGER PRIMARY KEY, TestName TEXT, "
        "TestType TEXT, TestMinimum REAL, TestMaximum REAL);";

    execute_command(test_tabel_sql);

    const std::string test_insert_sql =
        "INSERT INTO Tests VALUES(?,?,?,?,?);";

    prepare_statement(m_test_insert_stmt, test_insert_sql);
}

bool SQLite::insert_test_into_sqlite(int test_index, std::string const & test_name,
    std::string const & test_type, double test_minimum, double test_maximum)
{
    bind_value(m_test_insert_stmt, 1, test_index );
    bind_value(m_test_insert_stmt, 2, test_name);
    bind_value(m_test_insert_stmt, 3, test_type);
    bind_value(m_test_insert_stmt, 4, test_minimum);
    bind_value(m_test_insert_stmt, 5, test_maximum);

    int rc = step_command(m_test_insert_stmt);
    bool valid_insert = step_validity(rc);
    reset_command(m_test_insert_stmt);
    return valid_insert;
}

SQLiteWrapper::SQLiteWrapper( std::shared_ptr<sqlite3> const & db )
    :
    m_db(db)
{}

SQLiteWrapper::SQLiteWrapper( std::string const & db_name )
{
    int rc = -1;
    bool ok = true;
    bool in_memory = (db_name == ":memory:");
    char *err_msg = 0;

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

int SQLiteWrapper::execute_command(std::string const & command_buffer)
{
    char *err_msg = 0;
    int rc = sqlite3_exec(m_db.get(), command_buffer.c_str(), nullptr, 0, &err_msg);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_exec failed: " << err_msg << std::endl;
    }
    sqlite3_free(err_msg);
    return rc;
}

int SQLiteWrapper::prepare_statement(sqlite3_stmt * & stmt, std::string const & stmt_buffer)
{
    int rc = sqlite3_prepare_v2(m_db.get(), stmt_buffer.c_str(), -1, &stmt, nullptr);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_prepare_v2 failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, std::string const & text_buffer)
{
    int rc = sqlite3_bind_text(stmt, stmt_insert_col_index, text_buffer.c_str(), -1, SQLITE_TRANSIENT);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_text failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert)
{
    int rc = sqlite3_bind_int(stmt, stmt_insert_col_index, int_to_insert);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_int failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, double const double_to_insert)
{
    int rc = sqlite3_bind_double(stmt, stmt_insert_col_index, double_to_insert);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_double failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index)
{
    int rc = sqlite3_bind_null(stmt, stmt_insert_col_index);
    if ( rc != SQLITE_OK ) {
        std::cerr << "sqlite3_bind_null failed" << std::endl;
    }
    return rc;
}

int SQLiteWrapper::bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, bool const value_to_insert)
{
    return bind_value(stmt,stmt_insert_col_index, value_to_insert ? 1 : 0);
}

int SQLiteWrapper::bind_foreign_key(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert)
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

bool SQLiteWrapper::step_validity( int const rc )
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

int SQLiteWrapper::step_command(sqlite3_stmt * stmt)
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

int SQLiteWrapper::reset_command(sqlite3_stmt * stmt)
{
    return sqlite3_reset(stmt);
}

void SQLiteWrapper::begin_transaction()
{
    execute_command("BEGIN;");
}

void SQLiteWrapper::commit_transaction()
{
    execute_command("COMMIT;");
}

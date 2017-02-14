#ifndef AMO_LIBRARY_SQLITEWRAPPER_H
#define AMO_LIBRARY_SQLITEWRAPPER_H

#include <sqlite3.h>
#include <memory>
#include <string>

class SQLiteWrapper
{
protected:
    SQLiteWrapper( std::shared_ptr<sqlite3> const & db );

    SQLiteWrapper( std::string const & db_name );

    virtual ~SQLiteWrapper() {};

    int execute_command(std::string const & command_buffer);

    int prepare_statement(sqlite3_stmt * & stmt, std::string const & stmt_buffer);

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, std::string const & text_buffer);

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert);

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, double const double_to_insert);

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index);

    int bind_value(sqlite3_stmt * stmt, int const stmt_insert_col_index, const bool value_to_insert);

    int bind_foreign_key(sqlite3_stmt * stmt, int const stmt_insert_col_index, int const int_to_insert);

    bool step_validity( int const rc );

    int step_command(sqlite3_stmt * stmt);

    int reset_command(sqlite3_stmt * stmt);

    void begin_transaction();

    void commit_transaction();

private:
    sqlite3 * m_connection = nullptr;
    std::shared_ptr<sqlite3> m_db;

};

class SQLite : SQLiteWrapper
{
public:
    // Open the DB and prepare for writing data
    // Create all of the tables on construction
    SQLite( std::string const & db_name );

    // Close database and free prepared statements
    virtual ~SQLite();

    void create_test_table();

    bool insert_test_into_sqlite(int test_index, std::string const & test_name,
    std::string const & test_type, double test_minimum, double test_maximum);

private:
    sqlite3_stmt * m_test_insert_stmt;

};


#endif //AMO_LIBRARY_SQLITEWRAPPER_H

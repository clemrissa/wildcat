#include "SQLiteConnection.hpp"

#include <Domain/Odb/DataAccessFactory>

#include <odb/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/transaction.hxx>

#include <odb/sqlite/database.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/transaction.hxx>

#include <Uni/Logging/Logging>

// using Geo::Database::SQLiteConnection;

namespace Geo {
namespace Database {
SQLiteConnection::
SQLiteConnection() {
  setStatus(Status::Unknown);
  setDatabaseType(DatabaseType::SQLite);
  setDatabase("");
}

SQLiteConnection const&
SQLiteConnection::
operator=(SQLiteConnection const& other) {
  _databaseType = other._databaseType;
  _database     = other._database;

  return *this;
}

void
SQLiteConnection::
connect() {
  try {
    Domain::Odb::DataAccessFactory::Database db(
      new odb::sqlite::database(_database.toUtf8().constData(),
                                SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

    _dataAccessFactory = DataAccessFactory::Shared(
      new Domain::Odb::DataAccessFactory(db));

    // create Sqlite db scheme
    {
      odb::connection_ptr c(db->connection());

      c->execute("PRAGMA foreign_keys=OFF");
      odb::transaction t(c->begin());

      odb::schema_catalog::create_schema(*db);
      t.commit();
      c->execute("PRAGMA foreign_keys=ON");
    }

    setStatus(Status::Connected);
  } catch (odb::sqlite::database_exception const& exc) {
    _status = Status::Failed;
    setLastError(QString(exc.message().c_str()));
  }
}
}
}

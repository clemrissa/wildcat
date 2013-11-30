#include "Connection.hpp"

#include <Domain/Odb/DataAccessFactory>

#include <odb/schema-catalog.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/exceptions.hxx>
// --

using Geo::Database::Private::Connection;

Connection::
Connection(QObject* parent) : QObject(parent),
                              _databaseType(DatabaseType::Unknown),
                              _database(""),
                              _status(Status::Unknown),
                              _dataAccessFactory(0) {}

Connection::
~Connection() {}

Connection const&
Connection::
operator=(Connection const& other) {
  _databaseType = other._databaseType;
  _database     = other._database;

  return *this;
}

void
Connection::
connect() {
  switch (_databaseType) {
  case DatabaseType::MySql: {
      break;
    }

  case DatabaseType::SQLite: {
      try {
        Domain::Odb::DataAccessFactory::Database db(
          new odb::sqlite::database(
            _database.toUtf8().
            constData(),
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

        _dataAccessFactory = DataAccessFactory::Shared(
          new Domain::Odb::DataAccessFactory(db));

        status(Status::Connected);
      } catch (odb::sqlite::database_exception const& exc) {
        status(Status::Failed);
        lastError(QString(exc.message().c_str()));
      }

      break;
    }

  case DatabaseType::Unknown: {}

  default: {}
  }
}

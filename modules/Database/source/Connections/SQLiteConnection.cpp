#include "SQLiteConnection.hpp"

#include <QtCore/QDebug>

#include <Domain/Odb/DataAccessFactory>

#include <odb/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/transaction.hxx>

#include <odb/sqlite/database.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/transaction.hxx>

#include "ConnectionUtils.hpp"

namespace Geo
{
namespace Database
{

SQLiteConnection::
SQLiteConnection()
{
  setStatus(Status::Unknown);
  setDatabaseType(DatabaseType::SQLite);
  setDatabase("");
}


SQLiteConnection::
SQLiteConnection(QJsonObject & jsonConnection)
{
  setDatabaseType(DatabaseType::SQLite);
  setStatus(Status::Unknown);

  QString path = jsonConnection["path"].toString();

  setDatabase(path);
}


SQLiteConnection const&
SQLiteConnection::
operator=(SQLiteConnection const& other)
{
  _databaseType = other._databaseType;
  _database     = other._database;

  return *this;
}


void
SQLiteConnection::
setDatabase(QString const& database)
{
  _database = database;

  connect();

  emit databaseChanged(database);
}


IConnection::Status const&
SQLiteConnection::
status() const
{
  return _status;
}


QString const&
SQLiteConnection::
lastError() const
{
  return _lastError;
}


DatabaseType const&
SQLiteConnection::
databaseType() const
{
  return _databaseType;
}


QString const
SQLiteConnection::
textDescription() const
{
  return ConnectionUtils::connectionTypeName(_databaseType) +
         ": " +
         databasePath();
}


QString const
SQLiteConnection::
textType() const
{
  return ConnectionUtils::connectionTypeName(_databaseType);
}


QString const
SQLiteConnection::
databasePath() const
{
  return _database;
}


QJsonObject
SQLiteConnection::
jsonDescription() const
{
  QJsonObject json;

  json["type"] = ConnectionUtils::connectionTypeName(DatabaseType::SQLite);

  json["path"] = _database;

  return json;
}


void
SQLiteConnection::
connect()
{
  // TODO sofar no exception if db file is emply

  if (_database.isEmpty())
  {
    setStatus(Status::Failed);
    return;
  }

  try
  {
    Domain::Odb::DataAccessFactory::Database db(
      new odb::sqlite::database(_database.toUtf8().constData(),
                                SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

    _dataAccessFactory = DataAccessFactory::Shared(
      new Domain::Odb::DataAccessFactory(db));

    setStatus(Status::Connected);
  }
  catch (odb::sqlite::database_exception const& exc)
  {
    setStatus(Status::Failed);
    setLastError(QString(exc.message().c_str()));
  }

  // create Sqlite db scheme
  if (_status == Status::Connected)
  {
    try
    {
      auto odb_database = _dataAccessFactory->database();

      odb::connection_ptr c(odb_database->connection());

      c->execute("PRAGMA foreign_keys=OFF");
      odb::transaction t(c->begin());

      bool dropDB = false;
      odb::schema_catalog::create_schema(*odb_database, "", dropDB);
      t.commit();
      c->execute("PRAGMA foreign_keys=ON");
    }
    catch (odb::sqlite::database_exception const& exc)
    {
      setLastError(QString(exc.message().c_str()));
    }

    _dataAccessFactory->afterDBConnected();
  }
}


void
SQLiteConnection::
setLastError(QString const& lastError)
{
  _lastError = lastError;
  emit lastErrorChanged(lastError);
}


void
SQLiteConnection::
setStatus(Status const& status)
{
  _status = status;
  emit statusChanged(status);
}


void
SQLiteConnection::
setDatabaseType(DatabaseType databaseType)
{
  _databaseType = databaseType;
  emit databaseTypeChanged(_databaseType);
}


//
}
}

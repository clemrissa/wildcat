#include "SQLiteConnection.hpp"

#include <Domain/Odb/DataAccessFactory>

#include <odb/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/transaction.hxx>

#include <odb/sqlite/database.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/transaction.hxx>

#include <Uni/Logging/Logging>

using Geo::Database::Connections::DatabaseType;
using Geo::Database::Connections::SQLiteConnection;
using Geo::Database::Connections::Status;

SQLiteConnection::
SQLiteConnection()
{
  setStatus(Status::Unknown);
  setDatabaseType(DatabaseType::SQLite);
  setDatabase("");
}


SQLiteConnection::
SQLiteConnection(QDomElement& domElement)
{
  setDatabaseType(DatabaseType::SQLite);
  setStatus(Status::Unknown);

  QDomNodeList nodeList = domElement.elementsByTagName("Path");

  if (nodeList.size() > 0) {
    QDomNode node = nodeList.at(0);

    if (!node.isNull()) {
      QDomElement e = node.toElement();

      setDatabase(e.text());
    }
  }
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


Status const&
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
  return Connection::connectionTypeName(_databaseType) +
         ": " +
         databasePath();
}


QString const
SQLiteConnection::
databasePath() const
{
  return _database;
}


QDomElement
SQLiteConnection::
xmlDescription(QDomDocument& doc) const
{
  QDomElement tag = doc.createElement("Connection");

  tag.setAttribute("Type",
                   Connection::connectionTypeName(DatabaseType::SQLite));

  QDomElement e = doc.createElement("Path");
  tag.appendChild(e);

  QDomText t = doc.createTextNode(_database);
  e.appendChild(t);

  return tag;
}


void
SQLiteConnection::
connect()
{
  // TODO sofar no exception if db file is emply

  if (_database.isEmpty()) {
    setStatus(Status::Failed);
    return;
  }

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

      bool dropDB = false;
      odb::schema_catalog::create_schema(*db, "", dropDB);
      t.commit();
      c->execute("PRAGMA foreign_keys=ON");
    }

    setStatus(Status::Connected);
  } catch (odb::sqlite::database_exception const& exc) {
    setStatus(Status::Failed);
    setLastError(QString(exc.message().c_str()));
  }
}

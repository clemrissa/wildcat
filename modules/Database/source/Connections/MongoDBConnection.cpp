#include "MongoDBConnection.hpp"

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

MongoDBConnection::
MongoDBConnection()
{
  setStatus(Status::Unknown);
  setDatabaseType(DatabaseType::MongoDB);
  setDatabase("");
}


MongoDBConnection::
MongoDBConnection(QDomElement& domElement)
{
  setDatabaseType(DatabaseType::MongoDB);
  setStatus(Status::Unknown);

  QDomNodeList nodeList = domElement.elementsByTagName("Path");

  if (nodeList.size() > 0)
  {
    QDomNode node = nodeList.at(0);

    if (!node.isNull())
    {
      QDomElement e = node.toElement();

      setDatabase(e.text());
    }
  }
}


MongoDBConnection const&
MongoDBConnection::
operator=(MongoDBConnection const& other)
{
  _databaseType = other._databaseType;
  _database     = other._database;

  return *this;
}


void
MongoDBConnection::
setDatabase(QString const& database)
{
  _database = database;

  connect();

  emit databaseChanged(database);
}


IConnection::Status const&
MongoDBConnection::
status() const
{
  return _status;
}


QString const&
MongoDBConnection::
lastError() const
{
  return _lastError;
}


DatabaseType const&
MongoDBConnection::
databaseType() const
{
  return _databaseType;
}


QString const
MongoDBConnection::
textDescription() const
{
  return ConnectionUtils::connectionTypeName(_databaseType) +
         ": " +
         databasePath();
}


QString const
MongoDBConnection::
textType() const
{
  return ConnectionUtils::connectionTypeName(_databaseType);
}


QString const
MongoDBConnection::
databasePath() const
{
  return _database;
}


QDomElement
MongoDBConnection::
xmlDescription(QDomDocument& doc) const
{
  QDomElement tag = doc.createElement("Connection");

  tag.setAttribute("Type",
                   ConnectionUtils::connectionTypeName(DatabaseType::MongoDB));

  QDomElement e = doc.createElement("Path");
  tag.appendChild(e);

  QDomText t = doc.createTextNode(_database);
  e.appendChild(t);

  return tag;
}


void
MongoDBConnection::
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
MongoDBConnection::
setLastError(QString const& lastError)
{
  _lastError = lastError;
  emit lastErrorChanged(lastError);
}


void
MongoDBConnection::
setStatus(Status const& status)
{
  _status = status;
  emit statusChanged(status);
}


void
MongoDBConnection::
setDatabaseType(DatabaseType databaseType)
{
  _databaseType = databaseType;
  emit databaseTypeChanged(_databaseType);
}


//
}
}

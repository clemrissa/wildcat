#include "MongoDBConnection.hpp"

#include <QtCore/QDebug>

#include <Domain/Odb/DataAccessFactory>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/uri.hpp>

#include "MongoDBInstance.hpp"

#include "ConnectionUtils.hpp"

namespace Geo
{
namespace Database
{

MongoDBConnection::
MongoDBConnection()
  : _database("")
  , _host("localhost")
  , _port(27017)
{
  MongoDBInstance::instance();

  setStatus(Status::Unknown);
  setDatabaseType(DatabaseType::MongoDB);

  connect();
}


MongoDBConnection::
MongoDBConnection(QJsonObject & jsonConnection)
{
  MongoDBInstance::instance();
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

  emit databaseChanged(_database);
}


void
MongoDBConnection::
setHost(QString const& host)
{
  _host = host;

  connect();

  emit databaseChanged(_database);
}


void
MongoDBConnection::
setPort(unsigned int port)
{
  _port = port;

  connect();

  emit databaseChanged(_database);
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


QJsonObject
MongoDBConnection::
jsonDescription() const
{
  QJsonObject json;

  return json;
}


void
MongoDBConnection::
connect()
{
  QString uriString = QString("mongodb://%1:%2").arg(_host).arg(_port);

  mongocxx::uri uri(uriString.toStdString());
  //mongocxx::uri uri{};

  qDebug() << "URI:  " << uriString;

  mongocxx::client client(uri);

  if (client)
  {
    qDebug() << "Connection";
  }
  else
  {
    qDebug() << "No Connection";
  }

  try
  {
    bsoncxx::builder::stream::document ping;
    ping << "ping" << 1;
    auto db     = client["admin"];
    auto result = db.run_command(ping.view());

    if (result.view()["ok"].get_double() != 1)
    {
      qDebug() << "Ping to database failed: " << uriString;
    }
  }
  catch (const mongocxx::exception & e)
  {

    qDebug() << "Run command failed: " << uriString;
  }

  //if (_database.isEmpty())
  //{
  //setStatus(Status::Failed);
  //return;
  //}

  //try
  //{
  //Domain::Odb::DataAccessFactory::Database db(
  //new odb::sqlite::database(_database.toUtf8().constData(),
  //SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

  //_dataAccessFactory = DataAccessFactory::Shared(
  //new Domain::Odb::DataAccessFactory(db));

  //setStatus(Status::Connected);
  //}
  //catch (odb::sqlite::database_exception const& exc)
  //{
  //setStatus(Status::Failed);
  //setLastError(QString(exc.message().c_str()));
  //}

  //create Sqlite db scheme
  //if (_status == Status::Connected)
  //{
  //try
  //{
  //auto odb_database = _dataAccessFactory->database();

  //odb::connection_ptr c(odb_database->connection());

  //c->execute("PRAGMA foreign_keys=OFF");
  //odb::transaction t(c->begin());

  //bool dropDB = false;
  //odb::schema_catalog::create_schema(*odb_database, "", dropDB);
  //t.commit();
  //c->execute("PRAGMA foreign_keys=ON");
  //}
  //catch (odb::sqlite::database_exception const& exc)
  //{
  //setLastError(QString(exc.message().c_str()));
  //}

  //_dataAccessFactory->afterDBConnected();
  //}
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

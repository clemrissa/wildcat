#ifndef Geo_Database_Connection_hpp
#define Geo_Database_Connection_hpp

#include <Connection.hpp>

#include <Domain/DataAccessFactory>

#include <QObject>
#include <QSharedPointer>

// #include <QDebug>
#include <QString>

#include <boost/shared_ptr.hpp>

namespace Geo {
namespace Database {
namespace DatabaseType {
static const int Unknown = 1;
static const int MySql   = 2;
static const int SQLite  = 3;
}

namespace Status {
static const int Unknown   = 1;
static const int Connected = 2;
static const int Failed    = 3;
}

class Connection: public QObject {
  Q_OBJECT

public:
  typedef QSharedPointer<Connection> Shared;

  typedef int                       DatabaseType;
  typedef int                       Status;
  typedef Domain::DataAccessFactory DataAccessFactory;

private:
  Q_PROPERTY(int databaseType
             READ databaseType
             WRITE databaseType
             NOTIFY databaseTypeChanged)
  Q_PROPERTY(QString database
             READ database
             WRITE database
             NOTIFY databaseChanged)
  Q_PROPERTY(int status
             READ status
             NOTIFY statusChanged)
  Q_PROPERTY(QString lastError
             READ lastError
             NOTIFY lastErrorChanged)

private:
  typedef boost::shared_ptr<odb::database> DatabaseObject;

public:
  Q_INVOKABLE
  Connection(QObject* parent = 0);

  ~Connection();

  Connection const&
  operator=(Connection const& other);

  void
  databaseType(DatabaseType const& databaseType) {
    _databaseType = databaseType;
    emit databaseTypeChanged(databaseType);
  }

  DatabaseType const&
  databaseType() const { return _databaseType; }

  void
  database(QString const& database) {
    _database = database;
    emit databaseChanged(database);
  }

  QString const&
  database() const { return _database; }

  DataAccessFactory::Shared
  dataAccessFactory() const {
    return _dataAccessFactory;
  }

private:
  void
  status(Status const& status) {
    _status = status;
    emit statusChanged(status);
  }

public:
  Status const&
  status() const { return _status; }

private:
  void
  lastError(QString const& lastError) {
    _lastError = lastError;
    emit lastErrorChanged(lastError);
  }

public:
  QString const&
  lastError() const { return _lastError; }

signals:
  void
  databaseTypeChanged(DatabaseType const& databaseType);

  void
  databaseChanged(QString const& database);

  void
  statusChanged(Status const& staus);

  void
  lastErrorChanged(QString const& lastError);

public:
  Q_INVOKABLE void
  connect();

private:
  DatabaseType              _databaseType;
  QString                   _database;
  Status                    _status;
  QString                   _lastError;
  DataAccessFactory::Shared _dataAccessFactory;
};
}
}
#endif

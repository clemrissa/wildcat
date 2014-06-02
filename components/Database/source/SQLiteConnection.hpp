#ifndef Geo_Database_SQLiteConnection_hpp
#define Geo_Database_SQLiteConnection_hpp

#include "Connection.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QString>

namespace Geo {
namespace Database {
//

class SQLiteConnection: public Connection {
  Q_OBJECT

private:
  typedef QSharedPointer<odb::database> DatabaseObject;

public:
  Q_INVOKABLE
  SQLiteConnection();

  SQLiteConnection const&
  operator=(SQLiteConnection const& other);

  void
  setDatabase(QString const& database) {
    _database = database;
    emit databaseChanged(database);
  }

  QString const
  textDescription() const override {
    return Connection::connectionTypeName(_databaseType);
  }

  Status const&
  status() const override { return _status; }

  QString const&
  lastError() const override { return _lastError; }

  DatabaseType const&
  databaseType() const override { return _databaseType; }

public:
  Q_INVOKABLE void
  connect() override;

signals:
  void
  databaseTypeChanged(DatabaseType const& databaseType);

  void
  databaseChanged(QString const& database);

  void
  statusChanged(Status const& staus);

  void
  lastErrorChanged(QString const& lastError);

protected:
  void
  setLastError(QString const& lastError) {
    _lastError = lastError;
    emit lastErrorChanged(lastError);
  }

  void
  setStatus(Status const& status) {
    _status = status;
    emit statusChanged(status);
  }

  void
  setDatabaseType(DatabaseType const& databaseType) {
    _databaseType = databaseType;
    emit databaseTypeChanged(_databaseType);
  }

private:
  QString _lastError;

  DatabaseType _databaseType;

  Status _status;

  QString _database;
};
}
}
#endif

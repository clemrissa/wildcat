#ifndef Geo_Database_Connections_SQLiteConnection_hpp
#define Geo_Database_Connections_SQLiteConnection_hpp

#include "Connection.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QString>

namespace Geo {
namespace Database {
namespace Connections {
class SQLiteConnection: public Connection {
  Q_OBJECT

private:
  typedef QSharedPointer<odb::database> DatabaseObject;

public:
  Q_INVOKABLE
  SQLiteConnection();

  SQLiteConnection(QDomElement& domElement);

  SQLiteConnection const&
  operator=(SQLiteConnection const& other);

  void
  setDatabase(QString const& database);

  QString const
  database() const { return _database; }

  QString const
  textDescription() const override;

  QString const
  databasePath() const override;

  QDomElement
  xmlDescription(QDomDocument& doc) const override;

  Status const&
  status() const override;

  QString const&
  lastError() const override;

  DatabaseType const&
  databaseType() const override;

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
  setLastError(QString const& lastError)
  {
    _lastError = lastError;
    emit lastErrorChanged(lastError);
  }


  void
  setStatus(Status const& status)
  {
    _status = status;
    emit statusChanged(status);
  }


  void
  setDatabaseType(DatabaseType const& databaseType)
  {
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
}
#endif

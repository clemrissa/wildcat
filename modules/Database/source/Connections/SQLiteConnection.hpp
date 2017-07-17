#pragma once

#include "Connection.hpp"

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace Geo
{
namespace Database
{

class SQLiteConnection : public Connection
{
  Q_OBJECT

private:

  using DatabaseObject = std::shared_ptr<odb::database>;

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

  Connection::DatabaseType const&
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
  setDatabaseType(Connection::DatabaseType const& databaseType)
  {
    _databaseType = databaseType;
    emit databaseTypeChanged(_databaseType);
  }

private:
  QString _lastError;

  Connection::DatabaseType _databaseType;

  Connection::Status _status;

  QString _database;
};
}
}

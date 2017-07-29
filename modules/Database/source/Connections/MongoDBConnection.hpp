#pragma once

#include "IConnection.hpp"

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <Database/Connections/DatabaseType>

namespace Geo
{
namespace Database
{

class MongoDBConnection : public IConnection
{
  Q_OBJECT

private:

public:
  Q_INVOKABLE
  MongoDBConnection();

  MongoDBConnection(QDomElement& domElement);

  MongoDBConnection const&
  operator=(MongoDBConnection const& other);

  void
  setDatabase(QString const& database);

  QString const
  database() const { return _database; }

  QString const
  textDescription() const override;

  QString const
  textType() const override;

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
  setLastError(QString const& lastError);

  void
  setStatus(Status const& status);

  void
  setDatabaseType(DatabaseType databaseType);

private:

  QString _lastError;

  DatabaseType _databaseType;

  IConnection::Status _status;

  QString _database;
};
}
}

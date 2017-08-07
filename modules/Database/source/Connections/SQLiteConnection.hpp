#pragma once

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QString>

#include "DatabaseExport.hpp"

#include "IConnection.hpp"
#include "DatabaseType.hpp"

namespace Geo
{
namespace Database
{

class Database_PUBLIC SQLiteConnection : public IConnection
{
  Q_OBJECT

private:

  using DatabaseObject = std::shared_ptr<odb::database>;

public:
  Q_INVOKABLE
  SQLiteConnection();

  SQLiteConnection(QJsonObject & jsonConnection);

  SQLiteConnection const&
  operator=(SQLiteConnection const& other);

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

  QJsonObject
  jsonDescription() const override;

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

//
}
}

#pragma once

#include <Domain/DataAccessFactory>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include <memory>

namespace Geo
{
namespace Database
{

class Connection : public QObject
{
public:
  using DataAccessFactory = Domain::DataAccessFactory;

  using Shared = std::shared_ptr<Connection>;

public:

  enum DatabaseType { UnknownDB, SQLite, MongoDB };

  enum Status { Unknown, Connected, Failed };

public:
  virtual
  ~Connection() = default;

  virtual
  DataAccessFactory::Shared
  dataAccessFactory() const
  {
    return _dataAccessFactory;
  }

  virtual Status const&
  status() const = 0;

  virtual QString const&
  lastError() const = 0;

  virtual DatabaseType const&
  databaseType() const = 0;

  virtual QString const
  databasePath() const = 0;

  virtual QString const
  textDescription() const = 0;

  virtual QDomElement
  xmlDescription(QDomDocument& doc) const = 0;

  // static methods

public:
  static QString
  connectionTypeName(DatabaseType type);

  static Connection::Shared
  restoreConnectionFromXml(QDomElement& domElement);

public:
  virtual void
  connect() = 0;

  DataAccessFactory::Shared _dataAccessFactory;
};
}
}

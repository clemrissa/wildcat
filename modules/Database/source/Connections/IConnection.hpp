#pragma once

#include <memory>

#include <Domain/DataAccessFactory>

#include <QtXml/QDomElement>

#include "DatabaseType.hpp"

namespace Geo
{
namespace Database
{

class IConnection : public QObject
{
public:
  using DataAccessFactory = Domain::DataAccessFactory;

public:

  enum Status { Unknown, Connected, Failed };

public:

  virtual
  ~IConnection() = default;

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

  virtual QString const
  textType() const = 0;

  virtual QDomElement
  xmlDescription(QDomDocument& doc) const = 0;

public:

  virtual void
  connect() = 0;

  DataAccessFactory::Shared _dataAccessFactory;
};
}
}

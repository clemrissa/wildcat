#pragma once

#include <memory>
#include <vector>

#include <QtCore/QObject>

#include <Database/Connections/DatabaseType>

namespace Geo
{
namespace Database
{

class IConnection;

/// The class defines the interface of ConnectionManager.
class IConnectionManager : public QObject
{
public:

  virtual
  std::size_t
  size() const = 0;

  virtual
  std::shared_ptr<IConnection>
  operator[](std::size_t i) const = 0;

  virtual
  std::shared_ptr<IConnection>
  createConnection(DatabaseType databaseType) = 0;

  virtual
  void
  appendConnection(std::shared_ptr<IConnection> c) = 0;

  virtual
  void
  removeConnection(std::size_t i) = 0;

  virtual
  std::vector<std::shared_ptr<IConnection> > const &
  connections() const = 0;
};
}
}

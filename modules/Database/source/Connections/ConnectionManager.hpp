#pragma once

#include <memory>
#include <vector>

#include <Database/Connections/DatabaseType>
#include <Database/Connections/IConnection>
#include <Database/Connections/IConnectionManager>

#include <DatabaseExport.hpp>

namespace Geo
{
namespace Database
{

class IConnection;

/// The class stores a list of connections
/**
   The class is created as a singleton in terms of ComponentManager.
   The instance could be accessed as follows:

   @code{.cpp}
     auto connectionsManager =
       ComponentManager::create<ConnectionManager*>("Database.ConnectionManager");
   @endcode
 */
class Database_PUBLIC ConnectionManager
  : public IConnectionManager
{
  Q_OBJECT

public:

  Q_INVOKABLE
  ConnectionManager();

  std::size_t
  size() const override;

  std::shared_ptr<IConnection>
  operator[](std::size_t i) const override;

  std::shared_ptr<IConnection>
  createConnection(DatabaseType databaseType) override;

  void
  appendConnection(std::shared_ptr<IConnection> c) override;

  void
  removeConnection(std::size_t i) override;

  std::vector<std::shared_ptr<IConnection> > const &
  connections() const override;

private slots:

  void
  loadFromJson();

  void
  saveToJson();

  QString
  getDefaultConfigFile() const;

private:

  std::vector<std::shared_ptr<IConnection> > _connections;
};
}
}

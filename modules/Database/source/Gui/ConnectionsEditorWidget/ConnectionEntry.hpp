#pragma once

#include <Connections/IConnection.hpp>

#include "Entry.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

/// Class wraps Connection entity and provides information for table model.

/**
   If the internal _connection is empty then the Entry works as a drop-down
   list for adding new connections.
 */
class ConnectionEntry : public Entry
{
public:
  enum Column : int
  {
    Type        = 0,
    Database    = 1,
    CloseAction = 2,
    Size
  };

public:
  ConnectionEntry(std::shared_ptr<IConnection> connection)
    : _connection(connection)
  {}

  ConnectionEntry() = default;

  QVariant
  data(int role, int column) override;

  std::shared_ptr<IConnection>
  connection()
  {
    return _connection;
  }

private:

  QVariant
  getForegroundRole(int column);

  QVariant
  getDisplayRole(int column);

  QVariant
  getDecorationRole(int column);

  QVariant
  getBackgroundRole(int column);

private:

  std::shared_ptr<IConnection> _connection;
};

//
}
}
}

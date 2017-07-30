#pragma once

#include <QtCore/QObject>

namespace Geo
{
namespace Database
{

/// Class is responsible for constructing database-related widgets
class DatabaseController : public QObject
{
  Q_OBJECT

public:
  static DatabaseController &
  instance();

  DatabaseController() = default;

  virtual
  ~DatabaseController() = default;

public slots:

  void
  showConnectionsWidget();

  void
  showTraitsWidget();
};

//
}
}

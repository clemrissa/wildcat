#pragma once

#include <QObject>

namespace Geo
{
namespace  Database
{
class DatabaseController : public QObject
{
  Q_OBJECT

public:
  static DatabaseController &
  instance();

  virtual
  ~DatabaseController();

public slots:
  void
  showConnectionsWidget();

  void
  showSettingsWidget();

private:
  DatabaseController();

private:
  static DatabaseController* _instance;
};
}
}

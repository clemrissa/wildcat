#pragma once

#include <memory>

#include "Connections/IConnection.hpp"

#include <QtWidgets/QWidget>

namespace Geo
{
namespace Database
{
namespace Gui
{

class ConnectionPropertiesWiget;


class TraitsWidget : public QWidget
{
  Q_OBJECT

public:
  TraitsWidget();

  virtual
  ~TraitsWidget();

public slots:

  void
  setConnection(std::shared_ptr<Database::IConnection> connection);

private:
  void
  createUi();

  void
  connectSignals();

private:
  struct Private;

  std::unique_ptr<Private> _p;
};
}

//
}
}

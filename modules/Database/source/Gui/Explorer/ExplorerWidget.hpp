#pragma once

#include <memory>

#include <QtWidgets/QWidget>

#include "DatabaseExport.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

class Database_PUBLIC ExplorerWidget final : public QWidget
{

  Q_OBJECT

public:

  Q_INVOKABLE
  ExplorerWidget();

  ~ExplorerWidget();

private:

  void
  setupUi();

  void
  setupModels();

  void
  connectSignals();

private:

  struct Private;

  std::unique_ptr<Private> p;
};

//
}
}
}

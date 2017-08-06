#pragma once

#include <QtWidgets/QWidget>

#include <Database/Connections/IConnection>

namespace Geo
{

using Database::IConnection;

namespace Widgets
{
//

class IConnectionDrivenWidget : public QWidget
{

public:
  virtual
  ~IConnectionDrivenWidget() = default;

  virtual void
  setEditorWidget(QWidget* editorWidget) = 0;

signals:

  virtual
  void
  connectionChanged(std::shared_ptr<IConnection>) = 0;
};

//
}
}

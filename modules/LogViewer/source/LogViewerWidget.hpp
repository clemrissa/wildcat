#pragma once

#include <QtWidgets/QWidget>

namespace Geo {
namespace LogViewer {
class LogViewerWidget : public QWidget
{
  Q_OBJECT

public:
  Q_INVOKABLE
  LogViewerWidget();

  virtual
  ~LogViewerWidget();

private:
  struct Private;

  Private* _p;
};
} // namespace LogViewer
} // namespace Geo

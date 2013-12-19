#include "LogViewerWidgetFactory.hpp"

#include <QLabel>
#include <QWidget>

namespace Geo {
namespace LogViewer {
LogViewerWidgetFactory::
LogViewerWidgetFactory() {
  //
}

LogViewerWidgetFactory::
~LogViewerWidgetFactory() {
  //
}

Q_INVOKABLE QWidget*
LogViewerWidgetFactory::
createLogViewerWidget() const {
  return new
         QLabel("ololol");
}
}
}

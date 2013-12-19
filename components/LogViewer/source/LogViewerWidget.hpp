#ifndef Geo_LogView_LogViewerWidget_hpp
#define Geo_LogView_LogViewerWidget_hpp

#include <QWidget>

namespace Geo {
namespace LogViewer {
class LogViewerWidget : public QWidget {
  Q_OBJECT

public:
  Q_INVOKABLE
  LogViewerWidget();

  virtual
  ~LogViewerWidget();

private:
  struct Private;

  Private* p;
};
} // namespace LogViewer
} // namespace Geo

#endif // Geo_LogView_LogViewerWidget_hpp

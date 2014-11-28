#ifndef Geo_Import_CurveTypeWidget_hpp
#define Geo_Import_CurveTypeWidget_hpp

#include <QWidget>

namespace Geo {
namespace TypeSystem {
namespace Gui {
//

class CurveTypeWidget: public QWidget
{
  Q_OBJECT

public:
  CurveTypeWidget();

  virtual
  ~CurveTypeWidget();

  // public:
  // void
  // setModel(ImportTreeModel* importModel);

private slots:
  void
  onImportClicked();

  void
  onConnectionSelected(int index);

  void
  onTableViewMenuRequested(const QPoint&);

signals:
  void notifyMainWindow(QString);

private:
  void
  setupUi();

  void
  connectSignals();

private:
  struct Private;

  Private* p;
};

//
} // namespace Gui
} // namespace TypeSystem
} // namespace Geo

#endif // Geo_Import_CurveTypeWidget_hpp

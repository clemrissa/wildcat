#ifndef _GeoImport_ImportController_h_
#define _GeoImport_ImportController_h_

#include <QAbstractItemModel>
#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include <QWidget>

namespace Geo {
namespace Import {
class ImportTreeLasFileModel;
// Class collects
class ImportController: public QObject {
  Q_OBJECT

public:
  static ImportController*
  instance();

  virtual
  ~ImportController();

public slots:
  void
  selectFilesAndImport();

private:
  ImportController();

private:
  static ImportController* _instance;

  QAbstractItemModel* _importTreeModel;
};
}
}

#endif //  _GeoImport_ImportController_h_

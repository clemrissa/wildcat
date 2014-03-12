#ifndef Geo_Import_ImportController_hpp
#define Geo_Import_ImportController_hpp

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

#endif //  GeoImport_ImportController_hpp

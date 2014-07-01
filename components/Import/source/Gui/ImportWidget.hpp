#ifndef Geo_Import_ImportWidget_hpp
#define Geo_Import_ImportWidget_hpp

#include <QWidget>

#include "ImportTreeModel.hpp"

class QAbstractItemModel;

namespace Geo {
namespace Import {
namespace Gui {
class ImportWidget: public QWidget {
  Q_OBJECT

public:
  ImportWidget();

  virtual
  ~ImportWidget();

public:
  void
  setModel(QAbstractItemModel* importModel);

  void
  setupDataBinding();

private slots:
  void
  onImportClicked();

private:
  void
  setupUi();

private:
  struct Private;

  Private* p;
};
//

} // namespace Gui
} // namespace Import
} // namespace Geo

#endif

#ifndef Geo_Import_ImportWidget_hpp
#define Geo_Import_ImportWidget_hpp

#include <QWidget>

#include "ImportTreeModel.hpp"

class QAbstractItemModel;

namespace Geo {
namespace Import {
class ImportWidget: public QWidget {
  Q_OBJECT

public:
  ImportWidget();

  virtual
  ~ImportWidget();

public:
  void
  setupUi();

  void
  setModel(QAbstractItemModel* importModel);

  void
  setupDataBinding();

private:
  struct Private;

  Private* p;
};
} // namespace Import
} // namespace Geo

#endif

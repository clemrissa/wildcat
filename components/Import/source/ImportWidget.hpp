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
  ImportWidget(QAbstractItemModel* importModel);

  virtual
  ~ImportWidget();

private:
  class Private;

  Private* im;
};
} // namespace Import
} // namespace Geo

#endif

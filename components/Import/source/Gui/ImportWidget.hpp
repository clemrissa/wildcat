#ifndef Geo_Import_ImportWidget_hpp
#define Geo_Import_ImportWidget_hpp

#include <QWidget>

namespace Geo {
namespace Import {

class ImportTreeModel; 

namespace Gui {
class ImportWidget: public QWidget {
  Q_OBJECT

public:
  ImportWidget();

  virtual
  ~ImportWidget();

public:
  void
  setModel(ImportTreeModel* importModel);

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

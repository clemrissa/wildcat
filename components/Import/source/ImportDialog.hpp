#ifndef Geo_Import_ImportDialog_hpp
#define Geo_Import_ImportDialog_hpp

#include <QDialog>

namespace Geo {
namespace Import {
class ImportDialog: public QDialog {
  Q_OBJECT

public:
  Q_INVOKABLE
  ImportDialog();

  virtual
  ~ImportDialog();

public slots:
  void
  selectFile();

private:
  class Private;

  Private* im;
};
} // namespace Import
} // namespace Geo

#endif

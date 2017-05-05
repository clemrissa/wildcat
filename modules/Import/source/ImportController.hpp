#ifndef Geo_Import_ImportController_hpp
#define Geo_Import_ImportController_hpp

#include <QObject>

namespace Geo {
namespace Import {
class ImportController: public QObject
{
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
};
}
}

#endif //  Geo_Import_ImportController_hpp

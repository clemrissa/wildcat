#pragma once

#include <QObject>

namespace Geo
{
namespace Import
{

class ImportController : public QObject
{
  Q_OBJECT

public:

  static ImportController&
  instance();

public slots:

  void
  selectFilesAndImport();

private:

  ImportController() {};
};

//
}
}

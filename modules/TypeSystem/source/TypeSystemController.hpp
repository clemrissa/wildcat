#pragma once

#include <QtCore/QObject>

namespace Geo
{
namespace  TypeSystem
{

class TypeSystemController : public QObject
{
  Q_OBJECT

public:
  static TypeSystemController &
  instance();

  virtual
  ~TypeSystemController();

public slots:

  void
  showCurveTypeWidget();

  void
  showUnitsWidget();

private:
  TypeSystemController();

private:
};

//
}
}

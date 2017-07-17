#pragma once

#include <QtCore/QMap>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStyledItemDelegate>

#include <Domain/Dimensions>

namespace Geo
{
namespace TypeSystem
{
namespace Gui
{
//

class DimensionsDelegate : public QWidget
{
  Q_OBJECT

public:
  DimensionsDelegate(Domain::Dimensions& dimensions,
                     QWidget*            parent = nullptr);

private slots:
  void
  setupUi();

  void
  setValues();

  void
  onValueChanged(int d);

private:
  Domain::Dimensions& _dimensions;

  // maps certain spin box to its corresponding dimension
  QMap<QSpinBox*, int> _spinBoxMap;
};

//
} // namespace Gui
} // namespace TypeSystem
} // namespace Geo

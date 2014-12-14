#include "DimensionsDelegate.hpp"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

#include <iostream>

using Geo::TypeSystem::Gui::DimensionsDelegate;

DimensionsDelegate::
DimensionsDelegate(Geo::Domain::Dimensions& dimensions,
                   QWidget*                 parent):
  QWidget(parent),
  _dimensions(dimensions)
{
  setupUi();

  setValues();
}


void
DimensionsDelegate::
setupUi()
{
  using Geo::Domain::Dimensions;

  this->setAutoFillBackground(true);

  auto l = new QFormLayout(this);

  l->setContentsMargins(1, 1, 1, 1);
  l->setSpacing(1);

  for (int i = Dimensions::DLength; i < Dimensions::AllUnitsSize; ++i) {
    auto sb = new QSpinBox();

    sb->setRange(-100, 100);

    // sb->setValue(_dimensions[i]);

    connect(sb, SIGNAL(valueChanged(int)),
            this, SLOT(onValueChanged(int)));

    _spinBoxMap[sb] = i;

    l->addRow(new QLabel(Dimensions::getDimensionName(i)), sb);
  }

  setMinimumHeight(Dimensions::AllUnitsSize * 22);
}


void
DimensionsDelegate::
setValues()
{
  for (auto sb : _spinBoxMap.keys()) {
    int d = _spinBoxMap[sb];
    sb->setValue(_dimensions[d]);
  }
}


void
DimensionsDelegate::
onValueChanged(int d)
{
  using Geo::Domain::Dimensions;

  auto sb = static_cast<QSpinBox*>(sender());

  int dim = _spinBoxMap[sb];

  _dimensions.setDimension((Dimensions::Dimension)dim, d);

  setValues();
}

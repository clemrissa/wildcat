#include "DimensionsDelegate.hpp"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

#include <iostream>

using Geo::TypeSystem::Gui::DimensionsDelegate;

DimensionsDelegate::
DimensionsDelegate(Geo::Domain::Dimensions& dimensions,
                   QWidget*                 parent):
  QWidget(parent),
  _dimensions(dimensions)
{
  setupUi();
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

  for (int i = Dimensions::DLength; i < Dimensions::AllUnitsSize; ++i)
  {
    auto sb = new QSpinBox();
    sb->setRange(-100, 100);

    l->addRow(new QLabel(Dimensions::getDimensionName(i)), sb);
  }

  setMinimumHeight(Dimensions::AllUnitsSize * 20 );
}

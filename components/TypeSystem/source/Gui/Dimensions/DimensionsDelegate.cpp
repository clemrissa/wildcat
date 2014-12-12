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
  this->setAutoFillBackground(true);

  auto l = new QFormLayout(this);

  l->setContentsMargins(0, 0, 0, 0);

  l->addRow(new QLabel("Label"), new QSpinBox());
  l->addRow(new QLabel("Label"), new QSpinBox());
  l->addRow(new QLabel("Label"), new QSpinBox());
  l->addRow(new QLabel("Label"), new QSpinBox());
  l->addRow(new QLabel("Label"), new QSpinBox());
  l->addRow(new QLabel("Label"), new QSpinBox());
}

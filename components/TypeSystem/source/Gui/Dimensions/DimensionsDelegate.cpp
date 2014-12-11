#include "DimensionsDelegate.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>

#include <iostream>

using Geo::TypeSystem::Gui::DimensionsDelegate;

QWidget*
DimensionsDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(parent);
  Q_UNUSED(option);

  //QWidget* w = new QWidget(parent);

  //auto* la0 = new QLabel("Test");
  auto* la1 = new QLabel("Test");


  //auto l = new QHBoxLayout(w);
  //l->addWidget(la0);
  //l->addWidget(la1);

  std::cout <<"EDITOR DELEGATE " << std::endl;

  //return w;
  return la1;
}


void
DimensionsDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  editor->setGeometry(option.rect);
}


void
DimensionsDelegate::
setEditorData(QWidget*           editor,
              const QModelIndex& index) const
{
  Q_UNUSED(index);
  //
}


void
DimensionsDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  //
}

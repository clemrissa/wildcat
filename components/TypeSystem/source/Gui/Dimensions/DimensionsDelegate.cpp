#include "DimensionsDelegate.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>

using Geo::TypeSystem::Gui::Dimensions::DimensionsDelegate;

QWidget*
DimensionsDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(parent);
  Q_UNUSED(option);

  return nullptr;
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

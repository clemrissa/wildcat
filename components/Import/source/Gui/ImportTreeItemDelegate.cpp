#include "ImportTreeItemDelegate.hpp"

#include <Las/TreeWrapper/TreeEntry.hpp>

using Geo::Import::Gui::ImportTreeItemDelegate;


QWidget*
ImportTreeItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(option);

  if (index.parent().isValid())
    return 0;


  using Geo::Import::TreeWrapper::TreeEntry;

}


void
ImportTreeItemDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{

}


void
ImportTreeItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{

}

void
ImportTreeItemDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{

}

#include "ImportTreeItemDelegate.hpp"

#include <Las/TreeWrapper/TreeEntry.hpp>

#include <QtWidgets/QLineEdit>

using Geo::Import::Gui::ImportTreeItemDelegate;

QWidget*
ImportTreeItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(option);

  using Geo::Import::TreeWrapper::TreeEntry;

  auto treeEntry =
    static_cast<TreeEntry*>(index.internalPointer());

  QWidget* editor = treeEntry->delegateWidget(index.column());

  if (editor)
    editor->setParent(parent);

  return editor;
}


void
ImportTreeItemDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  editor->setGeometry(option.rect);
}


void
ImportTreeItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{
  Q_UNUSED(editor);
  Q_UNUSED(index);
}


void
ImportTreeItemDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  using Geo::Import::TreeWrapper::TreeEntry;

  auto treeEntry = static_cast<TreeEntry*>(index.internalPointer());

  treeEntry->setDataFromWidget(editor, index, model);
}

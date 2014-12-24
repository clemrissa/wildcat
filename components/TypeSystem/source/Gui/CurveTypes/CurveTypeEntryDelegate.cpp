#include "CurveTypeEntryDelegate.hpp"

#include <QtGui/QDoubleValidator>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QTableView>

#include <DependencyManager/ApplicationContext>

#include <Models/CurveTypes/CurveTypeEntry.hpp>
#include <Models/CurveTypes/FamilyEntry.hpp>
#include <Models/Units/UnitTableEntry.hpp>

#include <Gui/Dimensions/DimensionsDelegate.hpp>

using Geo::TypeSystem::Gui::CurveTypeEntryDelegate;
using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

QWidget*
CurveTypeEntryDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(parent);
  Q_UNUSED(option);

  using Geo::Domain::WellTrait;

  auto entry  = static_cast<TreeEntry*>(index.internalPointer());
  auto widget = entry->delegateWidget(index.column());

  if (widget)
    widget->setParent(parent);

  return widget;
}


void
CurveTypeEntryDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  QRect r = option.rect;
  editor->setGeometry(r);
}


void
CurveTypeEntryDelegate::
setEditorData(QWidget*           editor,
              const QModelIndex& index) const
{
  Q_UNUSED(index);

  switch (index.column()) {
  case TreeEntry::FamilyOrCurveName: {
    auto lineEdit = static_cast<QLineEdit*>(editor);

    auto entry = static_cast<TreeEntry*>(index.internalPointer());

    if (!entry)
      return;

    lineEdit->setText(entry->data(Qt::DisplayRole,
                                  index.column()).toString());
    break;
  }

  default:
    break;
  }
}


void
CurveTypeEntryDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  Q_UNUSED(editor);
  Q_UNUSED(model);
  Q_UNUSED(index);

  switch (index.column()) {
  case TreeEntry::FamilyOrCurveName: {
    auto lineEdit = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEdit->text(),
                   Qt::EditRole);

    break;
  }

  default:
    break;
  }
}

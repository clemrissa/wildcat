#include "UnitTableEntryDelegate.hpp"

#include <QtGui/QDoubleValidator>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QTableView>

#include <Gui/Units/UnitTableEntry.hpp>

#include "DimensionsDelegate.hpp"

using Geo::TypeSystem::Gui::UnitTableEntryDelegate;
using Geo::TypeSystem::Gui::Units::UnitTableEntry;

QWidget*
UnitTableEntryDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(parent);
  Q_UNUSED(option);

  using Geo::Domain::WellTrait;

  QWidget* result = nullptr;

  switch (index.column())
  {
    case UnitTableEntry::Name:
    case UnitTableEntry::Symbol:
    {
      result = new QLineEdit();

      result->setParent(parent);

      break;
    }

    case UnitTableEntry::Scale:
    case UnitTableEntry::Offset:
    {
      auto l = new QLineEdit();

      l->setParent(parent);
      l->setValidator(new QDoubleValidator());

      result = l;

      break;
    }

    case UnitTableEntry::Dimensions:
    {
      auto unitEntry = static_cast<UnitTableEntry*>(index.internalPointer());

      if (!unitEntry)
        return nullptr;

      using Geo::TypeSystem::Gui::DimensionsDelegate;

      auto c =
        new DimensionsDelegate(unitEntry->unit()->getDimensions());

      c->setParent(parent);

      result = c;
    }

    default:
      break;
  }

  return result;
}


void
UnitTableEntryDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  QRect r = option.rect;
  editor->setGeometry(r);
}


void
UnitTableEntryDelegate::
setEditorData(QWidget*           editor,
              const QModelIndex& index) const
{
  Q_UNUSED(index);

  switch (index.column())
  {
    case UnitTableEntry::Name:
    case UnitTableEntry::Symbol:
    case UnitTableEntry::Scale:
    case UnitTableEntry::Offset:
    {
      auto unitEntry =
        static_cast<UnitTableEntry*>(index.internalPointer());

      if (!unitEntry)
        return;

      auto lineEdit = static_cast<QLineEdit*>(editor);

      lineEdit->setText(unitEntry->data(Qt::DisplayRole,
                                        index.column()).toString());

      break;
    }

    default:
      break;
  }
}


void
UnitTableEntryDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  switch (index.column())
  {
    case UnitTableEntry::Name:
    case UnitTableEntry::Symbol:
    case UnitTableEntry::Scale:
    case UnitTableEntry::Offset:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);

      break;
    }

    /// fake "set data" to trigger save procedure
    case UnitTableEntry::Dimensions:
      model->setData(index, QString("Set Dimensions"),
                     Qt::EditRole);

      break;

    default:
      break;
  }
}

#include "UnitTableEntryDelegate.hpp"


#include <DependencyManager/ApplicationContext>

#include <Models/Units/UnitTableEntry.hpp>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtGui/QDoubleValidator>

using Geo::TypeSystem::Gui::UnitTableEntryDelegate;
using Geo::TypeSystem::Models::Units::UnitTableEntry;

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

  switch (index.column()) {
  case UnitTableEntry::Name:
  case UnitTableEntry::Symbol:
  {

    result = new QLineEdit();

    result->setParent(parent);

    break;
  }

  case UnitTableEntry::Scale:
  {
    auto l = new QLineEdit();
    l->setParent(parent);
    l->setValidator(new QDoubleValidator());
    
    result = l;

    break;
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

  editor->setGeometry(option.rect);
}


void
UnitTableEntryDelegate::
setEditorData(QWidget*           editor,
              const QModelIndex& index) const
{
  Q_UNUSED(index);

  switch (index.column()) {
  case UnitTableEntry::Name:
  case UnitTableEntry::Symbol: 
  case UnitTableEntry::Scale: {
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
  switch (index.column()) {
  case UnitTableEntry::Name:
  case UnitTableEntry::Symbol: 
  case UnitTableEntry::Scale:
    {
    auto lineEdit = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEdit->text(),
                   Qt::EditRole);

    break;
  }


  default:
    break;
  }
}


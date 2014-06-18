#include "ConnectionEntryItemDelegate.hpp"

#include <QComboBox>
#include <QLabel>
#include <QModelIndex>
#include <QWidget>

#include <Uni/Logging/Logging>

#include <Models/ConnectionsWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsWidgetModel/ConnectionsWidgetModel.hpp>

#include <Connections/Connection.hpp>

using Geo::Database::Gui::ConnectionEntryItemDelegate;

QWidget*
ConnectionEntryItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(option);

  using Geo::Database::Models::ConnectionsWidgetModel::ConnectionEntry;

  if (index.parent().isValid())
    return 0;

  ConnectionEntry* connection =
    static_cast<ConnectionEntry*>(index.internalPointer());

  if (connection) {
    QComboBox* cb = new QComboBox(parent);

    connect(cb,
            SIGNAL(activated(int)),
            this,
            SLOT(comboBoxActivated(int)));

    return cb;
  }

  return 0;
}


void
ConnectionEntryItemDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  editor->setGeometry(option.rect);
}


void
ConnectionEntryItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{
  Q_UNUSED(index);

  QComboBox* c = static_cast<QComboBox*>(editor);

  c->addItem(Connections::Connection::connectionTypeName(Connections::DatabaseType::MySql));
  c->addItem(Connections::Connection::connectionTypeName(Connections::DatabaseType::SQLite));

  c->showPopup();
}


void
ConnectionEntryItemDelegate::
setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  using Geo::Database::Models::ConnectionsWidgetModel::ConnectionsWidgetModel;

  if (!index.parent().isValid()) {
    QComboBox*              c = static_cast<QComboBox*>(editor);
    ConnectionsWidgetModel* m = static_cast<ConnectionsWidgetModel*>(model);

    m->addConnection((Connections::DatabaseType)c->currentIndex());
  }
}


void
ConnectionEntryItemDelegate::
comboBoxActivated(int index)
{
  Q_UNUSED(index);

  QComboBox* cd = static_cast<QComboBox*>(QObject::sender());

  emit commitData(cd);

  emit closeEditor(cd);
}

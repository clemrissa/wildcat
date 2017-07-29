#include "ConnectionEntryItemDelegate.hpp"

#include <QComboBox>
#include <QLabel>
#include <QModelIndex>
#include <QWidget>

#include "ConnectionEntry.hpp"
#include "ConnectionsEditorWidgetModel.hpp"

#include "Connections/IConnection.hpp"
#include "Connections/ConnectionUtils.hpp"

using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionEntryItemDelegate;

QWidget*
ConnectionEntryItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(option);

  using Geo::Database::Gui::ConnectionEntry;

  if (index.parent().isValid())
    return nullptr;

  ConnectionEntry* connection =
    static_cast<ConnectionEntry*>(index.internalPointer());

  if (connection)
  {
    QComboBox* cb = new QComboBox(parent);

    connect(cb,
            SIGNAL(activated(int)),
            this,
            SLOT(comboBoxActivated(int)));

    return cb;
  }

  return nullptr;
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

  c->addItem(ConnectionUtils::connectionTypeName(DatabaseType::SQLite));

  c->addItem(ConnectionUtils::connectionTypeName(DatabaseType::MongoDB));

  c->showPopup();
}


void
ConnectionEntryItemDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  using Geo::Database::Gui::ConnectionsEditorWidgetModel;

  if (!index.parent().isValid())
  {
    QComboBox* c = static_cast<QComboBox*>(editor);

    ConnectionsEditorWidgetModel* m = static_cast<ConnectionsEditorWidgetModel*>(model);

    DatabaseType databaseType = static_cast<DatabaseType>(c->currentIndex());

    m->addConnection(databaseType);
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

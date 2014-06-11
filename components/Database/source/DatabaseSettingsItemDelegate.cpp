#include "DatabaseSettingsItemDelegate.hpp"

#include <QComboBox>
#include <QLabel>
#include <QModelIndex>
#include <QWidget>

#include <Uni/Logging/Logging>

#include "Connection.hpp"
#include "DatabaseSettingsTreeConnection.hpp"
#include "DatabaseSettingsTreeModel.hpp"

using Geo::Database::DatabaseSettingsItemDelegate;

QWidget*
DatabaseSettingsItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const {
  if (index.parent().isValid())
    return 0;

  DatabaseSettingsTreeConnection* connection =
    static_cast<DatabaseSettingsTreeConnection*>(index.internalPointer());

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
DatabaseSettingsItemDelegate::
updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
  editor->setGeometry(option.rect);
}

void
DatabaseSettingsItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const {
  QComboBox* c = static_cast<QComboBox*>(editor);

  c->addItem(Connection::connectionTypeName(DatabaseType::MySql));
  c->addItem(Connection::connectionTypeName(DatabaseType::SQLite));

  c->showPopup();
}

void
DatabaseSettingsItemDelegate::
setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  if (!index.parent().isValid()) {
    QComboBox*                 c = static_cast<QComboBox*>(editor);
    DatabaseSettingsTreeModel* m =
      static_cast<DatabaseSettingsTreeModel*>(model);

    m->addConnection((DatabaseType)c->currentIndex());
  }
}

void
DatabaseSettingsItemDelegate::
comboBoxActivated(int index) {
  QComboBox* cd = static_cast<QComboBox*>(QObject::sender());
  emit       commitData(cd);

  emit closeEditor(cd);
}

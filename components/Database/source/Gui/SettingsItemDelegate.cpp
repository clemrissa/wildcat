#include "SettingsItemDelegate.hpp"

#include <QComboBox>
#include <QLabel>
#include <QModelIndex>
#include <QWidget>

#include <Uni/Logging/Logging>

#include "Connection.hpp"
#include "SettingsTreeConnection.hpp"
#include "SettingsTreeModel.hpp"

using Geo::Database::Gui::SettingsItemDelegate;

QWidget*
SettingsItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  if (index.parent().isValid())
    return 0;

  SettingsTreeConnection* connection =
    static_cast<SettingsTreeConnection*>(index.internalPointer());

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
SettingsItemDelegate::
updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  editor->setGeometry(option.rect);
}


void
SettingsItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{
  QComboBox* c = static_cast<QComboBox*>(editor);

  c->addItem(Connection::connectionTypeName(DatabaseType::MySql));
  c->addItem(Connection::connectionTypeName(DatabaseType::SQLite));

  c->showPopup();
}


void
SettingsItemDelegate::
setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  if (!index.parent().isValid()) {
    QComboBox*         c = static_cast<QComboBox*>(editor);
    SettingsTreeModel* m =
      static_cast<SettingsTreeModel*>(model);

    m->addConnection((DatabaseType)c->currentIndex());
  }
}


void
SettingsItemDelegate::
comboBoxActivated(int index)
{
  QComboBox* cd = static_cast<QComboBox*>(QObject::sender());
  emit       commitData(cd);

  emit closeEditor(cd);
}

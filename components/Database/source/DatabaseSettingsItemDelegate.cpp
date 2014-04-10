#include "DatabaseSettingsItemDelegate.hpp"

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QModelIndex>

#include <Uni/Logging/Logging>

#include "DatabaseSettingsTreeConnection.hpp"
#include "DatabaseSettingsTreeModel.hpp"
#include "Connection.hpp"

using Geo::Database::DatabaseSettingsItemDelegate;


QWidget * 
DatabaseSettingsItemDelegate::
createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {

  if (index.parent().isValid())
    return 0;

  DatabaseSettingsTreeConnection* connection = 
    static_cast<DatabaseSettingsTreeConnection*>(index.internalPointer());

  if (connection) {
    INFO << "Connection";

    QComboBox* cb = new QComboBox(parent);

    connect(cb,
            SIGNAL(activated(int)),
            this,
            SLOT(comboBoxActivated(int)));

    return cb;
  }
  else {
    INFO << " no connection";
    return 0;
  }
}


void 
DatabaseSettingsItemDelegate::
updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   editor->setGeometry(option.rect);
}



void 
DatabaseSettingsItemDelegate::
setEditorData(QWidget * editor, const QModelIndex & index) const {

  QComboBox* c = static_cast<QComboBox*>(editor);

  INFO << "Add data";

  c->addItem(Connection::connectionTypeName(DatabaseType::MySql));
  c->addItem(Connection::connectionTypeName(DatabaseType::SQLite));

  c->showPopup();
}


void 
DatabaseSettingsItemDelegate::
setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  //
  INFO << "save data";

  if (!index.parent().isValid()) {
    QComboBox* c = static_cast<QComboBox*>(editor);
    DatabaseSettingsTreeModel* m = 
      static_cast<DatabaseSettingsTreeModel*>(model);

  INFO << "current index " << c->currentIndex();

    m->addConnection((DatabaseType)c->currentIndex());
  }
}


void
DatabaseSettingsItemDelegate::
comboBoxActivated(int index)
{
  INFO << "activated";
 
  QComboBox* cd = static_cast<QComboBox*>(QObject::sender());
  emit commitData(cd);
  emit closeEditor(cd);
}


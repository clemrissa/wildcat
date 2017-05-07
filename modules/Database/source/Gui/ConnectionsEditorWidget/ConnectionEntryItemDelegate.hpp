#pragma once

#include <QStyledItemDelegate>

class QWidget;

namespace Geo {
namespace Database {
namespace Gui {
namespace ConnectionsEditorWidget {
//

class ConnectionEntryItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  QWidget*
  createEditor(QWidget*                    parent,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index) const override;

  void
  updateEditorGeometry(QWidget*                    editor,
                       const QStyleOptionViewItem& option,
                       const QModelIndex&          index) const override;

  void
  setEditorData(QWidget* editor, const QModelIndex& index) const override;

  virtual
  void
  setModelData(QWidget*            editor,
               QAbstractItemModel* model,
               const QModelIndex&  index) const override;

private slots:
  void
  comboBoxActivated(int index);
};

//
}
}
}
}

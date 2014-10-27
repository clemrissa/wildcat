#ifndef Geo_Database_Gui_DatabaseSettingsWidget_WellTraitItemDelegate_hpp
#define Geo_Database_Gui_DatabaseSettingsWidget_WellTraitItemDelegate_hpp

#include <QtWidgets/QStyledItemDelegate>

#include <map>
#include <utility>

class QWidget;

namespace Geo {
namespace Database {
namespace Gui {
namespace DatabaseSettingsWidget {
//

class WellTraitItemDelegate: public QStyledItemDelegate
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

  void
  setModelData(QWidget*            editor,
               QAbstractItemModel* model,
               const QModelIndex&  index) const override;

  QSize
  sizeHint(const QStyleOptionViewItem& option,
           const QModelIndex&          index) const override;

private:
  mutable std::map<std::pair<int, int>, QSize> _sizeHints;
};

//
}
}
}
}

#endif //  Geo_Database_Gui_DatabaseSettingsWidget_WellTraitItemDelegate_hpp

#ifndef Geo_Database_DatabasePropertiesWidgetModel_hpp
#define Geo_Database_DatabasePropertiesWidgetModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QVector>

namespace Geo {
namespace Database {

  //namespace Connections {
//class ConnectionManager;

//}


namespace Models {
namespace DatabaseSettingsWidgetModel {

class DatabasePropertiesWidgetModel: public QAbstractItemModel {
public:
  DatabasePropertiesWidgetModel();


  virtual
  ~DatabasePropertiesWidgetModel();

public:
  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  virtual
  QModelIndex
  parent(const QModelIndex& index) const override;

  virtual
  int
  columnCount(const QModelIndex& parent) const override;

  virtual
  int
  rowCount(const QModelIndex& parent) const override;

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

private:
  // database traits


};

}
}
}
}
#endif //  Geo_Database_DatabasePropertiesWidgetModel_hpp

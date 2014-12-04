#ifndef Geo_Models_ConnectionTableModel_hpp
#define Geo_Models_ConnectionTableModel_hpp

#include "ConnectionListModel.hpp"

namespace Geo {
namespace Models {
//

/// TODO: change base class to QAbstractItemModel
class ConnectionTableModel: public ConnectionListModel
{
public:
  virtual
  ~ConnectionTableModel();

public:
  virtual int
  columnCount(const QModelIndex& parent) const override;

  virtual QVariant
  data(const QModelIndex& index, int role) const override;
};

//
}
}
#endif //  Geo_Models_ConnectionTableModel_hpp

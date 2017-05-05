#ifndef Geo_Models_ConnectionTableModel_hpp
#define Geo_Models_ConnectionTableModel_hpp

#include "ConnectionListModel.hpp"

namespace Geo {
namespace Models {
namespace Implementation {

//

/// TODO: make class abstract, do not link to this library directly
class ConnectionTableModel: public ConnectionListModel
{
  Q_OBJECT

public:
  ConnectionTableModel();

  virtual
  ~ConnectionTableModel() {}

public:
  virtual int
  columnCount(const QModelIndex& parent) const override;

  virtual QVariant
  data(const QModelIndex& index, int role) const override;
};

//
}
}
}
#endif //  Geo_Models_ConnectionTableModel_hpp

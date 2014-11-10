#ifndef Geo_Import_TreeWrapper_WellInformation_hpp
#define Geo_Import_TreeWrapper_WellInformation_hpp

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include "TreeEntry.hpp"

#include <Uni/Logging/Logging>

namespace Geo {

namespace Domain {
  class WellTrait;
}

namespace Import {
namespace TreeWrapper {
//

class WellInfo: public TreeEntry
{
public:
  WellInfo(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent,
           int                     position);

  QVariant
  data(int role, int column) override;

  bool
  setData(int role, int column, QVariant value) override;

  const QSharedPointer<Geo::Domain::WellTrait> 
  getTrait() const;

  void
  setTrait(QSharedPointer<Geo::Domain::WellTrait> trait);

  void
  copyDataToLasToImport() override;

  QWidget*
  delegateWidget(int column) const override;

  void
  setDataFromWidget(QWidget* editor, QModelIndex const & index,
                    QAbstractItemModel *model) override;

  void
  setConnection(Geo::Database::Connections::Connection::Shared connection);

private:
  int _position;

  QSharedPointer<Geo::Domain::WellTrait> _trait;

private slots:
  void 
  importValueChanged();
};


//------------------------------------------------------


class WellInformationGroup: public TreeEntry
{
public:
  WellInformationGroup(QSharedPointer<LasFile> lasFile,
                       TreeEntry*              parent);

  QVariant
  data(int role, int column) override;
};


//
}
}
}

#endif // Geo_Import_TreeWrapper_WellInformation_hpp

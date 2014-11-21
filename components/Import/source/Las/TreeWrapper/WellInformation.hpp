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


class WellInfoBase: public TreeEntry
{
public:
  WellInfoBase(QSharedPointer<LasFile> lasFile,
               TreeEntry*              parent);

  virtual QWidget*
  delegateWidget(int column) const override;

  void
  setConnection(Geo::Database::Connections::Connection::Shared connection);
protected:
  virtual QStringList
  getWellTraitNames() const;

protected slots:
  void
  findAppropriateTrait();

protected:
  QSharedPointer<Geo::Domain::WellTrait> _trait;
};

// ------------------------------------------------------

class WellInfo: public WellInfoBase
{
public:
  WellInfo(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent,
           int                     position);

  QVariant
  data(int role, int column) const override;

  bool
  setData(int role, int column, QVariant value) override;

  const QSharedPointer<Geo::Domain::WellTrait>
  getTrait() const;

  void
  setTrait(QSharedPointer<Geo::Domain::WellTrait> trait);

  void
  copyDataToLasToImport() override;

  void
  setDataFromWidget(QWidget* editor, QModelIndex const& index,
                    QAbstractItemModel* model) override;


private:
  int _position;
};

// ------------------------------------------------------

class WellInformationGroup: public TreeEntry
{
public:
  WellInformationGroup(QSharedPointer<LasFile> lasFile,
                       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};

//
}
}
}

#endif // Geo_Import_TreeWrapper_WellInformation_hpp

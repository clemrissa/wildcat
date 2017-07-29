#pragma once

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Database/Connections/IConnection>
#include <Domain/WellTrait>

#include "TreeEntry.hpp"

namespace Geo
{

using Database::IConnection;

namespace Domain
{
class WellTrait;
}

namespace Import
{
namespace TreeWrapper
{
//

class WellInfoBase : public TreeEntry
{
public:
  WellInfoBase(std::shared_ptr<LasFile> lasFile,
               TreeEntry*              parent);

  virtual QWidget*
  delegateWidget(int column) const override;

  void
  setConnection(std::shared_ptr<IConnection> connection);

  bool
  setData(int role, int column, QVariant value) override;

  void
  setDataFromWidget(QWidget* editor, QModelIndex const& index,
                    QAbstractItemModel* model) override;

  virtual std::vector<Geo::Domain::WellTrait::Shared>
  getWellTraits() const;

protected:
  virtual QStringList
  getWellTraitNames() const;

  virtual void
  setImportValue(QVariant value) {}

  virtual void
  setTraitValue(QVariant trait);

  void
  setTrait(std::shared_ptr<Geo::Domain::WellTrait> trait);

  const std::shared_ptr<Geo::Domain::WellTrait>
  getTrait() const;

protected slots:
  void
  findAppropriateTrait();

protected:
  std::shared_ptr<Geo::Domain::WellTrait> _trait;
};

// ------------------------------------------------------

class WellInfo : public WellInfoBase
{
public:
  WellInfo(std::shared_ptr<LasFile> lasFile,
           TreeEntry*              parent,
           int position);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;

private:
  int _position;
};

// ------------------------------------------------------

class WellInformationGroup : public TreeEntry
{
public:
  WellInformationGroup(std::shared_ptr<LasFile> lasFile,
                       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};

//
}
}
}

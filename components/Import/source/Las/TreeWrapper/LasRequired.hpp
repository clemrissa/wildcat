#ifndef Geo_Import_TreeWrapper_LasRequired_hpp
#define Geo_Import_TreeWrapper_LasRequired_hpp

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


class WellName: public TreeEntry
{
public:
  WellName(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellCompany: public TreeEntry
{
public:
  WellCompany(QSharedPointer<LasFile> lasFile,
              TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellServiceCompany: public TreeEntry
{
public:
  WellServiceCompany(QSharedPointer<LasFile> lasFile,
                     TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellField: public TreeEntry
{
public:
  WellField(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellLocation: public TreeEntry
{
public:
  WellLocation(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellDate: public TreeEntry
{
public:
  WellDate(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class LasRequiredGroup: public TreeEntry
{
public:
  LasRequiredGroup(QSharedPointer<LasFile> lasFile,
                   TreeEntry*              parent);

  QVariant
  data(int role, int column) override;
};


//
}
}
}

#endif // Geo_Import_TreeWrapper_LasRequired_hpp

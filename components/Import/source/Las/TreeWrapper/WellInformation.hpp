#ifndef Geo_Import_TreeWrapper_WellInformation_hpp
#define Geo_Import_TreeWrapper_WellInformation_hpp

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include "TreeEntry.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
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


class WellStart: public TreeEntry
{
public:
  WellStart(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellStop: public TreeEntry
{
public:
  WellStop(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellStep: public TreeEntry
{
public:
  WellStep(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) override;

  void
  copyDataToLasToImport() override;
};


//------------------------------------------------------


class WellNull: public TreeEntry
{
public:
  WellNull(QSharedPointer<LasFile> lasFile,
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


//------------------------------------------------------


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

  void
  copyDataToLasToImport() override;

  QWidget*
  delegateWidget(int column) override;

private:
  int _position;
};

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

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

class RequiredFieldBase: public TreeEntry
{
public:
  RequiredFieldBase(QSharedPointer<LasFile> lasFile,
                    TreeEntry*              parent);

  virtual QWidget*
  delegateWidget(int column) const override;
};

class WellName: public RequiredFieldBase
{
public:
  WellName(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellCompany: public RequiredFieldBase
{
public:
  WellCompany(QSharedPointer<LasFile> lasFile,
              TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellServiceCompany: public RequiredFieldBase
{
public:
  WellServiceCompany(QSharedPointer<LasFile> lasFile,
                     TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellField: public RequiredFieldBase
{
public:
  WellField(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellLocation: public RequiredFieldBase
{
public:
  WellLocation(QSharedPointer<LasFile> lasFile,
               TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellDate: public RequiredFieldBase
{
public:
  WellDate(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellCountry: public RequiredFieldBase
{
public:
  WellCountry(QSharedPointer<LasFile> lasFile,
              TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellState: public RequiredFieldBase
{
public:
  WellState(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellCounty: public RequiredFieldBase
{
public:
  WellCounty(QSharedPointer<LasFile> lasFile,
             TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellProvince: public RequiredFieldBase
{
public:
  WellProvince(QSharedPointer<LasFile> lasFile,
               TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellAPI: public RequiredFieldBase
{
public:
  WellAPI(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class WellUWI: public RequiredFieldBase
{
public:
  WellUWI(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class LasRequiredGroup: public RequiredFieldBase
{
public:
  LasRequiredGroup(QSharedPointer<LasFile> lasFile,
                   TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};

//
}
}
}

#endif // Geo_Import_TreeWrapper_LasRequired_hpp

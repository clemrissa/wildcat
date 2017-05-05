#ifndef Geo_Import_TreeWrapper_LasRequired_hpp
#define Geo_Import_TreeWrapper_LasRequired_hpp

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include "TreeEntry.hpp"
#include "WellInformation.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
namespace Domain {
class WellTrait;
}

namespace Import {
namespace TreeWrapper {
//

class WellName: public WellInfoBase
{
public:
  WellName(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellCompany: public WellInfoBase
{
public:
  WellCompany(QSharedPointer<LasFile> lasFile,
              TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellServiceCompany: public WellInfoBase
{
public:
  WellServiceCompany(QSharedPointer<LasFile> lasFile,
                     TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellField: public WellInfoBase
{
public:
  WellField(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellLocation: public WellInfoBase
{
public:
  WellLocation(QSharedPointer<LasFile> lasFile,
               TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellDate: public WellInfoBase
{
public:
  WellDate(QSharedPointer<LasFile> lasFile,
           TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellCountry: public WellInfoBase
{
public:
  WellCountry(QSharedPointer<LasFile> lasFile,
              TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellState: public WellInfoBase
{
public:
  WellState(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellCounty: public WellInfoBase
{
public:
  WellCounty(QSharedPointer<LasFile> lasFile,
             TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellProvince: public WellInfoBase
{
public:
  WellProvince(QSharedPointer<LasFile> lasFile,
               TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellAPI: public WellInfoBase
{
public:
  WellAPI(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class WellUWI: public WellInfoBase
{
public:
  WellUWI(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;

protected:
  void
  setImportValue(QVariant value) override;
};

// ------------------------------------------------------

class LasRequiredGroup: public TreeEntry
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
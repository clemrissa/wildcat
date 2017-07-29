#pragma once

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include <Domain/WellTrait>

#include "TreeEntry.hpp"
#include "WellInformation.hpp"

namespace Geo
{
namespace Domain
{
class WellTrait;
}

namespace Import
{
namespace TreeWrapper
{
//

class WellName : public WellInfoBase
{
public:
  WellName(std::shared_ptr<LasFile> lasFile,
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

class WellCompany : public WellInfoBase
{
public:
  WellCompany(std::shared_ptr<LasFile> lasFile,
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

class WellServiceCompany : public WellInfoBase
{
public:
  WellServiceCompany(std::shared_ptr<LasFile> lasFile,
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

class WellField : public WellInfoBase
{
public:
  WellField(std::shared_ptr<LasFile> lasFile,
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

class WellLocation : public WellInfoBase
{
public:
  WellLocation(std::shared_ptr<LasFile> lasFile,
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

class WellDate : public WellInfoBase
{
public:
  WellDate(std::shared_ptr<LasFile> lasFile,
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

class WellCountry : public WellInfoBase
{
public:
  WellCountry(std::shared_ptr<LasFile> lasFile,
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

class WellState : public WellInfoBase
{
public:
  WellState(std::shared_ptr<LasFile> lasFile,
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

class WellCounty : public WellInfoBase
{
public:
  WellCounty(std::shared_ptr<LasFile> lasFile,
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

class WellProvince : public WellInfoBase
{
public:
  WellProvince(std::shared_ptr<LasFile> lasFile,
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

class WellAPI : public WellInfoBase
{
public:
  WellAPI(std::shared_ptr<LasFile> lasFile,
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

class WellUWI : public WellInfoBase
{
public:
  WellUWI(std::shared_ptr<LasFile> lasFile,
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

class LasRequiredGroup : public TreeEntry
{
public:
  LasRequiredGroup(std::shared_ptr<LasFile> lasFile,
                   TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};

//
}
}
}

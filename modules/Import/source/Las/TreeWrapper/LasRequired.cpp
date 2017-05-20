#include "LasRequired.hpp"

using Geo::Import::TreeWrapper::WellName;

WellName::
WellName(std::shared_ptr<LasFile> lasFile,
         TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellName::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("WELL");
      break;

    case TreeEntry::Description:
      return tr("Well name");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.wellName;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.wellName;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

      break;

    default:
      return QVariant();
      break;
  }
}


void
WellName::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.wellName =
    _lasFile->lasRequired.wellName;
}


void
WellName::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.wellName =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellCompany;

WellCompany::
WellCompany(std::shared_ptr<LasFile> lasFile,
            TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellCompany::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("COMP");
      break;

    case TreeEntry::Description:
      return tr("Oil Company");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.company;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.company;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

      break;

    default:
      return QVariant();
      break;
  }
}


void
WellCompany::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.company =
    _lasFile->lasRequired.company;
}


void
WellCompany::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.company =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellServiceCompany;

WellServiceCompany::
WellServiceCompany(std::shared_ptr<LasFile> lasFile,
                   TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellServiceCompany::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("SRVC");
      break;

    case TreeEntry::Description:
      return tr("Service Company");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.serviceCompany;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.serviceCompany;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

      break;

    default:
      return QVariant();
      break;
  }
}


void
WellServiceCompany::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.serviceCompany =
    _lasFile->lasRequired.serviceCompany;
}


void
WellServiceCompany::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.serviceCompany =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellField;

WellField::
WellField(std::shared_ptr<LasFile> lasFile,
          TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellField::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("FLD");
      break;

    case TreeEntry::Description:
      return tr("Field");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.field;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.field;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

      break;

    default:
      return QVariant();
      break;
  }
}


void
WellField::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.field =
    _lasFile->lasRequired.field;
}


void
WellField::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.field =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellLocation;

WellLocation::
WellLocation(std::shared_ptr<LasFile> lasFile,
             TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellLocation::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("LOC");
      break;

    case TreeEntry::Description:
      return tr("Location");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.location;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.location;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

      break;

    default:
      return QVariant();
      break;
  }
}


void
WellLocation::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.location =
    _lasFile->lasRequired.location;
}


void
WellLocation::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.location =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellDate;

WellDate::
WellDate(std::shared_ptr<LasFile> lasFile,
         TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellDate::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("DATE");
      break;

    case TreeEntry::Description:
      return tr("Date");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.date;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.date;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellDate::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.date =
    _lasFile->lasRequired.date;
}


void
WellDate::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.date =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellCountry;

WellCountry::
WellCountry(std::shared_ptr<LasFile> lasFile,
            TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellCountry::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("CTRY");
      break;

    case TreeEntry::Description:
      return tr("Country");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.country;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.country;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellCountry::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.country =
    _lasFile->lasRequired.country;
}


void
WellCountry::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.country =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellState;

WellState::
WellState(std::shared_ptr<LasFile> lasFile,
          TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellState::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("STAT");
      break;

    case TreeEntry::Description:
      return tr("State");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.state;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.state;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellState::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.state =
    _lasFile->lasRequired.state;
}


void
WellState::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.state =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellCounty;

WellCounty::
WellCounty(std::shared_ptr<LasFile> lasFile,
           TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellCounty::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("CNTY");
      break;

    case TreeEntry::Description:
      return tr("County");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.county;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.county;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellCounty::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.county =
    _lasFile->lasRequired.county;
}


void
WellCounty::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.county =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellProvince;

WellProvince::
WellProvince(std::shared_ptr<LasFile> lasFile,
             TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellProvince::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("PROV");
      break;

    case TreeEntry::Description:
      return tr("Province");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.province;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.province;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellProvince::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.province =
    _lasFile->lasRequired.province;
}


void
WellProvince::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.province =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellAPI;

WellAPI::
WellAPI(std::shared_ptr<LasFile> lasFile,
        TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellAPI::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("API");
      break;

    case TreeEntry::Description:
      return tr("API");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.api;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.api;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellAPI::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.api =
    _lasFile->lasRequired.api;
}


void
WellAPI::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.api =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellUWI;

WellUWI::
WellUWI(std::shared_ptr<LasFile> lasFile,
        TreeEntry*              parent) :
  WellInfoBase(lasFile, parent)
{}

QVariant
WellUWI::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("UWI");
      break;

    case TreeEntry::Description:
      return tr("UWI");
      break;

    case TreeEntry::Value:
      return _lasFile->lasRequired.uwi;
      break;

    case TreeEntry::ImportValue:
      return _lasFileToImport->lasRequired.uwi;
      break;

    case TreeEntry::Type:

      if (_trait)
        return _trait->name();
      else
        return QVariant();

    default:
      return QVariant();
      break;
  }
}


void
WellUWI::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.uwi =
    _lasFile->lasRequired.uwi;
}


void
WellUWI::
setImportValue(QVariant value)
{
  _lasFileToImport->lasRequired.uwi =
    value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::LasRequiredGroup;

LasRequiredGroup::
LasRequiredGroup(std::shared_ptr<LasFile> lasFile,
                 TreeEntry*              parent) :
  TreeEntry(lasFile, parent)
{
  _entries.push_back(new WellName(_lasFile, this));
  _entries.push_back(new WellCompany(_lasFile, this));
  _entries.push_back(new WellServiceCompany(_lasFile,
                                            this));
  _entries.push_back(new WellField(_lasFile, this));
  _entries.push_back(new WellLocation(_lasFile, this));
  _entries.push_back(new WellDate(_lasFile, this));
  _entries.push_back(new WellCountry(_lasFile, this));
  _entries.push_back(new WellState(_lasFile, this));
  _entries.push_back(new WellCounty(_lasFile, this));
  _entries.push_back(new WellProvince(_lasFile, this));
  _entries.push_back(new WellAPI(_lasFile, this));
  _entries.push_back(new WellUWI(_lasFile, this));
}


QVariant
LasRequiredGroup::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("Las Required");
      break;

    default:
      return QVariant();
      break;
  }
}


// ------------------------------------------------------

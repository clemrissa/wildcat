#include "LasRequired.hpp"

using Geo::Import::TreeWrapper::WellName;

WellName::
WellName(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}

QVariant
WellName::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("WELL");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.wellName;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.wellName;
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



//------------------------------------------------------


using Geo::Import::TreeWrapper::WellCompany;

WellCompany::
WellCompany(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
  
}


QVariant
WellCompany::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
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


//------------------------------------------------------


using Geo::Import::TreeWrapper::WellServiceCompany;

WellServiceCompany::
WellServiceCompany(QSharedPointer<LasFile> lasFile,
            TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
  
}


QVariant
WellServiceCompany::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
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

//------------------------------------------------------


using Geo::Import::TreeWrapper::WellField;

WellField::
WellField(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
}


QVariant
WellField::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
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


//------------------------------------------------------


using Geo::Import::TreeWrapper::WellLocation;

WellLocation::
WellLocation(QSharedPointer<LasFile> lasFile,
             TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
}


QVariant
WellLocation::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
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


//------------------------------------------------------


using Geo::Import::TreeWrapper::WellDate;

WellDate::
WellDate(QSharedPointer<LasFile> lasFile,
             TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
}


QVariant
WellDate::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
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


//------------------------------------------------------


using Geo::Import::TreeWrapper::LasRequiredGroup;


LasRequiredGroup::
LasRequiredGroup(QSharedPointer<LasFile> lasFile,
                 TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
  _entries.push_back(new WellName(_lasFile, this));

  _entries.push_back(new WellCompany(_lasFile, this));

  _entries.push_back(new WellServiceCompany(_lasFile, this));

  _entries.push_back(new WellField(_lasFile, this));

  _entries.push_back(new WellLocation(_lasFile, this));

  _entries.push_back(new WellDate(_lasFile, this));
}


QVariant
LasRequiredGroup::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Las Required");
    break;

  default:
    return QVariant();
    break;
  }
}


//------------------------------------------------------

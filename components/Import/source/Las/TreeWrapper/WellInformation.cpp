#include "WellInformation.hpp"

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

using Geo::Import::TreeWrapper::WellInfo;


WellInfo::
WellInfo(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent,
         int                     position):
  TreeEntry(lasFile, parent), _position(position)
{
}

QVariant
WellInfo::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  QString key = _lasFile->wellInformation.keys()[_position];

  switch (column) {
  case TreeEntry::Name:
    return _lasFile->wellInformation[key].name;
    break;

  case TreeEntry::Description:
    return _lasFile->wellInformation[key].description;
    break;

  case TreeEntry::Value:
    return _lasFile->wellInformation[key].value;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->wellInformation[key].value;
    break;


  case TreeEntry::Type: 
    if (!_trait.isNull())
      return _trait->name();
    else
      return QVariant();
    break;

  case TreeEntry::Units:
    return _lasFile->wellInformation[key].units;
    break;

  default:
    return QVariant();
    break;
  }
}


bool
WellInfo::
setData(int role, int column, QVariant value) 
{
  QString key = _lasFile->wellInformation.keys()[_position];

  bool result = false;

  switch (column) {
  case TreeEntry::ImportValue: {
    _lasFileToImport->wellInformation[key].value = value.toString();

    importValueChanged();

    result = true;
    break;
  }

  //case TreeEntry::Type: {
  //}

  default:
    break;
  }

  return result;
}


const QSharedPointer<Geo::Domain::WellTrait> 
WellInfo::
getTrait() const 
{
  return _trait;
}


void
WellInfo::
setTrait(QSharedPointer<Geo::Domain::WellTrait> trait)
{
  _trait = trait;
}


void
WellInfo::
copyDataToLasToImport() 
{
  QString key = _lasFile->wellInformation.keys()[_position];

  _lasFileToImport->wellInformation[key] =
    _lasFile->wellInformation[key];

  importValueChanged();
}


QWidget*
WellInfo::
delegateWidget(int column) 
{
  using Geo::Domain::WellTrait;

  QWidget* result = nullptr;

  if (_connection.isNull())
    return result;

  switch (column) {
  case TreeEntry::ImportValue: {
    QLineEdit* line = new QLineEdit();

    QString key = _lasFile->wellInformation.keys()[_position];
    line->setText(_lasFileToImport->wellInformation[key].value);

    result = line;
    break;
  }

  case TreeEntry::Type: {
    QComboBox* comboBox = new QComboBox();

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

    QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

    for (WellTrait::Shared t : traits)
      comboBox->addItem(t->name());

    result = comboBox;

    break;
  }

  default:
    break;
  }

  return result;
}


void
WellInfo::
setConnection(Geo::Database::Connections::Connection::Shared connection)
{
  TreeEntry::setConnection(connection);

  importValueChanged();
}


void 
WellInfo::
importValueChanged()
{
  using Geo::Domain::WellTrait;

  if (_connection.isNull())
    return;

  QString key = _lasFile->wellInformation.keys()[_position];
  QString name = _lasFile->wellInformation[key].name;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

  QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

  for (WellTrait::Shared t : traits)
    if (t->synonyms().contains(name))
    {
      _trait = t;
    }
}


//------------------------------------------------------

using Geo::Import::TreeWrapper::WellInformationGroup;


WellInformationGroup::
WellInformationGroup(QSharedPointer<LasFile> lasFile,
                     TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
  for (int i = 0; i < _lasFile->wellInformation.keys().size(); ++i)
    _entries.push_back(new WellInfo(_lasFile, this, i));
}


QVariant
WellInformationGroup::
data(int role, int column) 
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Well Information");
    break;

  default:
    return QVariant();
    break;
  }
}

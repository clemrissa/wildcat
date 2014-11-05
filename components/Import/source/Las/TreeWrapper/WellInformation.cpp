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
    return tr("Well");
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

using Geo::Import::TreeWrapper::WellStart;

WellStart::
WellStart(QSharedPointer<LasFile> lasFile,
          TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
WellStart::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Start");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.start;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.start;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}


void
WellStart::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.start =
    _lasFile->lasRequired.start;
}


//------------------------------------------------------

using Geo::Import::TreeWrapper::WellStop;


WellStop::
WellStop(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
WellStop::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Stop");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.stop;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.stop;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}


void
WellStop::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.stop =
    _lasFile->lasRequired.stop;
}



//------------------------------------------------------

using Geo::Import::TreeWrapper::WellStep;


WellStep::
WellStep(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}


QVariant
WellStep::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Step");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.step;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.step;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}

void
WellStep::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.step =
    _lasFile->lasRequired.step;
}


//------------------------------------------------------

using Geo::Import::TreeWrapper::WellNull;

WellNull::
WellNull(QSharedPointer<LasFile> lasFile,
         TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
}

QVariant
WellNull::
data(int role, int column)
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column) {
  case TreeEntry::Name:
    return tr("Null");
    break;

  case TreeEntry::Value:
    return _lasFile->lasRequired.nullValue;
    break;

  case TreeEntry::ImportValue:
    return _lasFileToImport->lasRequired.nullValue;
    break;

  case TreeEntry::Units:
    return _lasFile->lasRequired.units;
    break;

  default:
    return QVariant();
    break;
  }
}

void
WellNull::
copyDataToLasToImport()
{
  _lasFileToImport->lasRequired.nullValue =
    _lasFile->lasRequired.nullValue;
}


//------------------------------------------------------

using Geo::Import::TreeWrapper::LasRequiredGroup;


LasRequiredGroup::
LasRequiredGroup(QSharedPointer<LasFile> lasFile,
                 TreeEntry*              parent):
  TreeEntry(lasFile, parent)
{
  _entries.push_back(new WellName(_lasFile, this));

  _entries.push_back(new WellStart(_lasFile, this));

  _entries.push_back(new WellStop(_lasFile, this));

  _entries.push_back(new WellStep(_lasFile, this));

  _entries.push_back(new WellNull(_lasFile, this));
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

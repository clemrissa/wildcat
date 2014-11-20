#include "WellInformation.hpp"

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
data(int role, int column) const
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

  return QVariant();
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

  case TreeEntry::Type: {
    using Geo::Domain::WellTrait;

    auto dataAccessFactory = _connection->dataAccessFactory();

    auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

    QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

    setTrait(traits[value.toInt()]);

    break;
  }

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
delegateWidget(int column) const
{
  QWidget* result = nullptr;

  if (_connection.isNull())
    return result;

  switch (column) {
  case TreeEntry::ImportValue: {
    QLineEdit* line = new QLineEdit();

    line->setText(data(Qt::DisplayRole, TreeEntry::ImportValue).toString());
    result = line;
    break;
  }

  case TreeEntry::Type: {
    using Geo::Domain::WellTrait;

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
setDataFromWidget(QWidget*            editor,
                  QModelIndex const&  index,
                  QAbstractItemModel* model)
{
  switch (index.column()) {
  case TreeEntry::ImportValue: {
    auto lineEdit = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEdit->text(), Qt::EditRole);
    break;
  }

  case TreeEntry::Type: {
    auto cbox = static_cast<QComboBox*>(editor);

    model->setData(index, cbox->currentIndex(), Qt::EditRole);
    break;
  }

  default:
    break;
  }
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

  QString key  = _lasFile->wellInformation.keys()[_position];
  QString name = _lasFile->wellInformation[key].name;

  auto dataAccessFactory = _connection->dataAccessFactory();

  auto wellTraitAccess = dataAccessFactory->wellTraitAccess();

  QVector<WellTrait::Shared> traits = wellTraitAccess->findAll();

  for (WellTrait::Shared t : traits)
    if (t->synonyms().contains(name))
      _trait = t;

}


// ------------------------------------------------------

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
data(int role, int column) const
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

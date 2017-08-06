#include "WellInformation.hpp"

// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellInfoBase;

WellInfoBase::
WellInfoBase(std::shared_ptr<LasFile> lasFile,
             TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
  findAppropriateTrait();
}


QWidget*
WellInfoBase::
delegateWidget(int column) const
{
  QWidget* result = nullptr;

  switch (column)
  {
    case TreeEntry::ImportValue:
    {
      QLineEdit* line = new QLineEdit();

      line->setText(data(Qt::DisplayRole, TreeEntry::ImportValue).toString());

      result = line;
      break;
    }

    case TreeEntry::Type:
    {
      QComboBox* comboBox = new QComboBox();

      auto traitList = getWellTraitNames();

      for (QString s : traitList)
        comboBox->addItem(s);

      result = comboBox;
      break;
    }

    default:
      break;
  }

  return result;
}


void
WellInfoBase::
setConnection(std::shared_ptr<IConnection> connection)
{
  TreeEntry::setConnection(connection);

  findAppropriateTrait();
}


bool
WellInfoBase::
setData(int role, int column, QVariant value)
{
  Q_UNUSED(role);

  bool result = false;

  switch (column)
  {
    case TreeEntry::ImportValue:
    {
      setImportValue(value);

      result = true;
      break;
    }

    case TreeEntry::Type:
    {
      setTraitValue(value);

      result = true;
      break;
    }

    default:
      break;
  }

  return result;
}


void
WellInfoBase::
setDataFromWidget(QWidget*            editor,
                  QModelIndex const&  index,
                  QAbstractItemModel* model)
{
  switch (index.column())
  {
    case TreeEntry::ImportValue:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(), Qt::EditRole);
      break;
    }

    case TreeEntry::Type:
    {
      auto cbox = static_cast<QComboBox*>(editor);

      model->setData(index, cbox->currentIndex(), Qt::EditRole);
      break;
    }

    default:
      break;
  }
}


std::vector<Geo::Domain::WellTrait::Shared>
WellInfoBase::
getWellTraits() const
{
  using Geo::Domain::WellTrait;

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto wellTraitAccess   = dataAccessFactory->wellTraitAccess();

  return wellTraitAccess->findAll();
}


QStringList
WellInfoBase::
getWellTraitNames() const
{
  QStringList result;

  using Geo::Domain::WellTrait;

  std::vector<WellTrait::Shared> traits = getWellTraits();

  for (WellTrait::Shared t : traits)
    result.push_back(t->name());

  return result;
}


void
WellInfoBase::
setTraitValue(QVariant trait)
{
  using Geo::Domain::WellTrait;

  std::vector<WellTrait::Shared> traits = getWellTraits();

  setTrait(traits[trait.toInt()]);
}


void
WellInfoBase::
setTrait(std::shared_ptr<Geo::Domain::WellTrait> trait)
{
  _trait = trait;
}


const std::shared_ptr<Geo::Domain::WellTrait>
WellInfoBase::
getTrait() const
{
  return _trait;
}


void
WellInfoBase::
findAppropriateTrait()
{
  using Geo::Domain::WellTrait;

  if (!_connection)
    return;

  QString name = data(Qt::DisplayRole, TreeEntry::Name).toString();

  std::vector<WellTrait::Shared> traits = getWellTraits();

  bool changed = false;

  for (WellTrait::Shared t : traits)
    if (t->synonyms().contains(name))
    {
      changed = true;
      _trait  = t;
      break;
    }

  if (!changed)
    _trait.reset();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellInfo;

WellInfo::
WellInfo(std::shared_ptr<LasFile> lasFile,
         TreeEntry*              parent,
         int position) :
  WellInfoBase(lasFile, parent),
  _position(position)
{}

QVariant
WellInfo::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  QString key = _lasFile->wellInformation.keys()[_position];

  switch (column)
  {
    case TreeEntry::Name:
      return key;
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

      if (_trait)
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


void
WellInfo::
copyDataToLasToImport()
{
  QString key = _lasFile->wellInformation.keys()[_position];

  _lasFileToImport->wellInformation[key] =
    _lasFile->wellInformation[key];
}


void
WellInfo::
setImportValue(QVariant value)
{
  QString key = _lasFile->wellInformation.keys()[_position];

  _lasFileToImport->wellInformation[key].value = value.toString();
}


// ------------------------------------------------------

using Geo::Import::TreeWrapper::WellInformationGroup;

WellInformationGroup::
WellInformationGroup(std::shared_ptr<LasFile> lasFile,
                     TreeEntry*              parent)
  : TreeEntry(lasFile, parent)
{
  for (int i = 0; i < _lasFile->wellInformation.keys().size(); ++i)
    _entries.push_back(std::make_unique<WellInfo>(_lasFile, this, i));
}


QVariant
WellInformationGroup::
data(int role, int column) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  switch (column)
  {
    case TreeEntry::Name:
      return tr("Well Information");
      break;

    default:
      return QVariant();
      break;
  }
}

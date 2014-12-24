#include "CurveTypeEntry.hpp"

#include <QtGui/QColor>
#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>

#include "FamilyEntry.hpp"

using Geo::Domain::CurveType;
using Geo::TypeSystem::Models::CurveTypes::CurveTypeEntry;
using Geo::TypeSystem::Models::CurveTypes::FamilyEntry;
using Geo::TypeSystem::Models::CurveTypes::TreeEntry;

CurveTypeEntry::
CurveTypeEntry(Geo::Domain::CurveType::Shared curveType,
               TreeEntry*                     parent):
  TreeEntry(parent),
  _curveType(curveType),
  _persisted(_curveType->isValid())
{
}


CurveTypeEntry::
CurveTypeEntry(QString    curveTypeName,
               TreeEntry* parent):
  TreeEntry(parent),
  _curveType(new CurveType()),
  _persisted(_curveType->isValid())
{
  auto f = static_cast<FamilyEntry*>(parent);

  _curveType->setFamily(f->getFamily());
  _curveType->setName(curveTypeName);
}


// CurveTypeEntry::
// CurveTypeEntry(QDomElement& de,
// TreeEntry*   parent):
// TreeEntry(parent),
// _curveType(new CurveType()),
// _persisted(_curveType->isValid())
// {
// QDomElement mnem = de.firstChildElement("CurveMnemonic");

// QString family;
// QString name;

// if (mnem.isNull()) {
// family = de.firstChildElement("MainFamily").text();
// name   = de.firstChildElement("Family").text();
// } else {
// family = de.firstChildElement("Family").text();
// name   = de.firstChildElement("SubFamily").text();
// }

// _curveType->setFamily(family);
// _curveType->setName(name);

// _curveType->setMnemonic(de.firstChildElement("CurveMnemonic").text());
// _curveType->setTextUnit(de.firstChildElement("Unit").text());

// bool ok;
// _curveType->setMin(de.firstChildElement("Min").text().toDouble(&ok));
// _curveType->setMax(de.firstChildElement("Max").text().toDouble(&ok));

//// TODO scale
// _scale      = de.firstChildElement("Scale").text().toLower();
// _continuity = de.firstChildElement("Type").text();
// }

CurveTypeEntry::
~CurveTypeEntry()
{
}


void
CurveTypeEntry::
addXmlData(QDomElement& de)
{
  QString mnem = de.firstChildElement("CurveMnemonic").text();

  if (_curveType->mnemonic().isEmpty())
    _curveType->setMnemonic(mnem);

  else {
    QStringList synonyms = _curveType->synonyms();

    if (!synonyms.contains(mnem)) {
      synonyms.append(mnem);

      _curveType->setSynonyms(synonyms);
    }
  }

  _curveType->setTextUnit(de.firstChildElement("Unit").text());

  bool ok;
  _curveType->setMin(de.firstChildElement("Min").text().toDouble(&ok));
  _curveType->setMax(de.firstChildElement("Max").text().toDouble(&ok));

  // TODO scale
  _scale      = de.firstChildElement("Scale").text().toLower();
  _continuity = de.firstChildElement("Type").text();
}


QDomElement
CurveTypeEntry::
getXmlDescription(QDomDocument& doc)
{
  QDomElement tag = doc.createElement("CurveType");

  auto addValue = [&](QString n, QString v)
                  {
                    QDomElement e = doc.createElement(n);
                    tag.appendChild(e);

                    QDomText t = doc.createTextNode(v);
                    e.appendChild(t);
                  };

  addValue("Name", _curveType->name());
  addValue("Mnemonic", _curveType->mnemonic());
  addValue("TextUnit", _curveType->textUnit());
  addValue("Min", QString("%1").arg(_curveType->min(), 0, 'g', 3));
  addValue("Max", QString("%1").arg(_curveType->max(), 0, 'g', 3));

  return tag;
}


QVariant
CurveTypeEntry::
data(int role, int column) const
{
  switch (role) {
  case Qt::DisplayRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::EditRole:
    return getDisplayOrEditRole(column);
    break;

  case Qt::DecorationRole:
    return getDecorationRole(column);
    break;

  case Qt::ForegroundRole:
    return getForegroundRole(column);
    break;

  case Qt::BackgroundRole:
    return getBackgroundRole(column);
    break;

  default:
    break;
  }

  return QVariant();
}


QWidget*
CurveTypeEntry::
delegateWidget(int column) const
{
  QWidget* result = nullptr;

  switch (column) {
  case TreeEntry::FamilyOrCurveName:
  case TreeEntry::Mnemonic:
  case TreeEntry::Synonyms:
    result = new QLineEdit();

    break;

  case TreeEntry::Units: {
    auto comboBox = new QComboBox();

    auto unitNames = getUnitNames();

    for (QString s : unitNames)
      comboBox->addItem(s);

    result = comboBox;

    break;
  }

  default:
    break;
  }

  return result;
}


QVariant
CurveTypeEntry::
getDisplayOrEditRole(int column) const
{
  switch (column) {
  case TreeEntry::FamilyOrCurveName:

    return _curveType->name();
    break;

  case TreeEntry::Mnemonic:
    return _curveType->mnemonic();
    break;

  case TreeEntry::Synonyms:
    return QStringList(_curveType->synonyms()).join(",");

  case TreeEntry::Units:
    return _curveType->textUnit();
    break;

  case TreeEntry::Min:
    return _curveType->min();
    break;

  case TreeEntry::Max:
    return _curveType->max();
    break;

  case TreeEntry::Scale:
    return _scale;
    break;

  case TreeEntry::Continuity:
    return _continuity;
    break;

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


QVariant
CurveTypeEntry::
getDecorationRole(int column) const
{
  // TODO
  // if (!_unit->isValid())
  // return QVariant();

  if (column == CloseAction)

    switch (_state) {
    case Active:
      return QIcon(":/delete.png");
      break;

    case Deleted:
      return QIcon(":/revert.png");
      break;
    }

  return QVariant();
}


QVariant
CurveTypeEntry::
getForegroundRole(int column) const
{
  Q_UNUSED(column);

  QVariant result;

  switch (_state) {
  case Active: {
    QPalette palette;
    result =  QColor(palette.color(QPalette::WindowText));
    break;
  }

  case Deleted:
    result = QColor(Qt::lightGray);
    break;
  }

  return result;
}


QVariant
CurveTypeEntry::
getBackgroundRole(int column) const
{
  QVariant result;

  if (column != CurveTypeEntry::Units)
    return result;

  if (_curveType->unit().isNull())
    result = QColor(0xFF, 0xD0, 0xC0);

  return result;
}


QVector<Geo::Domain::Unit::Shared>
CurveTypeEntry::
getUnits() const
{
  QVector<Geo::Domain::Unit::Shared> result;

  if (_connection.isNull())
    return result;

  using Geo::Domain::WellTrait;

  auto dataAccessFactory = _connection->dataAccessFactory();
  auto unitAccess        = dataAccessFactory->unitAccess();
  result = unitAccess->findAll();

  std::cout << " UNITS LENGTH " << result.size() << std::endl;

  return result;
}


QStringList
CurveTypeEntry::
getUnitNames() const
{
  QStringList result;

  using Geo::Domain::Unit;

  auto units = getUnits();

  for (Unit::Shared u : units)
    result.append(u->getName());

  return result;
}

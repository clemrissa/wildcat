#include "UnitTableEntry.hpp"

#include <QtGui/QIcon>

using Geo::TypeSystem::Models::Units::UnitTableEntry;

using Geo::Domain::Dimensions;
using Geo::Domain::Unit;

UnitTableEntry::
UnitTableEntry(Unit::Shared unit):
  _unit(unit),
  _state(Active),
  _persisted(unit->isValid())
{
  //
}


UnitTableEntry::
UnitTableEntry():
  _unit(new Unit()),
  _state(Active),
  _persisted(_unit->isValid())
{
  //
}


UnitTableEntry::
~UnitTableEntry()
{
  for (UnitTableEntry* entry : _entries)
    delete entry;
}


Geo::Domain::Unit::Shared
UnitTableEntry::
unit() const
{
  return _unit;
}


QDomElement
UnitTableEntry::
getXmlDescription(QDomDocument& doc)
{
  QDomElement tag = doc.createElement("CurveType");

  auto addValue =
    [&](QString n, QString v)
    {
      QDomElement e = doc.createElement(n);
      tag.appendChild(e);

      QDomText t = doc.createTextNode(v);
      e.appendChild(t);
    };

  auto addRealValue =
    [&](QString n, double v)
    {
      addValue(n, QString("%1").arg(v, 0, 'g', 3));
    };

  addValue("Name", _unit->getName());

  addValue("Symbol", _unit->getSymbol().trimmed());

  addRealValue("Scale", _unit->getScale());
  addRealValue("Offset", _unit->getOffset());

  addValue("Dimensions",
           _unit->getDimensions().getAllUnitsAsString());

  return tag;
}


void
UnitTableEntry::
addXmlData(QDomElement& data)
{
  auto getValue =
    [&](QString n)
    {
      return data.firstChildElement(n).text();
    };

  auto getRealValue =
    [&](QString n)
    {
      bool ok;
      return getValue(n).toDouble(&ok);
    };

  auto getDimensions =
    [&](QString n)
    {
      auto list = getValue(n).split(" ", QString::SkipEmptyParts);

      Q_ASSERT(list.size() == Dimensions::AllUnitsSize);

      class Dimensions dim;

      for (auto i = 0; i < list.size(); ++i) {
        bool ok;

        dim[static_cast<Dimensions::Dimension>(i)] = list[i].toInt(&ok);
      }

      return dim;
    };

  _unit->setName(getValue("Name"));
  _unit->setSymbol(getValue("Symbol"));
  _unit->setScale(getRealValue("Scale"));
  _unit->setOffset(getRealValue("Offset"));
  _unit->setDimensions(getDimensions("Dimensions"));
}


int
UnitTableEntry::
positionOfChildEntry(UnitTableEntry* const childEntry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(),
                      childEntry);

  return it - _entries.begin();
}


QVariant
UnitTableEntry::
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

  default:
    return QVariant();
    break;
  }

  return QVariant();
}


QString
UnitTableEntry::
headerData(int column)
{
  QString result;

  switch (column) {
  case UnitTableEntry::Name:
    result = tr("Name");
    break;

  case UnitTableEntry::Symbol:
    result = tr("Symbol");
    break;

  case UnitTableEntry::Offset:
    result = tr("Offset");
    break;

  case UnitTableEntry::Scale:
    result = tr("Scale");
    break;

  case UnitTableEntry::Dimensions:
    result = tr("Dimensions");
    break;

  default:
    result = QString();
    break;
  }

  return result;
}


void
UnitTableEntry::
setConnection(Database::Connections::Connection::Shared connection)
{
  _connection = connection;

  for (UnitTableEntry* e : _entries)
    e->setConnection(connection);
}


void
UnitTableEntry::
switchState()
{
  switch (_state) {
  case Active:
    _state = Deleted;
    break;

  case Deleted:
    _state = Active;
    break;
  }
}


QWidget*
UnitTableEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}


// -----------------

QVariant
UnitTableEntry::
getDisplayOrEditRole(int column) const
{
  QVariant result;

  switch (column) {
  case UnitTableEntry::Name:
    result = _unit->getName();
    break;

  case UnitTableEntry::Symbol:
    result = _unit->getSymbol();
    break;

  case UnitTableEntry::Scale:
    result = _unit->getScale();
    break;

  case UnitTableEntry::Offset:
    result = _unit->getOffset();
    break;

  case UnitTableEntry::Dimensions:
    result =
      QString("[%1]").arg(_unit->getDimensions().getFundamentalAsString());

  default:
    break;
  }

  return result;
}


QVariant
UnitTableEntry::
getDecorationRole(int column) const
{
  if (!_unit->isValid())
    return QVariant();

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
UnitTableEntry::
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

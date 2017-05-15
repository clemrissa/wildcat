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
               TreeEntry*                     parent) :
  TreeEntry(parent),
  _curveType(curveType),
  _persisted(_curveType->isValid())
{}


CurveTypeEntry::
CurveTypeEntry(QString curveTypeName,
               TreeEntry* parent) :
  TreeEntry(parent),
  _curveType(new CurveType()),
  _persisted(_curveType->isValid())
{
  auto f = static_cast<FamilyEntry*>(parent);

  _curveType->setFamily(f->getFamily());
  _curveType->setName(curveTypeName);
}


CurveTypeEntry::
~CurveTypeEntry()
{}


void
CurveTypeEntry::
addXmlData(QDomElement& de, XmlSourceType type)
{
  auto updateMnemonic =
    [&](QString mnem)
    {
      if (_curveType->mnemonic().isEmpty())
        _curveType->setMnemonic(mnem);

      else
      {
        QStringList synonyms = _curveType->synonyms();

        if (!synonyms.contains(mnem))
        {
          synonyms.append(mnem);

          _curveType->setSynonyms(synonyms);
        }
      }
    };

  switch (type)
  {
    case CurveTypeEntry::XmlSourceType::Schlumberger:
    {
      QString mnem = de.firstChildElement("CurveMnemonic").text();

      updateMnemonic(mnem);

      _curveType->setTextUnit(de.firstChildElement("Unit").text());

      bool ok;
      _curveType->setMin(de.firstChildElement("Min").text().toDouble(&ok));
      _curveType->setMax(de.firstChildElement("Max").text().toDouble(&ok));

      // TODO scale
      _scale      = de.firstChildElement("Scale").text().toLower();
      _continuity = de.firstChildElement("Type").text();

      break;
    }

    case CurveTypeEntry::XmlSourceType::Geo:
    {
      QString mnem = de.firstChildElement("Mnemonic").text();

      updateMnemonic(mnem);

      _curveType->setTextUnit(de.firstChildElement("TextUnit").text());

      bool ok;
      _curveType->setMin(de.firstChildElement("Min").text().toDouble(&ok));
      _curveType->setMax(de.firstChildElement("Max").text().toDouble(&ok));

      auto scale =
        CurveType::scaleFromText(de.firstChildElement("Scale").text());
      _curveType->setScale(scale);

      auto cont =
        CurveType::continuityFromText(de.firstChildElement("Continuity").text());
      _curveType->setContinuity(cont);

      break;
    }
  }
}


QDomElement
CurveTypeEntry::
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

  addValue("Name", _curveType->name());
  addValue("Mnemonic", _curveType->mnemonic());
  addValue("TextUnit", _curveType->textUnit());
  addValue("Unit",
           _curveType->unit().isNull() ? QString() : _curveType->unit()->getName());

  addRealValue("Min", _curveType->min());
  addRealValue("Max", _curveType->max());
  addValue("Scale", CurveType::textScale(_curveType->scale()));
  addValue("Continuity", CurveType::textContinuity(_curveType->continuity()));

  return tag;
}


QVariant
CurveTypeEntry::
data(int role, int column) const
{
  switch (role)
  {
    case Qt::DisplayRole:
      return getDisplayRole(column);
      break;

    case Qt::EditRole:
      return getEditRole(column);
      break;

    case Qt::DecorationRole:
      return getDecorationRole(column);
      break;

    case Qt::ForegroundRole:
      return getForegroundRole(column);
      break;

    case Qt::BackgroundRole:

      if (_persisted)
        return getBackgroundRole(column);

      break;

    default:
      break;
  }

  return QVariant();
}


bool
CurveTypeEntry::
setData(int column, QVariant value)
{
  switch (column)
  {
    case TreeEntry::FamilyOrCurveName:
      _curveType->setName(value.toString());
      break;

    case TreeEntry::Mnemonic:
      _curveType->setMnemonic(value.toString());
      break;

    case TreeEntry::Synonyms:
    {
      auto list = value.toString().split(",", QString::SkipEmptyParts);
      _curveType->setSynonyms(list);

      break;
    }

    case TreeEntry::Units:
    {
      bool ok;
      _curveType->setUnit(getUnits()[value.toInt(&ok)]);
      break;
    }

    case TreeEntry::Min:
    {
      bool   ok;
      double min = value.toDouble(&ok);
      _curveType->setMin(min);
      break;
    }

    case TreeEntry::Max:
    {
      bool   ok;
      double max = value.toDouble(&ok);
      _curveType->setMax(max);
      break;
    }

    case TreeEntry::Scale:
    {
      bool ok;
      _curveType->setScale((CurveType::Scale)value.toInt(&ok));
      break;
    }

    case TreeEntry::Continuity:
    {
      bool ok;
      _curveType->setContinuity((CurveType::Continuity)value.toInt(&ok));
      break;
    }

    default:
      break;
  }

  return true;
}


QWidget*
CurveTypeEntry::
delegateWidget(int column) const
{
  QWidget* result = nullptr;

  switch (column)
  {
    case TreeEntry::FamilyOrCurveName:
    {
      QString d = data(Qt::EditRole, column).toString();
      result = new QLineEdit(d);

      break;
    }

    case TreeEntry::Mnemonic:
    {
      QString d = data(Qt::EditRole, column).toString();
      result = new QLineEdit(d);

      break;
    }

    case TreeEntry::Synonyms:
    {
      QString d = data(Qt::EditRole, column).toString();
      result = new QLineEdit(d);

      break;
    }

    case TreeEntry::Units:
    {
      auto comboBox = new QComboBox();

      auto unit = _curveType->unit();

      auto unitNames = getUnitNames();

      for (int i = 0; i < unitNames.size(); ++i)
      {
        comboBox->addItem(unitNames[i]);

        if (!unit.isNull() &&
            unit->getName() == unitNames[i])
          comboBox->setCurrentIndex(i);
      }

      result = comboBox;

      break;
    }

    case TreeEntry::Min:
    {
      QString d = data(Qt::EditRole, column).toString();

      auto l = new QLineEdit(d);

      l->setValidator(new QDoubleValidator());

      result = l;

      break;
    }

    case TreeEntry::Max:
    {
      QString d = data(Qt::EditRole, column).toString();

      auto l = new QLineEdit(d);

      l->setValidator(new QDoubleValidator());

      result = l;

      break;
    }

    case TreeEntry::Scale:
    {
      auto comboBox = new QComboBox();

      for (int i = 0; i <  CurveType::ScaleSize; ++i)
        comboBox->addItem(CurveType::textScale((CurveType::Scale)i));

      comboBox->setCurrentIndex(_curveType->scale());

      result = comboBox;

      break;
    }

    case TreeEntry::Continuity:
    {
      auto comboBox = new QComboBox();

      for (int i = 0; i <  CurveType::ContinuitySize; ++i)
        comboBox->addItem(CurveType::textContinuity((CurveType::Continuity)i));

      comboBox->setCurrentIndex(_curveType->continuity());

      result = comboBox;

      break;
    }

    default:
      break;
  }

  return result;
}


void
CurveTypeEntry::
setDataFromWidget(QWidget*            editor,
                  QModelIndex const&  index,
                  QAbstractItemModel* model)
{
  switch (index.column())
  {
    case TreeEntry::FamilyOrCurveName:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Mnemonic:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Synonyms:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Units:
    {
      auto comboBox = static_cast<QComboBox*>(editor);
      model->setData(index,
                     comboBox->currentIndex(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Min:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Max:
    {
      auto lineEdit = static_cast<QLineEdit*>(editor);

      model->setData(index, lineEdit->text(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Scale:
    {
      auto comboBox = static_cast<QComboBox*>(editor);
      model->setData(index,
                     comboBox->currentIndex(),
                     Qt::EditRole);
      break;
    }

    case TreeEntry::Continuity:
    {
      auto comboBox = static_cast<QComboBox*>(editor);
      model->setData(index,
                     comboBox->currentIndex(),
                     Qt::EditRole);
      break;
    }

    default:
      break;
  }
}


QVariant
CurveTypeEntry::
getDisplayRole(int column) const
{
  switch (column)
  {
    case TreeEntry::FamilyOrCurveName:

      if (_curveType->name().isEmpty())
        return tr("Change curve name");
      else
        return _curveType->name();

      break;

    case TreeEntry::Mnemonic:
      return _curveType->mnemonic();
      break;

    case TreeEntry::Synonyms:
      return QStringList(_curveType->synonyms()).join(",");

    case TreeEntry::Units:

      if (_curveType->unit().isNull())
        return _curveType->textUnit();

      else
        return _curveType->unit()->getName();

      break;

    case TreeEntry::Min:
      return _curveType->min();
      break;

    case TreeEntry::Max:
      return _curveType->max();
      break;

    case TreeEntry::Scale:
      return CurveType::textScale(_curveType->scale());
      break;

    case TreeEntry::Continuity:
      return CurveType::textContinuity(_curveType->continuity());
      break;

    default:
      return QVariant();
      break;
  }

  return QVariant();
}


QVariant
CurveTypeEntry::
getEditRole(int column) const
{
  switch (column)
  {
    case TreeEntry::FamilyOrCurveName:
      return _curveType->name();
      break;

    case TreeEntry::Mnemonic:
      return _curveType->mnemonic();
      break;

    case TreeEntry::Synonyms:
      return QStringList(_curveType->synonyms()).join(",");

    case TreeEntry::Min:
      return _curveType->min();
      break;

    case TreeEntry::Max:
      return _curveType->max();
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

    switch (_state)
    {
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

  switch (_state)
  {
    case Active:
    {
      QPalette palette;
      result = QColor(palette.color(QPalette::WindowText));
      break;
    }

    case Deleted:
      result = QColor(Qt::lightGray);
      break;
  }

  if (column == TreeEntry::FamilyOrCurveName)
    if (_curveType->name().isEmpty())
      result = QColor(Qt::lightGray);

  return result;
}


QVariant
CurveTypeEntry::
getBackgroundRole(int column) const
{
  Q_UNUSED(column);

  QVariant result;

  if (!_curveType->isValid())
    result = QColor(0xFF, 0xEE, 0xEE);

  return result;
}


QVector<Geo::Domain::Unit::Shared>
CurveTypeEntry::
getUnits() const
{
  QVector<Geo::Domain::Unit::Shared> result;

  if (!_connection)
    return result;

  using Geo::Domain::WellTrait;

  auto dataAccessFactory =
    _connection->dataAccessFactory();
  auto unitAccess =
    dataAccessFactory->unitAccess();
  result = unitAccess->findAll();

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

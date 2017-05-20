#include "WellTrait.hpp"

#include <QtCore/QObject>
#include <QtCore/QStringList>

using Geo::Domain::WellTrait;

WellTrait::
WellTrait()
  : _name(QString())
  , _type(WellTrait::Undefined)
  , _mandatory(false)
{}

WellTrait::
WellTrait(QString name)
  : _name(name)
  , _type(WellTrait::Undefined)
  , _mandatory(false)
{
  //
}


WellTrait::
WellTrait(QString name, bool mandatory) :
  _name(name),
  _type(WellTrait::Undefined),
  _mandatory(mandatory)
{
  //
}


void
WellTrait::
setName(QString name)
{
  _name = name;
}


void
WellTrait::
setSynonyms(QList<QString> synonyms)
{
  _synonyms.clear();

  for (QString s : synonyms)
    _synonyms.append(s.trimmed());
}


QString
WellTrait::
getSynonymsAsString()
{
  QStringList s(_synonyms);

  return s.join(",");
}


QString
WellTrait::
typeAsString(Type type)
{
  QString result;

  switch (type)
  {
    case Type::Undefined:
      result = QString();
      break;

    case Type::String:
      result = QObject::tr("String");
      break;

    case Type::Integer:
      result = QObject::tr("Integer");
      break;

    case Type::Double:
      result = QObject::tr("Double");
      break;

    case Type::Date:
      result = QObject::tr("Date");
      break;

    default:
      // should not get here
      break;
  }

  return result;
}


bool
WellTrait::
isValid() const
{
  return !_name.isEmpty() &&
         (_synonyms.size() > 0) &&
         _type != WellTrait::Undefined;
}

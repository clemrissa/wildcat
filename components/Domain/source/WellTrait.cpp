#include "WellTrait.hpp"

#include <QtCore/QStringList>

#include <Uni/Logging/Logging>

using Geo::Domain::WellTrait;

WellTrait::
WellTrait(QString name):
  _name(name),
  _mandatory(false)
{
  //
}


WellTrait::
WellTrait(QString name, bool mandatory):
  _name(name),
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


bool
WellTrait::
isValid() const
{
  return !_name.isEmpty() && (_synonyms.size() > 0);
}

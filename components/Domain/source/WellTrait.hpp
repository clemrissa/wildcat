#ifndef Geo_Domain_WellTrait_hpp
#define Geo_Domain_WellTrait_hpp

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

#include <iostream>

namespace Geo {
namespace Domain {
//


#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTrait
{
public:
  // which type do we store here?
  enum Type {
    Undefined = 0,
    String    = 1,
    Integer   = 2,
    Double    = 3,
    Date      = 4,
    Size
  };

public:
  typedef QSharedPointer<WellTrait> Shared;

public:
  WellTrait();

  WellTrait(QString name);

  WellTrait(QString name, bool mandatory);

  QString
  name() const { return _name; }

  void
  setName(QString name);

  QList<QString>
  synonyms() const { return _synonyms; }

  void
  setSynonyms(QList<QString> synonyms);

  QString
  getSynonymsAsString();

  static
  QString
  typeAsString(Type type);

  Type
  type() const { return _type; }

  void
  setType(Type type)
  {
    _type = type;
  }

public:
  bool
  isValid() const;

private:
  friend class odb::access;

#ifdef ODB_COMPILER
  #pragma db id
#endif
  QString _name;

  QList<QString> _synonyms;

  Type _type;

  bool _mandatory;
};


//
}
}

#endif //  Geo_Domain_WellTrait_hpp

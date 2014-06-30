#ifndef Geo_Domain_WellTrait_hpp
#define Geo_Domain_WellTrait_hpp

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

#include <odb/core.hxx>

namespace Geo {
namespace Domain {
#ifdef ODB_COMPILER
  #pragma db object
#endif
class WellTrait
{
public:
  typedef QSharedPointer<WellTrait> Shared;

public:
  WellTrait()
  {
  }

  WellTrait(QString name);

  WellTrait(QString name, bool mandatory);

  QString
  name() const { return _name; }

  void
  setName(QString name) { _name = name; }

  QList<QString>
  synonyms() const { return _synonyms; }

  void
  setSynonyms(QList<QString> synonyms);

  QString
  getSynonymsAsString();

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

  bool _mandatory;
};
}
}

#endif //  Geo_Domain_WellTrait_hpp

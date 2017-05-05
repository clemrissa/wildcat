#include "CurveTypeAccess.hpp"

#include <QtCore/QDebug>

#include "CurveType.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::CurveTypeAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::CurveType>  Query;
typedef odb::result<Geo::Domain::CurveType> Result;

CurveTypeAccess::
CurveTypeAccess(Database db) : _db(db) {}

void
CurveTypeAccess::
insert(Geo::Domain::CurveType::Shared curveType)
{
  try
  {
    transaction t(_db->begin());

    _db->persist(*curveType);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
CurveTypeAccess::
update(Geo::Domain::CurveType::Shared curveType)
{
  try
  {
    transaction t(_db->begin());

    _db->update(*curveType);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
CurveTypeAccess::
remove(Geo::Domain::CurveType::Shared curveType)
{
  try
  {
    transaction t(_db->begin());

    _db->erase(*curveType);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
CurveTypeAccess::
remove(unsigned int const& pk)
{
  try
  {
    transaction t(_db->begin());

    _db->erase<Geo::Domain::CurveType>(pk);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


QVector<Geo::Domain::CurveType::Shared>
CurveTypeAccess::
findAll()
{
  using Geo::Domain::CurveType;

  QVector<CurveType::Shared> vector;
  try
  {
    transaction t(_db->begin());

    Result r(_db->query<CurveType>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i)
    {
      CurveType::Shared curveType(i.load());

      vector.push_back(curveType);
    }

    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }

  return vector;
}


Geo::Domain::CurveType::Shared
CurveTypeAccess::
findByPrimaryKey(unsigned int const& pk)
{
  using Geo::Domain::CurveType;
  return CurveType::Shared(_db->load<CurveType>(pk));
}


void
CurveTypeAccess::
createDefaultCurveTypes()
{
  //auto existingCurveTypes = findAll();

  //QSet<Qstring> existingCurveTypeNames;

  //for (CurveType::Shared ct : existingCurveTypes)
  //existingCurveTypeNames.insert(cd->)
}

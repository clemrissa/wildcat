#include "UnitAccess.hpp"

#include <Uni/Logging/Logging>

#include "Unit.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::UnitAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::Unit>  Query;
typedef odb::result<Geo::Domain::Unit> Result;

UnitAccess::
UnitAccess(Database db): _db(db) {}

void
UnitAccess::
insert(Geo::Domain::Unit::Shared log)
{
  try {
    transaction t(_db->begin());

    _db->persist(*log);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
UnitAccess::
update(Geo::Domain::Unit::Shared log)
{
  try {
    transaction t(_db->begin());

    _db->update(*log);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
UnitAccess::
remove(Geo::Domain::Unit::Shared log)
{
  try {
    transaction t(_db->begin());

    _db->erase(*log);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
UnitAccess::
remove(unsigned int const& pk)
{
  try {
    transaction t(_db->begin());

    _db->erase<Geo::Domain::Unit>(pk);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


QVector<Geo::Domain::Unit::Shared>
UnitAccess::
findAll()
{
  using Geo::Domain::Unit;

  QVector<Unit::Shared> vector;
  try {
    transaction t(_db->begin());

    Result r(_db->query<Unit>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i) {
      Unit::Shared log(i.load());

      vector.push_back(log);
    }

    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }

  return vector;
}


Geo::Domain::Unit::Shared
UnitAccess::
findByPrimaryKey(unsigned int const& pk)
{
  using Geo::Domain::Unit;
  return Unit::Shared(_db->load<Unit>(pk));
}

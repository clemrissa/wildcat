#include "UnitAccess.hpp"

#include <Uni/Logging/Logging>

#include "Unit.odb.hpp"

#include <odb/transaction.hxx>

#include <QtCore/QSet>

using Geo::Domain::Odb::UnitAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::Unit>  Query;
typedef odb::result<Geo::Domain::Unit> Result;

UnitAccess::
UnitAccess(Database db): _db(db) {}

void
UnitAccess::
insert(Geo::Domain::Unit::Shared unit)
{
  try {
    transaction t(_db->begin());

    _db->persist(*unit);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
UnitAccess::
update(Geo::Domain::Unit::Shared unit)
{
  try {
    transaction t(_db->begin());

    _db->update(*unit);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
UnitAccess::
remove(Geo::Domain::Unit::Shared unit)
{
  try {
    transaction t(_db->begin());

    _db->erase(*unit);
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
      Unit::Shared unit(i.load());

      vector.push_back(unit);
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


void
UnitAccess::
createDefaultUnits()
{
  // create list of units
  QList<Unit::Shared> unitsToBeCreated;

  unitsToBeCreated
    << Unit::create(tr("Meter"), tr("m"), 1., 0., Dimensions::Length())
    << Unit::create(tr("Kilogram"), tr("kg"), 1., 0., Dimensions::Mass())
    << Unit::create(tr("Second"), tr("s"), 1., 0., Dimensions::Time())
    << Unit::create(tr("Ampere"), tr("A"), 1., 0., Dimensions::Current())
    << Unit::create(tr("Kelvin"), tr("K"), 1., 0., Dimensions::Temperature())
    << Unit::create(tr("Mole"), tr(
                    "mol"), 1., 0., Dimensions::AmountOfSubstance())
    << Unit::create(tr("Candela"), tr(
                    "cd"), 1., 0., Dimensions::LuminousIntensity());

  // insert list of units
  auto existingUnits = findAll();

  QSet<QString> existingUnitNames;

  for (Unit::Shared u : existingUnits)
    existingUnitNames.insert(u->getName());

  for (Unit::Shared u : unitsToBeCreated)
    if (!existingUnitNames.contains(u->getName()))
      insert(u);

}

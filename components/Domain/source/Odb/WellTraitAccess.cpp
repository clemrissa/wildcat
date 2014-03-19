#include "WellTraitAccess.hpp"

#include <Uni/Logging/Logging>

#include "WellTrait.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::WellTraitAccess;
using odb::core::transaction;

typedef odb::query<WellTraitAccess::WellTrait>  Query;
typedef odb::result<WellTraitAccess::WellTrait> Result;


WellTraitAccess::
WellTraitAccess(Database db): _db(db) {}

void
WellTraitAccess::
insert(WellTrait::Shared wellTrait) {
  try {
    transaction t(_db->begin());

    t.tracer(odb::core::stderr_tracer);

    _db->persist(*wellTrait);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellTraitAccess::
update(WellTrait::Shared wellTrait) {
  try {
    transaction t(_db->begin());

    _db->update(*wellTrait);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellTraitAccess::
remove(WellTrait::Shared wellTrait) {
  try {
    transaction t(_db->begin());

    _db->erase(*wellTrait);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellTraitAccess::
remove(QString const& pk) {
  try {
    transaction t(_db->begin());

    _db->erase<WellTrait>(pk);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

QVector<WellTraitAccess::WellTrait::Shared>
WellTraitAccess::
findAll() {
  QVector<WellTrait::Shared> vector;
  try {
    transaction t(_db->begin());

    Result r(_db->query<WellTrait>());

    Result::iterator i(r.begin());

    if (i != r.end()) {
      WellTrait::Shared wellTrait(i.load());

      vector.push_back(wellTrait);
    }

    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }

  return vector;
}

WellTraitAccess::WellTrait::Shared
WellTraitAccess::
findByPrimaryKey(QString const& pk) {
  return WellTrait::Shared(_db->load<WellTrait>(pk));
}

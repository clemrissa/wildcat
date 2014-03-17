#include "WellAccess.hpp"

#include <Uni/Logging/Logging>

#include "Well.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::WellAccess;
using odb::core::transaction;

typedef odb::query<WellAccess::Well>  Query;
typedef odb::result<WellAccess::Well> Result;

WellAccess::
WellAccess(Database db): _db(db) {}

void
WellAccess::
insert(Well::Shared well) {
  try {
    transaction t(_db->begin());

    t.tracer(odb::core::stderr_tracer);

    _db->persist(*well);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellAccess::
update(Well::Shared well) {
  try {
    transaction t(_db->begin());

    _db->update(*well);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellAccess::
remove(Well::Shared well) {
  try {
    transaction t(_db->begin());

    _db->erase(*well);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

void
WellAccess::
remove(unsigned int const& pk) {
  try {
    transaction t(_db->begin());

    _db->erase<Well>(pk);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

QVector<WellAccess::Well::Shared>
WellAccess::
findAll() {
  QVector<Well::Shared> vector;
  try {
    transaction t(_db->begin());

    Result r(_db->query<Well>());

    Result::iterator i(r.begin());

    if (i != r.end()) {
      Well::Shared well(i.load());

      vector.push_back(well);
    }

    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }

  return vector;
}

WellAccess::Well::Shared
WellAccess::
findByPrimaryKey(unsigned int const& pk) {
  return Well::Shared(_db->load<Well>(pk));
}

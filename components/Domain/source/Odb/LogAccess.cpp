#include "LogAccess.hpp"

#include <Uni/Logging/Logging>

#include "Log.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::LogAccess;
using odb::core::transaction;

typedef odb::query<LogAccess::Log>  Query;
typedef odb::result<LogAccess::Log> Result;

LogAccess::
LogAccess(Database db): _db(db) {}

void
LogAccess::
insert(Log::Shared log) {
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
LogAccess::
update(Log::Shared log) {
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
LogAccess::
remove(Log::Shared log) {
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
LogAccess::
remove(QUuid const& pk) {
  try {
    transaction t(_db->begin());

    _db->erase<Log>(pk);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}

QVector<LogAccess::Log::Shared>
LogAccess::
findAll() {
  QVector<Log::Shared> vector;
  try {
    transaction t(_db->begin());

    Result r(_db->query<Log>());

    Result::iterator i(r.begin());

    if (i != r.end()) {
      Log::Shared log(i.load());

      vector.push_back(log);
    }

    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }

  return vector;
}

LogAccess::Log::Shared
LogAccess::
findByPrimaryKey(QUuid const& pk) {
  return Log::Shared(_db->load<Log>(pk));
}

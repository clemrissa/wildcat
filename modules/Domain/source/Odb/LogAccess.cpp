#include "LogAccess.hpp"

#include "Log.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::LogAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::Log>  Query;
typedef odb::result<Geo::Domain::Log> Result;

LogAccess::
LogAccess(Database db) : _db(db) {}

void
LogAccess::
insert(Geo::Domain::Log::Shared log)
{
  try
  {
    transaction t(_db->begin());

    _db->persist(*log);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
LogAccess::
update(Geo::Domain::Log::Shared log)
{
  try
  {
    transaction t(_db->begin());

    _db->update(*log);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
LogAccess::
remove(Geo::Domain::Log::Shared log)
{
  try
  {
    transaction t(_db->begin());

    _db->erase(*log);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
LogAccess::
remove(unsigned int const& pk)
{
  try
  {
    transaction t(_db->begin());

    _db->erase<Geo::Domain::Log>(pk);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


QVector<Geo::Domain::Log::Shared>
LogAccess::
findAll()
{
  using Geo::Domain::Log;

  QVector<Log::Shared> vector;
  try
  {
    transaction t(_db->begin());

    Result r(_db->query<Log>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i)
    {
      Log::Shared log(i.load());

      vector.push_back(log);
    }

    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }

  return vector;
}


Geo::Domain::Log::Shared
LogAccess::
findByPrimaryKey(unsigned int const& pk)
{
  using Geo::Domain::Log;
  return Log::Shared(_db->load<Log>(pk));
}

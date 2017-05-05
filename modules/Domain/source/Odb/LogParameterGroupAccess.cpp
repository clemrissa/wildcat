#include "LogParameterGroupAccess.hpp"

#include "LogParameterGroup.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::LogParameterGroupAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::LogParameterGroup>  Query;
typedef odb::result<Geo::Domain::LogParameterGroup> Result;

LogParameterGroupAccess::
LogParameterGroupAccess(Database db) : _db(db) {}

void
LogParameterGroupAccess::
insert(Geo::Domain::LogParameterGroup::Shared log)
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
LogParameterGroupAccess::
update(Geo::Domain::LogParameterGroup::Shared log)
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
LogParameterGroupAccess::
remove(Geo::Domain::LogParameterGroup::Shared log)
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
LogParameterGroupAccess::
remove(unsigned int const& pk)
{
  try
  {
    transaction t(_db->begin());

    _db->erase<Geo::Domain::LogParameterGroup>(pk);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


QVector<Geo::Domain::LogParameterGroup::Shared>
LogParameterGroupAccess::
findAll()
{
  using Geo::Domain::LogParameterGroup;

  QVector<LogParameterGroup::Shared> vector;
  try
  {
    transaction t(_db->begin());

    Result r(_db->query<Geo::Domain::LogParameterGroup>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i)
    {
      LogParameterGroup::Shared log(i.load());

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


Geo::Domain::LogParameterGroup::Shared
LogParameterGroupAccess::
findByPrimaryKey(unsigned int const& pk)
{
  using Geo::Domain::LogParameterGroup;
  return LogParameterGroup::Shared(_db->load<LogParameterGroup>(pk));
}

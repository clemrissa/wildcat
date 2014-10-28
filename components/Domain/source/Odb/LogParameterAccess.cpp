#include "LogParameterAccess.hpp"

#include <Uni/Logging/Logging>

#include "LogParameter.odb.hpp"

#include <odb/transaction.hxx>

using Geo::Domain::Odb::LogParameterAccess;
using odb::core::transaction;

typedef odb::query<Geo::Domain::LogParameter>  Query;
typedef odb::result<Geo::Domain::LogParameter> Result;

LogParameterAccess::
LogParameterAccess(Database db): _db(db) {}

void
LogParameterAccess::
insert(Geo::Domain::LogParameter::Shared logParameter)
{
  try {
    transaction t(_db->begin());

    _db->persist(*logParameter);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
LogParameterAccess::
update(Geo::Domain::LogParameter::Shared logParameter)
{
  try {
    transaction t(_db->begin());

    _db->update(*logParameter);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
LogParameterAccess::
remove(Geo::Domain::LogParameter::Shared logParameter)
{
  try {
    transaction t(_db->begin());

    _db->erase(*logParameter);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


void
LogParameterAccess::
remove(unsigned int const& pk)
{
  try {
    transaction t(_db->begin());

    _db->erase<Geo::Domain::LogParameter>(pk);
    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }
}


QVector<Geo::Domain::LogParameter::Shared>
LogParameterAccess::
findAll()
{
  using Geo::Domain::LogParameter;

  QVector<LogParameter::Shared> vector;
  try {
    transaction t(_db->begin());

    Result r(_db->query<Geo::Domain::LogParameter>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i) {
      LogParameter::Shared logParameter(i.load());

      vector.push_back(logParameter);
    }

    t.commit();
  } catch (odb::exception const& e) {
    FATAL << "Odb error happened: "
          << e.what();
  }

  return vector;
}


Geo::Domain::LogParameter::Shared
LogParameterAccess::
findByPrimaryKey(unsigned int const& pk)
{
  using Geo::Domain::LogParameter;
  return LogParameter::Shared(_db->load<LogParameter>(pk));
}

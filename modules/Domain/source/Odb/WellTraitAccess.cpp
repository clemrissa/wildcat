#include "WellTraitAccess.hpp"

#include "WellTrait.odb.hpp"

#include <odb/result.hxx>
#include <odb/transaction.hxx>

#include <QtCore/QSet>
#include <QtCore/QStringList>

using Geo::Domain::Odb::WellTraitAccess;
using Geo::Domain::WellTrait;

using odb::core::transaction;

typedef odb::query<Geo::Domain::WellTrait>  Query;
typedef odb::result<Geo::Domain::WellTrait> Result;

WellTraitAccess::
WellTraitAccess(Database db) : _db(db) {}

void
WellTraitAccess::
insert(WellTrait::Shared wellTrait)
{
  try
  {
    transaction t(_db->begin());

    // t.tracer(odb::core::stderr_tracer);

    _db->persist(*wellTrait);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
WellTraitAccess::
update(WellTrait::Shared wellTrait)
{
  try
  {
    transaction t(_db->begin());

    _db->update(*wellTrait);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
WellTraitAccess::
remove(WellTrait::Shared wellTrait)
{
  try
  {
    transaction t(_db->begin());

    _db->erase(*wellTrait);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


void
WellTraitAccess::
remove(unsigned int const& pk)
{
  try
  {
    transaction t(_db->begin());

    _db->erase<WellTrait>(pk);
    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }
}


QVector<WellTrait::Shared>
WellTraitAccess::
findAll()
{
  QVector<WellTrait::Shared> vector;
  try
  {
    transaction t(_db->begin());

    Result r(_db->query<WellTrait>());

    for (Result::iterator i(r.begin()); i != r.end(); ++i)
    {
      WellTrait::Shared wellTrait(i.load());

      vector.push_back(wellTrait);
    }

    t.commit();
  }
  catch (odb::exception const& e)
  {
    qFatal("Odb error happened: '%s'", e.what());
  }

  return vector;
}


WellTrait::Shared
WellTraitAccess::
findByPrimaryKey(unsigned int const& pk)
{
  return WellTrait::Shared(_db->load<WellTrait>(pk));
}


void
WellTraitAccess::
createDefaultTraits()
{
  QStringList defaultTraits { tr("WELL"),
                              tr("COMPANY"),
                              tr("FIELD"),
                              tr("COUNTRY"),
                              tr("LOCATION"),
                              tr("DATE"),
                              tr("API"),
                              tr("UWI") };

  // ------------------
  // QVector<WellTrait::Shared> vector;
  // try {
  // transaction t(_db->begin());

  // Result r(_db->query<WellTrait>());

  // for (Result::iterator i(r.begin()); i != r.end(); ++i) {
  // WellTrait::Shared wellTrait(i.load());

  // vector.push_back(wellTrait);
  // }

  // t.commit();
  // } catch (odb::exception const& e) {
  // FATAL << "Odb error happened: "
  // << e.what();
  // }

  // ------------------

  QVector<WellTrait::Shared> traits = findAll();

  QSet<QString> existingTraits;

  for (WellTrait::Shared t : traits)
    existingTraits.insert(t->name());

  for (QString traitName : defaultTraits)
    if (!existingTraits.contains(traitName))
    {
      WellTrait::Shared emptyTrait(new WellTrait());

      emptyTrait->setName(traitName);

      emptyTrait->setSynonyms(QStringList { traitName }
                              );

      emptyTrait->setType(WellTrait::String);

      insert(emptyTrait);
    }
}

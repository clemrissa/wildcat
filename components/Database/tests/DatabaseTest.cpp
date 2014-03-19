#include <gtest/gtest.h>

#include <Uni/Logging/Logging>

#include <Las/LasFile>
#include <Las/LasFileParser>

#include <Database/Private/Connection>

#include <Domain/Log>
#include <Domain/LogAccess>
#include <Domain/Well>
#include <Domain/WellAccess>
#include <Domain/WellTrait>

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <QApplication>
#include <QFile>
#include <QSharedPointer>

TEST(DatabaseTest, CreateDB) {
  using DMContext = DependencyManager::ApplicationContext;
  using Geo::Database::Private::Connection;

  Connection* c =
    DMContext::create<Connection>("Database.Connection");

  c->databaseType(Geo::Database::Private::DatabaseType::SQLite);
  c->database("test.db");
  c->connect();

  auto dataAccessFactory = c->dataAccessFactory();

  Geo::Domain::WellAccess::Shared wellAccess = dataAccessFactory->wellAccess();
  Geo::Domain::LogAccess::Shared  logAccess  = dataAccessFactory->logAccess();

  using Geo::Domain::Well;

  Well::Shared well(new Well(QString("skvazhinka"),
                             0.5, 6.7, 5.7));

  Geo::Domain::Log::Shared
    log(new Geo::Domain::Log(QString("electro"),
                             QString("BKZ"),
                             QString("Lopata")));

  // objects interconnections
  well->addLog(log);
  log->setWell(well);

  // store both in DB
  wellAccess->insert(well);
  logAccess->insert(log);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}


TEST(DatabaseTest, Traits) {
  using DMContext = DependencyManager::ApplicationContext;
  using Geo::Database::Private::Connection;

  Connection* c =
    DMContext::create<Connection>("Database.Connection");

  c->databaseType(Geo::Database::Private::DatabaseType::SQLite);
  c->database("test.db");
  c->connect();

  auto dataAccessFactory = c->dataAccessFactory();

  Geo::Domain::WellTrait::Shared wellName(new Geo::Domain::WellTrait(QString("WellName")));
  Geo::Domain::WellTrait::Shared wellRegion(new Geo::Domain::WellTrait(QString("Region")));
  Geo::Domain::WellTrait::Shared wellType(new Geo::Domain::WellTrait(QString("Type")));

  Geo::Domain::WellTraitAccess::Shared traitsAccess  = dataAccessFactory->wellTraitAccess();

  traitsAccess->insert(wellName);
  traitsAccess->insert(wellRegion);
  traitsAccess->insert(wellType);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}

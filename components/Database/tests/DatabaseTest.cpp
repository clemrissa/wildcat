#include <gtest/gtest.h>

#include <Uni/Logging/Logging>

#include <Las/LasFile>
#include <Las/LasFileParser>

#include <Database/Connection>
#include <Database/SQLiteConnection>

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
  using Geo::Database::Connection;

  Geo::Database::SQLiteConnection* c =
    DMContext::create<Geo::Database::SQLiteConnection>("Database.SQLiteConnection");

  // c->setDatabaseType(Geo::Database::DatabaseType::SQLite);
  c->setDatabase("test.db");
  c->connect();

  auto dataAccessFactory = c->dataAccessFactory();

  Geo::Domain::WellAccess::Shared wellAccess = dataAccessFactory->wellAccess();
  Geo::Domain::LogAccess::Shared  logAccess  = dataAccessFactory->logAccess();

  using Geo::Domain::Well;

  Geo::Domain::Well::Shared well(new Well(QString("skvazhinka"),
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
  using Geo::Database::SQLiteConnection;

  SQLiteConnection* c =
    DMContext::create<SQLiteConnection>("Database.SQLiteConnection");

  // c->databaseType(Geo::Database::DatabaseType::SQLite);
  c->setDatabase("test.db");
  c->connect();

  auto dataAccessFactory = c->dataAccessFactory();

  Geo::Domain::WellTrait::Shared wellName(new Geo::Domain::WellTrait(QString("WellName")));

  Geo::Domain::WellTrait::Shared wellRegion(new Geo::Domain::WellTrait(QString("Region")));

  Geo::Domain::WellTrait::Shared wellType(new Geo::Domain::WellTrait(QString("Type")));

  Geo::Domain::WellTraitAccess::Shared traitsAccess = dataAccessFactory->wellTraitAccess();

  traitsAccess->insert(wellName);
  traitsAccess->insert(wellRegion);
  traitsAccess->insert(wellType);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}

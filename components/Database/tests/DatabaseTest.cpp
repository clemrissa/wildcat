#include <gtest/gtest.h>

#include <Uni/Logging/Logging>

#include <Las/LasFile>
#include <Las/LasFileParser>

#include <Database/Connections/SQLiteConnection>

#include <Domain/Log>
#include <Domain/LogAccess>
#include <Domain/LogParameterAccess>
#include <Domain/LogParameterGroupAccess>
#include <Domain/Well>
#include <Domain/WellAccess>
#include <Domain/WellTrait>

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QSharedPointer>

static const QString dbFileName("test.db");

TEST(DatabaseTest, CreateDB) {
  using DMContext = DependencyManager::ApplicationContext;
  using Geo::Database::Connections::Connection;

  Geo::Database::Connections::SQLiteConnection* c =
    DMContext::create<Geo::Database::Connections::SQLiteConnection>(
      "Database.SQLiteConnection");

  QFile::remove(dbFileName);

  // c->setDatabaseType(Geo::Database::DatabaseType::SQLite);
  c->setDatabase(dbFileName); // calls connect() inside

  auto dataAccessFactory = c->dataAccessFactory();

  using Geo::Domain::LogAccess;
  using Geo::Domain::WellAccess;

  WellAccess::Shared wellAccess = dataAccessFactory->wellAccess();
  LogAccess::Shared  logAccess  = dataAccessFactory->logAccess();

  using Geo::Domain::Log;
  using Geo::Domain::Well;

  Well::Shared well(new Well(QString("skvazhinka"),
                             0.5, 6.7, 5.7));

  Log::Shared log(new Log());

  // objects interconnections
  well->addLog(log);
  log->setWell(well);

  // store both in DB
  wellAccess->insert(well);
  logAccess->insert(log);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}

// -------------------------------------------------------------------

TEST(DatabaseTest, LogParameters) {
  using DMContext = DependencyManager::ApplicationContext;
  using Geo::Database::Connections::Connection;

  Geo::Database::Connections::SQLiteConnection* c =
    DMContext::create<Geo::Database::Connections::SQLiteConnection>(
      "Database.SQLiteConnection");

  QFile::remove(dbFileName);

  c->setDatabase(dbFileName); // calls connect() inside

  auto dataAccessFactory = c->dataAccessFactory();

  using Geo::Domain::LogParameterAccess;
  using Geo::Domain::LogParameterGroupAccess;
  using Geo::Domain::WellAccess;

  WellAccess::Shared wellAccess = dataAccessFactory->wellAccess();

  LogParameterGroupAccess::Shared logParameterGroupAccess =
    dataAccessFactory->logParameterGroupAccess();

  LogParameterAccess::Shared logParameterAccess =
    dataAccessFactory->logParameterAccess();

  using Geo::Domain::LogParameter;
  using Geo::Domain::LogParameterGroup;
  using Geo::Domain::LogParameterString;
  using Geo::Domain::Well;

  Well::Shared well(new Well(QString("skvazhinka"),
                             0.5, 6.7, 5.7));

  LogParameterGroup::Shared group(new LogParameterGroup());

  LogParameter::Shared parameter(new LogParameterString());

  parameter->setName("TestName");

  parameter->setValue("TestValue");

  parameter->setLogParameterGroup(group);

  group->setWell(well);

  wellAccess->insert(well);
  logParameterGroupAccess->insert(group);
  logParameterAccess->insert(parameter);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}

// -------------------------------------------------------------------

TEST(DatabaseTest, Traits) {
  using DMContext = DependencyManager::ApplicationContext;
  using Geo::Database::Connections::SQLiteConnection;

  SQLiteConnection* c =
    DMContext::create<SQLiteConnection>("Database.SQLiteConnection");

  QFile::remove(dbFileName);

  c->setDatabase(dbFileName);
  // c->connect();

  auto dataAccessFactory = c->dataAccessFactory();

  using Geo::Domain::WellTrait;

  WellTrait::Shared wellName(new WellTrait(QString("WellName")));

  WellTrait::Shared wellRegion(new WellTrait(QString("Region")));

  WellTrait::Shared wellType(new WellTrait(QString("Type")));

  Geo::Domain::WellTraitAccess::Shared traitsAccess =
    dataAccessFactory->wellTraitAccess();

  qDebug() << c->lastError();

  traitsAccess->insert(wellName);
  traitsAccess->insert(wellRegion);
  traitsAccess->insert(wellType);

  ASSERT_TRUE(c->lastError().isEmpty());

  delete c;
}

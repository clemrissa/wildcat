#include <gtest/gtest.h>

#include <Uni/Logging/Logging>

#include <Las/LasFile>
#include <Las/LasFileParser>

#include <Database/Private/Connection>

#include <Domain/Log>
#include <Domain/LogAccess>
#include <Domain/Well>
#include <Domain/WellAccess>

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

  Geo::Domain::Well::Shared well(new Geo::Domain::Well(QString("skvazhinka"),
                                                       0, 34, 0.5, 6.7, 5.7));

  Geo::Domain::Log::Shared
    log(new Geo::Domain::Log(QString("electro"),
                             QString("BKZ"),
                             QString("Lopata")));

  // FIRST LOG!!
  logAccess->insert(log);

  well->addLog(log);
  wellAccess->insert(well);

  ASSERT_TRUE(c->lastError().isEmpty());
}

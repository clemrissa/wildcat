#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <QApplication>
#include <QDir>
#include <QString>
#include <QStringList>

#include "gtest/gtest.h"

// using namespace Geo;

int
main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  QStringList nameFilter("*.xml");

  QDir directory(QString("%1/../components").arg(
                   QCoreApplication::applicationDirPath()));

  QStringList xmlFiles = directory.entryList(nameFilter);

  using DependencyManager::ApplicationContext;
  using DependencyManager::XmlApplicationContextLoader;

  XmlApplicationContextLoader applicationContextLoader;

  for (QString const& componentFilePath : xmlFiles) {
    QString absolutePath = directory.absoluteFilePath(componentFilePath);
    applicationContextLoader.addfilePath(absolutePath.toUtf8().constData());
  }

  ApplicationContext::load(&applicationContextLoader);

  // start google test
  return RUN_ALL_TESTS();
}

#define CATCH_CONFIG_RUNNER

#include <catch/catch.hpp>

#include <QtWidgets/QApplication>

int main( int argc, char* argv[] )
{
  QCoreApplication application(argc, argv);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return ( result < 0xff ? result : 0xff );
}


#if 0
#define CATCH_CONFIG_RUNNER
#include <catch/catch.hpp>

#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include <ComponentManager/ModuleLoader>
#include <ComponentManager/Creator>

int


int
main(int argc, char* argv[])
{
  QApplication application(argc, argv);

  testing::InitGoogleTest(&argc, argv);

  QStringList nameFilter("*.xml");

  QDir directory(QString("%1/../components").arg(
                   QCoreApplication::applicationDirPath()));

  QStringList xmlFiles = directory.entryList(nameFilter);

  using DependencyManager::ApplicationContext;
  using DependencyManager::XmlApplicationContextLoader;

  XmlApplicationContextLoader applicationContextLoader;

  for (QString const& componentFilePath : xmlFiles)
  {
    QString absolutePath = directory.absoluteFilePath(componentFilePath);
    applicationContextLoader.addfilePath(absolutePath.toUtf8().constData());
  }

  ApplicationContext::load(&applicationContextLoader);

  // start google test
  return RUN_ALL_TESTS();
}
#endif

#include "Application.hpp"

#include <DependencyManager/ApplicationContext>
#include <DependencyManager/XmlApplicationContextLoader>

#include <QDir>
#include <QString>
#include <QStringList>

#include <QtWidgets/QStyleFactory>

using namespace Geo;

int
main(int argc, char* argv[])
{
  Application application(argc, argv);

  application.setStyle(QStyleFactory::create("fusion"));

  QStringList nameFilter("*.xml");

  QDir directory(QString("%1/../components")
                 .arg(QCoreApplication::applicationDirPath()));

  QStringList xmlFiles = directory.entryList(nameFilter);

  using DependencyManager::ApplicationContext;
  using DependencyManager::XmlApplicationContextLoader;

  XmlApplicationContextLoader applicationContextLoader;

  for (QString const& componentFilePath : xmlFiles) {
    QString absolutePath = directory.absoluteFilePath(componentFilePath);
    applicationContextLoader.addfilePath(absolutePath.toUtf8().constData());
  }

  ApplicationContext::load(&applicationContextLoader);

  application.createMainWindow();

  return application.exec();
}

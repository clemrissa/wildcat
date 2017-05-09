#include "Application.hpp"

#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDebug>

#include <QtWidgets/QStyleFactory>

#include <ComponentManager/ModuleLoader>
#include <ComponentManager/Creator>

using namespace Geo;

int
main(int argc, char* argv[])
{
  Application application(argc, argv);

  application.setStyle(QStyleFactory::create("fusion"));

  QStringList nameFilter("*.json");

  QDir directory(QString("%1/../modules")
                 .arg(QCoreApplication::applicationDirPath()));

  QStringList jsonFiles = directory.entryList(nameFilter);

  std::vector<QString> jsonFilesVector;
  for (auto const & jf : jsonFiles)
  {
    auto s = directory.absoluteFilePath(jf);

    qDebug() << "JSON path: " << s;

    jsonFilesVector.push_back(s);
  }

  qDebug() << "Loading modules...";

  ComponentManager::loadModules(jsonFilesVector);

  {
    auto & componentCreatorSet = ComponentManager::Creator::instance();

    qDebug() << "Registered creators:";
    for (auto const & p : componentCreatorSet)
    {
      qDebug() << " - " << p.first;
    }
  }

  application.createMainWindow();

  return application.exec();
}

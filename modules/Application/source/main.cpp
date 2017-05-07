#include "Application.hpp"

#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QStringList>

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

  QDir directory(QString("%1/../components")
                 .arg(QCoreApplication::applicationDirPath()));

  QStringList jsonFiles = directory.entryList(nameFilter);

  std::vector<QString> jsonFilesVector;
  for (auto const & jf : jsonFiles)
  {
    jsonFilesVector.push_back(directory.absoluteFilePath(jf));
  }

  ComponentManager::loadModules(jsonFilesVector);

  application.createMainWindow();

  return application.exec();
}

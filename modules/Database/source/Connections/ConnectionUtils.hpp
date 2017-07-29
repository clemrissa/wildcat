#pragma once

#include <memory>

#include <QtCore/QString>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include "IConnection.hpp"
#include "DatabaseType.hpp"

namespace Geo
{
namespace Database
{
namespace ConnectionUtils
{

QString
connectionTypeName(DatabaseType type);

std::shared_ptr<IConnection>
restoreConnectionFromXml(QDomElement& domElement);

//
}
}
}

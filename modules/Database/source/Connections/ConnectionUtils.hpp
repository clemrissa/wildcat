#pragma once

#include <memory>

#include <QtCore/QString>
#include <QtCore/QJsonObject>

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
restoreConnectionFromJson(QJsonObject & jsonConnection);

//
}
}
}

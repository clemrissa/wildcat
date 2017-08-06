#pragma once

#include <mongocxx/instance.hpp>

namespace Geo
{
namespace Database
{

class MongoDBInstance
{
public:

  static
  mongocxx::instance const &
  instance()
  {
    static mongocxx::instance instance{};

    return instance;
  }

public:
  MongoDBInstance() = delete;
  MongoDBInstance(MongoDBInstance const &) = delete;
  MongoDBInstance(MongoDBInstance &&)      = delete;

  MongoDBInstance &
  operator=(MongoDBInstance const &)       = delete;

  MongoDBInstance &
  operator=(MongoDBInstance &&) = delete;
};
}
}

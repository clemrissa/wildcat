#pragma once

#include "ExplorerEntry.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

class CategoryEntry final : public ExplorerEntry
{
public:

  enum Column
  {
    Category    = 0,
    Description = 1,
    Size
  };

public:

  CategoryEntry(QString const & name)
    : _name(name)
  {}

  virtual QVariant
  data(int role, int column) override;

private:

  QString _name;
};

//
}
}
}

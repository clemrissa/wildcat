#pragma once

#include "TreeEntry.hpp"

namespace Geo
{
namespace Import
{
namespace TreeWrapper
{

class Start : public TreeEntry
{
public:
  Start(std::shared_ptr<LasFile> lasFile,
        TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Stop : public TreeEntry
{
public:
  Stop(std::shared_ptr<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Step : public TreeEntry
{
public:
  Step(std::shared_ptr<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Null : public TreeEntry
{
public:
  Null(std::shared_ptr<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

class LogMetricsGroup : public TreeEntry
{
public:
  LogMetricsGroup(std::shared_ptr<LasFile> lasFile,
                  TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};
}
}
}

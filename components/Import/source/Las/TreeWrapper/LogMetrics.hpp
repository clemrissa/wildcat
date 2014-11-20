#ifndef Geo_Import_LogMetrics_hpp
#define Geo_Import_LogMetrics_hpp

#include "TreeEntry.hpp"

namespace Geo {
namespace Import {
namespace TreeWrapper {
//

class Start: public TreeEntry
{
public:
  Start(QSharedPointer<LasFile> lasFile,
        TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Stop: public TreeEntry
{
public:
  Stop(QSharedPointer<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Step: public TreeEntry
{
public:
  Step(QSharedPointer<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

// ------------------------------------------------------

class Null: public TreeEntry
{
public:
  Null(QSharedPointer<LasFile> lasFile,
       TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;

  void
  copyDataToLasToImport() override;
};

class LogMetricsGroup: public TreeEntry
{
public:
  LogMetricsGroup(QSharedPointer<LasFile> lasFile,
                  TreeEntry*              parent);

  QVariant
  data(int role, int column) const override;
};
}
}
}

#endif // Geo_Import_LogMetrics_hpp

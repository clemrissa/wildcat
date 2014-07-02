#ifndef Geo_Import_TreeWrapper_TreeEntry_hpp
#define Geo_Import_TreeWrapper_TreeEntry_hpp

#include <algorithm>
#include <vector>

#include <QSharedPointer>
#include <QVariant>

#include <Las/LasFile.hpp>

#include <Database/Connections/Connection>

namespace Geo {
namespace Import {
namespace TreeWrapper {
/// Composite pattern. Used to represent LAS file strurcture as a tree
class TreeEntry: public QObject
{
public:
  enum Column { Name        = 0,
                Description = 1,
                Value       = 2,
                ImportValue = 3,
                Type        = 4,
                Units       = 5,
                ImportUnits = 6,
                Size };

public:
  TreeEntry(LasFile::Shared lasFile,
            TreeEntry*      parent = nullptr):
    _parent(parent),
    _lasFile(lasFile)
  {
    setLasFileToImport(LasFile::Shared(new LasFile()));
  }

  virtual
  ~TreeEntry();

  TreeEntry*
  parent() { return _parent; }

  std::vector<TreeEntry*> const
  entries() const { return _entries; }

  int
  positionOfChildEntry(TreeEntry* const childEntry) const;

  LasFile::Shared const
  lasFile() const { return _lasFile; }

  LasFile::Shared const
  lasFileToImport() const { return _lasFileToImport; }

  virtual QVariant
  data(int role, int column) = 0;

  virtual QWidget*
  delegateWidget(int column);

  void
  setConnection(Geo::Database::Connections::Connection::Shared connection);

  void
  setLasFileToImport(LasFile::Shared lasFileToImport);

protected:
  virtual void
  copyDataToLasToImport() {}

protected:
  TreeEntry* _parent;

  LasFile::Shared _lasFile;

  // contains processed/modified information
  LasFile::Shared _lasFileToImport;

  Geo::Database::Connections::Connection::Shared _connection;

  std::vector<TreeEntry*> _entries;
};
}
}
}
#endif // Geo_Import_TreeWrapper_TreeEntry_hpp

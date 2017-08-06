#include "TreeEntry.hpp"

using Geo::Database::IConnection;
using Geo::Import::TreeWrapper::TreeEntry;

int
TreeEntry::
positionOfChildEntry(TreeEntry* const childEntry) const
{
  auto it = std::find_if(_entries.begin(),
                         _entries.end(),
                         [&](std::unique_ptr<TreeEntry> const & e) { return (e.get() == childEntry); } );

  return it - _entries.begin();
}


void
TreeEntry::
setConnection(std::shared_ptr<IConnection> connection)
{
  _connection = connection;

  for (std::unique_ptr<TreeEntry> & e : _entries)
    e->setConnection(connection);
}


void
TreeEntry::
setLasFileToImport(std::shared_ptr<LasFile> lasFileToImport)
{
  _lasFileToImport = lasFileToImport;

  // copy some default values for las_to_import
  copyDataToLasToImport();

  for (std::unique_ptr<TreeEntry> & e : _entries)
    e->setLasFileToImport(lasFileToImport);
}


QWidget*
TreeEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}

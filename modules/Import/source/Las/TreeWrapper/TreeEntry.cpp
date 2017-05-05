#include "TreeEntry.hpp"

using Geo::Database::Connections::Connection;
using Geo::Import::TreeWrapper::TreeEntry;

TreeEntry::
~TreeEntry()
{
  for (TreeEntry* entry : _entries)
    delete entry;
}


int
TreeEntry::
positionOfChildEntry(TreeEntry* const childEntry) const
{
  auto it = std::find(_entries.begin(),
                      _entries.end(),
                      childEntry);

  return it - _entries.begin();
}


void
TreeEntry::
setConnection(Connection::Shared connection)
{
  _connection = connection;

  for (TreeEntry* e : _entries)
    e->setConnection(connection);
}


void
TreeEntry::
setLasFileToImport(LasFile::Shared lasFileToImport)
{
  _lasFileToImport = lasFileToImport;

  // copy some default values for las_to_import
  copyDataToLasToImport();

  for (TreeEntry* e : _entries)
    e->setLasFileToImport(lasFileToImport);
}


QWidget*
TreeEntry::
delegateWidget(int column) const
{
  Q_UNUSED(column);
  return nullptr;
}

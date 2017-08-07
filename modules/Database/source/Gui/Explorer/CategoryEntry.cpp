#include "CategoryEntry.hpp"

#include <QtGui/QIcon>
#include <QtWidgets/QFileIconProvider>

namespace Geo
{
namespace Database
{
namespace Gui
{

QVariant
CategoryEntry::
data(int role, int column)
{
  switch (role)
  {
    case Qt::DisplayRole:
    {
      switch (column)
      {
        case CategoryEntry::Category:
          return _name;
          break;

        default:
          return QVariant();
          break;
      }

      break;
    }

    case Qt::DecorationRole:
    {
      if (column == CategoryEntry::Category)
      {
        QFileIconProvider iconProvider;
        return iconProvider.icon(QFileIconProvider::Folder);
      }

      break;
    }

      //case Qt::BackgroundRole:
      //return QVariant(QColor(0xCC, 0xDD, 0xEE));
      //break;
  }

  return QVariant();
}


//
}
}
}

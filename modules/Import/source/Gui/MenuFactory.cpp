#include "MenuFactory.hpp"

#include <QtCore/QObject>
#include <QtWidgets/QMenu>

#include <Las/TreeWrapper/TreeEntry.hpp>
#include <Las/TreeWrapper/WellInformation.hpp>

#include <Domain/WellTrait>

using Geo::Import::Gui::TreeWrapperMenuFactory;
using Geo::Import::TreeWrapper::WellInfoBase;

QMenu*
TreeWrapperMenuFactory::
getWellInformationBaseMenu(WellInfoBase* wellInfo,
                           int           column)
{
  using Geo::Domain::WellTrait;
  using Geo::Import::TreeWrapper::TreeEntry;

  if (column != TreeEntry::Name)
    return nullptr;

  QMenu* addToTraitMenu = new QMenu(QObject::tr("Add to trait..."));

  auto wellTraits = wellInfo->getWellTraits();

  for (WellTrait::Shared wt : wellTraits)
    addToTraitMenu->addAction(wt->name());

  QMenu* result = new QMenu();

  result->addMenu(addToTraitMenu);

  return result;
}

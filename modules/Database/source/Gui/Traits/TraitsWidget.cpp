#include "TraitsWidget.hpp"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Gui/Traits/WellTraitItemDelegate.hpp>
#include <Gui/Traits/TraitsWidgetModel.hpp>
#include <Gui/Traits/WellTraitEntry.hpp>

using Geo::Database::IConnection;

namespace Geo
{
namespace Database
{
namespace Gui
{

struct TraitsWidget::Private
{
  QTableView* traitsTable = nullptr;

  std::unique_ptr<TraitsWidgetModel> traitsWidgetModel;
};

TraitsWidget::
TraitsWidget()
  : _p(std::make_unique<Private>())
{
  createUi();
  connectSignals();
}


TraitsWidget::
~TraitsWidget()
{}


void
TraitsWidget::
setConnection(std::shared_ptr<IConnection> connection)
{
  _p->traitsWidgetModel->setConnection(connection);
}


void
TraitsWidget::
createUi()
{
  setWindowTitle(tr("Well Traits Settings"));

  _p->traitsWidgetModel = std::make_unique<TraitsWidgetModel>();

  // --------------

  _p->traitsTable = new QTableView();

  // View does not tak ownership of the Model;
  _p->traitsTable->setModel(_p->traitsWidgetModel.get());

  // temporarily use standard edit tool
  _p->traitsTable->setItemDelegate(new WellTraitItemDelegate());

  _p->traitsTable->setAlternatingRowColors(true);

  auto headerView = _p->traitsTable->horizontalHeader();

  using Gui::WellTraitEntry;
  headerView->setStretchLastSection(false);
  headerView->setSectionResizeMode(WellTraitEntry::Trait,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Synonyms,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Type,
                                   QHeaderView::Stretch);

  headerView->setSectionResizeMode(WellTraitEntry::CloseAction,
                                   QHeaderView::Fixed);
  headerView->resizeSection(WellTraitEntry::CloseAction, 20);

  auto verticalHeader = _p->traitsTable->verticalHeader();
  verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
  verticalHeader->hide();

  _p->traitsTable->setEditTriggers(QAbstractItemView::AllEditTriggers);

  QVBoxLayout* l = new QVBoxLayout();

  l->setContentsMargins(0, 0, 0, 0);

  l->addWidget(_p->traitsTable);

  setLayout(l);
}


void
TraitsWidget::
connectSignals()
{
  // for deleting rows
  connect(_p->traitsTable, SIGNAL(clicked(const QModelIndex&)),
          _p->traitsWidgetModel.get(),   SLOT(onClicked(const QModelIndex&)));
}


//
}
}
}

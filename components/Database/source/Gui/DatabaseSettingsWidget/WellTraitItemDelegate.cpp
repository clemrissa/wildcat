#include "WellTraitItemDelegate.hpp"

#include <DependencyManager/ApplicationContext>

#include <Widgets/KeywordWidget>

#include <Models/DatabaseSettingsWidgetModel/WellTraitEntry.hpp>

#include <QtWidgets/QTableView>

using Geo::Database::Gui::DatabaseSettingsWidget::WellTraitItemDelegate;
using Geo::Database::Models::DatabaseSettingsWidgetModel::WellTraitEntry;

QWidget*
WellTraitItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(parent);
  Q_UNUSED(option);

  QWidget* result = nullptr;

  switch (index.column()) {
  case WellTraitEntry::Trait:
    break;

  case WellTraitEntry::Synonyms: {
    using AC = DependencyManager::ApplicationContext;
    using Geo::Widgets::KeywordWidget;

    result = AC::create<KeywordWidget>("Widgets.KeywordWidget");

    result->setParent(parent);

    // QTableView* t = static_cast<QTableView*>(parent);

    // connect(result, SIGNAL(keywordAdded()),
    // t->horizontalHeader(), SLOT(HHH));

    break;
  }
  }

  return result;
}


void
WellTraitItemDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  editor->setFixedWidth(option.rect.width());
  editor->move(option.rect.x(), option.rect.y());

  _sizeHints[std::make_pair(index.row(), index.column())] = editor->size();
}


void
WellTraitItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{
  Q_UNUSED(index);

  switch (index.column()) {
  case WellTraitEntry::Trait:
    return;
    break;

  case WellTraitEntry::Synonyms: {
    using Geo::Widgets::KeywordWidget;

    // auto w = static_cast<KeywordWidget*>(editor);

    auto traitEntry =
      static_cast<WellTraitEntry*>(index.internalPointer());

    if (!traitEntry)
      return;

    auto trait = traitEntry->trait();

    // w->setKeywords(trait->synonyms());

    break;
  }
  }
}


void
WellTraitItemDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  switch (index.column()) {
  case WellTraitEntry::Trait:
    return;
    break;

  case WellTraitEntry::Synonyms: {
    using Geo::Widgets::KeywordWidget;

    auto w = static_cast<KeywordWidget*>(editor);

    Q_ASSERT(w);

    auto traitEntry =
      static_cast<WellTraitEntry*>(index.internalPointer());

    if (!traitEntry)
      return;

    auto trait = traitEntry->trait();

    QStringList l = w->keywords();

    Q_ASSERT(l.size());

    // trait->setSynonyms(w->keywords());

    break;
  }
  }
}


// void
// WellTraitItemDelegate::
// paint(QPainter*                   painter,
// const QStyleOptionViewItem& option,
// const QModelIndex&          index) const
// {
// }

QSize
WellTraitItemDelegate::
sizeHint(const QStyleOptionViewItem& option,
         const QModelIndex&          index) const
{
  Q_UNUSED(option);
  auto iterator = _sizeHints.find(std::make_pair(index.row(), index.column()));

  if (iterator != _sizeHints.end())
    return iterator->second;
  else
    return QSize();
}

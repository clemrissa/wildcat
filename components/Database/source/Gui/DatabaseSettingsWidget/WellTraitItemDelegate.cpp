#include "WellTraitItemDelegate.hpp"

#include <DependencyManager/ApplicationContext>

#include <Widgets/KeywordWidget>

#include <Models/DatabaseSettingsWidgetModel/WellTraitEntry.hpp>

#include <Domain/WellTrait>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
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

  using Geo::Domain::WellTrait;

  QWidget* result = nullptr;

  switch (index.column()) {
  case WellTraitEntry::Trait:
  case WellTraitEntry::Synonyms: {
    // using AC = DependencyManager::ApplicationContext;
    // using Geo::Widgets::KeywordWidget;

    // result = AC::create<KeywordWidget>("Widgets.KeywordWidget");

    result = new QLineEdit();

    result->setParent(parent);

    // QTableView* t = static_cast<QTableView*>(parent);

    // connect(result, SIGNAL(keywordAdded()),
    // t->horizontalHeader(), SLOT(HHH));

    break;
  }

  case WellTraitEntry::Type: {
    auto cbox = new QComboBox(parent);

    for (int i = 0; i < WellTrait::Type::Size; ++i)
      cbox->addItem(WellTrait::typeAsString((WellTrait::Type)i));

    result = cbox;
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

  editor->setGeometry(option.rect);

  // editor->setFixedWidth(option.rect.width());
  // editor->move(option.rect.x(), option.rect.y());

  // _sizeHints[std::make_pair(index.row(),
  // index.column())] =
  // editor->size();
}


void
WellTraitItemDelegate::
setEditorData(QWidget*           editor,
              const QModelIndex& index) const
{
  Q_UNUSED(index);

  switch (index.column()) {
  case WellTraitEntry::Trait:
  case WellTraitEntry::Synonyms: {
    using Geo::Widgets::KeywordWidget;

    // auto w = static_cast<KeywordWidget*>(editor);

    auto traitEntry =
      static_cast<WellTraitEntry*>(index.internalPointer());

    if (!traitEntry)
      return;

    auto lineEdit = static_cast<QLineEdit*>(editor);

    lineEdit->setText(traitEntry->data(Qt::DisplayRole,
                                       index.column()).toString());

    // auto trait = traitEntry->trait();

    // w->setKeywords(trait->synonyms());

    break;
  }

  case WellTraitEntry::Type: {
    auto traitEntry =
      static_cast<WellTraitEntry*>(index.internalPointer());

    if (!traitEntry)
      return;

    auto cbox = static_cast<QComboBox*>(editor);

    cbox->setCurrentIndex(traitEntry->trait()->type());

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
  case WellTraitEntry::Synonyms: {
    using Geo::Widgets::KeywordWidget;

    auto lineEdit = static_cast<QLineEdit*>(editor);

    model->setData(index, lineEdit->text(),
                   Qt::EditRole);

    // auto w = static_cast<KeywordWidget*>(editor);

    // Q_ASSERT(w);

    // auto traitEntry = static_cast<WellTraitEntry*>(index.internalPointer());

    // if (!traitEntry)
    // return;

    // auto trait = traitEntry->trait();

    // QStringList l = w->keywords();

    // Q_ASSERT(l.size());

    // trait->setSynonyms(w->keywords());

    break;
  }

  case WellTraitEntry::Type: {
    auto cbox = static_cast<QComboBox*>(editor);
    model->setData(index,
                   cbox->currentIndex(),
                   Qt::EditRole);
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
  auto iterator =
    _sizeHints.find(std::make_pair(index.row(),
                                   index.column()));

  if (iterator != _sizeHints.end())
    return iterator->second;
  else
    return QSize();
}

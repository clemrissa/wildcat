#include "KeywordWidget.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

using Geo::Widgets::KeywordWidget;

KeywordWidget::
KeywordWidget(QWidget* parent):
  QWidget(parent)
{
  //
  setMinimumSize(60, 20);

  _lineEdit = new QLineEdit();

  _flowLayout = new FlowLayout();

  _flowLayout->addWidget(_lineEdit);

  setLayout(_flowLayout);

  connectSignals();
}

void
KeywordWidget::
setKeywords(QStringList const& keywordList)
{
  _keywords = keywordList;
}

QStringList
KeywordWidget::
keywordList() const
{
  return _keywords;
}

void
KeywordWidget::
connectSignals() const
{
  connect(_lineEdit, SIGNAL(textChanged(QString const &)),
          this, SLOT(onTextChanged(QString const &)));
}

void
KeywordWidget::
onTextChanged(QString const& text)
{
  if (text.trimmed().endsWith(",")) {
    QString newKeyword = text.trimmed();
    newKeyword.chop(1); // remove comma

    _keywords.append(newKeyword);

    _flowLayout->removeWidget(_lineEdit);

    _flowLayout->addWidget(new QLabel(newKeyword));

    _flowLayout->addWidget(_lineEdit);

    _lineEdit->clear();
  }
}

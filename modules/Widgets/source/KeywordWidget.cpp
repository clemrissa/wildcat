#include "KeywordWidget.hpp"

#include <QtCore/QEvent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include <QtGui/QMouseEvent>

using Geo::Widgets::KeywordWidget;

KeywordWidget::
KeywordWidget(QWidget* parent)
{
  _lineEdit = new QLineEdit();

  _lineEdit->setFrame(false);
  _lineEdit->setAutoFillBackground(true);

  _lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);

  setAutoFillBackground(true);
  setPalette(palette);

  _flowLayout = new FlowLayout();

  _flowLayout->addWidget(_lineEdit);
  _flowLayout->setMargin(1);

  setLayout(_flowLayout);

  connectSignals();

  QStringList testKeywords;
  testKeywords << "lalala";
  testKeywords << "privet";
  testKeywords << "nuremberg";
  testKeywords << "muenche";

  setKeywords(testKeywords);
}


void
KeywordWidget::
setKeywords(QStringList keywordList)
{
  _keywords = keywordList;

  for (QString keyword : _keywords)
    addKeyword(keyword);
}


QStringList
KeywordWidget::
keywords() const
{
  return _keywords;
}


bool
KeywordWidget::
eventFilter(QObject* obj, QEvent* event)
{
  // todo filter just LMB

  if (event->type() == QEvent::MouseButtonDblClick)
  {
    QMouseEvent* mouseEvent =
      static_cast<QMouseEvent*>(event);

    if (mouseEvent->buttons() & Qt::LeftButton)
    {
      QLabel* l = static_cast<QLabel*>(obj);

      int index = _flowLayout->indexOf(l);

      // remove label

      _flowLayout->removeWidget(l);
      delete l;

      _keywords.removeAt(index);

      event->accept();

      return true;
    }
  }

  event->ignore();

  return false;
}


void
KeywordWidget::
connectSignals() const
{
  connect(_lineEdit,
          SIGNAL(textChanged(QString const&)),
          this,
          SLOT(onTextChanged(QString const&)));
}


void
KeywordWidget::
onTextChanged(QString const& text)
{
  if (text.trimmed().endsWith(","))
  {
    QString newKeyword = text.trimmed();
    newKeyword.chop(1);                           // remove comma

    addKeyword(newKeyword);
  }
}


void
KeywordWidget::
addKeyword(QString keyword)
{
  if (keyword.isEmpty())
    return;

  _keywords.append(keyword);

  _flowLayout->removeWidget(_lineEdit);

  QLabel* label = new QLabel(keyword);

  label->setAutoFillBackground(true);

  label->installEventFilter(this);

  label->setMargin(3);

  label->setAlignment(Qt::AlignCenter);
  label->setFrameStyle(QFrame::StyledPanel);

  _flowLayout->addWidget(label);

  _flowLayout->addWidget(_lineEdit);

  _lineEdit->clear();

  emit keywordAdded();
}

#pragma once

#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

class QLineEdit;

namespace Geo
{
namespace Widgets
{
//

class IKeywordWidget : public QWidget
{
  //Q_OBJECT
public:
  virtual
  ~IKeywordWidget() {}

  virtual void
  setKeywords(QStringList keywordList) = 0;

  virtual QStringList
  keywords() const = 0;

signals:
  virtual void
  keywordAdded() = 0;

private slots:
  virtual void
  onTextChanged(QString const& text) = 0;
};

//
}
}

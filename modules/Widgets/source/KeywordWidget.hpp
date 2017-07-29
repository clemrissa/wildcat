#pragma once

#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

#include "IKeywordWidget.hpp"

#include "FlowLayout.hpp"

class QLineEdit;

namespace Geo
{
namespace Widgets
{
//

class KeywordWidget : public Geo::Widgets::IKeywordWidget
{
  Q_OBJECT

public:
  Q_INVOKABLE
  KeywordWidget(QWidget* parent = nullptr);

  void
  setKeywords(QStringList keywordList) override;

  QStringList
  keywords() const override;

protected:
  bool
  eventFilter(QObject* obj, QEvent* event) override;

private:
  void
  connectSignals() const;

  void
  addKeyword(QString keyword);

signals:

  void
  keywordAdded() override;

private slots:
  void
  onTextChanged(QString const& text) override;

private:
  QStringList _keywords;

  QLineEdit* _lineEdit;

  FlowLayout* _flowLayout;
};

//
}
}

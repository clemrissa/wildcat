#ifndef Geo_Widgets_Implementation_KeywordWidget_hpp
#define Geo_Widgets_Implementation_KeywordWidget_hpp

#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

// from ./source/
#include <KeywordWidget.hpp>

#include "FlowLayout.hpp"

class QLineEdit;

namespace Geo {
namespace Widgets {
namespace Implementation {
//

class KeywordWidget: public Geo::Widgets::KeywordWidget
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
  keywordAdded();

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
}
#endif //  Geo_Widgets_Implementation_KeywordWidget_hpp

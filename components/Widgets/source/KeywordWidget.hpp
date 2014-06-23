#ifndef Geo_Widgets_KeywordWidget_hpp
#define Geo_Widgets_KeywordWidget_hpp

#include <QtCore/QStringList>
#include <QtWidgets/QWidget>

#include "FlowLayout.hpp"

class QLineEdit;

namespace Geo {
namespace Widgets {
class KeywordWidget: public QWidget
{
  Q_OBJECT

public:
  Q_INVOKABLE
  KeywordWidget(QWidget* parent = nullptr);

  void
  setKeywords(QStringList const& keywordList);

  QStringList
  keywordList() const;

private:
  void
  connectSignals() const;

private slots:
  void
  onTextChanged(QString const& text);

private:
  QStringList _keywords;

  QLineEdit* _lineEdit;

  FlowLayout* _flowLayout;
};
}
}
#endif //  Geo_Widgets_KeywordWidget_hpp

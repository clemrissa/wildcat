#include "LogViewerWidget.hpp"

#include "RenderWidgets/BodyRenderWidget.hpp"
#include "RenderWidgets/HeaderRenderWidget.hpp"

#include "SectionControllers/MultiWellSectionController.hpp"
#include "SectionViews/MultiWellSectionView.hpp"

#include "Scalers/AxisScaler.hpp"
#include "Scalers/Scaler.hpp"

#include <QSplitter>
#include <QStatusBar>
#include <QVBoxLayout>

namespace Geo {
namespace LogViewer {
struct LogViewerWidget::Private {
  RenderWidgets::HeaderRenderWidget* headerRenderWidget;

  RenderWidgets::BodyRenderWidget* bodyRenderWidget;

  QSplitter* verticalSplitter;

  QStatusBar* statusBar;

  QSharedPointer<SectionControllers::AbstractSectionController> rootSection;

  Scalers::Scaler::Pointer headerScaler;
  Scalers::Scaler::Pointer bodyScaler;
};

LogViewerWidget::
LogViewerWidget()
  : p(new Private) {
  // setWindowTitle("LogView");

  setMinimumSize(400, 400);

  p->rootSection = SectionControllers::MultiWellSectionController::Pointer(
    new SectionControllers::MultiWellSectionController());

  double dotsPerInch = this->physicalDpiX();

  QSharedPointer<Scalers::AxisScaler> xScaler(new Scalers::AxisScaler(
                                                dotsPerInch, 0.6));

  QSharedPointer<Scalers::AxisScaler> yHeaderScaler(new Scalers::AxisScaler(
                                                      dotsPerInch, 1.0));

  QSharedPointer<Scalers::AxisScaler> yBodyScaler(new Scalers::AxisScaler(
                                                    dotsPerInch, 0.002));

  p->headerScaler = Scalers::Scaler::Pointer(new Scalers::Scaler(xScaler,
                                                                 yHeaderScaler));
  p->bodyScaler = Scalers::Scaler::Pointer(new Scalers::Scaler(xScaler,
                                                               yBodyScaler));
  p->headerRenderWidget = new
                          RenderWidgets::
                          HeaderRenderWidget(p->headerScaler, p->rootSection);

  p->bodyRenderWidget = new
                        RenderWidgets::
                        BodyRenderWidget(p->bodyScaler, p->rootSection);

  QVBoxLayout* layout = new
                        QVBoxLayout();
  layout->addWidget(p->verticalSplitter = new QSplitter(Qt::Vertical));
  p->verticalSplitter->addWidget(p->headerRenderWidget);
  p->verticalSplitter->addWidget(p->bodyRenderWidget);
  p->verticalSplitter->setStretchFactor(0, 1);
  p->verticalSplitter->setStretchFactor(1, 7);

  this->setLayout(layout);

  // setStatusBar(p->statusBar = new QStatusBar(this));
  // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // connect(xScaler.data(),       SIGNAL(scalerChanged()),
  // p->headerRenderWidget, SLOT(update()));
  // connect(xScaler.data(),       SIGNAL(scalerChanged()),
  // p->bodyRenderWidget, SLOT(update()));

  // connect(yHeaderScaler.data(), SIGNAL(scalerChanged()),
  // p->headerRenderWidget, SLOT(update()));

  // connect(yBodyScaler.data(),   SIGNAL(scalerChanged()),
  // p->bodyRenderWidget, SLOT(update()));
}

LogViewerWidget::~LogViewerWidget() {
  // We do not delete explicitly GUI objects
  // because it is done automatically by Qt

  // we do not delete rootSection and scalers either
  // due to used QSharedPointer classes
}
} // namespace LogViewer
} // namespace Geo

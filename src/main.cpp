#include "apptranslator.h"
#include "manager.h"
#include "singleapplication.h"
#include "widgetstate.h"

#include <QApplication>
#include <QCommandLineParser>

#include <locale.h>

#define STR2(XXX) #XXX
#define STR(XXX) STR2(XXX)

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setApplicationName("ScreenTranslator");
  a.setOrganizationName("Gres");
  a.setApplicationVersion(STR(VERSION));

  a.setQuitOnLastWindowClosed(false);

  {
    service::AppTranslator appTranslator({"screentranslator"});
    appTranslator.retranslate();
  }

  {
    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("OCR and translation tool"));
    parser.addHelpOption();
    parser.addVersionOption();
    service::WidgetState::addHelp(parser);

    parser.process(a);
  }

  service::SingleApplication guard;
  if (!guard.isValid())
    return 1;

  // tesseract recommends
  setlocale(LC_NUMERIC, "C");

  Manager manager;

  return a.exec();
}

#include "AboutDialog.hpp"
#include "Globals.hpp"
#include "plaintext/license_text.gen.hpp"
#include "ui/about.ui.h"
#include <QtCore/QDate>
#include <QtWidgets/QStyle>


AboutDialog::AboutDialog(QWidget* parent)
  : QDialog(parent),
    ui_(new Ui::About)
{
  ui_->setupUi(this);

  QString license_notice = qglobals::LICENSE_NOTICE;
  QString current_year = QString::number(QDate::currentDate().year());
  if (current_year != "2019")
    license_notice.replace("2019", "2019-" + current_year);

  setWindowTitle("About" + qglobals::APPLICATION_NAME);
  ui_->lbl_about->setText("About " + qglobals::APPLICATION_NAME);
  ui_->lbl_license->setText(license_notice);
}

AboutDialog::~AboutDialog()
{
}

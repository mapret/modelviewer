#include "LicenseDialog.hpp"
#include "plaintext/license_sources.gen.hpp"
#include "ui/licenses.ui.h"


namespace
{
  const char* LICENSES[] =
  {
    "Glew",   plaintext::Glew,
    "Assimp", plaintext::Assimp,
  };
}

LicenseDialog::LicenseDialog(QWidget* parent)
  : QDialog(parent),
    ui_(new Ui::Licenses)
{
  ui_->setupUi(this);

  std::string s;
  for (size_t i = 0; i < std::size(LICENSES); i += 2)
  {
    ui_->lst_names->addItem(QString::fromUtf8(LICENSES[i]));
  }

  QObject::connect(ui_->lst_names, SIGNAL(currentRowChanged(int)), this, SLOT(itemSelected(int)));
  ui_->txt_text->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
  ui_->txt_text->setMinimumWidth(ui_->txt_text->fontMetrics().width(' ') * 81 + QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
}

LicenseDialog::~LicenseDialog()
{
}

void LicenseDialog::itemSelected(int index)
{
  ui_->txt_text->setPlainText(QString::fromUtf8(LICENSES[index * 2 + 1]));
}

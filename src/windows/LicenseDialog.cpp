#include "LicenseDialog.hpp"
#include "plaintext/license_sources.gen.hpp"
#include "ui/licenses.ui.h"


namespace
{
  struct LicenseEntry
  {
      const char* name;
      const char* text;
      size_t text_length;
  }
  LICENSES[] =
  {
      {"Glew",              (char*)binary::Glew,            binary::Glew_size},
      {"Assimp",            (char*)binary::Assimp,          binary::Assimp_size},
      {"QDarkStyleSheet",   (char*)binary::QDarkStyleSheet, binary::QDarkStyleSheet_size},
      {"BreezeStyleSheets", (char*)binary::Breeze,          binary::Breeze_size}
  };
}

LicenseDialog::LicenseDialog(QWidget* parent)
  : QDialog(parent),
    ui_(new Ui::Licenses)
{
  ui_->setupUi(this);

  std::string s;
  for (const auto& license_entry : LICENSES)
    ui_->lst_names->addItem(QString::fromUtf8(license_entry.name));

  QObject::connect(ui_->lst_names, &QListWidget::currentRowChanged, this, &LicenseDialog::itemSelected);
  ui_->txt_text->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
  ui_->txt_text->setMinimumWidth(ui_->txt_text->fontMetrics().horizontalAdvance(' ') * 81 + QApplication::style()->pixelMetric(QStyle::PM_ScrollBarExtent));
}

LicenseDialog::~LicenseDialog()
{
}

void LicenseDialog::itemSelected(int index)
{
  ui_->txt_text->setPlainText(QString::fromUtf8(LICENSES[index].text, LICENSES[index].text_length));
}

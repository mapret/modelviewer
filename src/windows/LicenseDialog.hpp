#pragma once

#include <memory>
#include <QtWidgets/QDialog>


namespace Ui { class Licenses; }

class LicenseDialog : public QDialog
{
    Q_OBJECT

  public:
    LicenseDialog(QWidget* parent = nullptr);
    ~LicenseDialog();

  private:
    std::unique_ptr<Ui::Licenses> ui_;

  private slots:
    void itemSelected(int index);
};

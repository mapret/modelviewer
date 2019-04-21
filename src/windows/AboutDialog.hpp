#pragma once

#include <memory>
#include <QtWidgets/QDialog>


namespace Ui { class About; }

class AboutDialog : public QDialog
{
  public:
    AboutDialog(QWidget* parent = nullptr);
    ~AboutDialog();

  private:
    std::unique_ptr<Ui::About> ui_;
};

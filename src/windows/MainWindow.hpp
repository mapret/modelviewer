#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>


class GlWidget;
class QListWidgetItem;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    std::unique_ptr<Ui::MainWindow> ui_;
    GlWidget* gl_widget_;

  private slots:
    void openFileModal();
    void fileLoaded();
    void setWireframeVisible(bool value);
    void resetCamera();
    void resetCameraZoom();
    void startAnimation(QListWidgetItem* item);
    void toggleAnimation();
    void resetAnimation();
    void setAnimationSpeed(double value);
};

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include "glwidget.h"
#include <QRadioButton>
#include <QSlider>

namespace Ui {
class Interface;
}

class Interface : public QDialog
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

    void setWidget(_gl_widget *widget_pointer);

private:
    Ui::Interface *ui;

    _gl_widget *widget;

    //QRadioButton *cuboCheck;




public slots:
    // Selección Objeto a dibujar
    void activateCube();
    void activateTetrahedron();
    void activatePly();
    void activateRevolution();
    void activateHierarchy();
    void activateBoard();

    // Selección del modo de dibujado
    void selectPointsMode();
    void selectLineMode();
    void selectFillMode();
    void selectChessMode();
    void selectLightMode();
    void selectTextureMode();
    void selectFlatLightMode();
    void selectSmoothLightMode();
    void selectNormalMode();

    void changeLightDistance();
    void changeLight1Angle();
    void changeLight1xAngle();
    void changeLight2yAngle();
    void changeLight2Angle();

    void switchLight1();
    void switchLight2();

    void selectFirstMaterial();
    void selectSecondMaterial();
    void selectThirdMaterial();

    void changeBoardSize();
    void changeBoardFrame();
    void changeFramePosition();

    void increaseZoom();
    void decreaseZoom();
    void selectHorizontalCameraRotation();
    void selectVerticalCameraRotation();

    void switchProjection();
    void switchSelectedCamera();

};

#endif // INTERFACE_H

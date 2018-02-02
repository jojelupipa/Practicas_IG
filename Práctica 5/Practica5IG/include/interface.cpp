#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    // Handling what is going to be drawn by buttons
    connect(ui->cubeBox,SIGNAL(pressed()),this,SLOT(activateCube()));
    connect(ui->tethraedronBox,SIGNAL(pressed()),this,SLOT(activateTetrahedron()));
    connect(ui->plyBox,SIGNAL(pressed()),this,SLOT(activatePly()));
    connect(ui->revBox,SIGNAL(pressed()),this,SLOT(activateRevolution()));
    connect(ui->hierarchyBox,SIGNAL(pressed()),this,SLOT(activateHierarchy()));
    connect(ui->boardBox,SIGNAL(pressed()),this,SLOT(activateBoard()));

    // Handling which drawing mode will be used
    connect(ui->pointsModeBox,SIGNAL(pressed()),this,SLOT(selectPointsMode()));
    connect(ui->lineModeBox,SIGNAL(pressed()),this,SLOT(selectLineMode()));
    connect(ui->fillModeBox,SIGNAL(pressed()),this,SLOT(selectFillMode()));
    connect(ui->chessModeBox,SIGNAL(pressed()),this,SLOT(selectChessMode()));
    connect(ui->lightModeBox,SIGNAL(pressed()),this,SLOT(selectLightMode()));
    connect(ui->textureModeBox,SIGNAL(pressed()),this,SLOT(selectTextureMode()));
    connect(ui->flatLightBox, SIGNAL(pressed()),this,SLOT(selectFlatLightMode()));
    connect(ui->smoothLightBox, SIGNAL(pressed()),this,SLOT(selectSmoothLightMode()));
    connect(ui->normalModeBox,SIGNAL(pressed()),this,SLOT(selectNormalMode()));

// Light modifiers
    connect(ui->luzDistanceSlider,SIGNAL(valueChanged(int)),this,SLOT(changeLightDistance()));
    connect(ui->light1AngleSlider,SIGNAL(valueChanged(int)),this,SLOT(changeLight1Angle()));
    connect(ui->light1yAngleSlider,SIGNAL(valueChanged(int)),this,SLOT(changeLight1xAngle()));
    connect(ui->light2AngleSlider,SIGNAL(valueChanged(int)),this,SLOT(changeLight2Angle()));
    connect(ui->light2xAngleSlider,SIGNAL(valueChanged(int)),this,SLOT(changeLight2yAngle()));
    connect(ui->light1Button,SIGNAL(pressed()),this,SLOT(switchLight1()));
    connect(ui->light2Button,SIGNAL(pressed()),this,SLOT(switchLight2()));
    connect(ui->material1,SIGNAL(pressed()),this,SLOT(selectFirstMaterial()));
    connect(ui->material2,SIGNAL(pressed()),this,SLOT(selectSecondMaterial()));
    connect(ui->material3,SIGNAL(pressed()),this,SLOT(selectThirdMaterial()));

// Texture modifiers
    connect(ui->boardSizeButton,SIGNAL(valueChanged(int)),this,SLOT(changeBoardSize()));
    connect(ui->confirmBoardFrameButton,SIGNAL(pressed()),this,SLOT(changeBoardFrame()));
    connect(ui->confirmPositionButton,SIGNAL(pressed()),this,SLOT(changeFramePosition()));

//  Camera modifiers
    connect(ui->zoomInButton,SIGNAL(pressed()),this,SLOT(increaseZoom()));
    connect(ui->zoomOutButton,SIGNAL(pressed()),this,SLOT(decreaseZoom()));
    connect(ui->horizontalCameraMovementSlider,SIGNAL(valueChanged(int)),this,SLOT(selectHorizontalCameraRotation()));
    connect(ui->verticalCameraMovementSlider,SIGNAL(valueChanged(int)),this,SLOT(selectVerticalCameraRotation()));

    connect(ui->changePerspectiveButton,SIGNAL(pressed()),this,SLOT(switchProjection()));
    connect(ui->changeCameraButton,SIGNAL(pressed()),this,SLOT(switchSelectedCamera()));

}

Interface::~Interface()
{
    delete ui;
}

void Interface::setWidget(_gl_widget *widget_pointer){
    widget = widget_pointer;
}

void Interface::activateCube(){
    widget->ActivateCube();
}

void Interface::activateTetrahedron(){
    widget->ActivateTetrahedron();
}

void Interface::activatePly(){
    widget->ActivateLoaded();
}

void Interface::activateRevolution(){
    widget->ActivateRevolution();
}

void Interface::activateHierarchy(){
    widget->ActivateHierarchy();
}

void Interface::activateBoard(){
    widget->ActivateBoard();
}

void Interface::selectPointsMode(){
    widget->SelectPointMode();
}

void Interface::selectLineMode(){
    widget->SelectLineMode();
}

void Interface::selectFillMode(){
    widget->SelectFillMode();
}

void Interface::selectChessMode(){
    widget->SelectChessMode();
}

void Interface::selectLightMode(){
    widget->SelectLightMode();
}

void Interface::selectTextureMode(){
    widget->SelectTextureMode();
}

void Interface::selectFlatLightMode(){
    widget->SelectFlatLightMode();
}

void Interface::selectSmoothLightMode(){
    widget->SelectSmoothLightMode();
}

void Interface::selectNormalMode(){
    widget->SelectNormalMode();
}

void Interface::changeLightDistance(){
    widget->ChangeLight1Distance(ui->luzDistanceSlider->value());
}

void Interface::changeLight1Angle(){
    widget->ChangeLight1Angle(ui->light1AngleSlider->value());
}

void Interface::changeLight1xAngle(){
    widget->ChangeLight1xAngle(ui->light1yAngleSlider->value());
}
void Interface::changeLight2yAngle(){
    widget->ChangeLight2yAngle(ui->light2xAngleSlider->value());
}

void Interface::changeLight2Angle(){
    widget->ChangeLight2Angle(ui->light2AngleSlider->value());
}

void Interface::switchLight1(){
    widget->switchLight1();
}

void Interface::switchLight2(){
    widget->switchLight2();
}

void Interface::selectFirstMaterial(){
    widget->selectMaterial(1);
}

void Interface::selectSecondMaterial(){
    widget->selectMaterial(2);
}

void Interface::selectThirdMaterial(){
    widget->selectMaterial(3);
}

void Interface::changeBoardSize(){
    widget->sizeChange(ui->boardSizeButton->value());
    changeFramePosition();
}

void Interface::changeBoardFrame(){
    widget->modifyFrame(ui->framex1->value(),ui->framey1->value(),ui->framex2->value(),ui->framey2->value());
}

void Interface::changeFramePosition(){
    widget->modifyPosition(ui->posx1->value(),ui->posy1->value(),ui->posx2->value(),ui->posy2->value());
}

void Interface::increaseZoom(){
    widget->increaseZoom(true);
}

void Interface::decreaseZoom(){
    widget->increaseZoom(false);
}

void Interface::selectHorizontalCameraRotation(){
    widget->selectHorizontalCameraRotation(ui->horizontalCameraMovementSlider->value());
}

void Interface::selectVerticalCameraRotation(){
    widget->selectVerticalCameraRotation(ui->verticalCameraMovementSlider->value());
}

void Interface::switchProjection(){
    widget->switchProjection();
}

void Interface::switchSelectedCamera(){
    widget->switchSelectedCamera();
}

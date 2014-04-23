#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>

#include <QDebug>
#include <iostream>

QSqlDatabase db;
bool dbOpen;
int experimentLocation;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    closeDownRequest = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{

    bool ok;
    QString host, user, pw, dBase;

    user = QInputDialog::getText ( this, "Accompany DB", "User:",QLineEdit::Normal,"", &ok);
    if (!ok)
    {
       closeDownRequest = true;
       return;
    }

    pw = QInputDialog::getText ( this, "Accompany DB", "Password:", QLineEdit::Password,"", &ok);
    if (!ok)
    {
       closeDownRequest = true;
       return;
    }


    host = QInputDialog::getText ( this, "Accompany DB", "Host:",QLineEdit::Normal,"", &ok);
    if (!ok)
    {
       closeDownRequest = true;
       return;
    };

    dBase = QInputDialog::getText ( this, "Accompany DB", "Database:",QLineEdit::Normal,"", &ok);
    if (!ok)
    {
       closeDownRequest = true;
       return;
    };

    ui->locnLabel->setText(lv);

    if (lv=="ZUYD")
    {
       if (host=="") host = "accompany1";
       if (user=="") user = "accompanyUser";
       if (pw=="") pw = "accompany";

    }
    else
    {
        if (host=="") host = "localhost";
        if (user=="") user = "rhUser";
        if (pw=="") pw = "waterloo";
    }

    if (dBase=="") dBase = "Accompany";


    ui->userLabel->setText(user + " @ " + host);


    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(host);
    db.setDatabaseName(dBase);
    db.setUserName(user);
    db.setPassword(pw);

    dbOpen = db.open();

    if (!dbOpen)
    {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);

        msgBox.setText("Database error - login problem - see console log!");
        msgBox.exec();

        qCritical("Cannot open database: %s (%s)",
                  db.lastError().text().toLatin1().data(),
                  qt_error_string().toLocal8Bit().data());

        closeDownRequest = true;

        return;
    }
    else
    {
        qDebug() << "Database Opened";
    }

    // get experimental location


    QSqlQuery query("SELECT ExperimentalLocationId FROM SessionControl WHERE SessionId = 1 LIMIT 1");

    if (query.next())
    {
       experimentLocation = query.value(0).toInt();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);

        msgBox.setText("Can find session control table!");
        msgBox.exec();
        closeDownRequest = true;
        return;
    }

   // fillSequenceCombo();

   // QString top;
   // top = ui->comboBox->currentText();

   // fillDisplayArea(top);

    fillUserId_ComboBox();

    fillRobotGenericTaskId_ComboBox();

    fill_PhysicalInteraction_ApproachDistanceComboBox();
    fill_VerbalInteraction_ApproachDistanceComboBox();

    on_retrieveRobotGenericTaskBasedPreferencePushButton_clicked();
    on_physicalInteraction_RetrieveProxemicPreferencePushButton_clicked();
    on_verbalInteraction_RetrieveProxemicPreferencePushButton_clicked();

 }

void MainWindow::fillUserId_ComboBox()
{
    QString seqQuery;
    QSqlQuery query;

    seqQuery = "SELECT userId, firstName FROM Accompany.Users;";

    query = seqQuery;
    ui->userIdComboBox->clear();

    while(query.next())
    {
        ui->userIdComboBox->addItem(query.value(0).toString() + ". " + query.value(1).toString());
    }

}



void MainWindow::fillRobotGenericTaskId_ComboBox()
{
    QString seqQuery;
    QSqlQuery query;

    seqQuery = "SELECT robotGenericTaskId, name FROM Accompany.RobotGenericTask";

    query = seqQuery;
    ui->robotGenericTaskComboBox->clear();

    while(query.next())
    {
        ui->robotGenericTaskComboBox->addItem(query.value(0).toString() + ". " + query.value(1).toString());
    }  
}
void MainWindow::on_retrieveRobotGenericTaskBasedPreferencePushButton_clicked()
{

    QString seqQuery;
    QSqlQuery query;

    int preference;

    seqQuery = "SELECT proxemicsId FROM Accompany.UserProxemicsPreferences where userId = ";
    seqQuery += ui->userIdComboBox->currentText().section('.',0,0);
    seqQuery += " and robotGenericTaskId = ";
    seqQuery += ui->robotGenericTaskComboBox->currentText().section('.',0,0);
    seqQuery += ";";

    query = seqQuery;

    while(query.next())
    {
       preference = query.value(0).toInt();

       //qDebug()<<query.value(0).toString();
       //qDebug()<<preference;

    }

    switch (preference)
    {
    case 1: ui->frontDefaultRadioButton->setChecked(true);
        break;

    case 2: ui->frontleftDefaultRadioButton->setChecked(true);
        break;

    case 3: ui->frontrightDefaultRadioButton->setChecked(true);
        break;

    case 4: ui->sideleftDefaultRadioButton->setChecked(true);
        break;

    case 5: ui->siderightDefaultRadioButton->setChecked(true);
        break;

    case 6: ui->backleftDefaultRadioButton->setChecked(true);
        break;

    case 7: ui->backrightDefaultRadioButton->setChecked(true);
        break;

    case 8: ui->backDefaultRadioButton->setChecked(true);
        break;

    case 9: ui->frontFarRadioButton->setChecked(true);
        break;

    case 10: ui->frontleftFarRadioButton->setChecked(true);
        break;

    case 11: ui->frontrightFarRadioButton->setChecked(true);
        break;

    case 12: ui->sideleftFarRadioButton->setChecked(true);
        break;

    case 13: ui->siderightFarRadioButton->setChecked(true);
        break;

    case 14: ui->backleftFarRadioButton->setChecked(true);
        break;

    case 15: ui->backrightFarRadioButton->setChecked(true);
        break;

    case 16: ui->backFarRadioButton->setChecked(true);
        break;

    case 17: ui->frontCloseRadioButton->setChecked(true);
        break;

    case 18: ui->frontleftCloseRadioButton->setChecked(true);
        break;

    case 19: ui->frontrightCloseRadioButton->setChecked(true);
        break;

    case 20: ui->sideleftCloseRadioButton->setChecked(true);
        break;

    case 21: ui->siderightCloseRadioButton->setChecked(true);
        break;

    case 22: ui->backleftCloseRadioButton->setChecked(true);
        break;

    case 23: ui->backrightCloseRadioButton->setChecked(true);
        break;

    case 24: ui->backCloseRadioButton->setChecked(true);
        break;

    default: ui->proxemicsPreferenceUndefinedRadioButton->setChecked(true);
        break;
    }

   /*
   if (QMessageBox::No == QMessageBox::question(this, tr("Action Possibility Creator"),
                                    tr("Do you really want to clear Action Possibility Thresholds?"),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        return;
*/
}
int MainWindow::getCurrent_RobotGenericTask_ProxemicRadioButtonsState()
{
    int state=0;

    if(ui->frontDefaultRadioButton->isChecked())
       state = 1;

    if(ui->frontleftDefaultRadioButton->isChecked())
        state = 2;

    if(ui->frontrightDefaultRadioButton->isChecked())
        state = 3;

    if(ui->sideleftDefaultRadioButton->isChecked())
        state = 4;

    if(ui->siderightDefaultRadioButton->isChecked())
        state = 5;

    if(ui->backleftDefaultRadioButton->isChecked())
        state = 6;

    if(ui->backrightDefaultRadioButton->isChecked())
        state = 7;

    if(ui->backDefaultRadioButton->isChecked())
        state = 8;

    if(ui->frontFarRadioButton->isChecked())
        state = 9;

    if(ui->frontleftFarRadioButton->isChecked())
        state = 10;

    if(ui->frontrightFarRadioButton->isChecked())
        state = 11;

    if(ui->sideleftFarRadioButton->isChecked())
        state = 12;

    if(ui->siderightFarRadioButton->isChecked())
        state = 13;

    if(ui->backleftFarRadioButton->isChecked())
        state = 14;

    if(ui->backrightFarRadioButton->isChecked())
        state = 15;

    if(ui->backFarRadioButton->isChecked())
        state = 16;

    if(ui->frontCloseRadioButton->isChecked())
        state = 17;

    if(ui->frontleftCloseRadioButton->isChecked())
        state = 18;

    if(ui->frontrightCloseRadioButton->isChecked())
        state = 19;

    if(ui->sideleftCloseRadioButton->isChecked())
        state =20;

    if(ui->siderightCloseRadioButton->isChecked())
        state = 21;

    if(ui->backleftCloseRadioButton->isChecked())
        state = 22;

    if(ui->backrightCloseRadioButton->isChecked())
        state = 23;

    if(ui->backCloseRadioButton->isChecked())
        state = 24;

    return state;
}
void MainWindow::on_saveRobotGenericTaskBasedPreferencePushButton_clicked()
{

    QString seqQuery;
    QSqlQuery query;
    int preference = 0;

    preference = getCurrent_RobotGenericTask_ProxemicRadioButtonsState();

    if (preference > 0)
    {

        seqQuery = "SELECT * FROM Accompany.UserProxemicsPreferences where userId = ";
        seqQuery+= ui->userIdComboBox->currentText().section('.',0,0);
        seqQuery+= " and robotGenericTaskId = ";
        seqQuery+= ui->robotGenericTaskComboBox->currentText().section('.',0,0);
        seqQuery+= ";";

        query = seqQuery;

        qDebug()<<query.size();

        if (query.size() > 0) // update the database with new data
        {
            query.prepare("UPDATE Accompany.UserProxemicsPreferences SET proxemicsId = :proxemicsId"
                          " WHERE userId = :userId and robotGenericTaskId = :robotGenericTaskId" );
            query.bindValue(":proxemicsId",preference );
            query.bindValue(":userId",ui->userIdComboBox->currentText().section('.',0,0));
            query.bindValue(":robotGenericTaskId", ui->robotGenericTaskComboBox->currentText().section('.',0,0));


        }
        else if (query.size() == 0) // no data entry, insert a new entry
            {

            query.prepare("INSERT INTO Accompany.UserProxemicsPreferences (userId, robotGenericTaskId, proxemicsId)"
                          " VALUES (:userId, :robotGenericTaskId, :proxemicsId)");

            query.bindValue(":userId", ui->userIdComboBox->currentText().section('.',0,0));
            query.bindValue(":robotGenericTaskId", ui->robotGenericTaskComboBox->currentText().section('.',0,0));
            query.bindValue(":proxemicsId", QString::number(preference));
            }
            else {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setText("Rows size cannot be determined/the database does not support reporting information about query sizes.");
                    msgBox.exec();
                    return;
                  }

        if (!query.exec())
        {

            qDebug() << query.lastQuery();

            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);

            msgBox.setText("Can't add to ActionPossibilities table - duplicate?");
            msgBox.exec();

            qCritical("Cannot add/update: %s (%s)",
                      db.lastError().text().toLatin1().data(),
                      qt_error_string().toLocal8Bit().data());
            return;
        }

    }
    qDebug()<<preference;
}

//Physical Interaction
void MainWindow::fill_PhysicalInteraction_ApproachDistanceComboBox()
{
    QString seqQuery;
    QSqlQuery query;

    seqQuery = "SELECT robotApproachDistanceId, name FROM Accompany.RobotApproachDistance";

    query = seqQuery;
    ui->physicalInteraction_ApproachDistanceComboBox->clear();

    while(query.next())
    {
        ui->physicalInteraction_ApproachDistanceComboBox->addItem(query.value(0).toString() + ". " + query.value(1).toString());
    }
}
void MainWindow::on_physicalInteraction_RetrieveProxemicPreferencePushButton_clicked()
{

    QString seqQuery;
    QSqlQuery query;

    int preference;

    seqQuery = "SELECT proxemicsId FROM Accompany.UserProxemicsPreferences where userId = ";
    seqQuery += ui->userIdComboBox->currentText().section('.',0,0);
    seqQuery += " and robotGenericTaskId = ";
    seqQuery += "7";    //Physical Interaction
    seqQuery += ";";

    query = seqQuery;

    while(query.next())
    {
       preference = query.value(0).toInt();

       //qDebug()<<query.value(0).toString();
       //qDebug()<<preference;

    }

    switch (preference)
    {
    case 1: ui->physicalInteraction_FrontRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 2: ui->physicalInteraction_FrontleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 3: ui->physicalInteraction_FrontrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 4: ui->physicalInteraction_SideleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 5: ui->physicalInteraction_SiderightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 6: ui->physicalInteraction_BackleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 7: ui->physicalInteraction_BackrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 8: ui->physicalInteraction_BackRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 9: ui->physicalInteraction_FrontRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 10:ui->physicalInteraction_FrontleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 11:ui->physicalInteraction_FrontrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 12:ui->physicalInteraction_SideleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 13:ui->physicalInteraction_SiderightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 14:ui->physicalInteraction_BackleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 15:ui->physicalInteraction_BackrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 16:ui->physicalInteraction_BackRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 17:ui->physicalInteraction_FrontRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 18:ui->physicalInteraction_FrontleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 19:ui->physicalInteraction_FrontrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 20:ui->physicalInteraction_SideleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 21:ui->physicalInteraction_SiderightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 22:ui->physicalInteraction_BackleftRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 23:ui->physicalInteraction_BackrightRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 24:ui->physicalInteraction_BackRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    default:ui->physicalInteraction_UndefinedPreferenceRadioButton->setChecked(true);
            ui->physicalInteraction_ApproachDistanceComboBox->setCurrentIndex(3);
        break;
    }

}
int MainWindow::getCurrent_PhysicalInteraction_ApproachDirectionRadioButtonState()
{
    int state=0;

    if (ui->physicalInteraction_FrontRadioButton->isChecked())
       state = 1;

    if (ui->physicalInteraction_FrontleftRadioButton->isChecked())
        state = 2;

    if (ui->physicalInteraction_FrontrightRadioButton->isChecked())
        state = 3;

    if (ui->physicalInteraction_SideleftRadioButton->isChecked())
        state = 4;

    if (ui->physicalInteraction_SiderightRadioButton->isChecked())
        state = 5;

    if (ui->physicalInteraction_BackleftRadioButton->isChecked())
        state = 6;

    if (ui->physicalInteraction_BackrightRadioButton->isChecked())
        state = 7;

    if (ui->physicalInteraction_BackRadioButton->isChecked())
        state = 8;

    return state;
}
int MainWindow::getCurrent_PhysicalInteraction_ApproachDistanceComboBoxState()
{
      int currentIndex = ui->physicalInteraction_ApproachDistanceComboBox->currentIndex();

        currentIndex +=1;
      return currentIndex;
}

//VerbalInteraction
void MainWindow::fill_VerbalInteraction_ApproachDistanceComboBox()
{
    QString seqQuery;
    QSqlQuery query;

    seqQuery = "SELECT robotApproachDistanceId, name FROM Accompany.RobotApproachDistance";

    query = seqQuery;
    ui->verbalInteraction_ApproachDistanceComboBox->clear();

    while(query.next())
    {
        ui->verbalInteraction_ApproachDistanceComboBox->addItem(query.value(0).toString() + ". " + query.value(1).toString());
    }
}
void MainWindow::on_verbalInteraction_RetrieveProxemicPreferencePushButton_clicked()
{

    QString seqQuery;
    QSqlQuery query;

    int preference;

    seqQuery = "SELECT proxemicsId FROM Accompany.UserProxemicsPreferences where userId = ";
    seqQuery += ui->userIdComboBox->currentText().section('.',0,0);
    seqQuery += " and robotGenericTaskId = ";
    seqQuery += "8";    //Verbal Interaction
    seqQuery += ";";
    query = seqQuery;

    while(query.next())
    {
       preference = query.value(0).toInt();

       //qDebug()<<query.value(0).toString();
       //qDebug()<<preference;

    }

    switch (preference)
    {
    case 1: ui->verbalInteraction_FrontRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 2: ui->verbalInteraction_FrontleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 3: ui->verbalInteraction_FrontrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 4: ui->verbalInteraction_SideleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 5: ui->verbalInteraction_SiderightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 6: ui->verbalInteraction_BackleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 7: ui->verbalInteraction_BackrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 8: ui->verbalInteraction_BackRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(1);
        break;

    case 9: ui->verbalInteraction_FrontRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 10:ui->verbalInteraction_FrontleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 11:ui->verbalInteraction_FrontrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 12:ui->verbalInteraction_SideleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 13:ui->verbalInteraction_SiderightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 14:ui->verbalInteraction_BackleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 15:ui->verbalInteraction_BackrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 16:ui->verbalInteraction_BackRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(2);
        break;

    case 17:ui->verbalInteraction_FrontRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 18:ui->verbalInteraction_FrontleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 19:ui->verbalInteraction_FrontrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 20:ui->verbalInteraction_SideleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 21:ui->verbalInteraction_SiderightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 22:ui->verbalInteraction_BackleftRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 23:ui->verbalInteraction_BackrightRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    case 24:ui->verbalInteraction_BackRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(0);
        break;

    default:ui->verbalInteraction_UndefinedPreferenceRadioButton->setChecked(true);
            ui->verbalInteraction_ApproachDistanceComboBox->setCurrentIndex(3);
        break;
    }

}
int MainWindow::getCurrent_VerbalInteraction_ApproachDirectionRadioButtonState()
{
    int state=0;

    if (ui->verbalInteraction_FrontRadioButton->isChecked())
       state = 1;

    if (ui->verbalInteraction_FrontleftRadioButton->isChecked())
        state = 2;

    if (ui->verbalInteraction_FrontrightRadioButton->isChecked())
        state = 3;

    if (ui->verbalInteraction_SideleftRadioButton->isChecked())
        state = 4;

    if (ui->verbalInteraction_SiderightRadioButton->isChecked())
        state = 5;

    if (ui->verbalInteraction_BackleftRadioButton->isChecked())
        state = 6;

    if (ui->verbalInteraction_BackrightRadioButton->isChecked())
        state = 7;

    if (ui->verbalInteraction_BackRadioButton->isChecked())
        state = 8;

    return state;
}
int MainWindow::getCurrent_VerbalInteraction_ApproachDistanceComboBoxState()
{
      int currentIndex = ui->verbalInteraction_ApproachDistanceComboBox->currentIndex();

        currentIndex +=1;
      return currentIndex;
}

int MainWindow::saveUserProxemicsPreferenceToDatabase(int approachDirection, int approachDistance, int robotGenericTaskId)
{

    QString seqQuery;
    QSqlQuery query;
    int current_ApproachDirection = 0;
    int current_ApproachDistance = 0;
    int current_RobotGenericTaskId = 0;
    int preference = 0;

    current_ApproachDirection = approachDirection;
    current_ApproachDistance =  approachDistance;
    current_RobotGenericTaskId = robotGenericTaskId;

    //obtain proxemicsId from the user's current selection
    query.prepare("SELECT proxemicsId FROM Accompany.Proxemics where robotApproachDistanceId = :current_ApprochDistance"
                  " and robotApproachOrientationId = :current_ApproachDirection" );
    query.bindValue(":current_ApproachDistance",QString::number(current_ApproachDistance));
    query.bindValue(":current_ApproachDirection",QString::number(current_ApproachDirection));

    if (!query.exec())
    {
        qDebug() << query.lastQuery();

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);

        msgBox.setText("Can't add to ActionPossibilities table - duplicate?");
        msgBox.exec();

        qCritical("Cannot add/update: %s (%s)",
                  db.lastError().text().toLatin1().data(),
                  qt_error_string().toLocal8Bit().data());
        return 0;
    }

    while(query.next())
    {
        preference = query.value(0).toInt();
        qDebug()<<preference;
    }

    //Check if a previous entry of preference for the robotGenericTask exist
    if (preference > 0)
    {

        seqQuery = "SELECT * FROM Accompany.UserProxemicsPreferences where userId = ";
        seqQuery+= ui->userIdComboBox->currentText().section('.',0,0);
        seqQuery+= " and robotGenericTaskId = ";
        seqQuery+= QString::number(current_RobotGenericTaskId);
        seqQuery+= ";";

        query = seqQuery;
        qDebug()<<seqQuery;
        qDebug()<<query.size();

        if (query.size() > 0) // if previous entry of preference exist, update the database with new data
        {

            query.prepare("UPDATE Accompany.UserProxemicsPreferences SET proxemicsId = :proxemicsId"
                          " WHERE userId = :userId and robotGenericTaskId = :robotGenericTaskId" );
            query.bindValue(":proxemicsId",QString::number(preference) );
            query.bindValue(":userId",ui->userIdComboBox->currentText().section('.',0,0));
            query.bindValue(":robotGenericTaskId", QString::number(current_RobotGenericTaskId));


        }
        else if (query.size() == 0) // if no previous entry of preference exist, create a new entry
            {

            query.prepare("INSERT INTO Accompany.UserProxemicsPreferences (userId, robotGenericTaskId, proxemicsId)"
                          " VALUES (:userId, :robotGenericTaskId, :proxemicsId)");

            query.bindValue(":userId", ui->userIdComboBox->currentText().section('.',0,0));
            query.bindValue(":robotGenericTaskId", QString::number(current_RobotGenericTaskId));
            query.bindValue(":proxemicsId", QString::number(preference));
            }
            else {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setText("Rows size cannot be determined/the database does not support reporting information about query sizes.");
                    msgBox.exec();
                    return 0;
                  }


        if (!query.exec())
        {

            qDebug() << query.lastQuery();

            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);

            msgBox.setText("Can't add to ActionPossibilities table - duplicate?");
            msgBox.exec();

            qCritical("Cannot add/update: %s (%s)",
                      db.lastError().text().toLatin1().data(),
                      qt_error_string().toLocal8Bit().data());
            return 0;
        }

    }

return 1;

}

void MainWindow::on_savePhysicalVerbalInteractionPreferencesPushButton_clicked()
{
    int current_ApproachDirection = getCurrent_PhysicalInteraction_ApproachDirectionRadioButtonState();
    int current_ApproachDistance = getCurrent_PhysicalInteraction_ApproachDistanceComboBoxState();
    saveUserProxemicsPreferenceToDatabase(current_ApproachDirection, current_ApproachDistance, 7); //Physical Interaction


    current_ApproachDirection = getCurrent_VerbalInteraction_ApproachDirectionRadioButtonState();
    current_ApproachDistance = getCurrent_VerbalInteraction_ApproachDistanceComboBoxState();
    saveUserProxemicsPreferenceToDatabase(current_ApproachDirection, current_ApproachDistance, 8); //Verbal Interaction

}


void MainWindow::on_userIdComboBox_currentIndexChanged(const QString &arg1)
{
    qDebug()<<arg1;
    on_retrieveRobotGenericTaskBasedPreferencePushButton_clicked();
    on_physicalInteraction_RetrieveProxemicPreferencePushButton_clicked();
    on_verbalInteraction_RetrieveProxemicPreferencePushButton_clicked();
}

void MainWindow::on_robotGenericTaskComboBox_currentIndexChanged(const QString &arg1)
{
    on_retrieveRobotGenericTaskBasedPreferencePushButton_clicked();
}

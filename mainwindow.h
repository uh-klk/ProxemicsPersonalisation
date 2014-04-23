#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool closeDownRequest;

    void setup();


    void fillUserId_ComboBox();

    void fillRobotGenericTaskId_ComboBox();
    int getCurrent_RobotGenericTask_ProxemicRadioButtonsState();

    void fill_PhysicalInteraction_ApproachDistanceComboBox();
    int getCurrent_PhysicalInteraction_ApproachDirectionRadioButtonState();
    int getCurrent_PhysicalInteraction_ApproachDistanceComboBoxState();

    void fill_VerbalInteraction_ApproachDistanceComboBox();
    int getCurrent_VerbalInteraction_ApproachDirectionRadioButtonState();
    int getCurrent_VerbalInteraction_ApproachDistanceComboBoxState();

    int saveUserProxemicsPreferenceToDatabase(int approachDirection, int approachDistance, int robotGenericTaskId );

    QString lv;
    
private slots:

    void on_physicalInteraction_RetrieveProxemicPreferencePushButton_clicked();
    void on_verbalInteraction_RetrieveProxemicPreferencePushButton_clicked();

    void on_retrieveRobotGenericTaskBasedPreferencePushButton_clicked();
    void on_saveRobotGenericTaskBasedPreferencePushButton_clicked();


    void on_savePhysicalVerbalInteractionPreferencesPushButton_clicked();

    //void on_savePhysicalVerbalPreferencesPushButton_clicked();

    void on_userIdComboBox_currentIndexChanged(const QString &arg1);

    void on_robotGenericTaskComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

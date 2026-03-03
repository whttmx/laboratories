#include <QMainWindow>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>

class Mainwindow{
    
    Q_OBJECT

    public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

    private slots:
    void onSaveClicked();
    void onResetClicked();

    private:
    void setupUI();
    bool validateFields();

    QLineEdit *m_editNameRus;
    QLineEdit *m_editNameLat;
    QLineEdit *m_editWeight;
    QLineEdit *m_editWingspan;
    QRadioButton *m_radioFlyYes;
    QRadioButton *m_radioFlyNo;
    QCheckBox *m_checkMigratory;
    QCheckBox *m_checkAquatic;
    QCheckBox *m_checkDomestic;
    QPushButton *m_btnSave;
    QPushButton *m_btnReset;
}

#include <Mainwindow.hpp>
#include <Bird.hpp>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QLabel *titleLabel = new QLabel("Птица");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QFormLayout *formLayout = new QFormLayout();
    m_editNameRus   = new QLineEdit();
    m_editNameLat   = new QLineEdit();
    m_editWeight    = new QLineEdit();
    m_editWingspan  = new QLineEdit();

    formLayout->addRow("Название (P)", m_editNameRus);
    formLayout->addRow("Название (Л)", m_editNameLat);
    formLayout->addRow("Вес", m_editWeight);
    formLayout->addRow("Размах крыльев", m_editWingspan);
    mainLayout->addLayout(formLayout);

    QGroupBox *flyGroupBox = new QGroupBox("Возможность летать");
    QHBoxLayout *flyLayout = new QHBoxLayout();
    m_radioFlyYes = new QRadioButton("Да");
    m_radioFlyNo  = new QRadioButton("Нет");
    flyLayout->addWidget(m_radioFlyYes);
    flyLayout->addWidget(m_radioFlyNo);
    flyLayout->addStretch();
    flyGroupBox->setLayout(flyLayout);
    mainLayout->addWidget(flyGroupBox);

    QGroupBox *featuresGroupBox = new QGroupBox("Особенности");
    QHBoxLayout *featuresLayout = new QHBoxLayout();
    m_checkMigratory = new QCheckBox("Перелетные");
    m_checkAquatic   = new QCheckBox("Водоплавающие");
    m_checkDomestic  = new QCheckBox("Домашние");
    featuresLayout->addWidget(m_checkMigratory);
    featuresLayout->addWidget(m_checkAquatic);
    featuresLayout->addWidget(m_checkDomestic);
    featuresLayout->addStretch();
    featuresGroupBox->setLayout(featuresLayout);
    mainLayout->addWidget(featuresGroupBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_btnReset = new QPushButton("Сброс");
    m_btnSave  = new QPushButton("Сохранить");
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_btnReset);
    buttonLayout->addWidget(m_btnSave);
    mainLayout->addLayout(buttonLayout);

    connect(m_btnReset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(m_btnSave,  &QPushButton::clicked, this, &MainWindow::onSaveClicked);
}

void MainWindow::onResetClicked()
{
    m_editNameRus->clear();
    m_editNameLat->clear();
    m_editWeight->clear();
    m_editWingspan->clear();
    m_radioFlyYes->setChecked(false);
    m_radioFlyNo->setChecked(false);
    m_checkMigratory->setChecked(false);
    m_checkAquatic->setChecked(false);
    m_checkDomestic->setChecked(false);
}

bool MainWindow::validateFields()
{

    QString nameRus = m_editNameRus->text().trimmed();
    QRegularExpression rusRe("^[А-ЯЁ][а-яё]*$");
    if (!rusRe.match(nameRus).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Название (рус) должно начинаться с заглавной буквы и содержать только русские буквы.");
        return false;
    }

    QString nameLat = m_editNameLat->text().trimmed();
    QRegularExpression latRe("^[A-Z][a-z]*$");
    if (!latRe.match(nameLat).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Название (лат) должно начинаться с заглавной буквы и содержать только латинские буквы.");
        return false;
    }

    QString weightStr = m_editWeight->text().trimmed();
    QRegularExpression weightRe("^\\d+\\.\\d+$");
    if (!weightRe.match(weightStr).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Вес должен быть дробным числом с точкой (например, 0.150).");
        return false;
    }
    bool ok;
    double weight = weightStr.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат веса.");
        return false;
    }

    QString wingspanStr = m_editWingspan->text().trimmed();
    QRegularExpression wingspanRe("^(\\d+)-(\\d+)$");
    QRegularExpressionMatch wingspanMatch = wingspanRe.match(wingspanStr);
    if (!wingspanMatch.hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Размах крыльев должен быть в формате 'число-число' (например, 120-160).");
        return false;
    }
    int minWingspan = wingspanMatch.captured(1).toInt();
    int maxWingspan = wingspanMatch.captured(2).toInt();
    if (minWingspan >= maxWingspan) {
        QMessageBox::warning(this, "Ошибка", "Первое число в размахе крыльев должно быть меньше второго.");
        return false;
    }

    if (!m_radioFlyYes->isChecked() && !m_radioFlyNo->isChecked()) {
        QMessageBox::warning(this, "Ошибка", "Выберите возможность летать (Да или Нет).");
        return false;
    }
    bool canFly = m_radioFlyYes->isChecked();

    bool migratory = m_checkMigratory->isChecked();
    bool aquatic   = m_checkAquatic->isChecked();
    bool domestic  = m_checkDomestic->isChecked();

    Bird bird(nameRus, nameLat, weight, minWingspan, maxWingspan,
              canFly, migratory, aquatic, domestic);
    bird.saveToFile("result.txt");

    QMessageBox::information(this, "Успех", "Данные успешно сохранены в файл result.txt");
    return true;
}

void MainWindow::onSaveClicked()
{
    validateFields();
}
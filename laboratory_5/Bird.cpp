#include <Bird.hpp>
#include <QFile>
#include <QTextStream>

Bird::Bird(const QString &nameRus, const QString &nameLat, double weight, int wingspanMin, int wingspanMax, bool canFly, bool migratory, bool aquatic, bool domestic):
m_nameRus(nameRus), m_nameLat(nameLat), m_weight(weight), m_wingspanMin(wingspanMin), m_wingspanMax(wingspanMax), m_canFly(canFly), m_migratory(migratory), 
m_aquatic(aquatic), m_domestic(domestic) {}

void Bird::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)){
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << "Название (рус): " << m_nameRus << "\n";
    out << "Название (лат): " << m_nameLat << "\n";
    out << "Вес: " << m_weight << "\n";
    out << "Размах крыльев: " << m_wingspanMin << " - " << m_wingspanMax << "\n";
    out << "Летает: " << (m_canFly ? "Да" : "Нет") << "\n";
    out << "Особенности: ";

    QStringList features;
    if (m_migratory) features << "Перелетные";
    if (m_aquatic) features << "Водоплавающие";
    if (m_domestic) features << "Домашние";
    out << features.join(", ") << "\n";
    out << "-----------------------\n";

    file.close();
}
#include <QString>

class Bird{
    public:
    Bird(const QString &nameRus, const QString &nameLat, double weight, int wingspanMin, int wingspanMac, bool canFly, bool migratory, bool aquatic, bool domestic);

    void saveToFile(const QString &filename) const;

    private:
    QString m_nameRus;
    QString m_nameLat;
    double m_weight;
    int m_wingspanMin;
    int m_wingspanMax;
    bool m_canFly;
    bool m_migratory;
    bool m_aquatic;
    bool m_domestic;
};

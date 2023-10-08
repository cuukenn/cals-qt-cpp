#pragma once
#include <QObject>
#include <map>
using namespace std;

#define CALS_CONTEXT_TYPE_INT

#ifdef CALS_CONTEXT_TYPE_INT
#define CALS_CONTEXT_TYPENAME int
#define CALS_CONTEXT_QSTRING2STR toInt
#endif

#ifdef CALS_CONTEXT_TYPE_FLOAT
#define CALS_CONTEXT_TYPENAME float
#define CALS_CONTEXT_QSTRING2STR toFloat
#endif

class CalsContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastNumber READ getLastNumber WRITE setLastNumber NOTIFY lastNumberChanged)
    Q_PROPERTY(QString curNumber READ getCurNumber WRITE setCurNumber NOTIFY curNumberChanged)
    Q_PROPERTY(QString curOps READ getCurOps WRITE setCurOps NOTIFY curOpsChanged)
public:
    explicit CalsContext(QObject *parent = nullptr);

private:
    QString _lastNumber;
    QString _curNumber;
    QString _curOps;
    std::map<string, CALS_CONTEXT_TYPENAME (*)(CALS_CONTEXT_TYPENAME, CALS_CONTEXT_TYPENAME)> operations;
    std::map<string, CALS_CONTEXT_TYPENAME (*)(CALS_CONTEXT_TYPENAME)> mathFunctions;
    std::map<string, CALS_CONTEXT_TYPENAME (*)(CALS_CONTEXT_TYPENAME)> numbers;
    std::map<string, void (CalsContext::*)()> functions;

protected:
    void clear();
    void clearAll();

public:
    void setLastNumber(const QString &number);
    QString getLastNumber();
    void setCurNumber(const QString &number);
    QString getCurNumber();
    void setCurOps(const QString &ops);
    QString getCurOps();

public slots:
    void sendOps(const QString &ops);

signals:
    QString lastNumberChanged(const QString &number);
    QString curNumberChanged(const QString &number);
    QString curOpsChanged(const QString &ops);
};

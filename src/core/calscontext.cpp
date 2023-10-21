#include "calscontext.h"
#include "calculate.hpp"
CalsContext::CalsContext(QObject *parent)
    : QObject{parent}
{
    this->_lastNumber = "";
    this->_curNumber = "0";
    this->_curNumber = "";
    this->mathFunctions.insert({make_pair("<=", calculate::moveRight<CALS_CONTEXT_TYPENAME>),
                                make_pair("+/-", calculate::inverse<CALS_CONTEXT_TYPENAME>),
                                make_pair("x^2", calculate::square<CALS_CONTEXT_TYPENAME>),
                                make_pair("1/x", calculate::reciprocal<CALS_CONTEXT_TYPENAME>),
                                make_pair("√x", calculate::xsqrt<CALS_CONTEXT_TYPENAME>)});
    this->operations.insert({make_pair("+", calculate::add<CALS_CONTEXT_TYPENAME>),
                             make_pair("+", calculate::sub<CALS_CONTEXT_TYPENAME>),
                             make_pair("x", calculate::mul<CALS_CONTEXT_TYPENAME>),
                             make_pair("/", calculate::div<CALS_CONTEXT_TYPENAME>),
                             make_pair("%", calculate::xmod<CALS_CONTEXT_TYPENAME>)});
    this->numbers.insert({make_pair("0", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("1", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("2", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("3", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("4", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("5", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("6", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("7", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("8", calculate::returnSelf<CALS_CONTEXT_TYPENAME>),
                          make_pair("9", calculate::returnSelf<CALS_CONTEXT_TYPENAME>)});
    this->functions.insert({
        make_pair("C", &CalsContext::clearAll),
        make_pair("CE", &CalsContext::clear),
    });
}
void CalsContext::sendOps(const QString &ops)
{
    const string opsStr = ops.toStdString();
    void (CalsContext::*functionPtr)() = this->functions[opsStr];
    // 功能键
    if (functionPtr != nullptr)
    {
        (this->*functionPtr)();
        return;
    }
    // =
    if ("=" == opsStr)
    {
        const string lastOpsStr = this->getCurOps().toStdString();
        CALS_CONTEXT_TYPENAME(*operationPtr)
        (CALS_CONTEXT_TYPENAME, CALS_CONTEXT_TYPENAME) = this->operations[lastOpsStr];
        if (operationPtr != nullptr)
        {
            auto opsRs = operationPtr(this->getLastNumber().CALS_CONTEXT_QSTRING2STR(), this->getCurNumber().CALS_CONTEXT_QSTRING2STR());
            this->setCurOps(ops);
            this->setLastNumber(this->getCurNumber());
            this->setCurNumber(QString::fromStdString(to_string(opsRs)));
        }
        else
        {
            this->setCurOps(ops);
            this->setLastNumber(this->getCurNumber());
            this->setCurNumber("");
        }
        return;
    }
    // 双操作符
    CALS_CONTEXT_TYPENAME(*operationPtr)
    (CALS_CONTEXT_TYPENAME, CALS_CONTEXT_TYPENAME) = this->operations[opsStr];
    if (operationPtr != nullptr)
    {
        const string lastOpsStr = this->getCurOps().toStdString();
        CALS_CONTEXT_TYPENAME(*lastOperationPtr)
        (CALS_CONTEXT_TYPENAME, CALS_CONTEXT_TYPENAME) = this->operations[lastOpsStr];
        if (lastOperationPtr != nullptr)
        {
            auto opsRs = lastOperationPtr(this->getLastNumber().CALS_CONTEXT_QSTRING2STR(), this->getCurNumber().CALS_CONTEXT_QSTRING2STR());
            this->setCurOps(ops);
            this->setLastNumber(QString::fromStdString(to_string(opsRs)));
            this->setCurNumber("");
        }
        else
        {
            this->setCurOps(ops);
            this->setLastNumber(this->getCurNumber());
            this->setCurNumber("");
        }
        return;
    }

    CALS_CONTEXT_TYPENAME(*mathFunctionPtr)
    (CALS_CONTEXT_TYPENAME) = this->mathFunctions[opsStr];
    // 单函数操作
    if (mathFunctionPtr != nullptr)
    {
        auto opsRs = mathFunctionPtr(this->getCurNumber().CALS_CONTEXT_QSTRING2STR());
        this->setCurNumber(QString::fromStdString(to_string(opsRs)));
        return;
    }
    CALS_CONTEXT_TYPENAME(*numberPtr)
    (CALS_CONTEXT_TYPENAME) = this->numbers[opsStr];
    // 数字
    if (numberPtr != nullptr)
    {
        auto opsRs = numberPtr(ops.CALS_CONTEXT_QSTRING2STR());
        this->setCurNumber(this->getCurNumber() + QString::fromStdString(to_string(opsRs)));
        return;
    }
}
QString CalsContext::getCurNumber()
{
    return this->_curNumber;
}
void CalsContext::setCurNumber(const QString &number)
{
    if (number != this->_curNumber)
    {
        this->_curNumber = number;
        emit this->curNumberChanged(this->_curNumber);
    }
}
QString CalsContext::getLastNumber()
{
    return this->_lastNumber;
}
void CalsContext::setLastNumber(const QString &number)
{
    if (number != this->_lastNumber)
    {
        this->_lastNumber = number;
        emit this->lastNumberChanged(this->_lastNumber);
    }
}
QString CalsContext::getCurOps()
{
    return this->_curOps;
}
void CalsContext::setCurOps(const QString &ops)
{
    if (ops != this->_curOps)
    {
        this->_curOps = ops;
        emit this->curOpsChanged(this->_curOps);
    }
}
void CalsContext::clear()
{
    this->setCurNumber("");
}
void CalsContext::clearAll()
{
    this->setCurOps("");
    this->setLastNumber("");
    this->setCurNumber("");
}

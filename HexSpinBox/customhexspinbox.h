#ifndef CUSTOMHEXSPINBOX_H
#define CUSTOMHEXSPINBOX_H

#include <QSpinBox>
class QRegExpValidator;

class CustomHexSpinBox : public QSpinBox
{
public:
    CustomHexSpinBox(QWidget *parent = nullptr);
protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int value) const;
private:
    QRegExpValidator *validator;
};

#endif // CUSTOMHEXSPINBOX_H

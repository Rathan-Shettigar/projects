#include "customhexspinbox.h"
#include <QDebug>

CustomHexSpinBox::CustomHexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0, 255);
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

QValidator::State CustomHexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

//The textFromValue() function converts an integer value to a string.
//QSpinBox calls it to update the editor part of the spin
//box when the user presses the spin box's up or down arrows.
QString CustomHexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}

//The valueFromText() function performs the reverse conversion,
//from a string to an integer value. It is called by QSpinBox
//when the user types a value into the editor part of the spin box
//and presses Enter
int CustomHexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

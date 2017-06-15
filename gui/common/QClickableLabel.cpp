#include "QClickableLabel.h"

QClickableLabel::QClickableLabel(QWidget* parent)
    : QLabel(parent)
{

}


QClickableLabel::QClickableLabel(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    setText(text);
}

QClickableLabel::~QClickableLabel()
{
}

void QClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

#pragma once

#include <QLabel>

class QClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit QClickableLabel( const QString& text="", QWidget* parent=0 );
    explicit QClickableLabel(QWidget* parent=0 );
    ~QClickableLabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#include "tmylabel.h"

void TMyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit clicked();
}


TMyLabel::TMyLabel(QWidget *parent) : QLabel(parent)
{
}


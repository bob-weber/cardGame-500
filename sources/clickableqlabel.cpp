#include <QMouseEvent>

#include "game_settings.h"
#include "clickableqlabel.h"

ClickableQLabel::ClickableQLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

ClickableQLabel::~ClickableQLabel() {}

void ClickableQLabel::mousePressEvent(QMouseEvent* event)
{
	emit cardClicked(this->objectName(), event->buttons());
}

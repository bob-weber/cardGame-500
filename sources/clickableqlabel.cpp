#include <QMouseEvent>

#include "game_500_settings.h"
#include "clickableqlabel.h"

ClickableQLabel::ClickableQLabel(QWidget* parent)
    : QLabel(parent) {
}

ClickableQLabel::~ClickableQLabel() {}

void ClickableQLabel::mousePressEvent(QMouseEvent* event)
{
	emit cardClicked(this->objectName(), event->buttons());
}

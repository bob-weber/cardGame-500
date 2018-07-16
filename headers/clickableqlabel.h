#ifndef CLICKABLEQLABEL_H
#define CLICKABLEQLABEL_H

#include <QWidget>
#include <QLabel>
#include <QSignalMapper>

// See https://wiki.qt.io/Clickable_QLabel for how to make a label "clickable"

class ClickableQLabel : public QLabel
{
		Q_OBJECT

	public:
		explicit ClickableQLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
		~ClickableQLabel();

	signals:
		void cardClicked(QString labelName, Qt::MouseButtons buttons);

	protected:
		void mousePressEvent(QMouseEvent* event);

	private:
		//QSignalMapper *signalMapper;

};

#endif // CLICKABLEQLABEL_H

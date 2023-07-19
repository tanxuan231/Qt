#include "MyWindow.h"
#include <QPainter>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void MyWindow::setType(Type t)
{
    m_type = t;
}

void MyWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    painter.setClipping(true);
    QPainterPath canDrawingPathArea; // 能画上的区域
    canDrawingPathArea.addRoundedRect(rect(), 50, 50); // 这里的50是圆角幅度
    canDrawingPathArea.setFillRule(Qt::WindingFill); // 多块区域组合填充模式

    switch (m_type)
    {
    case LeftTop:// 左上角圆角
    {
        canDrawingPathArea.addRect(0, height() - 50, 50, 50); // 填充左下角
        canDrawingPathArea.addRect(width() - 50, 0, 50, 50); // 填充右上角
        canDrawingPathArea.addRect(width() - 50, height() - 50, 50, 50);// 填充右下角
        break;
    }
    case RightTop: // 右上角圆角
    {
        canDrawingPathArea.addRect(0, height() - 50, 50, 50); // 填充左下角
        canDrawingPathArea.addRect(0, 0, 50, 50); // 填充左上角
        canDrawingPathArea.addRect(width() - 50, height() - 50, 50, 50);// 填充右下角
        break;
    }
    case LeftBottom:// 左下角圆角
    {
        canDrawingPathArea.addRect(width() - 50, 0, 50, 50); // 填充右上角
        canDrawingPathArea.addRect(width() - 50, height() - 50, 50, 50);// 填充右下角
        canDrawingPathArea.addRect(0, 0, 50, 50); // 填充左上角
        break;
    }
    case RightBottom: // 右下角圆角
    {
        canDrawingPathArea.addRect(0, height() - 50, 50, 50); // 填充左下角
        canDrawingPathArea.addRect(width() - 50, 0, 50, 50); // 填充右上角
        canDrawingPathArea.addRect(0, 0, 50, 50); // 填充左上角
        break;
    }
    case Top:         // 上两个圆角
    {
        canDrawingPathArea.addRect(0, height() - 50, 50, 50); // 填充左下角
        canDrawingPathArea.addRect(width() - 50, height() - 50, 50, 50);// 填充右下角
        break;
    }
    case Bottom:     // 下两个圆角
    {
        canDrawingPathArea.addRect(width() - 50, 0, 50, 50); // 填充右上角
        canDrawingPathArea.addRect(0, 0, 50, 50); // 填充左上角
        break;
    }
    case Left:  // 左两个圆角
    {
        canDrawingPathArea.addRect(width() - 50, 0, 50, 50); // 填充右上角
        canDrawingPathArea.addRect(width() - 50, height() - 50, 50, 50);// 填充右下角
        break;
    }
    case Right:      // 右两个圆角
    {
        canDrawingPathArea.addRect(0, height() - 50, 50, 50); // 填充左下角
        canDrawingPathArea.addRect(0, 0, 50, 50); // 填充左上角
        break;
    }
    case All:          // 四个角圆角
    {
        break;
    }
    default:
        break;
    }
    painter.setClipPath(canDrawingPathArea);

    QColor color(Qt::darkRed);
    color.setAlpha(200);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRect(rect());

    return QWidget::paintEvent(event);
}

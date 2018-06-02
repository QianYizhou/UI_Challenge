#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class BaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BaseDialog(const QString &title, const QPoint& point, QWidget* parent = 0);
    ~BaseDialog();

    QWidget* m_widget;
    void setTitle(const QString& title);
    QString getTitle();

    void setWidgetPoint(const QPoint& point);
    QPoint getWidgetPoint();

    QString m_Title;

    void ShowAtPosition(const QPoint &point);
    int getTitleTailPosition();
signals:
    void closeBaseDialog();
protected:


public slots:

private:
    QLabel* m_TitleLabel;
    QLabel* m_pTitleLine;
    QLabel* m_bgLabel;
    QPoint m_Point;
    QPushButton* m_pClose;
};

#endif // BASEDIALOG_H

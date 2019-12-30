#ifndef GETSTARTEDWIDGET_H
#define GETSTARTEDWIDGET_H

//#include <QWidget>

#include <QVBoxLayout>
#include <QCommandLinkButton>
#include <QLabel>
#include <QSpacerItem>

/**
 * @brief The GetStartedWidget class
 * @file getstartedwidget.h
 * Defines the entry window
 */
class GetStartedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GetStartedWidget(QWidget *parent = nullptr);
    ~GetStartedWidget();

    QCommandLinkButton *newButton;
    QCommandLinkButton *openButton;
    QCommandLinkButton *prevSessionButton;

private:
    QHBoxLayout *labelLayout;
    QVBoxLayout *layout;
    QLabel *welcomeLabel;
    QLabel *imgLabel;
    QSpacerItem *spacer;
    QSpacerItem *bottomSpacer;
    QSpacerItem *leftSpacer;

signals:

public slots:
};

#endif // GETSTARTEDWIDGET_H

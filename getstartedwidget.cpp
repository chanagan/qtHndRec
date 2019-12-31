#include <QStandardPaths>
#include <QSettings>

#include "getstartedwidget.h"

GetStartedWidget::GetStartedWidget(QWidget *parent) : QWidget(parent)
{
    QString stdPath;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,"rechkw","Inventory");
   layout = new QVBoxLayout;

    stdPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    settings.setValue("stdPath", stdPath);

    labelLayout = new QHBoxLayout;

    imgLabel = new QLabel;
    imgLabel->setPixmap(QPixmap(":images/smallIcon.png"));
    imgLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    labelLayout->addWidget(imgLabel);
    labelLayout->addSpacing(20);

    welcomeLabel = new QLabel;
    QFont font("Arial", 24);
    welcomeLabel->setFont(font);
    welcomeLabel->setText(tr("Welcome to Inventory Management"));
    welcomeLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    labelLayout->addWidget(welcomeLabel);

    leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    labelLayout->addSpacerItem(leftSpacer);

    layout->addLayout(labelLayout);

    spacer = new QSpacerItem(0, 50, QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addSpacerItem(spacer);

    QStringList tmpString = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    newButton = new QCommandLinkButton(tr("Create new project"));
    newButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    layout->addWidget(newButton);
    layout->addSpacing(10);

//    openButton = new QCommandLinkButton(tr("Open project: "));
    openButton = new QCommandLinkButton(stdPath);
    openButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    layout->addWidget(openButton);
    layout->addSpacing(10);

    prevSessionButton = new QCommandLinkButton(tr("Restore last session"));
    prevSessionButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    layout->addWidget(prevSessionButton);
    layout->addSpacing(10);

    setLayout(layout);
}

GetStartedWidget::~GetStartedWidget()
{
    delete welcomeLabel;
    delete imgLabel;
    delete labelLayout;
    delete newButton;
    delete openButton;
    delete prevSessionButton;

    delete layout;
}



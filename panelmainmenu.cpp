#include "panelmainmenu.h"

PanelMainMenu::PanelMainMenu(QWidget *parent, QString login) : QWidget(parent)
{
    pbStartLearning = new QPushButton("Start learning");
    pbStartLearning->setToolTip("Try yourself in translation of every word from your base of words.");
    pbRepeat = new QPushButton("Repeat");
    pbRepeat->setToolTip("Improve your language with repeating 5 the least known words.");
    pbEdition = new QPushButton("Edit words' base");
    pbEdition->setToolTip("You can add or delete words here.");
    this->loginOfUser = login;

    layout1 = new QGridLayout();
    layout1->addWidget(pbStartLearning,0,0);
    layout1->addWidget(pbRepeat,1,0);
    layout1->addWidget(pbEdition,2,0);

    setLayout(layout1);

    connect(pbEdition, SIGNAL(clicked(bool)), this, SLOT(showEditWordWindow()));
    connect(pbStartLearning, SIGNAL(clicked(bool)), this, SLOT(showLearningWindow()));
    connect(pbRepeat, SIGNAL(clicked(bool)), this, SLOT(showRepeatWindow()));
}

void PanelMainMenu::showEditWordWindow()
{
    EditWordsWindow* editWord = new EditWordsWindow(0,loginOfUser);
    editWord->show();
}

void PanelMainMenu::showLearningWindow()
{
    LearningWindow* learn = new LearningWindow(0,loginOfUser);
    learn->show();
}

void PanelMainMenu::showRepeatWindow()
{
    RepeatWindow* repeat = new RepeatWindow(0,loginOfUser);
    repeat->show();
}


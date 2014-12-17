/********************************************************************************
** Form generated from reading UI file 'QStockMainWindows.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTOCKMAINWINDOWS_H
#define UI_QSTOCKMAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QStockMainWindows
{
public:
    QAction *actionAbout;
    QAction *action_SaveWatchList;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *page_watching;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QWidget *page_quote;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_11;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_12;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_runtime;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditAddCode;
    QPushButton *pushButtonAddCode;
    QStackedWidget *stackedWidget;
    QWidget *page_runtime;
    QVBoxLayout *verticalLayout;
    QTableWidget *runtimeTableWidget;
    QWidget *page_selectData;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menu_O;
    QMenu *menu_H;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QStockMainWindows)
    {
        if (QStockMainWindows->objectName().isEmpty())
            QStockMainWindows->setObjectName(QString::fromUtf8("QStockMainWindows"));
        QStockMainWindows->resize(1016, 641);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/icons/main_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        QStockMainWindows->setWindowIcon(icon);
        QStockMainWindows->setStyleSheet(QString::fromUtf8("#centralWidget{\n"
"	color:#FFFFFF;\n"
"}"));
        actionAbout = new QAction(QStockMainWindows);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        action_SaveWatchList = new QAction(QStockMainWindows);
        action_SaveWatchList->setObjectName(QString::fromUtf8("action_SaveWatchList"));
        centralWidget = new QWidget(QStockMainWindows);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Sunken);
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setMinimumSize(QSize(120, 0));
        toolBox->setMaximumSize(QSize(120, 16777215));
        toolBox->setFrameShape(QFrame::Box);
        toolBox->setFrameShadow(QFrame::Plain);
        page_watching = new QWidget();
        page_watching->setObjectName(QString::fromUtf8("page_watching"));
        page_watching->setGeometry(QRect(0, 0, 118, 506));
        verticalLayout_4 = new QVBoxLayout(page_watching);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(page_watching);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/icons/myFavirate.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pushButton);

        pushButton_3 = new QPushButton(page_watching);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(page_watching);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/icons/calendar.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(page_watching);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/main/icons/notes.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 339, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        toolBox->addItem(page_watching, icon, QString::fromUtf8("Mine"));
        page_quote = new QWidget();
        page_quote->setObjectName(QString::fromUtf8("page_quote"));
        page_quote->setGeometry(QRect(0, 0, 118, 506));
        verticalLayout_5 = new QVBoxLayout(page_quote);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton_11 = new QPushButton(page_quote);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setIcon(icon);
        pushButton_11->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_11);

        pushButton_2 = new QPushButton(page_quote);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_2);

        pushButton_7 = new QPushButton(page_quote);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setIcon(icon);
        pushButton_7->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_7);

        pushButton_9 = new QPushButton(page_quote);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setIcon(icon);
        pushButton_9->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(page_quote);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setIcon(icon);
        pushButton_10->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_10);

        pushButton_12 = new QPushButton(page_quote);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setIcon(icon);
        pushButton_12->setIconSize(QSize(32, 32));

        verticalLayout_5->addWidget(pushButton_12);

        verticalSpacer_2 = new QSpacerItem(20, 257, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        toolBox->addItem(page_quote, icon, QString::fromUtf8("Quote"));
        splitter->addWidget(toolBox);
        frame_runtime = new QFrame(splitter);
        frame_runtime->setObjectName(QString::fromUtf8("frame_runtime"));
        frame_runtime->setFrameShape(QFrame::NoFrame);
        frame_runtime->setFrameShadow(QFrame::Sunken);
        verticalLayout_2 = new QVBoxLayout(frame_runtime);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditAddCode = new QLineEdit(frame_runtime);
        lineEditAddCode->setObjectName(QString::fromUtf8("lineEditAddCode"));
        lineEditAddCode->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(lineEditAddCode);

        pushButtonAddCode = new QPushButton(frame_runtime);
        pushButtonAddCode->setObjectName(QString::fromUtf8("pushButtonAddCode"));
        pushButtonAddCode->setMinimumSize(QSize(0, 25));
        pushButtonAddCode->setIcon(icon2);
        pushButtonAddCode->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButtonAddCode);


        verticalLayout_2->addLayout(horizontalLayout);

        stackedWidget = new QStackedWidget(frame_runtime);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_runtime = new QWidget();
        page_runtime->setObjectName(QString::fromUtf8("page_runtime"));
        verticalLayout = new QVBoxLayout(page_runtime);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        runtimeTableWidget = new QTableWidget(page_runtime);
        if (runtimeTableWidget->columnCount() < 10)
            runtimeTableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        runtimeTableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        runtimeTableWidget->setObjectName(QString::fromUtf8("runtimeTableWidget"));
        runtimeTableWidget->setFrameShape(QFrame::NoFrame);
        runtimeTableWidget->setFrameShadow(QFrame::Plain);
        runtimeTableWidget->setDragEnabled(true);
        runtimeTableWidget->setDragDropOverwriteMode(false);
        runtimeTableWidget->setDefaultDropAction(Qt::MoveAction);
        runtimeTableWidget->setAlternatingRowColors(true);
        runtimeTableWidget->setSortingEnabled(true);
        runtimeTableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        runtimeTableWidget->horizontalHeader()->setDefaultSectionSize(100);
        runtimeTableWidget->horizontalHeader()->setStretchLastSection(false);
        runtimeTableWidget->verticalHeader()->setCascadingSectionResizes(true);
        runtimeTableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(runtimeTableWidget);

        stackedWidget->addWidget(page_runtime);
        page_selectData = new QWidget();
        page_selectData->setObjectName(QString::fromUtf8("page_selectData"));
        stackedWidget->addWidget(page_selectData);

        verticalLayout_2->addWidget(stackedWidget);

        splitter->addWidget(frame_runtime);

        verticalLayout_3->addWidget(splitter);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setLayoutDirection(Qt::RightToLeft);
        progressBar->setAutoFillBackground(true);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(true);

        verticalLayout_3->addWidget(progressBar);

        QStockMainWindows->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QStockMainWindows);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1016, 21));
        menu_O = new QMenu(menuBar);
        menu_O->setObjectName(QString::fromUtf8("menu_O"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QString::fromUtf8("menu_H"));
        QStockMainWindows->setMenuBar(menuBar);
        statusBar = new QStatusBar(QStockMainWindows);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QStockMainWindows->setStatusBar(statusBar);

        menuBar->addAction(menu_O->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_O->addAction(action_SaveWatchList);
        menu_H->addAction(actionAbout);

        retranslateUi(QStockMainWindows);

        toolBox->setCurrentIndex(0);
        toolBox->layout()->setSpacing(0);


        QMetaObject::connectSlotsByName(QStockMainWindows);
    } // setupUi

    void retranslateUi(QMainWindow *QStockMainWindows)
    {
        QStockMainWindows->setWindowTitle(QApplication::translate("QStockMainWindows", "\346\226\260\346\265\252A\350\202\241\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("QStockMainWindows", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("QStockMainWindows", "?", 0, QApplication::UnicodeUTF8));
        action_SaveWatchList->setText(QApplication::translate("QStockMainWindows", "\344\277\235\345\255\230\350\207\252\351\200\211(&S)", 0, QApplication::UnicodeUTF8));
        action_SaveWatchList->setShortcut(QApplication::translate("QStockMainWindows", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("QStockMainWindows", "\350\207\252\351\200\211", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("QStockMainWindows", "\346\214\201\344\273\223", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("QStockMainWindows", "\346\227\245\345\216\206", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("QStockMainWindows", "\344\277\256\345\205\273", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_watching), QApplication::translate("QStockMainWindows", "Mine", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("QStockMainWindows", "\345\244\247\347\233\230", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("QStockMainWindows", "\346\216\222\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("QStockMainWindows", "\346\226\260\350\202\241", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("QStockMainWindows", "\347\247\201\345\213\237", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("QStockMainWindows", "\345\205\250\347\220\203", 0, QApplication::UnicodeUTF8));
        pushButton_12->setText(QApplication::translate("QStockMainWindows", "\346\261\207\345\270\202", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_quote), QApplication::translate("QStockMainWindows", "Quote", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        lineEditAddCode->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        lineEditAddCode->setPlaceholderText(QApplication::translate("QStockMainWindows", "\350\276\223\345\205\245\345\215\225\344\270\252\350\202\241\347\245\250\344\273\243\347\240\201\345\246\202'sz002065'\357\274\214\346\214\211\345\233\236\350\275\246\346\210\226\350\200\205\345\217\263\350\276\271\345\212\240\350\207\252\351\200\211\346\214\211\351\222\256\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        pushButtonAddCode->setText(QApplication::translate("QStockMainWindows", "\345\212\240\350\207\252\351\200\211", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = runtimeTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QStockMainWindows", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = runtimeTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QStockMainWindows", "Code", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = runtimeTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QStockMainWindows", "Date", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = runtimeTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QStockMainWindows", "Current", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = runtimeTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QStockMainWindows", "Open", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = runtimeTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QStockMainWindows", "High", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = runtimeTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("QStockMainWindows", "Low", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = runtimeTableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("QStockMainWindows", "Close", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = runtimeTableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("QStockMainWindows", "Hands", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = runtimeTableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("QStockMainWindows", "Adjust", 0, QApplication::UnicodeUTF8));
        menu_O->setTitle(QApplication::translate("QStockMainWindows", "\346\211\223\345\274\200(&O)", 0, QApplication::UnicodeUTF8));
        menu_H->setTitle(QApplication::translate("QStockMainWindows", "\345\270\256\345\212\251(&H)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QStockMainWindows: public Ui_QStockMainWindows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTOCKMAINWINDOWS_H

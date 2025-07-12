#include <windows.h>
#include <nowide/args.hpp>

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include <QSlider>
#include <QProgressBar>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QMessageBox>
#include <QStyleFactory>
#include <QHBoxLayout>

int WINAPI WinMain(HINSTANCE, HINSTANCE, char*, int) {
    int argc = 0;
    char** argv = nullptr;
    nowide::args fix(argc, argv);
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Qt Styles Showcase");
    window.resize(500, 700);

    auto *mainLayout = new QVBoxLayout(&window);

    auto *styleButtonsLayout = new QHBoxLayout;

    auto addStyleButton = [&](const QString &styleName) {
        auto *btn = new QPushButton(styleName);
        QObject::connect(btn, &QPushButton::clicked, [styleName]() {
            if (QStyleFactory::keys().contains(styleName)) {
                QApplication::setStyle(QStyleFactory::create(styleName));
            } else {
                QMessageBox::warning(nullptr, "Ошибка", "Стиль " + styleName + " недоступен на этой платформе.");
            }
        });
        styleButtonsLayout->addWidget(btn);
    };

    addStyleButton("Fusion");
    addStyleButton("Windows");
    addStyleButton("windowsvista");
    addStyleButton("windows11");

    mainLayout->addLayout(styleButtonsLayout);

    auto *styleListButton = new QPushButton("Показать доступные стили");
    QObject::connect(styleListButton, &QPushButton::clicked, []() {
        QStringList styles = QStyleFactory::keys();
        QString styleList = styles.join("\n");
        QMessageBox::information(nullptr, "Доступные стили", styleList);
    });
    mainLayout->addWidget(styleListButton);

    mainLayout->addWidget(new QPushButton("Просто кнопка"));
    mainLayout->addWidget(new QCheckBox("Чекбокс"));

    auto *radioGroup = new QGroupBox("Выбор варианта");
    auto *radioLayout = new QVBoxLayout;
    radioLayout->addWidget(new QRadioButton("Вариант 1"));
    radioLayout->addWidget(new QRadioButton("Вариант 2"));
    radioGroup->setLayout(radioLayout);
    mainLayout->addWidget(radioGroup);

    auto *combo = new QComboBox;
    combo->addItems({"Пункт 1", "Пункт 2", "Пункт 3"});
    mainLayout->addWidget(combo);

    auto *lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("Введите текст...");
    mainLayout->addWidget(lineEdit);

    auto *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    mainLayout->addWidget(slider);

    auto *progress = new QProgressBar;
    progress->setValue(42);
    mainLayout->addWidget(progress);

    auto *table = new QTableWidget(3, 2);
    table->setHorizontalHeaderLabels({"Имя", "Значение"});
    table->setItem(0, 0, new QTableWidgetItem("A"));
    table->setItem(0, 1, new QTableWidgetItem("123"));
    table->setItem(1, 0, new QTableWidgetItem("B"));
    table->setItem(1, 1, new QTableWidgetItem("456"));
    table->setItem(2, 0, new QTableWidgetItem("C"));
    table->setItem(2, 1, new QTableWidgetItem("789"));
    table->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(table);

    window.setLayout(mainLayout);
    window.show();

    return app.exec();
}

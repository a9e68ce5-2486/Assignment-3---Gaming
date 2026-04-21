#ifndef STYLES_H
#define STYLES_H

#include <QString>

inline QString appStyleSheet() {
    return R"(
        QWidget {
            background-color: #1a1a2e;
            color: #e0e0e0;
            font-family: Arial;
            font-size: 13px;
        }
        QLineEdit, QDateEdit, QComboBox {
            background-color: #16213e;
            color: #e0e0e0;
            border: 1px solid #0f3460;
            border-radius: 5px;
            padding: 6px 8px;
        }
        QLineEdit:focus, QDateEdit:focus, QComboBox:focus {
            border: 1px solid #e94560;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: #16213e;
            color: #e0e0e0;
            selection-background-color: #0f3460;
        }
        QPushButton {
            background-color: #0f3460;
            color: #e0e0e0;
            border: none;
            border-radius: 6px;
            padding: 9px 18px;
            font-size: 13px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #e94560;
        }
        QPushButton:pressed {
            background-color: #c73652;
        }
        QLabel {
            color: #e0e0e0;
        }
        QTableWidget {
            background-color: #16213e;
            color: #e0e0e0;
            border: 1px solid #0f3460;
            gridline-color: #0f3460;
            selection-background-color: #e94560;
        }
        QHeaderView::section {
            background-color: #0f3460;
            color: #e0e0e0;
            padding: 5px;
            border: none;
            font-weight: bold;
        }
        QScrollBar:vertical {
            background: #16213e;
            width: 8px;
            border: none;
        }
        QScrollBar::handle:vertical {
            background: #0f3460;
            border-radius: 4px;
            min-height: 20px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )";
}

#endif // STYLES_H

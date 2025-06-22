
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_playButton_clicked();

    void on_doneButton_clicked();

    void on_gameGrid_cellChanged(int row, int column);

    void difficultySelected();

    void on_quitButton_clicked();

    void on_continueButton_clicked();

    void showTime();

    void on_completeHomeButton_clicked();

    void on_completeStatsButton_clicked();

    bool isValidSudokuSolution(int grid[9][9]);

    void on_statsButton_clicked();

    void on_howtoButton_clicked();

    void on_returnBtn_2_clicked();

    void on_returnBtn_clicked();

    void on_returnBtn_3_clicked();

    void on_solveButton_clicked();

    bool solveSudoku(int grid[9][9]);

    void on_exitBtn_clicked();

private:
    Ui::Widget *ui;

public:
    int playInstance[9][9]; // playing array - instance
    QString playDifficulty; // current selected difficulty
    int unsolvedPuzzle[9][9];
    int easyPuzzle[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    int midPuzzle[9][9] = {
        {0, 0, 0, 2, 0, 0, 0, 6, 3},
        {3, 0, 0, 0, 0, 5, 4, 0, 1},
        {0, 0, 1, 0, 0, 3, 9, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 9, 0},
        {0, 0, 0, 5, 3, 8, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 6, 3, 0, 0, 5, 0, 0},
        {5, 0, 3, 7, 0, 0, 0, 0, 8},
        {4, 7, 0, 0, 0, 1, 0, 0, 0}
    };
    int hardPuzzle[9][9] = {
        {0, 0, 5, 3, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 7, 0, 0, 1, 0, 5, 0, 0},
        {4, 0, 0, 0, 0, 5, 3, 0, 0},
        {0, 1, 0, 0, 7, 0, 0, 0, 6},
        {0, 0, 3, 2, 0, 0, 0, 8, 0},
        {0, 6, 0, 5, 0, 0, 0, 0, 9},
        {0, 0, 4, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 9, 7, 0, 0}
    };

    QTimer *timer;
    int minutes = 0;
    int seconds = 0;

    bool gameComplete = false;
};

#endif // WIDGET_H

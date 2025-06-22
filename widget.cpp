
#include "widget.h"
#include "ui_widget.h"


// importing modules
#include <fstream>
#include <iostream>

// a library to solve automatically
#include <algorithm>
#include <random>

// importing Qt GUI libraries
#include <QTableWidget> // to render the game board
#include <QColor>
#include <QDebug> // to print message on the console
#include <QFile> // to work with files in the Qt GUI framework
#include <QTimer> // to set timer


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //basic window setup
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // always boot in home screen



    // connect dificulty buttons
    connect(ui->easyButton, SIGNAL(released()),this, SLOT(difficultySelected()));
    connect(ui->midButton, SIGNAL(released()),this, SLOT(difficultySelected()));
    connect(ui->hardButton, SIGNAL(released()),this, SLOT(difficultySelected()));

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::isValidSudokuSolution(int grid[9][9]) {
    // Check rows
    for (int row = 0; row < 9; ++row) {
        bool used[10] = { false }; // Array to keep track of used numbers

        for (int col = 0; col < 9; ++col) {
            int num = grid[row][col];
            if (num != 0) {
                if (used[num]) {
                    return false; // return false if duplicate number found in the row
                }
                used[num] = true;
            }else{
                return false;
            }
        }
    }

    // Check columns
    for (int col = 0; col < 9; ++col) {
        bool used[10] = { false }; // Array to keep track of used numbers

        for (int row = 0; row < 9; ++row) {
            int num = grid[row][col];
            if (num != 0) {
                if (used[num]) {
                    return false; // return false if duplicate number found in the column
                }
                used[num] = true;
            }else{
                return false;
            }
        }
    }

    // Check subgrids
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            bool used[10] = { false }; // Array to keep track of used numbers

            for (int row = startRow; row < startRow + 3; ++row) {
                for (int col = startCol; col < startCol + 3; ++col) {
                    int num = grid[row][col];
                    if (num != 0) {
                        if (used[num]) {
                            return false; // return false if duplicate number found in the subgrid
                        }
                        used[num] = true;
                    }else{
                        return false;
                    }
                }
            }
        }
    }

    return true; // All checks passed, valid Sudoku solution
}


void Widget::showTime()
{
    // update seconds
    seconds++;
    if(seconds >= 60){
        minutes++;
        seconds = 0;
    }

    // display time on lcd screen
    QString timmer = QString::number(minutes) + ":" + QString::number(seconds);
    ui->playDuration->display(timmer);
}


void Widget::on_playButton_clicked()
{
    // direct to difficulty selection screen
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::difficultySelected(){

    //set up the grid to be rendered
    ui->gameGrid->setRowCount(9);
    ui->gameGrid->setColumnCount(9);

    // extract the text from the button
    QPushButton *button = (QPushButton *)sender();
    QString btnText = button->text();

    // set the difficulty based on the difficulty selected
    if(btnText == "Easy"){
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                playInstance[row][col] = easyPuzzle[row][col];
                unsolvedPuzzle[row][col] = easyPuzzle[row][col];
            }
        }
        playDifficulty = "Easy";
    }else if(btnText == "Medium"){
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                playInstance[row][col] = midPuzzle[row][col];
                unsolvedPuzzle[row][col] = midPuzzle[row][col];
            }
        }
        playDifficulty = "Medium";
    }else if(btnText == "Hard"){
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                playInstance[row][col] = hardPuzzle[row][col];
                unsolvedPuzzle[row][col] = hardPuzzle[row][col];
            }
        }
        playDifficulty = "Hard";
    }


    // generate game grid based on selected level
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(playInstance[i][j] != 0){
                // make item uneditable if part of initial puzzle
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(playInstance[i][j]));
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                QColor cellColor(Qt::lightGray);
                item->setData(Qt::BackgroundRole, cellColor);
                ui->gameGrid->setItem(i, j, item);
            }else{
                // empty cells to be filled
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                ui->gameGrid->setItem(i, j, item);
            }

        }
    }


    // render the game grid navigate to playing screen
    ui->gameGrid->show();
    ui->stackedWidget->setCurrentIndex(2);

    ui->playDuration->setStyleSheet("background-color: black; color: red");

    //setup timer
    minutes = 0;
    seconds = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    // start timer and trigger showTime every second
    timer->start(1000);
    showTime();
}



void Widget::on_doneButton_clicked()
{
    // high scores data
    struct highscore{
        QString difficulty;
        int minutes;
    };
    highscore readScores[5];
    bool found = false;

    timer->stop(); // Stop the timer

    if(isValidSudokuSolution(playInstance)){
        // if the user won
            //display win screen
        ui->completeLabel->setText("You won!");
        ui->completeDifficulty->setText("Difficulty: " + playDifficulty);
        ui->completeTime->setText("Time: "+QString::number(minutes)+":"+QString::number(seconds));

            //update high scores
         //read high score
        QFile statsFileIn("stats.txt");

        if(statsFileIn.open(QIODevice::ReadOnly)){
            QString readDifficulty;
            int readTime;
            QTextStream stats(&statsFileIn);
            for (int i = 0; i < 5; i++) {
                stats >> readDifficulty;
                stats >> readTime;
                if(minutes < readTime && !found){
                    readScores[i].difficulty = playDifficulty;
                    readScores[i].minutes = minutes;
                    found = true;
                }else if(i < 4){
                    readScores[i].difficulty = readDifficulty;
                    readScores[i].minutes = readTime;
                }
            }
            statsFileIn.close();
        }else{
            qDebug() << "Error opening file";
        }



        // write high score
        QFile statsFile("stats.txt");

        if(statsFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            QTextStream stats(&statsFile);
            for(int i = 0; i < 4; ++i){
                    stats << readScores[i].difficulty << " " << readScores[i].minutes << "\n";
            }
            statsFile.close();
        }else{
            qDebug() << "Error opening file";
        }
        //
        ui->stackedWidget->setCurrentIndex(4);

    }else{
        // if the user lost
        qDebug() <<"Game lost";
        ui->completeLabel->setText("You lost!");
        ui->completeDifficulty->setText("Difficulty: " + playDifficulty);
        ui->completeTime->setText("Time: "+QString::number(minutes)+":"+QString::number(seconds));
        ui->stackedWidget->setCurrentIndex(4);
    }

}




void Widget::on_gameGrid_cellChanged(int row, int column)
{
    QTableWidgetItem* item = ui->gameGrid->item(row, column);
    int value = item->text().toInt();
    playInstance[row][column] = value;
}


void Widget::on_quitButton_clicked()
{
    //stop the timer
    timer->stop();
    //disconnect(timer, &QTimer::timeout, this, &MyWidget::timerTimeout);

    // save before quit
    QFile saveGameFile("savedGame.txt");

    if(saveGameFile.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream saveGame(&saveGameFile);
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                saveGame << playInstance[row][col] << " ";
            }
            saveGame << "\n";
        }
        saveGame << playDifficulty;
        saveGame << "\n";
        saveGame << minutes;
        saveGame << "\n";
        saveGame << seconds;
        saveGameFile.close();
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        qDebug() << "Error opening file";
    }
    // ask for confirmation



}


void Widget::on_continueButton_clicked()
{
    QString difficulty;
    int selectedDifficulty[9][9];

    //set up the grid to be rendered
    ui->gameGrid->setRowCount(9);
    ui->gameGrid->setColumnCount(9);


        // read from savedGame file and populate playInstance
        QFile saveGameFile("savedGame.txt");

        if(saveGameFile.open(QIODevice::ReadOnly)){
            QTextStream saveGame(&saveGameFile);
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    saveGame >> playInstance[row][col];
                }
            }
            saveGame >> difficulty;
            saveGame >> minutes;
            saveGame >> seconds;
            saveGameFile.close();
            ui->stackedWidget->setCurrentIndex(0);
        }else{
            qDebug() << "Error opening file";
        }


        if(difficulty == "Easy"){
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    selectedDifficulty[row][col] = easyPuzzle[row][col];
                }
            }
            playDifficulty = "Easy";
        }else if(difficulty == "Medium"){
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    selectedDifficulty[row][col] = midPuzzle[row][col];
                }
            }
            playDifficulty = "Medium";
        }else if(difficulty == "Hard"){
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    selectedDifficulty[row][col] = hardPuzzle[row][col];
                }
            }
            playDifficulty = "Hard";
        }


        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(playInstance[i][j]));
                item->setTextAlignment(Qt::AlignCenter);
                if(playInstance[i][j] != 0 && playInstance[i][j] == selectedDifficulty[i][j]){
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item uneditable
                    QColor cellColor(Qt::lightGray);  // Set your desired background color
                    item->setData(Qt::BackgroundRole, cellColor);
                    ui->gameGrid->setItem(i, j, item);
                }else{
                    ui->gameGrid->setItem(i, j, item);
                }
            }
        }

        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
        timer->start(1000);
        showTime();

        ui->gameGrid->show();
        ui->stackedWidget->setCurrentIndex(2);

}



void Widget::on_completeHomeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_completeStatsButton_clicked()
{
    on_statsButton_clicked();
}


void Widget::on_statsButton_clicked()
{



    //read high score
    QFile statsFileIn("stats.txt");

    if(statsFileIn.open(QIODevice::ReadOnly)){
        QString readDifficulty;
        int readTime;
        QTextStream stats(&statsFileIn);
        for (int i = 0; i < 4; i++) {
                    stats >> readDifficulty;
                    stats >> readTime;

                    QLabel* topScore = new QLabel;
                    topScore->setText(readDifficulty +" " + QString::number(readTime));
                    topScore->setFont(QFont("Times", 15));
                    ui->statsDisplay->addWidget(topScore); // Add the QLabel to the QVBoxLayout directly
                }

        // Create a spacer widget
        QWidget* spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        spacer->setMinimumHeight(20); // Set the minimum height to 20 pixels
        spacer->setMaximumHeight(40); // Set the maximum height to 40 pixels
        ui->statsDisplay->addWidget(spacer);

        statsFileIn.close();

    ui->stackedWidget->setCurrentIndex(3);
}
}


void Widget::on_howtoButton_clicked()
{
    // direct to how to play screen
    ui->stackedWidget->setCurrentIndex(5);
}







void Widget::on_returnBtn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_returnBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_returnBtn_3_clicked()
{
    QLayoutItem* item;
    while ((item = ui->statsDisplay->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
    }
    ui->stackedWidget->setCurrentIndex(0);
}



// Function to check if a number can be placed in a particular position
bool isSafe(int grid[9][9], int row, int col, int num) {
    // Check if the number is already present in the same row
    for (int c = 0; c < 9; ++c) {
    if (grid[row][c] == num) {
                    return false;
    }
    }

    // Check if the number is already present in the same column
    for (int r = 0; r < 9; ++r) {
    if (grid[r][col] == num) {
                    return false;
    }
    }

    // Check if the number is already present in the same 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
                    if (grid[startRow + r][startCol + c] == num) {
                    return false;
                    }
    }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool Widget::solveSudoku(int grid[9][9]) {
    for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
                    // Find an empty cell
                    if (grid[row][col] == 0) {
                    // Generate a random sequence of numbers from 1 to 9
                    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::random_shuffle(nums, nums + 9, [](int i) { return rand() % i; });

                    // Try each number in the random sequence
                    for (int num : nums) {
                    if (isSafe(grid, row, col, num)) {
                        // Place the number in the cell
                        grid[row][col] = num;

                        // Recursively solve the rest of the puzzle
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // If the current configuration doesn't lead to a solution,
                        // backtrack by removing the number from the cell
                        grid[row][col] = 0;
                    }
                    }

                    // If no number can be placed in the cell, return false
                    return false;
                    }
    }
    }

    // If all cells are filled, the puzzle is solved
    return true;
}




void Widget::on_solveButton_clicked()
{
    if (solveSudoku(unsolvedPuzzle)) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(unsolvedPuzzle[i][j]));
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Make the item uneditable
            QColor cellColor(Qt::lightGray);  // Set your desired background color
            item->setData(Qt::BackgroundRole, cellColor);
            ui->gameGrid->setItem(i, j, item);
        }
    }
    timer->stop();
    }
}






void Widget::on_exitBtn_clicked()
{
    timer->stop();
    ui->stackedWidget->setCurrentIndex(0);
}


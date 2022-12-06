#ifndef ADVENTOFCODE_H
#define ADVENTOFCODE_H

#include <QtWidgets/QMainWindow>
#include "ui_adventofcode.h"

namespace AdventOfCode {

class AdventOfCode : public QMainWindow
{
      Q_OBJECT

public:
      AdventOfCode(const QStringList& args, QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
      ~AdventOfCode();

private slots:
      void clearGUI();
      void process();

private:
      Ui::AdventOfCodeClass ui;
};

} // namespace AdventOfCode

#endif // ADVENTOFCODE_H

#include "adventofcode.h"

namespace AdventOfCode {

AdventOfCode::AdventOfCode(const QStringList& args, QWidget* parent, Qt::WindowFlags flags)
      : QMainWindow(parent, flags)
{
      ui.setupUi(this);

      for (int i = 0; i < 26; i++) {
            ui.dayComboBox->addItem(QString("%1").arg(i + 1));
      }
      ui.dayComboBox->setMaxVisibleItems(25);
      connect(ui.dayComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(clearGUI()));

      connect(ui.processPushButton, SIGNAL(clicked(bool)), this, SLOT(process()));
}

void AdventOfCode::clearGUI()
{
      ui.resultTextEdit->clear();
}

void AdventOfCode::process()
{
      int currentDay = ui.dayComboBox->currentIndex() + 1;
      QStringList input = ui.inputTextEdit->toPlainText().split("\n");
      QStringList result;

      switch (currentDay) {
      case 1:
      {
            // Partie 1
            QList<int> totals;
            int currentIndex = 0;
            totals.append(0);
            foreach(const QString& line, input) {

                  if (line.isEmpty() == true) {
                        currentIndex++;
                        totals.append(0);
                        continue;
                  }

                  totals[currentIndex] += line.toInt();
            }

            QList<int>::iterator it = std::max_element(totals.begin(), totals.end());
            result.append(QString("%1").arg(*it));

            // Partie 2
            int fullTotal = *it;

            totals.removeOne(*it);
            it = std::max_element(totals.begin(), totals.end());
            fullTotal += *it;

            totals.removeOne(*it);
            it = std::max_element(totals.begin(), totals.end());
            fullTotal += *it;
            result.append(QString("%1").arg(fullTotal));
      }
      break;

      case 2:
      {
            // Partie 1
            auto dualScore = [] (QChar other, QChar me) -> int {
                  // A X : pierre
                  // B Y : papier
                  // C Z : ciseaux
                  bool win = ((me == 'X' && other == 'C') || (me == 'Y' && other == 'A') || (me == 'Z' && other == 'B'));
                  if (win == true) {
                        return 6;
                  }
                  bool null = ((me == 'X' && other == 'A') || (me == 'Y' && other == 'B') || (me == 'Z' && other == 'C'));
                  if (null == true) {
                        return 3;
                  }
                  return 0;
            };
            auto ownScore = [] (char choice) -> int {
                  // A/X : pierre
                  // B/Y : papier
                  // C/Z : ciseaux
                  switch (choice) {
                  case 'A':
                  case 'X':
                        return 1;
                  case 'B':
                  case 'Y':
                        return 2;
                  case 'C':
                  case 'Z':
                        return 3;
                  default:
                        Q_ASSERT(0);
                        return 0;
                  }
            };

            int score = 0;
            foreach(const QString& line, input) {
                  QStringList game = line.split(" ");
                  QChar other = game.at(0).at(0);
                  QChar me = game.at(1).at(0);
                  int currentScore = ownScore(me.toLatin1()) + dualScore(other, me);
                  score += currentScore;
            }
            result.append(QString("%1").arg(score));

            // Partie 2
            int score2 = 0;
            auto whatForMe = [] (char other, char endRequired) -> QChar {
                  // endRequired :
                  // X : je perds
                  // Y : match nul
                  // Z : je gagne
                  // Choix du tour :
                  // A X: pierre
                  // B Y : papier
                  // C Z : ciseaux
                  if (endRequired == 'X') {  // Je dois perdre
                        switch (other) {
                        case 'A':
                              return 'Z';
                        case 'B':
                              return 'X';
                        case 'C':
                              return 'Y';
                        }
                  }
                  else if (endRequired == 'Y') {  // Match null
                        switch (other) {
                        case 'A':
                              return 'X';
                        case 'B':
                              return 'Y';
                        case 'C':
                              return 'Z';
                        }
                  }
                  else { // Je dois gagner
                        switch (other) {
                        case 'A':
                              return 'Y';
                        case 'B':
                              return 'Z';
                        case 'C':
                              return 'X';
                        }
                  }
                  return ' ';
            };
            foreach(const QString& line, input) {
                  QStringList game = line.split(" ");
                  QChar other = game.at(0).at(0);
                  QChar endRequired = game.at(1).at(0);
                  QChar me = whatForMe(other.toLatin1(), endRequired.toLatin1());
                  int currentScore = ownScore(me.toLatin1()) + dualScore(other, me);
                  score2 += currentScore;
            }
            result.append(QString("%1").arg(score2));
      }
      break;

      case 3:
      {
            // Partie 1
            auto charScore = [](const QChar& car) -> int {
                  int currentInt = int(car.toLatin1());
                  if (car.toLower() == car) {
                        int refInt = int(QChar('a').toLatin1());
                        return currentInt - refInt + 1;
                  }
                  else {
                        int refInt = int(QChar('A').toLatin1());
                        return 26 + currentInt - refInt + 1;
                  }
                  Q_ASSERT(0);
                  return -1;
            };

            int score = 0;
            foreach(const QString & line, input) {
                  QString sacADos1 = line.left(line.count() / 2);
                  QString sacADos2 = line.right(line.count() / 2);
                  foreach(const QChar & theChar, sacADos1) {
                        if (sacADos2.contains(theChar) == true) {
                              score += charScore(theChar);
                              break;
                        }
                  }
            }
            result.append(QString("%1").arg(score));

            // Partie 2
            int score2 = 0;
            for (int i = 0; i < input.count(); i += 3) {

                  QString sacADos_1 = input.at(i);
                  QString sacADos_2 = input.at(i + 1);
                  QString sacADos_3 = input.at(i + 2);

                  foreach(const QChar & theChar1, sacADos_1) {
                        bool found2 = sacADos_2.indexOf(theChar1) >= 0;
                        if (found2 == false) {
                              continue;
                        }
                        bool found3 = sacADos_3.indexOf(theChar1) >= 0;
                        if (found3 == false) {
                              continue;
                        }
                        score2 += charScore(theChar1);
                        break;
                  }
            }
            result.append(QString("%1").arg(score2));
      }
      break;

      case 4:
      {
            // Partie 1
            int score = 0;
            foreach(const QString& line, input) {
                  QStringList ranges = line.split(",");
                  QStringList range1 = ranges.at(0).split("-");
                  QStringList range2 = ranges.at(1).split("-");
                  QPair<int, int> elfe1(range1.at(0).toInt(), range1.at(1).toInt());
                  QPair<int, int> elfe2(range2.at(0).toInt(), range2.at(1).toInt());

                  if ((elfe1.first >= elfe2.first && elfe1.second <= elfe2.second) ||
                      (elfe2.first >= elfe1.first && elfe2.second <= elfe1.second)) {
                        score++;
                  }
            }
            result.append(QString("%1").arg(score));

            // Partie 2
            int score2 = 0;
            foreach(const QString& line, input) {
                  QStringList ranges = line.split(",");
                  QStringList range1 = ranges.at(0).split("-");
                  QStringList range2 = ranges.at(1).split("-");
                  QPair<int, int> elfe1(range1.at(0).toInt(), range1.at(1).toInt());
                  QPair<int, int> elfe2(range2.at(0).toInt(), range2.at(1).toInt());

                  if (((elfe1.second >= elfe2.first) && (elfe1.second <= elfe2.second)) ||
                      ((elfe1.first >= elfe2.first) && (elfe1.first <= elfe2.second)) ||
                      ((elfe2.second >= elfe1.first) && (elfe2.second <= elfe1.second)) ||
                      ((elfe2.first >= elfe1.first) && (elfe2.first <= elfe1.second))) {
                        score2++;
                  }
            }
            result.append(QString("%1").arg(score2));
      }
      break;

      case 5:
      {
            // Partie 1
            QString result1;
            int firstMoveId = 0;
            foreach(const QString & line, input) {
                  firstMoveId++;
                  if (line.trimmed().isEmpty() == true) {
                        break;
                  }
            }
            QStringList boxesInput = input.mid(0, firstMoveId - 1);
            QStringList moves = input.mid(firstMoveId);

            int nbCols = boxesInput.last().split(" ", QString::SkipEmptyParts).count();
            boxesInput.removeLast();

            QVector<QList<QChar> > boxes;
            for (int i = 0; i < nbCols; i++) {
                  boxes.append(QList<QChar>());
            }
            int nbLinesBoxes = boxesInput.count();
            for (int i = nbLinesBoxes - 1; i >= 0; i--) {
                  QString workLine = boxesInput.at(i);
                  
                  for (int j = 0; j < nbCols; j++) {
                        int letterId = 1 + j * 4;
                        if (letterId >= workLine.count()) {
                              break;
                        }
                        QChar letter = workLine.at(letterId);
                        if (letter != ' ') {
                              boxes[j].append(letter);
                        }
                  }
            }
            QVector<QList<QChar> > boxes2 = boxes;
            foreach(const QString & line, moves) {
                  QString workLine = line;
                  workLine.replace("move", "");
                  workLine.replace("from", "");
                  workLine.replace("to", "");
                  workLine = workLine.simplified();
                  QStringList cut = workLine.split(" ");
                  int quantity = cut.at(0).toInt();
                  int from = cut.at(1).toInt() - 1;
                  int to = cut.at(2).toInt() - 1;

                  for (int k = 0; k < quantity; k++) {
                        int nbToKeep = boxes.at(from).count() - 1;
                        boxes[to].append(boxes.at(from).mid(nbToKeep));
                        boxes[from] = boxes.at(from).mid(0, nbToKeep);
                  }
            }

            for (int i = 0; i < nbCols; i++) {
                  result1 += boxes.at(i).last();
            }
            result.append(QString("%1").arg(result1));

            // Partie 2
            QString result2 = 0;
            foreach(const QString& line, moves) {
                  QString workLine = line;
                  workLine.replace("move", "");
                  workLine.replace("from", "");
                  workLine.replace("to", "");
                  workLine = workLine.simplified();
                  QStringList cut = workLine.split(" ");
                  int quantity = cut.at(0).toInt();
                  int from = cut.at(1).toInt() - 1;
                  int to = cut.at(2).toInt() - 1;

                  int nbToKeep = boxes2.at(from).count() - quantity;
                  boxes2[to].append(boxes2.at(from).mid(nbToKeep));
                  boxes2[from] = boxes2.at(from).mid(0, nbToKeep);
            }

            for (int i = 0; i < nbCols; i++) {
                  result2 += boxes2.at(i).last();
            }
            result.append(QString("%1").arg(result2));
      }
      break;

      case 6:
            break;

      case 7:
            break;

      case 8:
            break;

      case 9:
            break;

      case 10:
            break;

      case 11:
            break;

      case 12:
            break;

      case 13:
            break;

      case 14:
            break;

      case 15:
            break;

      case 16:
            break;

      case 17:
            break;

      case 18:
            break;

      case 19:
            break;

      case 20:
            break;

      case 21:
            break;

      case 22:
            break;

      case 23:
            break;

      case 24:
            break;

      case 25:
            break;
      }

      ui.resultTextEdit->setText(result.join("\n"));
}

AdventOfCode::~AdventOfCode()
{

}

} // namespace AdventOfCode
/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2012 - Emmanuel Nicolas

  GEAC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  ---

  Emmanuel Nicolas - CheckFileDialog.h

    The class CheckFileDialog defines an extension of QFileDialog in
    order to add dilters to the default Qt file dialog.

*/

#ifndef CHECKFILEDIALOG_H
#define CHECKFILEDIALOG_H

#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>

class CheckFileDialog : public QFileDialog
{
    Q_OBJECT
public:
    enum fileFilter{
        all,
        outAndLog,
        out,
        log
    };
    CheckFileDialog();
    void setMultipleFilesMode();
    void setDirectoryMode();
    bool getRecursivity();
    int getFileFilter();

private:
    QCheckBox *recursive;
    QComboBox *fileFilterBox;
    QStringList filters;
};

#endif // CHECKFILEDIALOG_H

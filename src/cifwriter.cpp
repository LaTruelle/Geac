/*
This file is part of GEAC (Gaussian ESI Automated Creator)

  GEAC - Copyright (C) 2020 - Emmanuel Nicolas

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

  Emmanuel Nicolas - CifWriter

*/

#include "cifwriter.h"
#include <QDebug>
#include <QTextStream>

CifWriter::CifWriter()
{
    // Constructor
}

void CifWriter::addFiletoList(CheckableFile file)
{
    // Add file to the list of files to include in cif file
    // TODO Checks?
    CheckableFile *newFile = new CheckableFile(file);
    files.append(newFile);
}

void CifWriter::addListofFiles(QList<CheckableFile *> list)
{
    // Add List of Files
    files.append(list);
}

void CifWriter::setOutputFile(QFile &file)
{
    // Transfer File Name
    outputFile.setFileName(file.fileName());
}

void CifWriter::createCif()
{
    // The main function that actually does the job!
    // TODO: Checks for existence of files and everything
    // Open the file
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    // Setup a QTextStream
    QTextStream out(&outputFile);
    // Add data according to requirements
    out << "Starting CIF File" << Qt::endl;

    for (int i = 0; i < files.size(); ++i) {
        // Add each file as a new cif block
        QString fileName = files.at(i)->fileName().right(
            files.at(i)->fileName().size() -
            files.at(i)->fileName().lastIndexOf("/") - 1);
        QList<QStringList> XYZCoordinates = files.at(i)->getXYZCoordinates();
        out << "data_" + fileName << Qt::endl;
        out << Qt::endl;
        out << "_cell_length_a                    1.00" << Qt::endl;
        out << "_cell_length_b                    1.00" << Qt::endl;
        out << "_cell_length_c                    1.00" << Qt::endl;
        out << "_cell_angle_alpha                90.00" << Qt::endl;
        out << "_cell_angle_beta                 90.00" << Qt::endl;
        out << "_cell_angle_gamma                90.00" << Qt::endl;
        out << "_cell_volume                      1.00" << Qt::endl;
        out << "_cell_formula_units_Z             1" << Qt::endl;
        out << Qt::endl;
        out << "loop_" << Qt::endl;
        out << "_atom_site_type_symbol" << Qt::endl;
        out << "_atom_site_fract_x" << Qt::endl;
        out << "_atom_site_fract_y" << Qt::endl;
        out << "_atom_site_fract_z" << Qt::endl;
        for (int j = 0; j < files.at(i)->getNAtoms().toInt(); ++j) {
            QStringList line = XYZCoordinates.at(j);
            QString formattedLine;
            formattedLine += line.at(0).leftJustified(7, ' ');
            formattedLine += line.at(1).rightJustified(16, ' ');
            formattedLine += line.at(2).rightJustified(16, ' ');
            formattedLine += line.at(3).rightJustified(16, ' ');
            out << formattedLine << Qt::endl;
        }
        out << Qt::endl;
        out << "# end of " + fileName << Qt::endl;
        out << Qt::endl;
    }
    out << "__ Full End " << Qt::endl;
    outputFile.close();
    QString fileName = outputFile.fileName();
    emit fileProcessed(
        fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1) +
        " written.");
}

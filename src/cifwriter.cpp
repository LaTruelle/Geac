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
    qDebug() << newFile->fileName();
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
    out << "Starting CIF File" << endl;

    for (int i = 0; i < files.size(); ++i) {
        // Add each file as a new cif block
        QString fileName = files.at(i)->fileName().right(
            files.at(i)->fileName().size() -
            files.at(i)->fileName().lastIndexOf("/") - 1);
        QList<QStringList> XYZCoordinates = files.at(i)->getXYZCoordinates();
        out << "data_" + fileName << endl;
        out << endl;
        out << "_cell_length_a                    1.00" << endl;
        out << "_cell_length_b                    1.00" << endl;
        out << "_cell_length_c                    1.00" << endl;
        out << "_cell_angle_alpha                90.00" << endl;
        out << "_cell_angle_beta                 90.00" << endl;
        out << "_cell_angle_gamma                90.00" << endl;
        out << "_cell_volume                      1.00" << endl;
        out << "_cell_formula_units_Z             1" << endl;
        out << endl;
        out << "loop_" << endl;
        out << "_atom_site_type_symbol" << endl;
        out << "_atom_site_fract_x" << endl;
        out << "_atom_site_fract_y" << endl;
        out << "_atom_site_fract_z" << endl;
        for (int j = 0; j < files.at(i)->getNAtoms().toInt(); ++j) {
            QStringList line = XYZCoordinates.at(j);
            QString formattedLine;
            formattedLine += line.at(0).leftJustified(7, ' ');
            formattedLine += line.at(1).rightJustified(16, ' ');
            formattedLine += line.at(2).rightJustified(16, ' ');
            formattedLine += line.at(3).rightJustified(16, ' ');
            out << formattedLine << endl;
        }
        out << endl;
        out << "# end of " + fileName << endl;
        out << endl;
    }
    out << "__ Full End " << endl;
    outputFile.close();
    QString fileName = outputFile.fileName();
    emit fileProcessed(
        fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1) +
        " written.");
}

#include "xyzwriter.h"

#include <QTextStream>

XYZWriter::XYZWriter()
{
    // Constructor
}

void XYZWriter::addFiletoList(CheckableFile file)
{
    // Add file to the list of files to include in xyz file
    // TODO Checks?
    CheckableFile *newFile = new CheckableFile(file);
    files.append(newFile);
}

void XYZWriter::addListofFiles(QList<CheckableFile *> list)
{
    // Add list of files
    files.append(list);
}

void XYZWriter::setOutputFile(QFile &file)
{
    // Transfer File Name
    outputFile.setFileName(file.fileName());
}

void XYZWriter::createXYZ()
{
    // The main function that actually does the job!
    // TODO: Checks for existence of files and everything
    // Open the file
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    // Setup a QTextStream
    QTextStream out(&outputFile);
    // Add data according to specifications
    for (int i = 0; i < files.size(); ++i) {
        // Add each file as a new xyz block
        // Retrieve data for current file
        QString natoms = files.at(i)->getNAtoms();
        QString fileName = files.at(i)->fileName().right(
            files.at(i)->fileName().size() -
            files.at(i)->fileName().lastIndexOf("/") - 1);
        QList<QStringList> XYZCoordinates = files.at(i)->getXYZCoordinates();
        // Write header
        out << natoms << Qt::endl;
        out << fileName << Qt::endl;
        // Write XYZ coordinates
        for (int j = 0; j < files.at(i)->getNAtoms().toInt(); ++j) {
            QStringList line = XYZCoordinates.at(j);
            QString formattedLine;
            formattedLine += line.at(0).leftJustified(7, ' ');
            formattedLine += line.at(1).rightJustified(16, ' ');
            formattedLine += line.at(2).rightJustified(16, ' ');
            formattedLine += line.at(3).rightJustified(16, ' ');
            out << formattedLine << Qt::endl;
        }
        // Jump line
        out << Qt::endl;
    }
    outputFile.close();
    QString fileName = outputFile.fileName();
    emit fileProcessed(
        fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1) +
        " written.");
}

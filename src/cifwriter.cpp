#include <QTextStream>
#include "cifwriter.h"
#include <QDebug>

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
    qDebug() << "Entering Create CIF";
    qDebug() << outputFile.fileName();
    qDebug() << "List: " + files.first()->fileName();
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
        QString fileName = files.at(i)->fileName().right(files.at(i)->fileName().size()
                                                        - files.at(i)->fileName().lastIndexOf("/")
                                                        - 1);
        QList<QStringList> XYZCoordinates = files.at(i)->getXYZCoordinates();
        out << "_file " + fileName << endl;
        out << "__ XYZ Coordinates __" << endl;
        for (int j = 0; j < files.at(i)->getNAtoms().toInt(); ++j) {
            QStringList line = XYZCoordinates.at(j);
            QString formattedLine;
            formattedLine += line.at(0).leftJustified(7,' ');
            formattedLine += line.at(1).rightJustified(16,' ');
            formattedLine += line.at(2).rightJustified(16,' ');
            formattedLine += line.at(3).rightJustified(16,' ');
            out << formattedLine << endl;
        }
        out << "__end of " + fileName << endl;
    }
    out << "__ Full End " << endl;
    outputFile.close();
    QString fileName = outputFile.fileName();
    emit fileProcessed(fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1) + " written.");
}

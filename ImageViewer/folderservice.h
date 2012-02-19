#ifndef FOLDERSERVICE_H
#define FOLDERSERVICE_H
#include <fileinfo.h>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>

class FolderService
{
private:
    QString folderPath;
    QStringList fileNameList;
    int currentIndex;
public:
    FolderService(QString path);
    QString GetNextFile();
    QString GetPreviousFile();
    QString CurrentFile();
    int CurrentFileIndex();
};

#endif // FOLDERSERVICE_H
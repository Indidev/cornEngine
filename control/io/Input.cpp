#include "Input.h"

QString Input::TAG = "control/util/Input";

Input::Input()
{
}

QHash<QString, QString> Input::loadMap(QString filepath)
{
    QHash<QString, QString> hashList;
    QString key;

    //itterate through all lines
    for (QString line: loadLines(filepath)) {
        //remove comments
        line.remove(QRegExp("//.*"));
        if (!line.trimmed().isEmpty()) {
            //split on doublepoint
            QStringList splitted = line.split(":");
            QString value("");

            //get key if present, otherwise use key from before
            if (splitted.length() >= 2) {
                key = splitted[0].trimmed();
                splitted.removeFirst();
            }

            //append to existing value if key allready exists
            if (hashList.contains(key))
                value = hashList[key];

            value += splitted[0].trimmed();

            hashList.insert(key, value);
        }
    }

    return hashList;
}

QStringList Input::listDirs(QString dirPath, QString filter)
{
    QStringList dirs;
    QDir cur(dirPath);
    if (cur.exists() && cur.isReadable()) {
        dirs.append(cur.entryList(QStringList(filter), QDir::Filter::Dirs|QDir::Filter::NoDotAndDotDot));
    } else {
        Log::e(TAG, "Could not read directory", "listDirs(QString)");
    }
    return dirs;
}

QStringList Input::listFiles(QString dirPath, QString filter)
{
    QStringList dirs;
    QDir cur(dirPath);
    if (cur.exists() && cur.isReadable()) {
        dirs.append(cur.entryList(QStringList(filter), QDir::Filter::Files));
    } else {
        Log::e(TAG, "Could not read directory", "listDirs(QString)");
    }
    return dirs;
}

QStringList Input::loadLines(QString filepath)
{
    QStringList list;

    QFile file(filepath.trimmed());
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.trimmed().startsWith("include(")) {
                list.append(loadLines(line.remove("include(").remove(")")));
            } else {
                list.append(line);
            }
        }
    } else {
        Log::e(TAG, "file(" + filepath + ") could not be loaded", "loadLines(QString)");
    }

    return list;
}

QImage Input::loadImage(QString filepath)
{
    return QImage(filepath);
}

QStringList Input::getExtensions(QString filepath)
{
    //return if no filepath is given
    if (filepath.isEmpty()) {
        Log::e(TAG, "filepath is empty!", "getExtensions(QString)");
        return QStringList();
    }

    //split folder from file
    int index = filepath.lastIndexOf("/");
    QString folderPath = index >= 0 ? filepath.left(index++) : "./";
    QString fileName = index > 0 ? filepath.right(filepath.length() - index) : filepath;

    //print folder and file as debug information
    Log::d(TAG, "Folder: " + folderPath, "getExtensions(QString)");
    Log::d(TAG, "File: " + fileName, "getExtensions(QString)");

    QDir folder(folderPath);

    //return if folder does not exist
    if (!folder.exists()) {
        Log::e(TAG, "folder(" + folderPath + ") does not exist", "getExtensions(QString)");
        return QStringList();
    }

    //return if no file is given
    if (fileName.isEmpty()) {
        Log::e(TAG, "no file given", "getExtensions(QString)");
        return QStringList();
    }

    //check if is readable
    if (!folder.isReadable()) {
        Log::e(TAG, "folder(" + folderPath + ") is unreadable", "getExtensions(QString)");
        return QStringList();
    }

    //read folder
    return folder.entryList(QStringList(fileName + ".*"), QDir::Filter::Files);
}

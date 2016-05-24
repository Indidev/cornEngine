#ifndef INPUT_H
#define INPUT_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QDir>
#include <QImage>
#include <QTextStream>
#include <QImage>

#include "control/util/Log.h"

/**
 * @brief The Input class
 * class which contains functions to read from files
 */
class Input
{
public:
    /**
     * load content of a file as a map (key: value)
     * if a value is not present, the key will be saved without a value.
     * empty lines will be skipped
     * @param filepath path of the file...
     * @return key-value hashmap
     */
    static QHash<QString, QString> loadMap(QString filepath);

    /**
     * @brief list all directories in this directory
     * @param dirPath directory to list directories of
     * @param filter e.g. map*
     * @return directories in dir
     */
    static QStringList listDirs(QString dirPath, QString filter = "*");

    /**
     * @brief list all files in this directory
     * @param dirPath directory to list files of
     * @param filter e.g. *.png
     * @return files in dir
     */
    static QStringList listFiles(QString dirPath, QString filter = "*");

    /**
     * load all lines of a file
     * @param filepath path of the file...
     * @return content of file as list
     */
    static QStringList loadLines(QString filepath);

    /**
     * @brief loadImage loads an image
     * @param filepath path the the image file
     * @return loaded image or null if image could not be loaded
     */
    static QImage loadImage(QString filepath);

    /**
     * @brief getFilename get all files with that given name
     * @param name folder/.../filename without extension
     * @return list of entries with extension
     */
    static QStringList getExtensions(QString filepath);

private:
    static QString TAG;
    Input();

};

#endif // INPUT_H

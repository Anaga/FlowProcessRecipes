#ifndef RECIPESREADER_H
#define RECIPESREADER_H

#include <QXmlStreamReader>
#include <QIcon>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class RecipesReader
{
public:
    RecipesReader(QTreeWidget *treeWidget);
    bool readFile(QIODevice *device);
    QString errorString() const;

private:
    void readXML();
    void readTitle(QTreeWidgetItem *item);
    void readSeparator(QTreeWidgetItem *item);
    void readFolder(QTreeWidgetItem *item);
    void readBookmark(QTreeWidgetItem *item);

    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);

    QXmlStreamReader xml;
    QTreeWidget *treeWidget;

    QIcon folderIcon;
    QIcon bookmarkIcon;
};

#endif // RECIPESREADER_H

#include <QtGui>
#include "recipesreader.h"

RecipesReader::RecipesReader(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
}

bool RecipesReader::readFile(QIODevice *device)
{
    xml.setDevice(device);

    if (xml.readNextStartElement()) {
        if (xml.name() == "xml" && xml.attributes().value("version") == "1.0")
            readXML();
        else
            xml.raiseError(QObject::tr("The file is not an XML version 1.0 file."));
    }

    return !xml.error();
}

QString RecipesReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

void RecipesReader::readXML()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "xml");

    while (xml.readNextStartElement()) {
        if (xml.name() == "folder")
            readFolder(0);
        else if (xml.name() == "bookmark")
            readBookmark(0);
        else if (xml.name() == "separator")
            readSeparator(0);
        else
            xml.skipCurrentElement();
    }
}

void RecipesReader::readTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "title");

    QString title = xml.readElementText();
    item->setText(0, title);
}

void RecipesReader::readSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "separator");

    QTreeWidgetItem *separator = createChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}

void RecipesReader::readFolder(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "folder");

    QTreeWidgetItem *folder = createChildItem(item);
    bool folded = (xml.attributes().value("folded") != "no");
    treeWidget->setItemExpanded(folder, !folded);

    while (xml.readNextStartElement()) {
        if (xml.name() == "title")
            readTitle(folder);
        else if (xml.name() == "folder")
            readFolder(folder);
        else if (xml.name() == "bookmark")
            readBookmark(folder);
        else if (xml.name() == "separator")
            readSeparator(folder);
        else
            xml.skipCurrentElement();
    }
}

void RecipesReader::readBookmark(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "bookmark");

    QTreeWidgetItem *bookmark = createChildItem(item);
    bookmark->setFlags(bookmark->flags() | Qt::ItemIsEditable);
    bookmark->setIcon(0, bookmarkIcon);
    bookmark->setText(0, QObject::tr("Unknown title"));
    bookmark->setText(1, xml.attributes().value("href").toString());

    while (xml.readNextStartElement()) {
        if (xml.name() == "title")
            readTitle(bookmark);
        else
            xml.skipCurrentElement();
    }
}

QTreeWidgetItem *RecipesReader::createChildItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem;
    if (item) {
        childItem = new QTreeWidgetItem(item);
    } else {
        childItem = new QTreeWidgetItem(treeWidget);
    }
    childItem->setData(0, Qt::UserRole, xml.name().toString());
    return childItem;
}

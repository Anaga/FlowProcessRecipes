#ifndef RECIPESWRITER_H
#define RECIPESWRITER_H

#include <QXmlStreamWriter>
#include <QTreeWidget>
#include <QTreeWidgetItem>


class RecipesWriter
{
public:
   RecipesWriter(QTreeWidget *treeWidget);
   bool writeFile(QIODevice *device);

private:
   void writeItem(QTreeWidgetItem *item);
   QXmlStreamWriter xml;
   QTreeWidget *treeWidget;
};
#endif // RECIPESWRITER_H

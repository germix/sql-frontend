#ifndef SQLHIGHLIGHTER_H
#define SQLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
class SqlHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SqlHighlighter(QTextDocument* doc);
    ~SqlHighlighter();
public:
    void highlightBlock(const QString& text);
};
#endif // SQLHIGHLIGHTER_H

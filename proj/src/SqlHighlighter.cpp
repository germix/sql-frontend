#include "SqlHighlighter.h"

SqlHighlighter::SqlHighlighter(QTextDocument* doc) : QSyntaxHighlighter(doc)
{
}
SqlHighlighter::~SqlHighlighter()
{

}
void SqlHighlighter::highlightBlock(const QString& text)
{
    enum
    {
        NORMAL_STATE,
        INSIDE_STRING_1,
        INSIDE_STRING_2,
    };
    QColor colorReservedWord = Qt::blue;
    QColor colorInsideString = QColor(255, 0, 255);
    int state = previousBlockState();
    int start = 0;
    // https://dev.mysql.com/doc/refman/8.0/en/keywords.html
    static const char* reservedWords[] =
    {
        "AND",
        "CREATE",
        "FROM",
        "OR",
        "SELECT",
        "WHERE"
    };

    for (int i = 0; i < text.length(); ++i) {

        if(state == INSIDE_STRING_1)
        {
            if(text.mid(i, 1) == "\'")
            {
                state = NORMAL_STATE;
                setFormat(start, i - start + 1, colorInsideString);
            }
        }
        else if(state == INSIDE_STRING_2)
        {
            if(text.mid(i, 1) == "\`")
            {
                state = NORMAL_STATE;
                setFormat(start, i - start + 1, colorInsideString);
            }
        }
        else
        {
            if(text.mid(i, 1) == "\'")
            {
                start = i;
                state = INSIDE_STRING_1;
            }
            else if(text.mid(i, 1) == "\'")
            {
                start = i;
                state = INSIDE_STRING_2;
            }
            else
            {
                bool found = false;
                for(int j = 0; j < sizeof(reservedWords)/sizeof(const char*); j++)
                {
                    QString s = reservedWords[j];
                    if(text.mid(i, s.size()) == s)
                    {
                        found = true;
                        setFormat(i, s.size(), colorReservedWord);
                        i += s.size();
                        break;
                    }
                }
            }
        }
    }
    if(state == INSIDE_STRING_1)
        setFormat(start, text.length() - start, colorInsideString);

    setCurrentBlockState(state);
}

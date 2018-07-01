#ifndef MARKDOWN_HIGHLIGHTER_H
#define MARKDOWN_HIGHLIGHTER_H
#include <QSyntaxHighlighter>

#include <qtextedit.h>

#include <qtextdocument.h>

#include <QTextCharFormat>

#include <qtextcursor.h>

#include <qhash.h>

#include <qvector.h>

#include <qregexp.h>

#include <qcolor.h>

#include <qstring.h>

class markdown_highlighter : public QSyntaxHighlighter

{

public:

    markdown_highlighter(QTextEdit *parent = 0);

    void highlightBlock(const QString &text);

    void SetColorText(const QString &str, const QColor &color);

    void clearRules();

private:

     struct HighlightingRule

      {

          QRegExp pattern;

          QTextCharFormat format;

      };

      QVector<HighlightingRule> highlightingRules;

};

#endif // MARKDOWN_HIGHLIGHTER_H

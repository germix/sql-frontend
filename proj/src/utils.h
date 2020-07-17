#ifndef UTILS_H
#define UTILS_H
#include <QString>

extern QString mysql;

QString exec_sql(const QString& sql, QString* err = 0);

#endif // UTILS_H

#include "LasFileParser.hpp"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTextStream>

// Everybody stand back! I know regular expressions
#include <QSharedPointer>
#include <QtCore/QRegExp>

#include "LasFileParser.hpp"

#include <Uni/Logging/Logging>

namespace Geo {
namespace Import {
QSharedPointer<LasFile>
LasFileParser::
parse(const QString fileName) {
  _lines.clear();
  _wrap    = false;
  _version = QString();

  // result
  QSharedPointer<LasFile> lasFile(new LasFile());

  if (!QFile::exists(fileName)) {
    return lasFile;
    Q_ASSERT(false);
  }

  QFileInfo fileInfo(fileName);

  lasFile->fileName = fileInfo.fileName();

  QFile inputFile(fileName);

  if (inputFile.open(QIODevice::ReadOnly)) {
    QTextStream in(&inputFile);

    while (!in.atEnd()) {
      QString line = in.readLine().trimmed();

      // filter comments
      if (!line.startsWith("#"))
        _lines.append(line);
    }
  }

  inputFile.close();

  // now work with lines and close the file
  parseLines(lasFile);

  return lasFile;
}

void
LasFileParser::
parseLines(QSharedPointer<LasFile>& lasFile) {
  int i = 0;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith(QString::fromUtf8("~V")))
      parseVersionSection(lasFile, i);
    else if (line.startsWith(QString::fromUtf8("~W")))
      parseWellInformationSection(lasFile, i);
    else if (line.startsWith(QString::fromUtf8("~C")))
      parseLogInformationSection(lasFile, i);
    else if (line.startsWith(QString::fromUtf8("~P")))
      parseParameterInformationSection(lasFile, i);
    else if (line.startsWith(QString::fromUtf8("~O")))
      parseOtherInformationSection(lasFile, i);
    else if (line.startsWith(QString::fromUtf8("~A")))
      parseAsciiLogDataSection(lasFile, i);

    ++i;
  }
}

bool
LasFileParser::
parseVersionSection(QSharedPointer<LasFile>& lasFile,
                    int&                     lineNumber) {
  int& i = lineNumber;

  /*
   *  this section must contain following information:
   *  VERS. 2.0 : CWLS LOG ASCII STANDARD - VERSION 2.0
   *
   *  Refers to which version of Las is used.
   *
   *  and
   *
   *  WRAP. YES : Multiple lines per depth step
   *
   *  or
   *
   *  WRAP. NO : One line per depth step
   */

  // next line
  QString line = _lines[++i];

  // QRegExp reVersion("(\\d\\.\\d+)");
  QRegExp reVersion("(1\\.2|2\\.0)");

  line = _lines[i];

  int pos = reVersion.indexIn(line);

  if (pos > -1)
    _version = reVersion.cap(1);

  else
    return false;

  // next line with WRAP parameter
  line = _lines[++i];

  QRegExp reWrap("(YES|NO)");

  pos = reWrap.indexIn(line);

  // have information about warpping
  if (pos > -1) {
    QString s = reWrap.cap(1);
    _wrap = s == "YES" ? true : false;
  } else
    return false;

  return true;
}

void
LasFileParser::
parseWellInformationSection(QSharedPointer<LasFile>& lasFile, int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile->wellInformation.entries.clear();

  // STRT.M        583.0:
  QRegExp reStart("(STRT)( *\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reStop("(STOP)( *\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reStep("(STEP)( *\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reNULL("(NULL)( *\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  //  WELL.                WELL:   4832/116
  // QRegExp reWell("(WELL *)(:)( *.*$)");
  QRegExp reWell("(WELL)(\\. )(.+)(:)(.*$)");

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //  name .units   name:value
  // QRegExp reRestEntries("(^.+)( *\\.[^ ]*)(.+)( *:)( *.*$)");
  QRegExp reRestEntries("(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

  reRestEntries.setMinimal(true);

  // next line
  ++i;

  while (i < _lines.size()) {
    QString line = _lines[i];

    // if next section has started
    if (line.startsWith("~")) {
      --i;
      return;
    }

    if (reStart.indexIn(line) >= 0) {
      QString all     = reStart.cap(0);
      QString strt    = reStart.cap(1);
      QString units   = reStart.cap(2);
      QString value   = reStart.cap(3).trimmed();
      QString comment = reStart.cap(5);

      bool ok;
      lasFile->wellInformation.start = value.toDouble(&ok);
    } else if (reStop.indexIn(line) >= 0) {
      QString all     = reStop.cap(0);
      QString strt    = reStop.cap(1);
      QString units   = reStop.cap(2).trimmed().remove(0, 1);
      QString value   = reStop.cap(3).trimmed();
      QString comment = reStop.cap(5);

      bool ok;
      lasFile->wellInformation.stop = value.toDouble(&ok);
    } else if (reStep.indexIn(line) >= 0) {
      QString all     = reStep.cap(0);
      QString strt    = reStep.cap(1);
      QString units   = reStep.cap(2).trimmed().remove(0, 1);
      QString value   = reStep.cap(3).trimmed();
      QString comment = reStep.cap(5);

      bool ok;
      lasFile->wellInformation.step  = value.toDouble(&ok);
      lasFile->wellInformation.units = units;
    } else if (reNULL.indexIn(line) >= 0) {
      QString all     = reNULL.cap(0);
      QString strt    = reNULL.cap(1);
      QString units   = reNULL.cap(2).trimmed().remove(0, 1);
      QString value   = reNULL.cap(3).trimmed();
      QString comment = reNULL.cap(5);

      bool ok;
      lasFile->wellInformation.nullValue = value.toDouble(&ok);
    } else if (reWell.indexIn(line) >= 0) {
      QString all = reWell.cap(0);

      QString well  = reWell.cap(3).trimmed();
      QString value = reWell.cap(5).trimmed();

      if (_version == "1.2")
        lasFile->wellInformation.wellName = value;
      else if (_version == "2.0")
        lasFile->wellInformation.wellName = well;
    }
    // all the rest fields
    else if (reRestEntries.indexIn(line) >= 0) {
      // QRegExp reRestEntries("(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

      // name .units   name:value
      LasFile::WellInformationEntry entry;

      QString all = reRestEntries.cap(0);

      QString mnem = reRestEntries.cap(1).trimmed();
      entry.units = reRestEntries.cap(2).trimmed().remove(0, 1);

      if (_version == "1.2") {
        entry.name = reRestEntries.cap(3).trimmed();
        entry.name.chop(1);
        entry.name  = entry.name.trimmed();
        entry.value = reRestEntries.cap(4).trimmed();
      } else if (_version == "2.0") {
        entry.name  = reRestEntries.cap(4).trimmed();
        entry.value = reRestEntries.cap(3).trimmed();
        entry.value.chop(1);
        entry.value = entry.value.trimmed();
      }

      lasFile->wellInformation.entries[mnem] = entry;
    }

    ++i;
  }
}

void
LasFileParser::
parseLogInformationSection(QSharedPointer<LasFile>& lasFile, int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile->logInformation.clear();

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //                     name .units   name:value
  QRegExp reLogInfoEntries("(^.+)(\\.[^ ]*)(.+)( *:)( *.*$)");

  // next line
  ++i;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith("~")) {
      --i;
      return;
    }

    // all the rest fields
    if (reLogInfoEntries.indexIn(line) >= 0) {
      // name .units   name:value
      LasFile::LogInformationEntry entry;

      QString all = reLogInfoEntries.cap(0);

      QString mnem = reLogInfoEntries.cap(1).trimmed();
      entry.units = reLogInfoEntries.cap(2).trimmed().remove(0, 1);
      entry.code  = reLogInfoEntries.cap(3).trimmed();
      // cap(4) == ":"
      entry.description = reLogInfoEntries.cap(5).trimmed();

      lasFile->logInformation[mnem] = entry;
    }

    ++i;
  }
}

void
LasFileParser::
parseParameterInformationSection(QSharedPointer<LasFile>& lasFile, int& lineNumber) {
  //
  Q_UNUSED(lineNumber);
}

void
LasFileParser::
parseOtherInformationSection(QSharedPointer<LasFile>& lasFile, int& lineNumber) {
  //
  Q_UNUSED(lineNumber);
}

void
LasFileParser::
parseAsciiLogDataSection(QSharedPointer<LasFile>& lasFile, int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile->data.clear();

  for (auto entryKey : lasFile->logInformation.keys())
    lasFile->data[entryKey] = QVector<double>();

  // corresponds to any number of form [-]333.566
  QRegExp reNumValue("(-?\\d+\\.\\d+)");

  const int numberOfMnemonics  = lasFile->data.size();
  int       currentMnemonicNum = 0;

  // next line
  ++i;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith("~")) {
      --i;
      return;
    }

    // parse array
    int pos = 0;

    while ((pos = reNumValue.indexIn(line, pos)) != -1) {
      {
        // select next key
        QString key = lasFile->data.keys()[currentMnemonicNum];

        QString value = reNumValue.cap(1);
        double  valueDouble; bool ok;
        valueDouble = value.toDouble(&ok);

        lasFile->data[key].append(valueDouble);

        currentMnemonicNum = (currentMnemonicNum + 1) % numberOfMnemonics;
      }

      pos += reNumValue.matchedLength();
    }

    ++i;
  }
}
}
}

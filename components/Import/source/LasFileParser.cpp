#include "LasFileParser.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>

// Everybody stand back! I know regular expressions
#include <QtCore/QRegExp>

#include "LasFileParser.hpp"

#include "Auxiliary/ExecutionControl.hpp"

namespace Geo {
namespace Import {
LasFile
LasFileParser::
parse(const QString fileName) {
  if (!QFile::exists(fileName))
    return LasFile();

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
  parseLines();

  return lasFile;
}

void
LasFileParser::
parseLines() {
  int i = 0;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith(QString::fromUtf8("~V")))
      parseVersionSection(i);
    else if (line.startsWith(QString::fromUtf8("~W")))
      parseWellInformationSection(i);
    else if (line.startsWith(QString::fromUtf8("~C")))
      parseCurveInformationSection(i);
    else if (line.startsWith(QString::fromUtf8("~P")))
      parseParameterInformationSection(i);
    else if (line.startsWith(QString::fromUtf8("~O")))
      parseOtherInformationSection(i);
    else if (line.startsWith(QString::fromUtf8("~A")))
      parseAsciiLogDataSection(i);

    ++i;
  }
}

bool
LasFileParser::
parseVersionSection(int& lineNumber) {
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
parseWellInformationSection(int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile.wellInformation.entries.clear();

  // STRT.M        583.0:
  QRegExp reStart("(STRT)(\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reStop("(STOP)(\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reStep("(STEP)(\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  QRegExp reNULL("(NULL)(\\..+ )(-?\\d+\\.\\d+)( *:)( *.*$)");

  //  WELL.                WELL:   4832/116
  // QRegExp reWell("(WELL *)(:)( *.*$)");
  QRegExp reWell("(WELL)(\\. )(.+)(:)(.*$)");

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //  name .units   name:value
  QRegExp reRestEntries("(^.+)(\\.[^ ]*)(.+)( *:)( *.*$)");

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
      QString value   = reStart.cap(3);
      QString comment = reStart.cap(5);

      bool ok;
      lasFile.wellInformation.start = value.toDouble(&ok);
    } else if (reStop.indexIn(line) >= 0) {
      QString all     = reStop.cap(0);
      QString strt    = reStop.cap(1);
      QString units   = reStop.cap(2);
      QString value   = reStop.cap(3);
      QString comment = reStop.cap(5);

      bool ok;
      lasFile.wellInformation.stop = value.toDouble(&ok);
    } else if (reStep.indexIn(line) >= 0) {
      QString all     = reStep.cap(0);
      QString strt    = reStep.cap(1);
      QString units   = reStep.cap(2);
      QString value   = reStep.cap(3);
      QString comment = reStep.cap(5);

      bool ok;
      lasFile.wellInformation.step  = value.toDouble(&ok);
      lasFile.wellInformation.units = units;
    } else if (reNULL.indexIn(line) >= 0) {
      QString all     = reNULL.cap(0);
      QString strt    = reNULL.cap(1);
      QString units   = reNULL.cap(2);
      QString value   = reNULL.cap(3);
      QString comment = reNULL.cap(5);

      bool ok;
      lasFile.wellInformation.nullValue = value.toDouble(&ok);
    } else if (reWell.indexIn(line) >= 0) {
      QString all = reWell.cap(0);

      QString well  = reWell.cap(3).trimmed();
      QString value = reWell.cap(5).trimmed();

      if (_version == "1.2")
        lasFile.wellInformation.wellName = value;
      else if (_version == "2.0")
        lasFile.wellInformation.wellName = well;
    }
    // all the rest fields
    else if (reRestEntries.indexIn(line) >= 0) {
      // name .units   name:value
      LasFile::WellInformationEntry entry;

      QString all = reRestEntries.cap(0);

      QString mnem = reRestEntries.cap(1).trimmed();
      entry.units = reRestEntries.cap(2).trimmed().remove(0, 1);

      if (_version == "1.2") {
        entry.name  = reRestEntries.cap(3).trimmed();
        entry.value = reRestEntries.cap(5).trimmed();
      } else if (_version == "2.0") {
        entry.name  = reRestEntries.cap(5).trimmed();
        entry.value = reRestEntries.cap(3).trimmed();
      }

      // lasFile.wellInformation.wellName = well;

      lasFile.wellInformation.entries[mnem] = entry;
    }

    ++i;
  }
}

void
LasFileParser::
parseCurveInformationSection(int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile.curveInformation.clear();

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //                     name .units   name:value
  QRegExp reCurveInfoEntries("(^.+)(\\.[^ ]*)(.+)( *:)( *.*$)");

  // next line
  ++i;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith("~")) {
      --i;
      return;
    }

    // all the rest fields
    if (reCurveInfoEntries.indexIn(line) >= 0) {
      // name .units   name:value
      LasFile::CurveInformationEntry entry;

      QString all = reCurveInfoEntries.cap(0);

      QString mnem = reCurveInfoEntries.cap(1).trimmed();
      entry.units = reCurveInfoEntries.cap(2).trimmed().remove(0, 1);
      entry.code  = reCurveInfoEntries.cap(3).trimmed();
      // cap(4) == ":"
      entry.description = reCurveInfoEntries.cap(5).trimmed();

      lasFile.curveInformation[mnem] = entry;
    }

    ++i;
  }
}

void
LasFileParser::
parseParameterInformationSection(int& lineNumber) {
  //
  Q_UNUSED(lineNumber);
}

void
LasFileParser::
parseOtherInformationSection(int& lineNumber) {
  //
  Q_UNUSED(lineNumber);
}

void
LasFileParser::
parseAsciiLogDataSection(int& lineNumber) {
  int& i = lineNumber;

  // clear old values
  lasFile.data.clear();

  for (auto entryKey : lasFile.curveInformation.keys())
    lasFile.data[entryKey] = QVector<double>();

  // corresponds to any number of form [-]333.566
  QRegExp reNumValue("(-?\\d+\\.\\d+)");

  const int numberOfMnemonics  = lasFile.data.size();
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
        QString key = lasFile.data.keys()[currentMnemonicNum];

        QString value = reNumValue.cap(1);
        double  valueDouble; bool ok;
        valueDouble = value.toDouble(&ok);

        lasFile.data[key].append(valueDouble);

        currentMnemonicNum = (currentMnemonicNum + 1) % numberOfMnemonics;
      }

      pos += reNumValue.matchedLength();
    }

    ++i;
  }
}
}
}

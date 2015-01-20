#include "LasFileParser.hpp"
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTextStream>

#include <iostream>

// Everybody stand back! I know regular expressions
#include <QSharedPointer>
#include <QtCore/QRegExp>

#include "LasFileParser.hpp"

#include <Uni/Logging/Logging>

using Geo::Import::LasFile;
using Geo::Import::LasFileParser;

QSharedPointer<LasFile>
LasFileParser::
parse(const QString fileName)
{
  _lines.clear();
  _wrap    = false;
  _version = 0;

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
parseLines(QSharedPointer<LasFile>& lasFile)
{
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
                    int&                     lineNumber)
{
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

  if (reVersion.indexIn(line) >= 0) {
    auto s = reVersion.cap(1).trimmed();

    if (s == "1.2")
      _version = 12;
    else if (s == "2.0")
      _version = 20;
  } else
    return false;

  // next line with WRAP parameter
  line = _lines[++i];

  QRegExp reWrap("(YES|NO)");

  // have information about warpping
  if (reWrap.indexIn(line) >= 0) {
    QString s = reWrap.cap(1);
    _wrap = s == "YES" ? true : false;
  } else
    return false;

  return true;
}


void
LasFileParser::
parseWellInformationSection(QSharedPointer<LasFile>& lasFile, int& lineNumber)
{
  int& i = lineNumber;

  // clear old values
  lasFile->wellInformation.clear();

  // %1 defines a number format or just any symbols before the last ":"
  // %2 defines the field name ("WELL", "START");
  const QString baseField("(%2 *)(\\.[^ ]*)( %1)(:.*$)");

  const QString numericWord("*-?\\d*\\.\\d+.*");

  const QString nonNumericWord(".*");

  const QString numericalField(baseField.arg(numericWord));

  // STRT.M        583.0:
  QRegExp reStart(numericalField.arg("STRT"));

  QRegExp reStop(numericalField.arg("STOP"));

  QRegExp reStep(numericalField.arg("STEP"));

  QRegExp reNull(numericalField.arg("NULL"));

  //  WELL.                WELL:   4832/116
  const QString specificField(baseField.arg(nonNumericWord));

  QRegExp reWell(specificField.arg("WELL"));

  QRegExp reComp(specificField.arg("COMP"));

  QRegExp reServiceComp(specificField.arg("SRVC"));

  QRegExp reField(specificField.arg("FLD"));

  QRegExp reLocation(specificField.arg("LOC"));

  QRegExp reDate(specificField.arg("DATE"));

  QRegExp reCountry(specificField.arg("CTRY"));

  QRegExp reState(specificField.arg("STAT"));

  QRegExp reCounty(specificField.arg("CNTY"));

  QRegExp reProvince(specificField.arg("PROV"));

  QRegExp reAPI(specificField.arg("API"));

  QRegExp reUWI(specificField.arg("UWI"));

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //  name .units   name:value
  QRegExp reRestEntries(specificField.arg("^[^ ]+"));

  // reRestEntries.setMinimal(true);

  // next line
  ++i;

  // function for addressing results of RegExp matching
  auto selectValue =
    [&](QRegExp& re) {
      QString s1 = re.cap(3).trimmed();

      // std::cout << "S1 " << s1.toLocal8Bit().data()
      // <<
      // std::endl;

      QString s2 =
        re.cap(4).trimmed().remove(0,
                                   1); s2 =
        s2.trimmed();

      // std::cout << "S2 " << s2.toLocal8Bit().data()
      // <<
      // std::endl;

      QString result;

      if (_version == 12)
        result = s2;
      else if (_version == 20)
        result = s1;

      return result;
    };

  // function for addressing results of "floating point"
  // RegExp matching
  auto selectNumericalValue =
    [](QRegExp& re) {
      QString value = re.cap(3).trimmed();

      bool ok;
      return value.toDouble(&ok);
    };

  auto selectNumericalUnits =
    [](QRegExp& re) {
      QString units =
        re.cap(2).trimmed().remove(0, 1);

      return units;
    };

  while (i < _lines.size()) {
    QString line = _lines[i];

    // if next section has started
    if (line.startsWith("~")) {
      --i;
      return;
    }

    // for less typing
    auto& lasRequired = lasFile->lasRequired;

    auto& logMetrics = lasFile->logMetrics;

    if (reStart.indexIn(line) >= 0)
      logMetrics.start = selectNumericalValue(reStart);
    else if (reStop.indexIn(line) >= 0)
      logMetrics.stop = selectNumericalValue(reStop);
    else if (reStep.indexIn(line) >= 0) {
      logMetrics.step  = selectNumericalValue(reStep);
      logMetrics.units = selectNumericalUnits(reStep);
    } else if (reNull.indexIn(line) >= 0)
      logMetrics.nullValue =
        selectNumericalValue(reNull);
    else if (reWell.indexIn(line) >= 0) {
      std::cout << "WELL " << std::endl;
      lasRequired.wellName = selectValue(reWell);
    } else if (reComp.indexIn(line) >= 0)
      lasRequired.company = selectValue(reComp);
    else if (reServiceComp.indexIn(line) >= 0)
      lasRequired.serviceCompany =
        selectValue(reServiceComp);
    else if (reField.indexIn(line) >= 0)
      lasRequired.field = selectValue(reField);
    else if (reLocation.indexIn(line) >= 0)
      lasRequired.location = selectValue(reLocation);
    else if (reDate.indexIn(line) >= 0)
      lasRequired.date = selectValue(reDate);
    else if (reCountry.indexIn(line) >= 0)
      lasRequired.country = selectValue(reCountry);
    else if (reState.indexIn(line) >= 0)
      lasRequired.state = selectValue(reState);
    else if (reCounty.indexIn(line) >= 0)
      lasRequired.county = selectValue(reCounty);
    else if (reProvince.indexIn(line) >= 0)
      lasRequired.province = selectValue(reProvince);
    else if (reAPI.indexIn(line) >= 0)
      lasRequired.api = selectValue(reAPI);
    else if (reUWI.indexIn(line) >= 0)
      lasRequired.uwi = selectValue(reUWI);
    // all the rest fields
    else if (reRestEntries.indexIn(line) >= 0) {
      // QRegExp reRestEntries("(^[^ ]+ *)(\\.[^ ]*)(
      // *.* *:)( *.*$)");

      // name .units   name:value
      LasFile::WellInformationEntry entry;

      QString all = reRestEntries.cap(0);

      QString name = reRestEntries.cap(1).trimmed();
      entry.units =
        reRestEntries.cap(2).trimmed().remove(0, 1);

      if (_version == 12) {
        entry.description =
          reRestEntries.cap(3).trimmed();
        entry.description.chop(1);
        entry.description = entry.description.trimmed();
        entry.value       =
          reRestEntries.cap(4).trimmed();
      } else if (_version == 20) {
        entry.description =
          reRestEntries.cap(4).trimmed();
        entry.value =
          reRestEntries.cap(3).trimmed();
        entry.value.chop(1);
        entry.value = entry.value.trimmed();
      }

      lasFile->wellInformation[name] = entry;
    }

    ++i;
  }
}


void
LasFileParser::
parseLogInformationSection(QSharedPointer<LasFile>&
                           lasFile, int& lineNumber)
{
  int& i = lineNumber;

  // clear old values
  lasFile->logInformation.clear();

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //                     name .units   :value
  QRegExp reLogInfoEntries(
    "(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

  // QRegExp reLogInfoEntries("(^.+)(\\.[^ ]*)(.+)(
  // *:)( *.*$)");

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

      QString mnem =
        reLogInfoEntries.cap(1).trimmed();
      entry.units =
        reLogInfoEntries.cap(2).trimmed().remove(0,
                                                 1);

      entry.code = reLogInfoEntries.cap(3).trimmed();

      entry.description =
        reLogInfoEntries.cap(4).trimmed();

      lasFile->logInformation[mnem] = entry;
    }

    ++i;
  }
}


void
LasFileParser::
parseParameterInformationSection(QSharedPointer<
                                   LasFile>& lasFile,
                                 int&
                                 lineNumber)
{
  int& i = lineNumber;

  // clear old values
  lasFile->parameterInformation.clear();

  QRegExp reParameterInformation(
    "(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

  // next line
  ++i;

  while (i < _lines.size()) {
    QString line = _lines[i];

    if (line.startsWith("~")) {
      --i;
      return;
    }

    // all the rest fields
    if (reParameterInformation.indexIn(line) >= 0) {
      // name .units   name:value
      LasFile::ParameterInformationEntry entry;

      QString all = reParameterInformation.cap(0);

      entry.name =
        reParameterInformation.cap(1).trimmed();
      entry.units =
        reParameterInformation.cap(2).trimmed().remove(
          0, 1);

      entry.value =
        reParameterInformation.cap(3).trimmed();
      entry.value.chop(1);
      entry.value = entry.value.trimmed();

      entry.description =
        reParameterInformation.cap(4).trimmed();

      lasFile->parameterInformation[entry.name] =
        entry;
    }

    ++i;
  }
}


void
LasFileParser::
parseOtherInformationSection(QSharedPointer<LasFile>&
                             lasFile,
                             int& lineNumber)
{
  //
  Q_UNUSED(lineNumber);
}


void
LasFileParser::
parseAsciiLogDataSection(QSharedPointer<LasFile>&
                         lasFile, int& lineNumber)
{
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

    while ((pos =
              reNumValue.indexIn(line, pos)) != -1) {
      {
        // select next key
        QString key =
          lasFile->data.keys()[currentMnemonicNum];

        QString value = reNumValue.cap(1);
        double  valueDouble; bool ok;
        valueDouble = value.toDouble(&ok);

        lasFile->data[key].append(valueDouble);

        currentMnemonicNum =
          (currentMnemonicNum +
           1) % numberOfMnemonics;
      }

      pos += reNumValue.matchedLength();
    }

    ++i;
  }
}

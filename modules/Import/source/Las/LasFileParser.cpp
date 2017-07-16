#include "LasFileParser.hpp"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>
#include <QtCore/QMap>

// Everybody stand back! I know regular expressions

#include <QtCore/QRegExp>
#include <QtCore/QRegularExpression>

#include "LasFileParser.hpp"

#include <utility>
#include <array>

using Geo::Import::LasFile;
using Geo::Import::LasFileParser;

std::shared_ptr<LasFile>
LasFileParser::
parse(QString const & fileName)
{
  _lines.clear();
  _wrap    = false;
  _version = 0;

  // result
  std::shared_ptr<LasFile> lasFile(new LasFile());

  if (!QFile::exists(fileName))
  {
    return lasFile;
    Q_ASSERT(false);
  }

  QFileInfo fileInfo(fileName);

  lasFile->fileName = fileInfo.fileName();

  QFile inputFile(fileName);

  if (inputFile.open(QIODevice::ReadOnly))
  {
    QTextStream in(&inputFile);

    while (!in.atEnd())
    {
      QString line = in.readLine().trimmed();

      // filter comments
      if (!line.startsWith("#"))
        _lines.push_back(std::move(line));
    }
  }

  inputFile.close();

  // now work with lines and close the file
  parseLines(lasFile);

  return lasFile;
}


void
LasFileParser::
parseLines(std::shared_ptr<LasFile>& lasFile)
{
  std::size_t i = 0;

  while (i < _lines.size())
  {
    QString line = _lines[i];

    if (line.startsWith(QStringLiteral("~V")))
      parseVersionSection(lasFile, i);
    else if (line.startsWith(QStringLiteral("~W")))
      parseWellInformationSection(lasFile, i);
    else if (line.startsWith(QStringLiteral("~C")))
      parseLogInformationSection(lasFile, i);
    else if (line.startsWith(QStringLiteral("~P")))
      parseParameterInformationSection(lasFile, i);
    else if (line.startsWith(QStringLiteral("~O")))
      parseOtherInformationSection(lasFile, i);
    else if (line.startsWith(QStringLiteral("~A")))
      parseAsciiLogDataSection(lasFile, i);

    ++i;
  }
}


bool
LasFileParser::
parseVersionSection(std::shared_ptr<LasFile>& lasFile,
                    std::size_t & lineNumber)
{
  std::size_t & i = lineNumber;

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

  // QRegularExpression reVersion("(\\d\\.\\d+)");
  QRegularExpression regVersion("(1\\.2|2\\.0)");

  line = _lines[i];

  QRegularExpressionMatch m = regVersion.match(line);

  if (m.hasMatch())
  {
    auto s = m.captured(1).trimmed();

    if (s == "1.2")
      _version = 12;
    else if (s == "2.0")
      _version = 20;
  }
  else
    return false;

  // next line with WRAP parameter
  line = _lines[++i];

  QRegularExpression regWrap("(YES|NO)");

  m = regWrap.match(line);

  // have information about warpping
  if (m.hasMatch())
  {
    QString s = m.captured(1);
    _wrap = s == "YES" ? true : false;
  }
  else
    return false;

  return true;
}


void
LasFileParser::
parseWellInformationSection(std::shared_ptr<LasFile>& lasFile, std::size_t & lineNumber)
{
  std::size_t & i = lineNumber;

  // clear old values
  lasFile->wellInformation.clear();

  // %1 defines a number format or just any symbols before the last ":"
  // %2 defines the field name ("WELL", "START");
  QString const baseField("(%2 *)(\\.[^ ]*)( %1)(:.*$)");

  QString const numericWord("*-?\\d*\\.\\d+.*");

  QString const nonNumericWord(".*");

  QString const numericalField(baseField.arg(numericWord));

  // STRT.M        583.0:
  QRegularExpression reStart(numericalField.arg("STRT"));

  QRegularExpression reStop(numericalField.arg("STOP"));

  QRegularExpression reStep(numericalField.arg("STEP"));

  QRegularExpression reNull(numericalField.arg("NULL"));

  //  WELL.                WELL:   4832/116
  QString const specificField(baseField.arg(nonNumericWord));

  QRegularExpression reWell(specificField.arg("WELL"));

  QRegularExpression reComp(specificField.arg("COMP"));

  QRegularExpression reServiceComp(specificField.arg("SRVC"));

  QRegularExpression reField(specificField.arg("FLD"));

  QRegularExpression reLocation(specificField.arg("LOC"));

  QRegularExpression reDate(specificField.arg("DATE"));

  QRegularExpression reCountry(specificField.arg("CTRY"));

  QRegularExpression reState(specificField.arg("STAT"));

  QRegularExpression reCounty(specificField.arg("CNTY"));

  QRegularExpression reProvince(specificField.arg("PROV"));

  QRegularExpression reAPI(specificField.arg("API"));

  QRegularExpression reUWI(specificField.arg("UWI"));

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //  name .units   name:value
  QRegularExpression reRestEntries(specificField.arg("^[^ ]+"));

  // reRestEntries.setMinimal(true);

  // next line
  ++i;

  // function for addressing results of RegularExpression matching
  auto selectValue =
    [&](QRegularExpressionMatch& m) {
      QString s1 = m.captured(3).trimmed();

      QString s2 = m.captured(4).trimmed().remove(0, 1).trimmed();

      QString result;

      if (_version == 12)
        result = s2;
      else if (_version == 20)
        result = s1;

      return result;
    };

  // function for addressing results of "floating point"
  // RegularExpression matching
  auto selectNumericalValue =
    [](QRegularExpressionMatch& m) {
      QString value = m.captured(3).trimmed();

      bool ok;

      return value.toDouble(&ok);
    };

  auto selectNumericalUnits =
    [](QRegularExpressionMatch& m) {
      QString units =
        m.captured(2).trimmed().remove(0, 1);

      return units;
    };

  // for less typing
  auto& lasRequired = lasFile->lasRequired;

  auto& logMetrics = lasFile->logMetrics;

  while (i < _lines.size())
  {
    QString const & line = _lines[i];

    // if next section has started
    if (line.startsWith("~"))
    {
      --i;
      return;
    }

    using Function = std::function<void(QRegularExpressionMatch &)>;

    using MatchingStruct = std::pair<QRegularExpression, Function>;

    std::array<MatchingStruct, 17> matchingStructs
    {

      std::make_pair(reStart, [&](QRegularExpressionMatch & m) {
        logMetrics.start = selectNumericalValue(m);
      }),

      std::make_pair(reStop, [&](QRegularExpressionMatch & m) {
        logMetrics.stop = selectNumericalValue(m);
      }),

      std::make_pair(reStep, [&](QRegularExpressionMatch & m) {
        logMetrics.step = selectNumericalValue(m);
        logMetrics.units = selectNumericalUnits(m);
      }),

      std::make_pair(reNull, [&](QRegularExpressionMatch & m) {
        logMetrics.nullValue = selectNumericalValue(m);
      }),

      std::make_pair(reWell, [&](QRegularExpressionMatch & m) {
        lasRequired.wellName = selectValue(m);
      }),

      std::make_pair(reComp, [&](QRegularExpressionMatch & m) {
        lasRequired.company = selectValue(m);
      }),

      std::make_pair(reServiceComp, [&](QRegularExpressionMatch & m) {
        lasRequired.serviceCompany = selectValue(m);
      }),

      std::make_pair(reField, [&](QRegularExpressionMatch & m) {
        lasRequired.field = selectValue(m);
      }),

      std::make_pair(reLocation, [&](QRegularExpressionMatch & m) {
        lasRequired.location = selectValue(m);
      }),

      std::make_pair(reDate, [&](QRegularExpressionMatch & m) {
        lasRequired.date = selectValue(m);
      }),

      std::make_pair(reCountry, [&](QRegularExpressionMatch & m) {
        lasRequired.country = selectValue(m);
      }),

      std::make_pair(reState, [&](QRegularExpressionMatch & m) {
        lasRequired.state = selectValue(m);
      }),

      std::make_pair(reCounty, [&](QRegularExpressionMatch & m) {
        lasRequired.county = selectValue(m);
      }),

      std::make_pair(reProvince, [&](QRegularExpressionMatch & m) {
        lasRequired.province = selectValue(m);
      }),

      std::make_pair(reAPI, [&](QRegularExpressionMatch & m) {
        lasRequired.api = selectValue(m);
      }),

      std::make_pair(reAPI, [&](QRegularExpressionMatch & m) {
        lasRequired.uwi = selectValue(m);
      }),

      std::make_pair(reRestEntries, [&](QRegularExpressionMatch & m) {
        // name .units   description:value
        LasFile::WellInformationEntry entry;

        QString name = m.captured(1).trimmed();
        entry.units = m.captured(2).trimmed().remove(0, 1);

        QString description = m.captured(3).trimmed();
        QString value = m.captured(4).trimmed().remove(0, 1).trimmed();

        if (_version == 12)
        {
          entry.description = description;
          entry.value = value;
        }
        else if (_version == 20)
        {
          entry.description = value;
          entry.value = description;
        }

        lasFile->wellInformation[name] = entry;
      })
    };

    // Iterate over all regular expressions tryint to match something for the given line
    for (auto const & e : matchingStructs)
    {
      QRegularExpressionMatch m = e.first.match(line);

      if (m.hasMatch())
      {
        e.second(m);
        break;
      }
    }

    ++i;
  }
}


void
LasFileParser::
parseLogInformationSection(std::shared_ptr<LasFile> & lasFile,
                           std::size_t & lineNumber)
{
  std::size_t & i = lineNumber;

  // clear old values
  lasFile->logInformation.clear();

  //  UWI .      UNIQUE WELL ID:326R000K116_F0W4832_
  //                     name .units   :value
  QRegularExpression reLogInfoEntries("(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

  // QRegularExpression reLogInfoEntries("(^.+)(\\.[^ ]*)(.+)( // *:)( *.*$)");

  // next line
  ++i;

  while (i < _lines.size())
  {
    QString line = _lines[i];

    if (line.startsWith("~"))
    {
      --i;
      return;
    }

    QRegularExpressionMatch m = reLogInfoEntries.match(line);

    // all the rest fields
    if (m.hasMatch())
    {
      // name .units   name:value
      LasFile::LogInformationEntry entry;

      QString all = m.captured(0);

      QString mnem =
        m.captured(1).trimmed();
      entry.units =
        m.captured(2).trimmed().remove(0, 1);

      entry.code = m.captured(3).trimmed();

      entry.description = m.captured(4).trimmed();

      lasFile->logInformation[mnem] = entry;
    }

    ++i;
  }
}


void
LasFileParser::
parseParameterInformationSection(std::shared_ptr<LasFile>& lasFile,
                                 std::size_t & lineNumber)
{
  std::size_t & i = lineNumber;

  // clear old values
  lasFile->parameterInformation.clear();

  QRegularExpression reParameterInformation("(^[^ ]+ *)(\\.[^ ]*)( *.* *:)( *.*$)");

  // next line
  ++i;

  while (i < _lines.size())
  {
    QString line = _lines[i];

    if (line.startsWith("~"))
    {
      --i;
      return;
    }

    QRegularExpressionMatch m = reParameterInformation.match(line);

    // all the rest fields
    if (m.hasMatch())
    {
      // name .units   name:value
      LasFile::ParameterInformationEntry entry;

      QString all = m.captured(0);

      entry.name  = m.captured(1).trimmed();
      entry.units = m.captured(2).trimmed().remove( 0, 1);

      entry.value = m.captured(3).trimmed();
      entry.value.chop(1);
      entry.value = entry.value.trimmed();

      entry.description = m.captured(4).trimmed();

      lasFile->parameterInformation[entry.name] = entry;
    }

    ++i;
  }
}


void
LasFileParser::
parseOtherInformationSection(std::shared_ptr<LasFile>& lasFile,
                             std::size_t & lineNumber)
{
  Q_UNUSED(lasFile);
  Q_UNUSED(lineNumber);
}


void
LasFileParser::
parseAsciiLogDataSection(std::shared_ptr<LasFile>& lasFile,
                         std::size_t & lineNumber)
{
  std::size_t & i = lineNumber;

  // clear old values
  lasFile->data.clear();

  for (auto entryKey : lasFile->logInformation.keys())
    lasFile->data[entryKey] = std::vector<double>();

  // corresponds to any number of form [-]333.566
  QRegularExpression reNumValue("(-?\\d+\\.\\d+)");

  const int numberOfMnemonics = lasFile->data.size();
  int currentMnemonicNum      = 0;

  // next line
  ++i;

  while (i < _lines.size())
  {
    QString line = _lines[i];

    if (line.startsWith("~"))
    {
      --i;
      return;
    }

    // parse array

    QRegularExpressionMatchIterator mi = reNumValue.globalMatch(line);

    while (mi.hasNext())
    {
      {
        QRegularExpressionMatch m = mi.next();
        // select next key
        QString key = lasFile->data.keys()[currentMnemonicNum];

        QString value = m.captured(1);
        bool ok;
        double valueDouble = value.toDouble(&ok);

        lasFile->data[key].push_back(valueDouble);

        currentMnemonicNum = (currentMnemonicNum + 1) % numberOfMnemonics;
      }
    }

    ++i;
  }
}

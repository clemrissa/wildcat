#include <gtest/gtest.h>

#include <LasFile.hpp>
#include <LasFileParser.hpp>

#include "Auxiliary/ExecutionControl.hpp"

#include <QApplication>
#include <QFile>

TEST(ImportLas, Las12) {
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_minimal.las");

  ASSERT_TRUE(QFile::exists(fileName));

  // parsing
  Geo::Import::LasFile lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile.wellInformation.wellName ==
              QString("ANY ET AL A9-16-49-20"));

  // check some key numbers
  ASSERT_FLOAT_EQ(635.0, lasFile.wellInformation.start);
  ASSERT_FLOAT_EQ(400.0, lasFile.wellInformation.stop);
  ASSERT_FLOAT_EQ(-0.1250, lasFile.wellInformation.step);
  ASSERT_FLOAT_EQ(-999.25, lasFile.wellInformation.nullValue);

  // check total number of additional entries
  ASSERT_EQ(7, lasFile.wellInformation.entries.size());

  // check mnemonics and their values
  ASSERT_TRUE(lasFile.wellInformation.entries["FLD"].value == "EDAM");
  ASSERT_TRUE(lasFile.wellInformation.entries["LOC"].value ==
              "A9-16-49-20W3M");
  ASSERT_TRUE(lasFile.wellInformation.entries["PROV"].value == "SASKATCHEWAN");

  // check curve information
  ASSERT_EQ(8, lasFile.curveInformation.size());

  ASSERT_TRUE(lasFile.curveInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile.curveInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile.data["SFLA"].size() == lasFile.data["ILD"].size());
}

//// -----------------------------

TEST(ImportLas, Las20) {
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_2.0_minimal.las");

  ASSERT_TRUE(QFile::exists(fileName));

  // parsing
  Geo::Import::LasFile lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile.wellInformation.wellName ==
              QString("ANY ET AL 12-34-12-34"));

  ASSERT_FLOAT_EQ(635.0, lasFile.wellInformation.start);
  ASSERT_FLOAT_EQ(400.0, lasFile.wellInformation.stop);

  // check total number of additional entries
  ASSERT_EQ(7, lasFile.wellInformation.entries.size());

  ASSERT_TRUE(lasFile.wellInformation.entries["FLD"].value == "WILDCAT");
  ASSERT_TRUE(lasFile.wellInformation.entries["LOC"].value ==
              "12-34-12-34W5M");
  ASSERT_TRUE(lasFile.wellInformation.entries["PROV"].value == "ALBERTA");

  // check curve information
  ASSERT_EQ(8, lasFile.curveInformation.size());

  ASSERT_TRUE(lasFile.curveInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile.curveInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile.data["SFLA"].size() == lasFile.data["ILD"].size());
}

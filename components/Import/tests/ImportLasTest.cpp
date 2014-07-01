#include <gtest/gtest.h>

#include <Las/LasFile.hpp>
#include <Las/LasFileParser.hpp>

#include <Uni/Logging/Logging>

#include <QApplication>
#include <QFile>
#include <QSharedPointer>

TEST(ImportLas, Las12) {
  Geo::Import::LasFileParser parser;

  // construct las file name
  QString fileName = QString("%1/../tests/%2").
                     arg(QCoreApplication::applicationDirPath()).
                     arg("sample_minimal.las");

  ASSERT_TRUE(QFile::exists(fileName));

  // parsing
  QSharedPointer<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile->lasRequired.wellName ==
              QString("ANY ET AL A9-16-49-20"));

  // check some key numbers
  ASSERT_FLOAT_EQ(635.0, lasFile->lasRequired.start);
  ASSERT_FLOAT_EQ(400.0, lasFile->lasRequired.stop);
  ASSERT_FLOAT_EQ(-0.1250, lasFile->lasRequired.step);
  ASSERT_FLOAT_EQ(-999.25, lasFile->lasRequired.nullValue);

  // check total number of additional entries
  ASSERT_EQ(7, lasFile->wellInformation.size());

  // check mnemonics and their values
  ASSERT_TRUE(lasFile->wellInformation["FLD"].value == "EDAM");
  ASSERT_TRUE(lasFile->wellInformation["LOC"].value ==
              "A9-16-49-20W3M");
  ASSERT_TRUE(lasFile->wellInformation["PROV"].value ==
              "SASKATCHEWAN");

  // check curve information
  ASSERT_EQ(8, lasFile->logInformation.size());

  ASSERT_TRUE(lasFile->logInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile->logInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
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
  QSharedPointer<Geo::Import::LasFile> lasFile = parser.parse(fileName);

  // check well information
  ASSERT_TRUE(lasFile->lasRequired.wellName ==
              QString("ANY ET AL 12-34-12-34"));

  ASSERT_FLOAT_EQ(635.0, lasFile->lasRequired.start);
  ASSERT_FLOAT_EQ(400.0, lasFile->lasRequired.stop);

  // check total number of additional entries
  ASSERT_EQ(7, lasFile->wellInformation.size());

  ASSERT_TRUE(lasFile->wellInformation["FLD"].value == "WILDCAT");
  ASSERT_TRUE(lasFile->wellInformation["LOC"].value ==
              "12-34-12-34W5M");
  ASSERT_TRUE(lasFile->wellInformation["PROV"].value == "ALBERTA");

  // check curve information
  ASSERT_EQ(8, lasFile->logInformation.size());

  ASSERT_TRUE(lasFile->logInformation["RHOB"].units == "K/M3");
  ASSERT_TRUE(lasFile->logInformation["SFLA"].description ==
              "SHALLOW RESISTIVITY");

  ASSERT_TRUE(lasFile->data["SFLA"].size() == lasFile->data["ILD"].size());
}
